#ifndef VMT_H
#define VMT_H
#ifdef _WIN32
#pragma once
#endif

namespace detail {

	class protect_guard 
	{
	public:

		protect_guard(void* base, size_t len, std::uint32_t flags) 
		{
			_base = base;
			_length = len;
			if (!VirtualProtect(base, len, flags, (PDWORD)& _old))
				throw std::runtime_error("failed to protect region");
		}

		~protect_guard() 
		{
			VirtualProtect(_base, _length, _old, (PDWORD)& _old);
		}

	private:
		PVOID			_base;
		size_t			_length;
		std::uint32_t	_old;
	};

}

inline const bool table_is_hooked(void* table, const char* module_table_dst)
{

	if (table == nullptr)
		return false;

	const auto module_base = GetModuleHandleA(module_table_dst);

	const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER> (module_base);
	const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS> (reinterpret_cast<std::uint8_t*>(module_base) + dos_header->e_lfanew);

	const auto module_end = reinterpret_cast<std::uintptr_t>(module_base) + nt_headers->OptionalHeader.SizeOfImage - sizeof(std::uintptr_t);

	const auto table_dst = *reinterpret_cast<std::uintptr_t*>(table);

	return (table_dst < reinterpret_cast<std::uintptr_t>(module_base) || table_dst > module_end);

}

class vmt_hook 
{
private:

	std::size_t estimate_vftbl_length(std::uintptr_t* vftbl_start) 
	{

		MEMORY_BASIC_INFORMATION memInfo = { NULL };
		int size = -1;
		do {
			size++;
			VirtualQuery(reinterpret_cast<LPCVOID>(vftbl_start[size]), &memInfo, sizeof(memInfo));
		} while (memInfo.Protect == PAGE_EXECUTE_READ || memInfo.Protect == PAGE_EXECUTE_READWRITE);

		return size;

	}

	PVOID			class_base;
	std::size_t     vftbl_len;
	std::uintptr_t* new_vftb1;
	std::uintptr_t* old_vftbl;
	LPCVOID         search_base		= nullptr;
	bool			was_allocated	= false;

public:

	vmt_hook()
		: class_base(nullptr), vftbl_len(0), new_vftb1(nullptr), old_vftbl(nullptr) {
	}

	vmt_hook(void* base)
		: class_base(base), vftbl_len(0), new_vftb1(nullptr), old_vftbl(nullptr) {
	}

	~vmt_hook() 
	{
		release();
		if (was_allocated)
			delete[] new_vftb1;
	}

	uintptr_t* search_free_data_page(const char* module_name, const std::size_t vmt_size)
	{

		auto check_data_section = [&](LPCVOID address, const std::size_t vmt_size) 
		{

			const DWORD data_protection = (PAGE_EXECUTE_READWRITE | PAGE_READWRITE);
			MEMORY_BASIC_INFORMATION mbi = { 0 };

			if (VirtualQuery(address, &mbi, sizeof(mbi)) == sizeof(mbi) && mbi.AllocationBase && mbi.BaseAddress &&
				mbi.State == MEM_COMMIT && !(mbi.Protect & PAGE_GUARD) && mbi.Protect != PAGE_NOACCESS) {
				if ((mbi.Protect & data_protection) && mbi.RegionSize >= vmt_size) {
					return ((mbi.Protect & data_protection) && mbi.RegionSize >= vmt_size) ? true : false;
				}
			}
			return false;

		};

		auto module_addr = GetModuleHandleA(module_name);

		if (module_addr == nullptr)
			return nullptr;

		const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER> (module_addr);
		const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS> (reinterpret_cast<std::uint8_t*>(module_addr) + dos_header->e_lfanew);

		const auto module_end = reinterpret_cast<std::uintptr_t>(module_addr) + nt_headers->OptionalHeader.SizeOfImage - sizeof(std::uintptr_t);

		for (auto current_address = module_end; current_address > (DWORD)module_addr; current_address -= sizeof(std::uintptr_t)) 
		{

			if (*reinterpret_cast<std::uintptr_t*>(current_address) == 0 && check_data_section(reinterpret_cast<LPCVOID>(current_address), vmt_size)) {
				bool is_good_vmt = true;
				auto page_count = 0u;

				for (; page_count < vmt_size && is_good_vmt; page_count += sizeof(std::uintptr_t)) {
					if (*reinterpret_cast<std::uintptr_t*>(current_address + page_count) != 0)
						is_good_vmt = false;
				}

				if (is_good_vmt && page_count >= vmt_size)
					return (uintptr_t*)current_address;
			}

		}

		return nullptr;

	}

	bool setup(void* base, const char* module_name = nullptr) 
	{

		if (base != nullptr)
			class_base = base;

		if (class_base == nullptr)
			return false;

		old_vftbl = *(std::uintptr_t**)class_base;
		vftbl_len = estimate_vftbl_length(old_vftbl) * sizeof(std::uintptr_t);

		if (vftbl_len == 0)
			return false;

		if (module_name) {
			new_vftb1 = search_free_data_page(module_name, vftbl_len + sizeof(std::uintptr_t));
			std::memset(new_vftb1, NULL, vftbl_len + sizeof(std::uintptr_t));
			std::memcpy(&new_vftb1[1], old_vftbl, vftbl_len);
			new_vftb1[0] = old_vftbl[-1];
			try {
				auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };

				*(std::uintptr_t**)class_base = &new_vftb1[1];
				was_allocated = false;
				if (table_is_hooked(base, module_name)) {
					Beep(500, 500);
				}
			}
			catch (...) {
				delete[] new_vftb1;
				return false;
			}
		}
		else {
			new_vftb1 = new std::uintptr_t[vftbl_len + 1]();
			std::memcpy(&new_vftb1[1], old_vftbl, vftbl_len);
			try {
				auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };
				new_vftb1[0] = old_vftbl[-1];
				*(std::uintptr_t**)class_base = &new_vftb1[1];
				was_allocated = true;
			}
			catch (...) {
				delete[] new_vftb1;
				return false;
			}
		}

		return true;

	}

	void hook_index(size_t fn_index, void* fn_pointer) 
	{
		assert(fn_index >= 0 && fn_index <= (int)vftbl_len);
		new_vftb1[fn_index + 1] = reinterpret_cast<std::uintptr_t>(fn_pointer);
	}

	void release() 
	{

		try {
			if (old_vftbl != nullptr) {
				auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };
				*(std::uintptr_t**)class_base = old_vftbl;
				old_vftbl = nullptr;
			}
		}
		catch (...) {
		}

	}

	void* get_original_function(size_t fn_index) 
	{
		return reinterpret_cast<void*>(old_vftbl[fn_index]);
	}

};

#endif // !VMT_H
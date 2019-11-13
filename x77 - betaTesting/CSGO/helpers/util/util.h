#ifndef UTIL_H
#define UTIL_H
#ifdef _WIN32
#pragma once
#endif

#define in_range(x, a, b) (x >= a && x <= b) 
#define get_bits(x) (in_range((x & (~0x20)),'A','F') ? ((x & (~0x20)) - 'A' + 0xa) : (in_range(x,'0','9') ? x - '0' : 0))
#define get_byte(x) (get_bits(x[0]) << 4 | get_bits(x[1]))

#define rad(x) x * 0.01745329251

typedef float matrix3x4_t[3][4];

namespace u
{

	void fix_movement(vector ang);
	void fix_movement(vector old_angles, float old_forward, float old_side_move);
	float get_fov(const vector& ang, const vector& start, const vector& end);

	template<typename fn>
	inline fn call_vfunc(const PVOID virt, int index)
	{
		return (fn)*(*(const PVOID**)virt + index);
	}

	template <typename t = address>
	__forceinline static t get_method(address this_ptr, size_t index) {
		return (t)this_ptr.to< t* >()[index];
	}

	inline float normalize(const float& f)
	{
		return std::remainderf(f, 360.f);
	}

	template<typename t>
	inline t minimum(const t& a, const t& b)
	{
		return a < b ? a : b;
	}

	template<typename t>
	inline t maximum(const t& a, const t& b)
	{
		return a > b ? a : b;
	}

	template <typename t>
	inline t clamp(const t& val, const t& lower, const t& upper)
	{
		return maximum(lower, minimum(val, upper));
	}

	inline void sin_cos(float radian, float* sin, float* cos)
	{
		*sin = std::sin(radian);
		*cos = std::cos(radian);
	}

	inline float degree_to_radian(float fl)
	{
		return (fl * (M_PI / 180.0f));
	}

	inline void vector_transform(const vector in1, const matrix3x4_t in2, vector& out) {
		out[0] = dot_product(in1, vector(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3];
		out[1] = dot_product(in1, vector(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3];
		out[2] = dot_product(in1, vector(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3];
	}

	inline float radius_to_degree(float fl) {
		return (fl * (180.0f / M_PI));
	}

	inline void make_vector(const vector & in, vector & out) {

		float pitch = degree_to_radian(in.x);
		float yaw = degree_to_radian(in.y);
		float temp = cos(pitch);

		out.x = -temp * -cos(yaw);
		out.y = sin(yaw) * temp;
		out.z = -sin(pitch);

	}

	inline float get_distance(vector origin, vector local_origin)
	{

		vector delta = origin - local_origin;

		float distance = delta.length();

		if (distance < 1.0f)
			return 1.0f;

		return distance;

	}

	inline uint64_t find_signature(const char* module, const char* signature)
	{

		MODULEINFO module_info;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(module), &module_info, sizeof(MODULEINFO));

		DWORD		start_address = (DWORD)module_info.lpBaseOfDll;
		DWORD		end_address = start_address + module_info.SizeOfImage;
		const char* pat = signature;
		DWORD		first_match = 0;

		for (DWORD cur = start_address; cur < end_address; cur++) {

			if (!*pat)
				return first_match;

			if (*(PBYTE)pat == '\?' || *(BYTE*)cur == get_byte(pat)) {

				if (!first_match)
					first_match = cur;

				if (!pat[2])
					return first_match;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else pat += 2;
			}
			else {
				pat = signature;
				first_match = 0;
			}

		}

		return NULL;

	}

	static DWORD find_pattern(const char* module_name, const BYTE* mask, const char* mask_string)
	{
		const unsigned int module_address = reinterpret_cast<unsigned int>(GetModuleHandle(module_name));

		MODULEINFO module_info;
		GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(module_address), &module_info, sizeof(MODULEINFO));

		auto is_correct_mask = [](const unsigned char* data, const unsigned char* mask, const char* mask_string) -> bool {
			for (; *mask_string; ++mask_string, ++mask, ++data)
				if (*mask_string == 'x' && *mask != *data)
					return false;

			return (*mask_string) == 0;
		};

		for (unsigned int c = 0; c < module_info.SizeOfImage; c += 1) {
			if (is_correct_mask(reinterpret_cast<unsigned char*>(module_address + c), mask, mask_string))
				return (module_address + c);
		}

		return 0;
	}

	template<class T>
	static T* find_hud_element(const char* name)
	{
		static auto sig = *reinterpret_cast<DWORD**>(find_signature("client_panorama.dll", "B9 ? ? ? ? E8 ? ? ? ? 8B 5D 08") + 1);

		static auto find_hud_element = reinterpret_cast<DWORD(__thiscall*)(PVOID, const char*)>(find_signature("client_panorama.dll", "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28"));
		return (T*)find_hud_element(sig, name);
	}

	inline auto clamp_angles(vector& angle)
	{

		if (angle.x > 89.0f && angle.x <= 180.0f)
			angle.x = 89.0f;

		if (angle.x > 180.0f)
			angle.x = angle.x - 360.0f;

		if (angle.x < -89.0f)
			angle.x = -89.0f;

		angle.y = fmodf(angle.y + 180, 360) - 180;

		angle.z = 0;

	}

	inline auto angle_normalize(vector& v)
	{
		for (auto i = 0; i < 3; i++) {
			if (v[i] < -180.0f) v[i] += 360.0f;
			if (v[i] > 180.0f) v[i] -= 360.0f;
		}
	}

	inline void angle_vectors(const vector& angles, vector* forward)
	{
		assert(s_bMathlibInitialized);
		assert(forward);

		float	sp, sy, cp, cy;

		sy = sin(DEG2RAD(angles[1]));
		cy = cos(DEG2RAD(angles[1]));

		sp = sin(DEG2RAD(angles[0]));
		cp = cos(DEG2RAD(angles[0]));

		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	inline void angle_vectors(const vector& angles, vector* forward, vector* right, vector* up)
	{

		float sp, sy, sr, cp, cy, cr;

		sin_cos(degree_to_radian(angles.x), &sp, &cp);
		sin_cos(degree_to_radian(angles.y), &sy, &cy);
		sin_cos(degree_to_radian(angles.z), &sr, &cr);

		if (forward != nullptr) {
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if (right != nullptr) {
			right->x = -1 * sr * sp * cy + -1 * cr * -sy;
			right->y = -1 * sr * sp * sy + -1 * cr * cy;
			right->z = -1 * sr * cp;
		}

		if (up != nullptr) {
			up->x = cr * sp * cy + -sr * -sy;
			up->y = cr * sp * sy + -sr * cy;
			up->z = cr * cp;
		}

	}

	inline float random_float(float min, float max)
	{
		static auto random_float = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat"));

		return random_float(min, max);
	}

	static float normalize_yaw(float yaw)
	{
		if (yaw > 180) {
			yaw -= (round(yaw / 360) * 360.f);
		} else if (yaw < -180) {
			yaw += (round(yaw / 360) * -360.f);
		}
		return yaw;
	}

	inline vector forward(vector vec)
	{
		float cp, cy, sp, sy;

		sin_cos(rad(vec.x), &sp, &cp);
		sin_cos(rad(vec.y), &sy, &cy);

		return vector(cp * cy, cp * sy, -sp);
	}

	static float normalize_pitch(float pitch)
	{
		while (pitch > 89.f)
			pitch -= 180.f;
		while (pitch < -89.f)
			pitch += 180.f;

		return pitch;
	}

	static vector normalize_angle(vector angle)
	{
		angle.x = normalize_pitch(angle.x);
		angle.y = normalize_yaw(angle.y);

		if ((angle.z > 50) || (angle.z < 50))
			angle.z = 0;

		return angle;
	}

	inline float yaw_distance(float first, float second)
	{
		if (first == second)
			return 0.f;

		bool opposite = false;

		if (first > 0 && second < 0)
			opposite = true;
		else if (first < 0 && second > 0)
			opposite = true;

		if (!opposite)
			return fabs(first - second);

		bool past90 = false;

		if (first > 90 && second < -90) {
			first	-= (first - 90);
			second	+= (second + 90);
		} else if (first < -90 && second > 90) {
			first	+= (first + 90);
			second	-= (second - 90);
		}

		float dist;

		dist = fabs(first - second);

		return dist;
	}

	inline vector get_rotated_position(vector start, const float rotation, const float distance)
	{
		const auto rad = degree_to_radian(rotation);
		start.x += cosf(rad) * distance;
		start.y += sinf(rad) * distance;

		return start;
	};

	inline vector calc_angle(const vector& vecSource, const vector& vecDestination)
	{
		vector	ang, 
				delta	= vector((vecSource[0] - vecDestination[0]), (vecSource[1] - vecDestination[1]), (vecSource[2] - vecDestination[2]));
		float	hyp		= sqrtf(delta[0] * delta[0] + delta[1] * delta[1]);

		ang[0] = (float)(atan(delta[2] / hyp) * (180.0f / M_PI));
		ang[1] = (float)(atan(delta[1] / delta[0]) * (180.0f / M_PI));
		ang[2] = 0.f;

		if (delta[0] >= 0.f)
			ang[1] += 180.f;

		return ang;
	}

	inline std::string remove_excessive_ws(std::string s)
	{
		auto is_doubled_space =
			[seen_space = false](unsigned char c) mutable {
			return std::exchange(seen_space, std::isspace(c))
				&& seen_space;
		};
		s.erase(std::remove_if(s.begin(), s.end(), is_doubled_space), s.end());
		// remove trailing whitespace
		if (!s.empty() && std::isspace(static_cast<unsigned char>(s.back()))) {
			s.pop_back();
		}
		// convert all whitespace into ordinary space character
		std::replace_if(s.begin(), s.end(),
			[](unsigned char c) { return std::isspace(c); }, ' ');
		return s;
	}

}

#endif // !UTIL_H
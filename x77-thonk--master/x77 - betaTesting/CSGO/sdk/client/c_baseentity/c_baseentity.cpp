#include "../../../main.h"

vector c_baseentity::get_bone_position(int bone)
{
	matrix3x4_t matrix[128];

	setup_bones(matrix, 128, 0x100, i::globals->curtime);

	return vector(matrix[bone][0][3], matrix[bone][1][3], matrix[bone][2][3]);
}

base_weapon* c_baseentity::get_active_weapon() {

	auto wep_handle	= *reinterpret_cast<uintptr_t*>(this + 0x2EF8);
	auto weapon		= reinterpret_cast<base_weapon*>(i::entitylist->get_client_entity_from_handle(wep_handle));

	return weapon;

}

int c_baseentity::get_sequence_activity(int sequence)
{
	auto hdr = i::modelinfo->get_studio_model(this->get_model());

	if (!hdr)
		return -1;

	static auto get_sequence_activity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>(u::find_signature("client_panorama.dll", "55 8B EC 53 8B 5D 08 56 8B F1 83"));

	return get_sequence_activity(this, hdr, sequence);
}

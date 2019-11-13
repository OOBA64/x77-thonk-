#ifndef SETUP_H
#define SETUP_H
#ifdef _WIN32
#pragma once
#endif

namespace s
{
	extern void __fastcall hk_create_move_proxy(PVOID _this, int, int sequence_number, float input_sample_frametime, bool active);
	extern void setup_interfaces();
	extern void setup_hooks();
	extern bool ready_to_blast();
	extern void detach();
}

#endif // !SETUP_H
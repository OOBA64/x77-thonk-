#ifndef HVH_H
#define HVH_H
#ifdef _WIN32
#pragma once
#endif

namespace hvh
{
	extern void fake_lag(bool& send_packet);
	extern void fake_walk(bool& send_packet);
	extern void fake_duck(bool& send_packet);
	extern bool should_break_lby();
	extern void anti_aim(bool& send_packet);
}

#endif // !HVH_H
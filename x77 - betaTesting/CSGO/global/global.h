#ifndef GLOBAL_H
#define GLOBAL_H
#ifdef _WIN32
#pragma once
#endif

namespace g
{

	extern c_baseentity*		local;
	extern c_baseentity*		target;
	extern user_cmd*			cmd;
	extern verified_user_cmd*	verified;

	extern vector				last_real_tick;
	extern vector				last_fake_tick;

	extern bool					third_person_bind;
	extern bool					left_key_pressed;
	extern bool					down_key_pressed;
	extern bool					right_key_pressed;

	extern bool					send_packet;

	extern bool					lowest_accuracy;

	extern int					shots_fired;
	extern int					shots_hit;
	extern int					shots_missed;

	extern int					width;
	extern int					height;

}

#endif // !GLOBAL_H

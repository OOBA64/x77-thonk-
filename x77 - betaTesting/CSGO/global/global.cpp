#include "../main.h"

namespace g
{

	// pointers
	c_baseentity*		local{};
	c_baseentity*		target{};
	user_cmd*			cmd{};
	verified_user_cmd*	verified{};

	// createmove
	vector last_real_tick;
	vector last_fake_tick;

	// binds
	bool third_person_bind	= false;
	bool left_key_pressed	= false;
	bool right_key_pressed	= true;
	bool down_key_pressed	= false;

	bool send_packet;

	bool lowest_accuracy = false;

	int	shots_fired		= 0;
	int	shots_hit		= 0;
	int shots_missed	= 0;

	int width;
	int height;

}

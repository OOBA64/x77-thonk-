#include "../../main.h"

namespace hvh
{

	void fake_lag(bool& send_packet)
	{

		auto net_channel = i::engineclient->get_net_channel();

		if (i::engineclient->is_voice_recordering() || !net_channel) return;

		if (vars::hvh::hvh_fake_lag > 0) {

			if (g::local->get_life_state() == LIFE_ALIVE) {
				if (net_channel->choked_packets < vars::hvh::hvh_fake_lag) {
					send_packet = false;
				} else {
					send_packet = true;
				}
			}

		}

	}

	void fake_walk(bool& send_packet)
	{

		static int choked = 0;
		choked = choked > 7 ? 0 : choked + 1;

		if (i::engineclient->is_voice_recordering()) return;

		if (vars::hvh::hvh_fake_walk && i::inputsystem->is_button_down(KEY_LSHIFT)) {

			g::cmd->forwardmove = choked < 2 || choked > 5 ? 0 : g::cmd->forwardmove;
			g::cmd->sidemove	= choked < 2 || choked > 5 ? 0 : g::cmd->sidemove;

			send_packet = choked < 1;

		}

	}

	void fake_duck(bool& send_packet)
	{
		auto net_channel = i::engineclient->get_net_channel();

		if (!net_channel) return;

		g::cmd->buttons |= IN_BULLRUSH;

		if (vars::hvh::hvh_fake_duck && i::inputsystem->is_button_down(KEY_C))
			(net_channel->choked_packets >= (vars::hvh::hvh_fake_lag / 2)) ? g::cmd->buttons |= IN_DUCK : g::cmd->buttons &= ~IN_DUCK;
	}

	float get_direction()
	{

		// manual direction
		if (g::left_key_pressed)
			return 90.f;
		else if (g::right_key_pressed)
			return -90.f;

	}

	float get_pitch()
	{

		switch (vars::hvh::hvh_pitch) {
		case 0:
			return g::cmd->viewangles.x;
			break;
		case 1:
			return 89.f;
			break;
		case 2:
			return -89.f;
			break;
		case 3:
			return 0.f;
			break;
		case 4:
			return u::random_float(-89.f, 89.f);
			break;
		}

	}

	float get_current_time(user_cmd* cmd) 
	{

		static user_cmd*	last_cmd	= nullptr;
		static int			tick		= 0;

		if (!last_cmd || last_cmd->hasbeenpredicted) {
			tick = g::local->get_tick_base();
		} else {
			++tick;
		}

		last_cmd = cmd;

		return tick * i::globals->interval_per_tick;

	}

	bool should_break_lby() 
	{
		static float	next_lby_update	= 0;
		float			server_time		= get_current_time(g::cmd);
		float			velocity		= g::local->get_velocity().length2d();
		float			delta			= (g::last_real_tick.y - g::local->get_lower_body_yaw());

		if (g::local->get_flags() & FL_ONGROUND) {

			if (velocity > 0.1f) {
				next_lby_update = server_time + 0.22f;
			}

			if (server_time >= next_lby_update) {
				next_lby_update = server_time + 1.1f;
				return true;
			}

		}

		return false;
	}

	void anti_aim(bool& send_packet)
	{

		vector	ang		= g::cmd->viewangles;
		float	delta	= g::local->get_max_desync_delta();
		float	speed	= g::local->get_velocity().length2d() <= 0.1 ? (delta + 30.f) : delta;
		auto	wep		= g::local->get_active_weapon();

		auto feet_yaw_delta = g::cmd->viewangles.y - u::normalize_yaw(g::local->get_anim_state()->goal_feet_yaw);
		
		if (!wep || wep->get_cs_wpn_info()->weapon_type == WEAPONTYPE_GRENADE) return;

		if (g::local->get_move_type() == MOVETYPE_LADDER || 
			g::local->get_move_type() == MOVETYPE_NOCLIP) return;

		if (vars::hvh::hvh_anti_aim && !(g::cmd->buttons & IN_ATTACK)) {

			if (send_packet && !i::clientstate->choked_commands) {

				ang.y += g::right_key_pressed ? get_direction() - speed : get_direction() + speed;

				if (feet_yaw_delta < delta)
					g::right_key_pressed ? ang.y += u::random_float(-vars::hvh::hvh_jitter_range, vars::hvh::hvh_jitter_range) : ang.y -= u::random_float(-vars::hvh::hvh_jitter_range, vars::hvh::hvh_jitter_range);

			} else if (!send_packet && !i::clientstate->choked_commands) {
				ang.y += get_direction();
			}

			if (should_break_lby()) {
				send_packet = false;
				ang.y += 180.f;
			}

			if (vars::hvh::hvh_yaw_add > 0.f)
				g::right_key_pressed ? get_direction() - vars::hvh::hvh_yaw_add : get_direction() - vars::hvh::hvh_yaw_add;

			ang.x = get_pitch();

		}

		u::fix_movement(ang);

		g::cmd->viewangles = ang;

	}

}
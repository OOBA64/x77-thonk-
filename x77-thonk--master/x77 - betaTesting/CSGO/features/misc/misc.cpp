#include "../../main.h"

namespace m
{

	void set_clan_tag(const char* tag)
	{
		static auto set_clan_tag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(u::find_signature("engine.dll", "53 56 57 8B DA 8B F9 FF 15"));
		set_clan_tag(tag, tag);
	}

/*	void time_tag()
	{ //valve code 
		time_t t;
		struct tm* t_m;
		t = time(NULL);
		t_m = localtime(&t);
		if (vars::ctags::time_clan_tag) {
			std::string time = (t_m->tm_hour) + ":" + (t_m->tm_min) + (t_m->tm_sec);
			set_clan_tag(time.c_str());
		}
		if (!vars::ctags::time_clan_tag) {
			std::string time = " ";
		}
	}*/

	void clan_tag() // I tried doing some valve code for this but it didnt work :(
	{
		static bool	reverse;
		static int	index;

		//tag reset
		if (vars::ctags::clan_tag_changer == 0) {
			std::string tag = " "; //After adding multiple tags tag.clear doesnt work
				set_clan_tag(tag.substr(0, index).c_str());
		}
		else if (vars::ctags::clan_tag_changer == 1) {
			std::string tag = " x77 Alpha  ";
			if (g::cmd->command_number % 20 == 0) {

				index += reverse ? -1 : 1;

				if (index > tag.length() - 1 || index < 1)
					reverse = !reverse;

				index = u::clamp(index, 0, static_cast<int>(tag.length()));
				if (vars::ctags::clan_tag_changer == 0) {
					tag.clear();
				}

				set_clan_tag(tag.substr(0, index).c_str());
			}
		}
		else if (vars::ctags::clan_tag_changer == 2) {
			std::string tag = " gamesense    "; //Scaring away de predators 
			if (g::cmd->command_number % 24 == 0) {

				index += reverse ? -1 : 1;

				if (index > tag.length() - 1 || index < 1)
					reverse = !reverse;

				index = u::clamp(index, 0, static_cast<int>(tag.length()));
				if (vars::ctags::clan_tag_changer == 0) {
					tag.clear();
				}

				set_clan_tag(tag.substr(0, index).c_str());
			}
		}
		else if (vars::ctags::clan_tag_changer == 3) {
			std::string tag = " w33b stomp3r  ";
			if (g::cmd->command_number % 16 == 0) {

				index += reverse ? -1 : 1;

				if (index > tag.length() - 1 || index < 1)
					reverse = !reverse;

				index = u::clamp(index, 0, static_cast<int>(tag.length()));
				if (vars::ctags::clan_tag_changer == 0) {
					tag.clear();
				}

				set_clan_tag(tag.substr(0, index).c_str());
			}
		}
		else if (vars::ctags::clan_tag_changer == 4) {
			std::string tag = "..-.._.--..";
			if (g::cmd->command_number % 18 == 0) {

				index += reverse ? -1 : 1;

				if (index > tag.length() - 1 || index < 1)
					reverse = !reverse;

				index = u::clamp(index, 0, static_cast<int>(tag.length()));
				if (vars::ctags::clan_tag_changer == 0) {
					tag.clear();
				}

				set_clan_tag(tag.substr(0, index).c_str());
			}
		}
		else if (vars::ctags::clan_tag_changer == 5) {
			std::string tag = "AyyWare  ";
			if (g::cmd->command_number % 22 == 0) {

				index += reverse ? -1 : 1;

				if (index > tag.length() - 1 || index < 1)
					reverse = !reverse;

				index = u::clamp(index, 0, static_cast<int>(tag.length()));
				if (vars::ctags::clan_tag_changer == 0) {
					tag.clear();
				}

				set_clan_tag(tag.substr(0, index).c_str());

			}
		}
		else if (vars::ctags::clan_tag_changer == 6) {
			std::string tag = "Dracula Premium  ";
			if (g::cmd->command_number % 18 == 0) {

				index += reverse ? -1 : 1;

				if (index > tag.length() - 1 || index < 1)
					reverse = !reverse;

				index = u::clamp(index, 0, static_cast<int>(tag.length()));
				if (vars::ctags::clan_tag_changer == 0) {
					tag.clear();
				}

				set_clan_tag(tag.substr(0, index).c_str());

			}
		}

		else if (vars::ctags::clan_tag_changer == 10) {
		std::string tag = "oneclap.su ";
		if (g::cmd->command_number % 18 == 0) {

			index += reverse ? -1 : 1;

			if (index > tag.length() - 1 || index < 1)
				reverse = !reverse;

			index = u::clamp(index, 0, static_cast<int>(tag.length()));
			if (vars::ctags::clan_tag_changer == 0) {
				tag.clear();
			}

			set_clan_tag(tag.substr(0, index).c_str());

		}
		}
		//---------------------------static---------------------------//
	
		else if (vars::ctags::clan_tag_changer == 7) {
			std::string tag = "x77 Cheats ";
			index = u::clamp(index, 0, static_cast<int>(tag.length()));

			if (vars::ctags::clan_tag_changer == 0) {
				tag.clear();
			}
			set_clan_tag(tag.substr(0, index).c_str());
		}
		else if (vars::ctags::clan_tag_changer == 8) {
			std::string tag = "hopped ";
			if (vars::ctags::clan_tag_changer == 0) {
				tag.clear();
			}
			set_clan_tag(tag.substr(0, index).c_str());
		}
		//THey patched the valve ctag :'(
		else if (vars::ctags::clan_tag_changer == 9) {
			std::string tag = "[VALVE] ";
			if (vars::ctags::clan_tag_changer == 0) {
				tag.clear();
			}
			set_clan_tag(tag.substr(0, index).c_str());
		}

	}

	void auto_movement()
	{

		static bool jump_released;

		if (g::local->get_move_type() == MOVETYPE_LADDER || 
			g::local->get_move_type() == MOVETYPE_FLY || 
			g::local->get_move_type() == MOVETYPE_OBSERVER ||
			g::local->get_move_type() == MOVETYPE_NOCLIP) return;

		if (g::cmd->buttons & IN_JUMP) {

			if (!jump_released) {

				if (!(g::local->get_flags() & FL_ONGROUND)) {

					if (vars::misc::misc_auto_hop)
						g::cmd->buttons &= ~IN_JUMP;

					if (vars::misc::misc_auto_strafe) {

						if (g::cmd->mousedx > 1 || g::cmd->mousedx < -1) {
							g::cmd->sidemove = g::cmd->mousedx < 0.f ? -450.f : 450.f;
						} else {
							g::cmd->forwardmove = 5850.f / g::local->get_velocity().length2d();
							g::cmd->sidemove = (g::cmd->command_number % 2) == 0 ? -450.f : 450.f;
						}

					}

				}

			}
			
			if (jump_released)
				jump_released = false;

		} else if (jump_released == false) {
			jump_released = true;
		}

	}

	void crosshair()
	{

		static convar* crosshair				= i::cvar->find_var("crosshair");
		static convar* weapon_debug_spread_show = i::cvar->find_var("weapon_debug_spread_show");
		weapon_debug_spread_show->flags &= ~FCVAR_CHEAT;

		if (g::local->get_life_state() != LIFE_ALIVE)
			weapon_debug_spread_show->set_value(0);

		if (vars::vis::vis_force_crosshair) {
		
			if (!g::local->is_scoped()) {
				weapon_debug_spread_show->set_value(3);
			} else if (vars::vis::vis_no_scope && g::local->is_scoped()) {
				weapon_debug_spread_show->set_value(3);
			} else {
				weapon_debug_spread_show->set_value(0);
			}

		} else {
			weapon_debug_spread_show->set_value(0);
		}

	}

	void viewmodel()
	{

		static convar* viewmodel_offset_x = i::cvar->find_var("viewmodel_offset_x");
		static convar* viewmodel_offset_y = i::cvar->find_var("viewmodel_offset_y");
		static convar* viewmodel_offset_z = i::cvar->find_var("viewmodel_offset_z");

		if (vars::vis::offset_x > 0 || vars::vis::offset_x < 0) {
			*(float*)((DWORD)&viewmodel_offset_x->change_callback + 0xC) = NULL;
			viewmodel_offset_x->set_value(vars::vis::offset_x);
		}

		if (vars::vis::offset_y > 0 || vars::vis::offset_y < 0) {
			*(float*)((DWORD)&viewmodel_offset_y->change_callback + 0xC) = NULL;
			viewmodel_offset_y->set_value(vars::vis::offset_y);
		}

		if (vars::vis::offset_z > 0 || vars::vis::offset_z < 0) {
			*(float*)((DWORD)&viewmodel_offset_z->change_callback + 0xC) = NULL;
			viewmodel_offset_z->set_value(vars::vis::offset_z);
		}


	}

}


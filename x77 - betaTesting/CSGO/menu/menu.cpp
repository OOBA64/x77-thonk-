#include "../main.h"

struct menu_item_t
{

	std::string name;

	union {
		float*	m_float;
		int*	m_int;
		bool*	m_bool;
	};

	float	float_step;
	int		int_step;
	int		type;

	union {
		float	float_min;
		int		int_min;
	};

	union {
		float	float_max;
		int		int_max;
	};

}; menu_item_t items[120];

const char* esp_options[] = {
	"Off", "Always", "Dead"
};

const char* hitbox_options[] = {
	"Auto", "Head", "Body"
};

const char* health_options[] = {
	"Off", "Text", "Bar", "Both"
};

const char* armor_options[] = {
	"Off", "Text", "Bar", "Both"
};

const char* box_options[] = {
	"Off", "Bounding", "Edge", "3D"
};

const char* aa_pitch[] = {
	"Off", "Down", "Up", "Zero", "Random"
};

const char* tp_options[] = {
	"Off", "Real", "Fake"
};

namespace menu
{

	int add_menu_entry(int i, std::string name, bool* value)
	{
		items[i].name	= name;
		items[i].m_bool = value;
		items[i].type	= 0;

		return (i + 1);
	}

	int add_menu_entry(int i, std::string name, int* value, int min, int max, int step)
	{
		items[i].name		= name;
		items[i].m_int		= value;
		items[i].int_min	= min;
		items[i].int_max	= max;
		items[i].int_step	= step;
		items[i].type		= 1;

		return (i + 1);
	}

	int add_menu_entry(int i, std::string name, float* value, float min, float max, float step)
	{
		items[i].name		= name;
		items[i].m_float	= value;
		items[i].float_min	= min;
		items[i].float_max	= max;
		items[i].float_step	= step;
		items[i].type		= 2;

		return (i + 1);
	}

	int add_menu_entry_int_string(int i, std::string name, int* value, int min, int max, int step)
	{
		items[i].name		= name;
		items[i].m_int		= value;
		items[i].int_min	= min;
		items[i].int_max	= max;
		items[i].int_step	= step;
		items[i].type		= 3;

		return (i + 1);
	}

	void insert_menu_items()
	{

		int i = 0;

		if (!vars::aim::aim_tab)
			i = add_menu_entry(i, "[+] Aimbot:", &vars::aim::aim_tab);
		if (vars::aim::aim_tab) {

			i = add_menu_entry(i, "[-] Aimbot:", &vars::aim::aim_tab);

			i = add_menu_entry(i, "- Enabled", &vars::aim::aim_enabled);
			i = add_menu_entry_int_string(i, "- Hitbox", &vars::aim::aim_hitbox, 0, 2, 1);
			i = add_menu_entry(i, "- FOV", &vars::aim::aim_fov, 0.f, 180.f, 1.f);
			i = add_menu_entry(i, "- Smooth", &vars::aim::aim_smooth, 0.f, 35.f, 1.f);
			i = add_menu_entry(i, "- Hitchance Amount", &vars::aim::aim_hitchance_amt, 1.f, 100.f, 5);
			i = add_menu_entry(i, "- On Attack", &vars::aim::aim_on_attack);
			i = add_menu_entry(i, "- Silent", &vars::aim::aim_silent);
			i = add_menu_entry(i, "- Autoshoot", &vars::aim::aim_auto_shoot);
			i = add_menu_entry(i, "- Autostop", &vars::aim::aim_auto_stop);
			i = add_menu_entry(i, "- Autoscope", &vars::aim::aim_auto_scope);
			i = add_menu_entry(i, "- Autorevolver", &vars::aim::aim_auto_revolver);
			i = add_menu_entry(i, "- Target Teammates", &vars::aim::aim_target_teammates);
			i = add_menu_entry(i, "- Ignore Jumping", &vars::aim::aim_ignore_jumping);

		}

		if (!vars::esp::esp_tab)
			i = add_menu_entry(i, "[+] ESP:", &vars::esp::esp_tab);
		if (vars::esp::esp_tab) {

			i = add_menu_entry(i, "[-] ESP:", &vars::esp::esp_tab);

			i = add_menu_entry_int_string(i, "- Mode", &vars::esp::esp_enabled, 0, 2, 1);
			i = add_menu_entry(i, "- Name", &vars::esp::esp_name);
			i = add_menu_entry(i, "- Enemy Only", &vars::esp::esp_enemy_only);
			i = add_menu_entry_int_string(i, "- Box", &vars::esp::esp_box, 0, 3, 1);
			
			if (vars::esp::esp_box > 0 && vars::esp::esp_box != 3)
				i = add_menu_entry(i, "- Fill", &vars::esp::esp_fill, 0.f, 60.f, 5);

			i = add_menu_entry(i, "- Glow", &vars::esp::esp_glow);

			if (vars::esp::esp_glow)
				i = add_menu_entry(i, "- Glow Style", &vars::esp::esp_glow_style, 0, 2, 1);

			i = add_menu_entry_int_string(i, "- Health", &vars::esp::esp_health, 0, 3, 1);
			i = add_menu_entry(i, "- Projectiles", &vars::esp::esp_projectiles);
			i = add_menu_entry(i, "- Steam", &vars::esp::esp_steam_id);
			i = add_menu_entry(i, "- Flags", &vars::esp::esp_flags);
			i = add_menu_entry_int_string(i, "- Armor", &vars::esp::esp_armor, 0, 3, 1);
			i = add_menu_entry(i, "- Weapon", &vars::esp::esp_weapon);
			i = add_menu_entry(i, "- Money", &vars::esp::esp_money);
			i = add_menu_entry(i, "- Index", &vars::esp::esp_index);
			i = add_menu_entry(i, "- Distance", &vars::esp::esp_distance);
			i = add_menu_entry(i, "- Local Player", &vars::esp::esp_local_player);
		}

		if (!vars::vis::vis_tab)
			i = add_menu_entry(i, "[+] Visuals:", &vars::vis::vis_tab);
		if (vars::vis::vis_tab) {

			i = add_menu_entry(i, "[-] Visuals:", &vars::vis::vis_tab);

			i = add_menu_entry(i, "- No Scope", &vars::vis::vis_no_scope);
			i = add_menu_entry(i, "- Draw FOV Circle", &vars::vis::vis_fov_circle);
			i = add_menu_entry_int_string(i, "- Thirdperson (H)", &vars::vis::vis_third_person, 0, 2, 1);
			i = add_menu_entry(i, "- No Vis Recoil", &vars::vis::vis_no_vis_recoil);
			i = add_menu_entry(i, "- Recoil Crosshair", &vars::vis::vis_recoil_crosshair);// not working as of now, peek code in visuals//
			i = add_menu_entry(i, "- Force Crosshair", &vars::vis::vis_force_crosshair);
			i = add_menu_entry(i, "- Nightmode", &vars::vis::vis_night_mode);
			i = add_menu_entry(i, "- Field Of View", &vars::vis::vis_fov, 0.f, 80.f, 5.f);
			i = add_menu_entry(i, "- LBY Indicator", &vars::vis::vis_lby_indicator);
			i = add_menu_entry(i, "- AA Lines", &vars::vis::vis_anti_aim_lines);
			i = add_menu_entry(i, "- Watermark", &vars::vis::vis_watermark);

			if (!vars::vis::vis_viewmodel_tab)
				i = add_menu_entry(i, "[+] Viewmodel:", &vars::vis::vis_viewmodel_tab);
			if (vars::vis::vis_viewmodel_tab) {

				i = add_menu_entry(i, "[-] Viewmodel:", &vars::vis::vis_viewmodel_tab);

				i = add_menu_entry(i, "- viewmodel_fov", &vars::vis::vis_viewmodel_fov, -180.f, 180.f, 5.f);
				i = add_menu_entry(i, "- viewmodel_offset_x", &vars::vis::offset_x, -7.5, 7.5, .5);
				i = add_menu_entry(i, "- viewmodel_offset_y", &vars::vis::offset_y, -7.5, 7.5, .5);
				i = add_menu_entry(i, "- viewmodel_offset_z", &vars::vis::offset_z, -7.5, 7.5, .5);

			}

			if (!vars::vis::vis_color_tab)
				i = add_menu_entry(i, "[+] Color:", &vars::vis::vis_color_tab);
			if (vars::vis::vis_color_tab) {

				i = add_menu_entry(i, "[-] Color:", &vars::vis::vis_color_tab);

				if (!vars::vis::vis_ct_tab)
					i = add_menu_entry(i, "[+] Counter-Terrorist Color:", &vars::vis::vis_ct_tab);
				if (vars::vis::vis_ct_tab) {

					i = add_menu_entry(i, "[-] Counter-Terrorist Color:", &vars::vis::vis_ct_tab);

					i = add_menu_entry(i, "- R", &vars::vis::ct_r, 0, 255, 5);
					i = add_menu_entry(i, "- G", &vars::vis::ct_g, 0, 255, 5);
					i = add_menu_entry(i, "- B", &vars::vis::ct_b, 0, 255, 5);

				}

				if (!vars::vis::vis_t_tab)
					i = add_menu_entry(i, "[+] Terrorist Color:", &vars::vis::vis_t_tab);
				if (vars::vis::vis_t_tab) {

					i = add_menu_entry(i, "[-] Terrorist Color:", &vars::vis::vis_t_tab);

					i = add_menu_entry(i, "- R", &vars::vis::t_r, 0, 255, 5);
					i = add_menu_entry(i, "- G", &vars::vis::t_g, 0, 255, 5);
					i = add_menu_entry(i, "- B", &vars::vis::t_b, 0, 255, 5);

				}

				if (!vars::vis::vis_local_tab)
					i = add_menu_entry(i, "[+] Local Color:", &vars::vis::vis_local_tab);
				if (vars::vis::vis_local_tab) {

					i = add_menu_entry(i, "[-] Local Color:", &vars::vis::vis_local_tab);

					i = add_menu_entry(i, "- R", &vars::vis::local_r, 0, 255, 5);
					i = add_menu_entry(i, "- G", &vars::vis::local_g, 0, 255, 5);
					i = add_menu_entry(i, "- B", &vars::vis::local_b, 0, 255, 5);

				}

				if (!vars::vis::vis_ambient_tab)
					i = add_menu_entry(i, "[+] World Color:", &vars::vis::vis_ambient_tab);
				if (vars::vis::vis_ambient_tab) {

					i = add_menu_entry(i, "[-] World Color:", &vars::vis::vis_ambient_tab);

					i = add_menu_entry(i, "- R", &vars::vis::ambient_r, 0.f, 255.f, 5.f);
					i = add_menu_entry(i, "- G", &vars::vis::ambient_g, 0.f, 255.f, 5.f);
					i = add_menu_entry(i, "- B", &vars::vis::ambient_b, 0.f, 255.f, 5.f);

				}

			}

		}

		if (!vars::hvh::hvh_tab)
			i = add_menu_entry(i, "[+] HvH:", &vars::hvh::hvh_tab);
		if (vars::hvh::hvh_tab) {

			i = add_menu_entry(i, "[-] HvH:", &vars::hvh::hvh_tab);

			i = add_menu_entry(i, "- Resolver", &vars::hvh::hvh_resolver);
			i = add_menu_entry(i, "- Fake Lag", &vars::hvh::hvh_fake_lag, 1, 14, 1);
			i = add_menu_entry(i, "- Slow Walk (LSHIFT)", &vars::hvh::hvh_fake_walk);
			i = add_menu_entry(i, "- Fake Duck (C)", &vars::hvh::hvh_fake_duck);
			i = add_menu_entry(i, "- Anti Aim", &vars::hvh::hvh_anti_aim);

			if (vars::hvh::hvh_anti_aim) {
				i = add_menu_entry(i, "- Jitter Range", &vars::hvh::hvh_jitter_range, 0.f, 180.f, 5.f);
				i = add_menu_entry_int_string(i, "- Pitch", &vars::hvh::hvh_pitch, 0, 4, 1);
			}

		}

		if (!vars::misc::misc_tab)
			i = add_menu_entry(i, "[+] Misc:", &vars::misc::misc_tab);
		if (vars::misc::misc_tab) {

			i = add_menu_entry(i, "[-] Misc:", &vars::misc::misc_tab);

			i = add_menu_entry(i, "- Auto Hop", &vars::misc::misc_auto_hop);
			i = add_menu_entry(i, "- Auto Strafe", &vars::misc::misc_auto_strafe);
			i = add_menu_entry(i, "- Anti Untrusted", &vars::misc::misc_anti_untrusted);

			if (!vars::ctags::ctag_tab)
				i = add_menu_entry(i, "[+] CTags:", &vars::ctags::ctag_tab);
			if (vars::ctags::ctag_tab) {

				i = add_menu_entry(i, "[-] Ctags:", &vars::ctags::ctag_tab);

				i = add_menu_entry(i, "- x77 assware", &vars::ctags::clan_tag_changer_2);
				i = add_menu_entry(i, "- gamesense", &vars::ctags::clan_tag_changer); // to scare people cuz this cheat is ass 
			}
		}

		vars::menu::total_items = i;

	}

	void draw_menu(unsigned long font)
	{
	
		// title
		d::draw_string(vars::menu::menu_x + 365, vars::menu::menu_y - 235, color(66, 149, 245), font, " x77 Alpha");

		std::stringstream	string;
		player_info_t		info;
		static int			fps, old_tick_count;
	
		// arrow
		d::draw_string(vars::menu::menu_x + 344, vars::menu::menu_y - 226 + (vars::menu::font_size * vars::menu::current_pos) + 5, color(120, 120, 120), font, ">");

		// times
		for (int i = 0; i < vars::menu::total_items; ++i) {

			if (!strncmp(items[i].name.c_str(), "[+]", 3) || !strncmp(items[i].name.c_str(), "[-]", 3)) { // 260, 370 new |||||| 60, 170 old      + and -
				d::draw_string(vars::menu::menu_x + 360, vars::menu::menu_y - 213 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, items[i].name.c_str());
			} else {

				switch (items[i].type) {
				case 0:
					d::draw_string(vars::menu::menu_x + 360, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, items[i].name.c_str());
					d::draw_string(vars::menu::menu_x + 470, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, "%s", (*items[i].m_bool) ? "On" : "Off");
					break;
				case 1:
					d::draw_string(vars::menu::menu_x + 360, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, items[i].name.c_str());
					d::draw_string(vars::menu::menu_x + 470, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, "%i", *items[i].m_int);
					break;
				case 2:
					d::draw_string(vars::menu::menu_x + 360, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, items[i].name.c_str());
					d::draw_string(vars::menu::menu_x + 470, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, "%.2f", *items[i].m_float);
					break;
				case 3:
					d::draw_string(vars::menu::menu_x + 360, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, items[i].name.c_str());
					break;
				default:
					break;
				}

				if (!strcmp(items[i].name.c_str(), "- Mode")) {
					d::draw_string(vars::menu::menu_x + 470, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, "%s", esp_options[(int)items[i].m_int[0]]);
				}

				if (!strcmp(items[i].name.c_str(), "- Hitbox")) {
					d::draw_string(vars::menu::menu_x + 470, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, "%s", hitbox_options[(int)items[i].m_int[0]]);
				}

				if (!strcmp(items[i].name.c_str(), "- Box")) {
					d::draw_string(vars::menu::menu_x + 470, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, "%s", box_options[(int)items[i].m_int[0]]);
				}

				if (!strcmp(items[i].name.c_str(), "- Health")) {
					d::draw_string(vars::menu::menu_x + 470, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, "%s", health_options[(int)items[i].m_int[0]]);
				}

				if (!strcmp(items[i].name.c_str(), "- Armor")) {
					d::draw_string(vars::menu::menu_x + 470, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, "%s", armor_options[(int)items[i].m_int[0]]);
				}

				if (!strcmp(items[i].name.c_str(), "- Thirdperson (H)")) {
					d::draw_string(vars::menu::menu_x + 470, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, "%s", tp_options[(int)items[i].m_int[0]]);
				}

				if (!strcmp(items[i].name.c_str(), "- Pitch")) {
					d::draw_string(vars::menu::menu_x + 470, vars::menu::menu_y - 210 + (vars::menu::font_size * i) - 8, color(255, 255, 255, 255), font, "%s", aa_pitch[(int)items[i].m_int[0]]);
				}

			}

		}

	}

	int handle_input(int key_num)
	{

		if (key_num == 72) {
			vars::menu::menu_active = !vars::menu::menu_active;
		}

		if (vars::menu::menu_active) {

			if (key_num == 88) {

				if (vars::menu::current_pos > 0) {
					vars::menu::current_pos--;
				} else {
					vars::menu::current_pos = vars::menu::total_items - 1;
				}

				return 0;

			} else if (key_num == 90) {

				if (vars::menu::current_pos < vars::menu::total_items - 1) {
					vars::menu::current_pos++;
				} else {
					vars::menu::current_pos = 0;
				}

			} else if (key_num == 89) {

				switch (items[vars::menu::current_pos].type) {
				case 0:
					*items[vars::menu::current_pos].m_bool = !*items[vars::menu::current_pos].m_bool;
					break;
				case 1:
					*items[vars::menu::current_pos].m_int -= items[vars::menu::current_pos].int_step;
					if (*items[vars::menu::current_pos].m_int < items[vars::menu::current_pos].int_min)
						*items[vars::menu::current_pos].m_int = items[vars::menu::current_pos].int_max;
					break;
				case 2:
					*items[vars::menu::current_pos].m_float -= items[vars::menu::current_pos].float_step;
					if (*items[vars::menu::current_pos].m_float < items[vars::menu::current_pos].float_min)
						*items[vars::menu::current_pos].m_float = items[vars::menu::current_pos].float_max;
					break;
				case 3:
					*items[vars::menu::current_pos].m_int -= items[vars::menu::current_pos].int_step;
					if (*items[vars::menu::current_pos].m_int < items[vars::menu::current_pos].int_min)
						*items[vars::menu::current_pos].m_int = items[vars::menu::current_pos].int_max;
					break;
				default:
					break;
				}

			} else if (key_num == 91) {

				switch (items[vars::menu::current_pos].type) {
				case 0:
					*items[vars::menu::current_pos].m_bool = !*items[vars::menu::current_pos].m_bool;
					break;
				case 1:

					*items[vars::menu::current_pos].m_int += items[vars::menu::current_pos].int_step;

					if (*items[vars::menu::current_pos].m_int > items[vars::menu::current_pos].int_max) {
						*items[vars::menu::current_pos].m_int = items[vars::menu::current_pos].int_min;
					}

					break;

				case 2:

					*items[vars::menu::current_pos].m_float += items[vars::menu::current_pos].float_step;

					if (*items[vars::menu::current_pos].m_float > items[vars::menu::current_pos].float_max) {
						*items[vars::menu::current_pos].m_float = items[vars::menu::current_pos].float_min;
					}

					break;

				case 3:

					*items[vars::menu::current_pos].m_int += items[vars::menu::current_pos].int_step;

					if (*items[vars::menu::current_pos].m_int > items[vars::menu::current_pos].int_max) {
						*items[vars::menu::current_pos].m_int = items[vars::menu::current_pos].int_min;
					}

					break;

				default:
					break;
				}

			}

		}

		return 0;

	}



}

#include "../../main.h"
#include "../../helpers/vector.h"
#include <sstream>


namespace v
{

	bool w2s(const vector& from, vector& screen)
	{
		return (i::debugoverlay->screen_position(from, screen) != 1);
	}

	void vector_transform(const vector& some, const matrix3x4_t& matrix, vector& out)
	{
		for (auto i = 0; i < 3; i++)
			out[i] = some.dot((vector&)matrix[i]) + matrix[i][3];
	}

	color get_entity_color(c_baseentity* entity) 
	{

		if (entity != nullptr) {

			if (entity->get_index() == g::local->get_index())
				return color(vars::vis::local_r, vars::vis::local_g, vars::vis::local_b);

			switch (entity->get_team_num()) {
			default:
				return color(255, 255, 255);
				break;
			case 2:
				return color(vars::vis::t_r, vars::vis::t_g, vars::vis::t_b);
				break;
			case 3:
				return color(vars::vis::ct_r, vars::vis::ct_g, vars::vis::ct_b);
				break;
			}

		}

	}

	void draw_3d_box(const vector& mins, const vector& maxs, color col)
	{

		vector diff = maxs - mins;
		vector points_to_draw[24] = {

			// bottom horizontal lines
			mins, mins + vector(diff.x, 0, 0),								// 1 - 2
			mins + vector(diff.x, 0, 0), mins + vector(diff.x, diff.y, 0),	// 2 - 3
			mins + vector(diff.x, diff.y, 0), mins + vector(0, diff.y, 0),	// 3 - 4
			mins + vector(0, diff.y, 0), mins,								// 4 - 1

			// vertical lines
			mins, mins + vector(0, 0, diff.z), // 1 - 6
			mins + vector(diff.x, 0, 0), mins + vector(diff.x, 0, diff.z),				// 2 - 7
			mins + vector(diff.x, diff.y, 0), mins + vector(diff.x, diff.y, diff.z),	// 3 - 8
			mins + vector(0, diff.y, 0), mins + vector(0, diff.y, diff.z),				// 4 - 5

			// top horizontal lines
			maxs, maxs - vector(diff.x, 0, 0),								// 8 - 5
			maxs - vector(diff.x, 0, 0), maxs - vector(diff.x, diff.y, 0),	// 5 - 6
			maxs - vector(diff.x, diff.y, 0), maxs - vector(0, diff.y, 0),	// 6 - 7
			maxs - vector(0, diff.y, 0), maxs								// 7 - 8
		};

		vector start_pos, end_pos;
		for (int i = 0; i < 24; i += 2) {
			if (w2s(points_to_draw[i], start_pos)) {
				if (w2s(points_to_draw[i + 1], end_pos))
					d::draw_line(start_pos.x, start_pos.y, end_pos.x, end_pos.y, col);
			}
		}

	}

	void draw_dynamic_box(c_baseentity* entity, player_info_t info, color col)
	{

		matrix3x4_t& trans = *(matrix3x4_t*)(entity + 0x444);

		vector min = entity->get_collideable_mins();
		vector max = entity->get_collideable_maxs();

		vector pos = entity->get_abs_origin();

		vector points[] = {
			vector(min.x, min.y, min.z),
			vector(min.x, max.y, min.z),
			vector(max.x, max.y, min.z),
			vector(max.x, min.y, min.z),
			vector(max.x, max.y, max.z),
			vector(min.x, max.y, max.z),
			vector(min.x, min.y, max.z),
			vector(max.x, min.y, max.z)
		};

		vector points_transformed[8];
		for (int i = 0; i < 8; i++) {
			vector_transform(points[i], trans, points_transformed[i]);
		}

		vector flb;
		vector brt;
		vector blb;
		vector frt;
		vector frb;
		vector brb;
		vector blt;
		vector flt;

		if (!w2s(points_transformed[3], flb) || !w2s(points_transformed[5], brt)
			|| !w2s(points_transformed[0], blb) || !w2s(points_transformed[4], frt)
			|| !w2s(points_transformed[2], frb) || !w2s(points_transformed[1], brb)
			|| !w2s(points_transformed[6], blt) || !w2s(points_transformed[7], flt))
			return;

		vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

		float left		= flb.x;
		float top		= flb.y;
		float right		= flb.x;
		float bottom	= flb.y;

		for (int i = 1; i < 8; i++) {
			if (left > arr[i].x)
				left = arr[i].x;
			if (top < arr[i].y)
				top = arr[i].y;
			if (right < arr[i].x)
				right = arr[i].x;
			if (bottom > arr[i].y)
				bottom = arr[i].y;
		}

		float x = left;
		float y = bottom;
		float w = right - left;
		float h = top - bottom;

		x += ((right - left) / 8);
		w -= ((right - left) / 8) * 2;

		if (vars::esp::esp_enabled > 0)
			players(x, y, w, h, info, entity, col, f::arial, min, max, pos);

	}


	void entity_loop()
	{
		player_info_t info;

		for (auto i = 1; i <= i::entitylist->get_highest_entity_index(); i++) {

			// acquire a pointer to an entity on the server
			auto entity = reinterpret_cast<c_baseentity*>(i::entitylist->get_client_entity(i));

			// make sure the entity exists
			if (entity == nullptr) continue;

			// make sure our local player exists
			if (g::local == nullptr) continue;

			// make sure the entity isn't dormant
			if (entity->is_dormant()) continue;

			// dead check
			if (vars::esp::esp_enabled == 2 && g::local->get_life_state() != LIFE_DEAD) continue;

			draw_dynamic_box(entity, info, get_entity_color(entity));

			projectiles(entity, color::white(), f::arial_blur);

		}

	}

	void projectiles(c_baseentity* entity, color col, unsigned long font)
	{

		if (vars::esp::esp_enabled <= 0 || !vars::esp::esp_projectiles) return;

		auto client_client	= entity->get_client_class();
		auto model			= entity->get_model();

		if (!model) return;

		if (model) {

			bool	should_draw = true;
			vector	world, screen;

			auto model = i::modelinfo->get_studio_model(entity->get_model());

			if (!model || !strstr(model->name, "thrown") && !strstr(model->name, "dropped"))
				return;

			std::string name = model->name, str;

			world = entity->get_abs_origin();

			if (!w2s(world, screen)) return;

			if (name.find("flashbang") != std::string::npos)
				str = "Flash";
			else if (name.find("smokegrenade") != std::string::npos)
				str = "Smoke";
			else if (name.find("incendiarygrenade") != std::string::npos)
				str = "Incendiary";
			else if (name.find("molotov") != std::string::npos)
				str = "Molotov";
			else if (name.find("fraggrenade") != std::string::npos)
				str = "Grenade";
			else if (name.find("decoy") != std::string::npos)
				str = "Decoy";
			else
				should_draw = false;
			
			if (should_draw)
				d::draw_string_box(font, str.c_str(), screen.x, screen.y, color::black(175), col);

		}

	}

	void players(float x, float y, float w, float h, player_info_t info, c_baseentity* entity, color col, unsigned long font, vector min, vector max, vector pos)
	{

		if (!i::engineclient->get_player_info(entity->get_index(), &info)) return;

		if (vars::esp::esp_enemy_only && (entity->get_team_num() == g::local->get_team_num())) {
			if (entity->get_index() != g::local->get_index()) return;
		}

		if (entity->get_health() <= 0 || entity->get_life_state() != LIFE_ALIVE) return;

		if (vars::esp::esp_local_player) {
			if (vars::vis::vis_third_person < 1) {
				if (entity->get_index() == g::local->get_index()) return;
			}
		} else if (!vars::esp::esp_local_player && (entity->get_index() == g::local->get_index())) {
			return;
		}

		int health		= entity->get_health();
		int armor		= entity->get_armor();
		int max_health	= entity->get_max_health();

		if (health > max_health)
			health = max_health;

		if (armor > 100)
			armor = 100;

		int health_bar		= w / max_health * health;
		int armor_bar		= h / 100 * armor;
		int armor_bar_delta = h - armor_bar;

		RECT text_size = i::surface->get_text_size_rect(font, info.name);

		uint8_t g = (255 * health / max_health);
		uint8_t r = 255 - g;

		int side_add	= 0;
		int top_add		= 0;

		// fill
		if ((vars::esp::esp_box > 0 && vars::esp::esp_fill > 0) && vars::esp::esp_box != 3)
			d::draw_filled_rect(x, y, w, h, color(col.r(), col.g(), col.b(), vars::esp::esp_fill));

		switch (vars::esp::esp_box) {
		case 1:
			d::draw_outlined_rect(x + 2, y + 2, w - 4, h - 4, color(0, 0, 0));
			d::draw_outlined_rect(x + 2, y + 2, w - 4, h - 4, color(col.r(), col.g(), col.b(), 60));
			d::draw_outlined_rect(x + 1, y + 1, w - 2, h - 2, col);
			d::draw_outlined_rect(x, y, w, h, color(0, 0, 0));
			d::draw_outlined_rect(x, y, w, h, color(col.r(), col.g(), col.b(), 60));
			break;
		case 2:
			d::draw_corner_box(x, y, w, h, col);
			break;
		case 3:
			draw_3d_box(pos + min, pos + max, col);
			break;
		}

		if (entity->get_active_weapon() != nullptr) {

			auto weapon			= entity->get_active_weapon();
			auto weapon_name	= weapon->get_name();

			weapon_name.erase(0, 7);

			if (strcmp(weapon_name.c_str(), "deagle") == 0) {
				if (weapon->item_definition_index() == WEAPON_REVOLVER)
					weapon_name = "revolver";
				else
					weapon_name = "deagle";
			}

			if (strcmp(weapon_name.c_str(), "hkp2000") == 0) {
				if (weapon->item_definition_index() == WEAPON_USP_SILENCER)
					weapon_name = "usp-s";
				else
					weapon_name = "hkp2000";
			}

			if (vars::esp::esp_weapon)
				d::draw_string_box(font, weapon_name.c_str(), x, y + (h + 4), color::black(175), col);

		}

		if (vars::esp::esp_health == 2 ||
			vars::esp::esp_health == 3) {

			d::draw_filled_rect(x, (y - 6) - top_add, w, 4, color(0, 0, 0, 210));
			d::draw_filled_rect(x, (y - 6) - top_add, health_bar, 4, color(r, g, 0, 255));
			d::draw_outlined_rect(x, (y - 6) - top_add, w, 4, color(0, 0, 0, 255));
			d::draw_outlined_rect(x, (y - 6) - top_add, w, 4, color(r, g, 0, 30));

			top_add += 5;

		}

		if (vars::esp::esp_name) {
			d::draw_string_box(font, info.name, x, (y - 17) - top_add, color::black(175), col);
			top_add += 6;
		}

		if (strcmp(info.sz_steam_id, "STEAM_1:0:4242891") == 0) {
			d::draw_string(x + w + 4, (y - 2) + side_add, color(150, 30, 65), font, "Developer");
			side_add += 13;
		}

		if (vars::esp::esp_index) {
			d::draw_string(x + w + 4, (y - 2) + side_add, color(255, 255, 0), font, "I: %d", entity->get_index());
			side_add += 13;
		}

		if (vars::esp::esp_steam_id) {
			d::draw_string(x + w + 4, (y - 2) + side_add, col, font, "%s", info.sz_steam_id);
			side_add += 13;
		}

		if (vars::esp::esp_health == 1 ||
			vars::esp::esp_health == 3) {
			d::draw_string(x + w + 4, (y - 2) + side_add, color(r, g, 0), font, "%d HP", entity->get_health());
			side_add += 13;
		}

		if (vars::esp::esp_money) {
			d::draw_string(x + w + 4, (y - 2) + side_add, color(60, 179, 113), font, "$%d", entity->get_money());
			side_add += 13;
		}

		if (vars::esp::esp_flags) {

			if (entity->is_scoped()) {
				d::draw_string(x + w + 4, (y - 2) + side_add, col, font, "ZOOM");
				side_add += 13;
			} if (entity->get_flags() & FL_DUCKING) {
				d::draw_string(x + w + 4, (y - 2) + side_add, col, font, "DUCK");
				side_add += 13;
			} if (resolver::is_fake_ducking(entity) && entity->get_index() != g::local->get_index()) {
				d::draw_string(x + w + 4, (y - 2) + side_add, col, font, "FAKE DUCK");
				side_add += 13;
			}

		}

		if (vars::esp::esp_armor == 1 || 
			vars::esp::esp_armor == 3) {
			d::draw_string(x + w + 4, (y - 2) + side_add, col, font, entity->get_armor_name());
			side_add += 13;
		}

		if (vars::esp::esp_distance) {
			d::draw_string(x + w + 4, (y - 2) + side_add, col, font, "%.0f hu", u::get_distance(entity->get_origin(), g::local->get_origin()));
			side_add += 13;
		}

		if (vars::esp::esp_armor == 2 || 
			vars::esp::esp_armor == 3) {
			if (entity->get_armor() > 0) {
				d::draw_filled_rect(x - 7, y, 4, h, color(0, 0, 0, 210));
				d::draw_filled_rect(x - 7, y + armor_bar_delta, 4, armor_bar, color(0, 75, 255));
				d::draw_outlined_rect(x - 7, y, 4, h, color(0, 0, 0));
				d::draw_outlined_rect(x - 7, y, 4, h, color(0, 75, 255, 65));
			}
		}

	}

	void fov_circle()
	{

		if (!vars::aim::aim_enabled || g::local == nullptr) return;

		float x1 = tan(u::degree_to_radian(vars::aim::aim_fov)) / tan(DEG2RAD(106.3f) / 2) * (g::width / 2);

		if (g::local->get_life_state() == LIFE_ALIVE && (vars::aim::aim_fov > 0 && vars::vis::vis_fov_circle)) {
			d::draw_circle(g::width / 2, g::height / 2, x1, 255, color().rainbow(.01f, 255));
		}

	}

	void third_person(client_frame_stage_t stage)
	{

		float range = 150.f;

		vector angles;
		i::engineclient->get_view_angles(angles);

		if (stage) {

			if (vars::vis::vis_third_person > 0 && g::third_person_bind) {

				// make sure we're not in third person already
				if (i::input->camera_in_third_person) return;

				// change camera offsets roll to our range
				angles.z = range;

				i::input->camera_in_third_person	= true;
				i::input->camera_offset				= angles;

			} else {
				i::input->camera_in_third_person	= false;
				i::input->camera_offset.z			= 0.f;
			}

		}

	}

	void third_person_angles(client_frame_stage_t stage)
	{
		if (stage) {
			if (g::local != nullptr && g::local->get_life_state() == LIFE_ALIVE) {
				if (vars::vis::vis_third_person == 1 || vars::vis::vis_third_person == 2) {
					if (g::third_person_bind && g::cmd != nullptr) {
						if (vars::vis::vis_third_person == 1) {
							*reinterpret_cast<vector*>(reinterpret_cast<uintptr_t>(g::local) + 0x31D8) = g::last_real_tick;
						} else if (vars::vis::vis_third_person == 2) {
							*reinterpret_cast<vector*>(reinterpret_cast<uintptr_t>(g::local) + 0x31D8) = g::last_fake_tick;
						}
					}
				}
			}
		}
	}

	void aa_indicator()
	{

		if (!vars::hvh::hvh_anti_aim) return;

		if (g::local == nullptr) return;

		if (g::local->get_life_state() == LIFE_ALIVE) {
			// left arrow
			d::draw_string_centered(vars::menu::menu_x - 200, vars::menu::menu_y + 750, g::left_key_pressed ? color(255, 255, 255, 0) : color(255, 0, 0, 255), f::aa_indicator, "<-----left");

			// right arrow
			d::draw_string_centered(vars::menu::menu_x - 200, vars::menu::menu_y + 750, g::right_key_pressed ? color(255, 255, 255, 0) : color(255, 0, 0, 255), f::aa_indicator, "right----->");

			// down arrow
			//d::draw_string_centered((w / 2), (h / 2) + 50, g::down_key_pressed ? color().rainbow(.04f, 130) : color(255, 255, 255, 130), f::arial_large, u8"▼");
		}

	}

	void night_mode()
	{

		auto mat_force_tonemap_scale	= i::cvar->find_var("mat_force_tonemap_scale");
		auto mat_ambient_light_r		= i::cvar->find_var("mat_ambient_light_r");
		auto mat_ambient_light_g		= i::cvar->find_var("mat_ambient_light_g");
		auto mat_ambient_light_b		= i::cvar->find_var("mat_ambient_light_b");

		if (vars::vis::vis_night_mode) {
			if (mat_force_tonemap_scale->get_float() != 0.1f)
				mat_force_tonemap_scale->set_value(0.1f);
		}
		else if (!vars::vis::vis_night_mode && mat_force_tonemap_scale->get_float() != 1.f)
			mat_force_tonemap_scale->set_value(1.f);

		mat_ambient_light_r->set_value(vars::vis::ambient_r > 0.f ? vars::vis::ambient_r / 255.f : 0.f);
		mat_ambient_light_g->set_value(vars::vis::ambient_g > 0.f ? vars::vis::ambient_g / 255.f : 0.f);
		mat_ambient_light_b->set_value(vars::vis::ambient_b > 0.f ? vars::vis::ambient_b / 255.f : 0.f);

	}

	void occlusion(client_frame_stage_t stage)
	{
		if (stage) {
			for (auto i = 1; i <= i::globals->max_clients; i++) {

				auto entity = reinterpret_cast<c_baseentity*>(i::entitylist->get_client_entity(i));

				if (!entity || entity->get_index() == g::local->get_index()) continue;

				*(int*)((uintptr_t)entity + 0xA30) = i::globals->framecount;
				*(int*)((uintptr_t)entity + 0xA28) = 0;

			}
		}
	}

	void watermark()
	{

		std::stringstream	string;
		player_info_t		info;
		static int			fps, old_tick_count;

		auto net_channel = i::engineclient->get_net_channel_info();

		if (!g::local || !net_channel || !i::globals || !i::engineclient->get_player_info(i::engineclient->get_local_player(), &info)) return;

		if ((i::globals->tickcount - old_tick_count) > 50) {
			fps				= static_cast<int>(1.f / i::globals->frametime);
			old_tick_count	= i::globals->tickcount;
		}

		std::string outgoing = g::local ? std::to_string((int)(net_channel->get_latency(FLOW_OUTGOING) * 1000)) : "0";

		auto t	= std::time(nullptr);
		auto tm = *std::localtime(&t);

		string << "x77 N-Bomb" << " | " << (std::string)info.name << " | Fag Time " << std::put_time(&tm, "%H:%M:%S");

		RECT text_size = i::surface->get_text_size_rect(f::arial, string.str().c_str());

		d::draw_filled_rect(g::width - (text_size.right + 15), 25, text_size.right + 10, 2, color(66, 149, 245, 125));
		d::draw_filled_rect(g::width - (text_size.right + 15), 5, text_size.right + 10, 20, color(40, 40, 40, 0));
		d::draw_string(g::width - (text_size.right + 10), 8, color(200, 200, 200), f::arial, string.str().c_str());

	}
	
	void user()
	{

		std::stringstream	string;
		player_info_t		info;
		static int			fps, old_tick_count;

		auto net_channel = i::engineclient->get_net_channel_info();

		if (!g::local || !net_channel || !i::globals || !i::engineclient->get_player_info(i::engineclient->get_local_player(), &info)) return;

		if ((i::globals->tickcount - old_tick_count) > 50) {
			fps = static_cast<int>(1.f / i::globals->frametime);
			old_tick_count = i::globals->tickcount;
		}

		std::string outgoing = g::local ? std::to_string((int)(net_channel->get_latency(FLOW_OUTGOING) * 1000)) : "0";

		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		string << "Hello" << " " << (std::string)info.name << " " << ":)";

		RECT text_size = i::surface->get_text_size_rect(f::arial_small, string.str().c_str());

		d::draw_string(vars::menu::menu_x + 43, vars::menu::menu_y - 235, color(250, 196, 0), f:: arial_small, string.str().c_str());
		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 250, color(250, 196, 0), f::arial_small, " Thanks MasterLooser :)");
		d::draw_string(vars::menu::menu_x + 165, vars::menu::menu_y - 250, color(250, 196, 0), f::arial_small, " Thanks Urosaurus :)");
		d::draw_string(vars::menu::menu_x - 240, vars::menu::menu_y - 200, color(66, 149, 245), f::arial_small, " x77 Alpha");
		d::draw_string(vars::menu::menu_x - 240, vars::menu::menu_y - 190, color().rainbow(.01f, 255), f::arial_small, " -------------");
		d::draw_string(vars::menu::menu_x - 240, vars::menu::menu_y - 210, color().rainbow(.01f, 255), f::arial_small, " -------------");


		//Welcome to x88 on down syndrome BLICKY WAS HERE CUH GANG GANG CRIP GANG SWANG BANG//
		
		//Aimbot x77//
		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 200, color(255, 255, 255), f::tahoma_x88, " Aimbot:");
		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 185, color(255, 255, 255), f::tahoma_x88, " Aim Mode:");
		if (vars::aim::aim_enabled) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 200, color(66, 149, 245), f::tahoma_x88, " ON");
		else d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 200, color(255, 255, 255), f::tahoma_x88, " OFF");

		//Aimbot Type/Mode 
		
			if (vars::aim::aim_silent) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 185, color().rainbow(0.001f, 255), f::tahoma_x88, " pSilent :)");
			else if (vars::aim::aim_on_attack) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 185, color(219, 56, 15), f::tahoma_x88, " Attack");
			else if (vars::aim::aim_smooth > 0) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 185, color(37, 184, 181), f::tahoma_x88, " Smooth");
			else if (vars::aim::aim_enabled) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 185, color(250, 196, 0), f::tahoma_x88, " Lock");
			else d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 185, color(255, 255, 255), f::tahoma_x88, " OFF");
		
		
		//Esp//
		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 170, color(255, 255, 255), f::tahoma_x88, " Esp:");
		if (vars::esp::esp_enabled == 1) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 170, color(66, 149, 245), f::tahoma_x88, " Always");
	    else if (vars::esp::esp_enabled == 2) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 170, color(176, 48, 44), f::tahoma_x88, " Dead");
	    else d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y -170, color(255, 255, 255), f::tahoma_x88, " OFF");
		
		//Ctag//
		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 155, color(255, 255, 255), f::tahoma_x88, " Ctag:");
		if (vars::ctags::clan_tag_changer == true) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 155, color(66, 149, 245), f::tahoma_x88, " gamesense");
		else if (vars::ctags::clan_tag_changer_2 == true) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 155, color(66, 149, 245), f::tahoma_x88, " x77 Alpha");
		else d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 155, color(255, 255, 255), f::tahoma_x88, " OFF");


		//ThirdPerson// 
		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 140, color(255, 255, 255), f::tahoma_x88, " ThirdP:");
		if (vars::vis::vis_third_person == 1) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 140, color(66, 149, 245), f::tahoma_x88, " Real");
		else if (vars::vis::vis_third_person == 2) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 140, color(250, 196, 0), f::tahoma_x88, " Fake");
		else d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 140, color(255, 255, 255), f::tahoma_x88, " OFF");


		//AntiAim//
		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 125, color().rainbow(.001f, 255), f::tahoma_x88, " AA:");
		if (vars::hvh::hvh_anti_aim) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 125, color(176, 48, 44), f::tahoma_x88, " WARNING: ON");
		else d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 125, color(255, 255, 255), f::tahoma_x88, " OFF");


		//AntiAim Mode//
		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 110, color(225, 255, 255), f::tahoma_x88, " AA Mode:");

		if (vars::hvh::hvh_anti_aim) {

			if (vars::hvh::hvh_jitter_range > 0.f)	d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 110, color(247, 20, 221), f::tahoma_x88, " JITTA");
			else if (vars::hvh::hvh_jitter_range == 0.f)	d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 110, color(149, 59, 245), f::tahoma_x88, " STATEK");
		}
		else if (!vars::hvh::hvh_anti_aim)	d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 110, color(255, 255, 255), f::tahoma_x88, " OFF");


		//AntiAim dir// 
		if (vars::hvh::hvh_anti_aim) {

			if (g::left_key_pressed)	d::draw_string(vars::menu::menu_x + 80, vars::menu::menu_y - 125, color(105, 7, 242), f::tahoma_x88, " RIGHT");
			else if (g::right_key_pressed)	d::draw_string(vars::menu::menu_x + 80, vars::menu::menu_y - 125, color(237, 17, 94), f::tahoma_x88, " LEFT");
			
		}

		//bhop (I need to make a pointer so I can have both (strafe and hops) on movement)//
		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 95, color(255, 255, 255), f::tahoma_x88, " Bhop:");
		if (vars::misc::misc_auto_hop) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 95, color(66, 149, 245), f::tahoma_x88, " ON");
		else d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 95, color(255, 255, 255), f::tahoma_x88, " OFF");


		//soon to be triggerbot
		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 80, color(255, 255, 255), f::tahoma_x88, " Triggerbot:");
		d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 80, color(245, 97, 5), f::tahoma_x88, " N/A");


		//soon to be chams
		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 65, color(255, 255, 255), f::tahoma_x88, " Chams:");
		d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 65, color(245, 97, 5), f::tahoma_x88, " N/A");


		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 50, color(255, 255, 255), f::tahoma_x88, " Resolver:");
		if (vars::hvh::hvh_resolver) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 50, color(66, 149, 245), f::tahoma_x88, " ON");
		else d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 50, color(255, 255, 255), f::tahoma_x88, " OFF");


		//xhair
		d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 35, color(255, 255, 255), f::tahoma_x88, " Xhair:");
		if (vars::vis::vis_force_crosshair) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 35, color(66, 149, 245), f::tahoma_x88, " Forced");
		else if (vars::vis::vis_recoil_crosshair ) d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 35, color(250, 196, 0), f::tahoma_x88, " Recoil");
		else	d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 35, color(255, 255, 255), f::tahoma_x88, " OFF");

		//Aim FOV this is fucking aids but GANG GANG GANG CUH 
	
			d::draw_string(vars::menu::menu_x + 40, vars::menu::menu_y - 20, color(255, 255, 255), f::tahoma_x88, " a_FOV:");
			
				d::draw_string(vars::menu::menu_x + 150, vars::menu::menu_y - 20, color(255, 255, 255), f::tahoma_x88, " OFF");
		
	}

	void lby_indicator()
	{

		if (!g::local || g::local->get_life_state() != LIFE_ALIVE) return;

		float	difference	= (g::last_real_tick.y - g::local->get_lower_body_yaw()), velocity = g::local->get_velocity().length2d();
		bool	flip		= difference > 35 && velocity < 0.1f;

		if (vars::vis::vis_lby_indicator)
			d::draw_string(5, g::height - 45, flip ? color(0, 255, 0) : color(255, 0, 0), f::tahoma_large, "LBY");

	}

	
	void recoil_crosshair()//not finished, don't know why this doesnt work i'm fucking retarded. 
	{
		// checks lplayer is alive
		//if (!g::local || g::local->get_life_state() != LIFE_ALIVE) return;
		
		

				int h, w;

				i::engineclient->get_screen_size(w, h);

				int x = w / 2;
				int y = h / 2;
				int dy = h / 97;
				int dx = w / 97;

				vector punchAngle = g::local->get_aim_punch_angle();

				x -= dx * punchAngle.yaw;
				y += dy * punchAngle.pitch;


				d::draw_line(x - 5, y, x + 6, y , color(255, 255, 255));
				d::draw_line(x, y - 5, x, y + 6, color(255, 255, 255));
		
	}

	void arrows()
	{

		static const auto real_color	= color::green();
		static const auto fake_color	= color::red();
		static const auto lby_color		= color::blue();

		auto local = reinterpret_cast<c_baseentity*>(i::entitylist->get_client_entity(i::engineclient->get_local_player()));
		if (!local) return;

		if (vars::vis::vis_anti_aim_lines && 
			vars::hvh::hvh_anti_aim && 
			(vars::vis::vis_third_person && g::third_person_bind)) {

			constexpr auto distance = 50.f;

			vector origin = local->get_abs_origin(), screen1, screen2;

			if (w2s(origin, screen1)) {

				// real
				if (vars::hvh::hvh_fake_lag > 0) {
					if (!i::debugoverlay->screen_position(u::get_rotated_position(origin, g::last_real_tick.y, distance), screen2)) {
						d::draw_line(screen1.x, screen1.y, screen2.x, screen2.y, real_color);
						d::draw_string_centered(screen2.x, screen2.y, real_color, f::arial, "real");
					}
				}

				// fake
				if (w2s(u::get_rotated_position(origin, g::last_fake_tick.y, distance), screen2)) {
					d::draw_line(screen1.x, screen1.y, screen2.x, screen2.y, fake_color);
					d::draw_string_centered(screen2.x, screen2.y, fake_color, f::arial, "desync");
				}

				// lby
				if (g::local->get_lower_body_yaw()) {
					if (w2s(u::get_rotated_position(origin, g::local->get_lower_body_yaw(), distance), screen2)) {
						d::draw_line(screen1.x, screen1.y, screen2.x, screen2.y, lby_color);
						d::draw_string_centered(screen2.x, screen2.y, lby_color, f::arial, "lby");
					}
				}

			}

		}

	}

}

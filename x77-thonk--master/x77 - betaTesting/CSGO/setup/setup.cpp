#include "../main.h"

void __stdcall hk_create_move(
	int		sequence_number, 
	float	input_sample_frametime, 
	bool	active, 
	bool&	send_packet)
{

	static auto original_create_move = reinterpret_cast<decltype(&s::hk_create_move_proxy)>(h::client_hook->get_original_function(22));

	// call the original createmove
	original_create_move(i::client, NULL, sequence_number, input_sample_frametime, active);

	auto cmd		= i::input->get_user_cmd(sequence_number);
	auto verified	= i::input->get_verified_cmd(sequence_number);

	if (!cmd || !cmd->command_number) return;

	// acquire a global pointer to our local player
	g::local = reinterpret_cast<c_baseentity*>(i::entitylist->get_client_entity(i::engineclient->get_local_player()));

	// global target pointer
	g::target = reinterpret_cast<c_baseentity*>(i::entitylist->get_client_entity(a::get_target()));

	// acquire a global usercmd pointer
	g::cmd = cmd;

	// acquire a global sendpacket pointer
	g::send_packet = send_packet;

	auto sv_cheats = i::cvar->find_var("sv_cheats");

	// spoof
	if (sv_cheats->get_int() != 1) {
		*reinterpret_cast<int*>((DWORD)&sv_cheats->change_callback + 0xC) = 0;
		sv_cheats->set_value(1);
	}

	// make sure we're resetting here aswell
	if (!g::target) {
		g::shots_fired	= 0;
		g::shots_hit	= 0;
		g::shots_missed = 0;
	}

	if (i::engineclient->is_in_game() && i::engineclient->is_connected()) {

		if (g::local != nullptr) {

			v::night_mode();
			m::clan_tag();
			//m::time_tag();

			if (g::local->get_life_state() == LIFE_ALIVE) {

				a::do_auto_stop();

				// misc
				m::crosshair();
				m::viewmodel();
				m::auto_movement();
			

				// hvh
				hvh::fake_lag(send_packet);
				hvh::fake_duck(send_packet);
				hvh::fake_walk(send_packet);
				hvh::anti_aim(send_packet);

				// rage
				a::do_auto_revolver();
				a::do_aimbot();

			}

		}

	}

	// anti ut
	if (vars::misc::misc_anti_untrusted)
		g::cmd->viewangles = u::normalize_angle(g::cmd->viewangles);

	if (!send_packet && !i::clientstate->choked_commands)
		g::last_real_tick = cmd->viewangles;
	else if (send_packet && !i::clientstate->choked_commands)
		g::last_fake_tick = cmd->viewangles;

	verified->m_cmd = *cmd;
	verified->m_crc = cmd->get_checksum();

}

__declspec(naked) void __fastcall s::hk_create_move_proxy(
	PVOID	_this, 
	int, 
	int		sequence_number, 
	float	input_sample_frametime, 
	bool	active)
{
	__asm {
		push ebp
		mov  ebp, esp
		push ebx
		lea  ecx, [esp]
		push ecx
		push dword ptr[active]
		push dword ptr[input_sample_frametime]
		push dword ptr[sequence_number]
		call hk_create_move
		pop  ebx
		pop  ebp
		retn 0Ch
	}
}

bool __fastcall hk_do_post_screen_effects(
	iclientmodeshared*	ecx,
	PVOID				edx,
	view_setup*			setup)
{

	static auto original_do_post_screen_effects = reinterpret_cast<decltype(&hk_do_post_screen_effects)>(h::client_mode_hook->get_original_function(44));

	if (i::engineclient->is_in_game() && i::engineclient->is_connected()) {

		if (vars::esp::esp_enabled > 0 && vars::esp::esp_glow) {

			for (auto i = 0; i < i::glow_manager->get_size(); i++) {

				auto&	glow_object	= i::glow_manager->glow_object_definitions[i];
				auto	entity		= reinterpret_cast<c_baseentity*>(glow_object.entity);

				// validate glow object
				if (glow_object.is_unused()) continue;

				// validate entity
				if (g::local == nullptr || entity == nullptr || entity->get_life_state() != LIFE_ALIVE) continue;

				// dormant check
				if (entity->is_dormant()) continue;

				// health check
				if (entity->get_health() <= 0 || entity->get_life_state() != LIFE_ALIVE) continue;

				// team check
				if (vars::esp::esp_enemy_only && (entity->get_team_num() == g::local->get_team_num())) {
					if (entity->get_index() != g::local->get_index()) continue;
				}

				// dead check
				if (vars::esp::esp_enabled == 2 && g::local->get_life_state() != LIFE_DEAD) continue;

				// local player check
				if (vars::esp::esp_local_player) {
					if (vars::vis::vis_third_person < 1) {
						if (entity->get_index() == g::local->get_index()) continue;
					}
				} else if (!vars::esp::esp_local_player && (entity->get_index() == g::local->get_index())) {
					continue;
				}

				if (entity->get_index() == g::local->get_index()) {
					glow_object.glow_style				= vars::esp::esp_glow_style;
					glow_object.alpha					= 0.85f;
					glow_object.red						= vars::vis::local_r / 255.0f;
					glow_object.green					= vars::vis::local_g / 255.0f;
					glow_object.blue					= vars::vis::local_b / 255.0f;
					glow_object.render_when_occluded	= true;
					glow_object.render_when_unoccluded	= false;
					glow_object.full_bloom_render		= false;
				}
				else if (entity->get_team_num() == 2) {
					glow_object.glow_style				= vars::esp::esp_glow_style;
					glow_object.alpha					= 0.85f;
					glow_object.red						= vars::vis::t_r / 255.0f;
					glow_object.green					= vars::vis::t_g / 255.0f;
					glow_object.blue					= vars::vis::t_b / 255.0f;
					glow_object.render_when_occluded	= true;
					glow_object.render_when_unoccluded	= false;
					glow_object.full_bloom_render		= false;
				} else if (entity->get_team_num() == 3) {
					glow_object.glow_style				= vars::esp::esp_glow_style;
					glow_object.alpha					= 0.85f;
					glow_object.red						= vars::vis::ct_r / 255.0f;
					glow_object.green					= vars::vis::ct_g / 255.0f;
					glow_object.blue					= vars::vis::ct_b / 255.0f;
					glow_object.render_when_occluded	= true;
					glow_object.render_when_unoccluded	= false;
					glow_object.full_bloom_render		= false;
				}

			}

		}

	}

	return original_do_post_screen_effects(ecx, edx, setup);

}

float __fastcall hk_get_viewmodel_fov(
	iclientmodeshared* ecx, 
	PVOID edx)
{
	static auto original_get_viewmodel_fov = reinterpret_cast<decltype(&hk_get_viewmodel_fov)>(h::client_mode_hook->get_original_function(35));

	auto fov = original_get_viewmodel_fov(ecx, edx);
	if (vars::vis::vis_viewmodel_fov > 0 || vars::vis::vis_viewmodel_fov < 0)
		fov = vars::vis::vis_viewmodel_fov;

	return fov;
}

int __fastcall hk_key_event(
	chlclient*		ecx,
	PVOID			edx,
	int				event_code,
	int				key_num,
	const char*		current_binding)
{

	static auto original_key_event = reinterpret_cast<decltype(&hk_key_event)>(h::client_hook->get_original_function(21));

	if (event_code == 1) {

		menu::handle_input(key_num);

		if (key_num == KEY_H && vars::vis::vis_third_person > 0)
			g::third_person_bind = !g::third_person_bind;

		if (key_num == KEY_N && vars::hvh::hvh_air_stuck)
			g::air_stuck_bind = !g::air_stuck_bind;

		// manual anti aim
		if (!vars::menu::menu_active) {

			
			if (key_num == KEY_LEFT) {
				g::left_key_pressed = true; g::right_key_pressed = false;
			} else if (key_num == KEY_RIGHT) {
				g::left_key_pressed = false; g::right_key_pressed = true;
			}

		}

	}

	return original_key_event(ecx, edx, event_code, key_num, current_binding);

}







	







void __fastcall hk_paint_traverse(
	ipanel*			ecx,
	PVOID			edx,
	unsigned int	vgui_panel,
	bool			force_repaint,
	bool			allow_force)
{

	if (vars::vis::vis_no_scope && !strcmp("HudZoom", i::panel->get_name(vgui_panel)))
		return;

	static auto original_paint_traverse = reinterpret_cast<decltype(&hk_paint_traverse)>(h::panel_hook->get_original_function(41));
	original_paint_traverse(ecx, edx, vgui_panel, force_repaint, allow_force);

	static bool init = true;

	if (init) {

		f::arial		= i::surface->create_font();
		i::surface->set_font_glyph_set(f::arial, "Arial", 15, 400, 0, 0, FONTFLAG_DROPSHADOW);

		f::aa_indicator = i::surface->create_font();
		i::surface->set_font_glyph_set(f::aa_indicator, "Arial", 16, 450, 0, 0, FONTFLAG_DROPSHADOW);

		f::arial_blur	= i::surface->create_font();
		i::surface->set_font_glyph_set(f::arial_blur, "Arial", 15, 400, 0, 0, FONTFLAG_OUTLINE | FONTFLAG_GAUSSIANBLUR);

		f::arial_small = i::surface->create_font();
		i::surface->set_font_glyph_set(f::arial_small, "Arial", 14, 200, 0, 0, FONTFLAG_DROPSHADOW);

		f::arial_large	= i::surface->create_font();
		i::surface->set_font_glyph_set(f::arial_large, "Arial", 45, 500, 0, 0, FONTFLAG_OUTLINE);

		f::tahoma_large	= i::surface->create_font();
		i::surface->set_font_glyph_set(f::tahoma_large, "Tahoma", 45, 700, 0, 0, FONTFLAG_DROPSHADOW);

		f::tahoma_x88 = i::surface->create_font();
		i::surface->set_font_glyph_set(f::tahoma_x88, "Tahoma", 16, 700, 0, 0, FONTFLAG_DROPSHADOW);
		init = false;

	}

	// allow global usage of screen size
	i::engineclient->get_screen_size(g::width, g::height);

	if (vgui_panel == i::enginevgui->get_panel(PANEL_TOOLS) && (i::engineclient->is_in_game() && i::engineclient->is_connected())) {

		if (g::local != nullptr) {

			if (vars::vis::vis_watermark)
				v::watermark();
			if (vars::vis::vis_hit_miss)
				v::hitmiss();
			if (vars::vis::vis_user)
				v::user();

			v::entity_loop();

			if (g::local->get_life_state() == LIFE_ALIVE) {

				v::lby_indicator();
				v::arrows();

				v::aa_indicator();
				v::fov_circle();

			}

		}

		if (vars::menu::menu_active) {
			menu::insert_menu_items();
			menu::draw_menu(f::arial_small);
		}

	}

}

void __fastcall hk_frame_stage_notify(
	chlclient*				ecx,
	PVOID					edx,
	client_frame_stage_t	stage)
{

	static auto original_frame_stage_notify = reinterpret_cast<decltype(&hk_frame_stage_notify)>(h::client_hook->get_original_function(37));

	if (i::engineclient->is_in_game() && i::engineclient->is_connected()) {

		if (g::local != nullptr && g::cmd != nullptr) {

			if (g::local->get_life_state() == LIFE_ALIVE) {

				v::occlusion();

				v::third_person();
				v::third_person_angles();

				// sponsored by prayer and faith in god
				resolver::resolver();

			}

			if (stage == FRAME_RENDER_END) {

				for (unsigned long i = 0; i < player_data.size(); i++) {
					std::pair<c_baseentity*, vector> player_aa_data = player_data[i];
					*player_aa_data.first->get_eye_angles_ptr() = player_aa_data.second;
				}

				player_data.clear();

			}

		}

	}

	original_frame_stage_notify(ecx, edx, stage);

}

mdlhandle_t __fastcall hk_find_mdl(
	imdlcache*	ecx,
	PVOID		edx,
	char*		relative_path)
{

	static auto original_find_mdl = reinterpret_cast<decltype(&hk_find_mdl)>(h::data_hook->get_original_function(10));

	return original_find_mdl(ecx, edx, relative_path);

}

void __fastcall hk_override_view(
	iclientmodeshared*	ecx, 
	PVOID				edx, 
	view_setup*			setup)
{

	static auto original_override_view = reinterpret_cast<decltype(&hk_override_view)>(h::client_mode_hook->get_original_function(18));

	if (!g::local)
		original_override_view(ecx, edx, setup);

	if (i::engineclient->is_in_game() && i::engineclient->is_connected()) {

		if (g::local != nullptr && g::local->get_life_state() == LIFE_ALIVE) {

			int& default_fov = *(int*)(g::local + 0x31E8);

			// fov changer
			if (vars::vis::vis_fov > 0 && (!vars::vis::vis_third_person || !g::third_person_bind)) {
				if (!g::local->is_scoped())
					setup->fov += vars::vis::vis_fov;
				else
					setup->fov = default_fov;
			}

			// no vis recoil
			if (vars::vis::vis_no_vis_recoil) {

				vector view	= g::local->get_view_punch_angle();
				vector aim	= g::local->get_aim_punch_angle();

				setup->angles[0] -= (view[0] + (aim[0] * 2 * 0.4499999f));
				setup->angles[1] -= (view[1] + (aim[1] * 2 * 0.4499999f));
				setup->angles[2] -= (view[2] + (aim[2] * 2 * 0.4499999f));

			}

		}

	}

	return original_override_view(ecx, edx, setup);

}

void __fastcall hk_draw_model_execute(
	imodelrender*				ecx, 
	PVOID						edx, 
	imatrendercontext*			context, 
	const draw_model_state&		state, 
	const model_render_info_t&	info, 
	matrix3x4_t*				matrix)
{

	static auto original_draw_model_execute = reinterpret_cast<decltype(&hk_draw_model_execute)>(h::model_hook->get_original_function(21));

	bool original_model = true;

	if (original_model)
		original_draw_model_execute(ecx, edx, context, state, info, matrix);

}

namespace s
{

	void setup_interfaces()
	{

		// interfaces
		create_interface_fn client	= reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA("client_panorama.dll"), "CreateInterface"));
		create_interface_fn input	= reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA("inputsystem.dll"), "CreateInterface"));
		create_interface_fn engine	= reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"));
		create_interface_fn vgui2	= reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA("vgui2.dll"), "CreateInterface"));
		create_interface_fn vgui	= reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA("vguimatsurface.dll"), "CreateInterface"));
		create_interface_fn data	= reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA("datacache.dll"), "CreateInterface"));
		create_interface_fn vstd	= reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "CreateInterface"));
		create_interface_fn phys	= reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA("vphysics.dll"), "CreateInterface"));

		// client
		i::client			= static_cast<chlclient*>(client("VClient018", nullptr));
		i::entitylist		= static_cast<icliententitylist*>(client("VClientEntityList003", nullptr));
		i::clientmode		= **(iclientmodeshared***)((*(DWORD**)i::client)[10] + 0x5);
		i::glow_manager		= *reinterpret_cast<glow_object_manager**>(u::find_signature("client_panorama.dll", "0F 11 05 ? ? ? ? 83 C8 01") + 3);
		i::input			= *reinterpret_cast<cinput**>(u::find_signature("client_panorama.dll", "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10") + 1);

		// datacache
		i::mdlcache			= static_cast<imdlcache*>(data("MDLCache004", nullptr));

		// engine
		i::engineclient		= static_cast<ivengineclient*>(engine("VEngineClient014", nullptr));
		i::debugoverlay		= static_cast<ivdebugoverlay*>(engine("VDebugOverlay004", nullptr));
		i::enginetrace		= static_cast<ienginetrace*>(engine("EngineTraceClient004", nullptr));
		i::enginevgui		= static_cast<ienginevgui*>(engine("VEngineVGui001", nullptr));
		i::clientstate		= u::get_method(i::engineclient, 12).add(16).get(2).as< client_state* >();
		i::modelinfo		= static_cast<ivmodelinfo*>(engine("VModelInfoClient004", nullptr));

		// vphysics
		i::surfaceprops		= static_cast<iphysicssurfaceprops*>(phys("VPhysicsSurfaceProps001", nullptr));

		// public
		i::eventmgr			= static_cast<igameeventmanager*>(engine("GAMEEVENTSMANAGER002", nullptr));
		i::inputsystem		= static_cast<iinputsystem*>(input("InputSystemVersion001", nullptr));
		i::cvar				= static_cast<icvar*>(vstd("VEngineCvar007", nullptr));
		i::globals			= **(global_vars_base***)(u::find_signature("client_panorama.dll", "A1 ? ? ? ? 5E 8B 40 10") + 1);

		// vgui
		i::surface			= static_cast<isurface*>(vgui("VGUI_Surface031", nullptr));
		i::panel			= static_cast<ipanel*>(vgui2("VGUI_Panel009", nullptr));

	}

	void setup_hooks()
	{

		if (i::client != nullptr) {
			h::client_hook = std::make_unique<vmt_hook>();
			h::client_hook->setup(i::client);

			h::client_hook->hook_index(21, reinterpret_cast<int*>(hk_key_event));
			h::client_hook->hook_index(22, reinterpret_cast<PVOID>(hk_create_move_proxy));
			h::client_hook->hook_index(37, reinterpret_cast<PVOID>(hk_frame_stage_notify));
		}

		if (i::clientmode != nullptr) {
			h::client_mode_hook = std::make_unique<vmt_hook>();
			h::client_mode_hook->setup(i::clientmode);

			h::client_mode_hook->hook_index(44, reinterpret_cast<bool*>(hk_do_post_screen_effects));
			h::client_mode_hook->hook_index(35, reinterpret_cast<float*>(hk_get_viewmodel_fov));
			h::client_mode_hook->hook_index(18, reinterpret_cast<PVOID>(hk_override_view));
		}

		if (i::panel != nullptr) {
			h::panel_hook = std::make_unique<vmt_hook>();
			h::panel_hook->setup(i::panel);

			h::panel_hook->hook_index(41, reinterpret_cast<PVOID>(hk_paint_traverse));
		}

		if (i::modelrender != nullptr) {
			h::model_hook = std::make_unique<vmt_hook>();
			h::model_hook->setup(i::modelrender);

			h::model_hook->hook_index(21, reinterpret_cast<PVOID>(hk_draw_model_execute));
		}

	}

	bool ready_to_blast()
	{

		if (i::client == nullptr)
			return true;

		return false;

	}

	void detach()
	{
		h::client_hook->release();
		h::client_mode_hook->release();
		h::panel_hook->release();
		h::data_hook->release();
	}

}

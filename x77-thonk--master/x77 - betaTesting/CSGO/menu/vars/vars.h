#ifndef VARS_H
#define VARS_H
#ifdef _WIN32
#pragma once
#endif

namespace vars
{

	namespace menu
	{

		extern bool menu_active;

		extern int total_items;
		extern int current_pos;
		extern int font_size;
		extern int menu_x;
		extern int menu_y;
		extern int bar_width;
		extern int bar_height;

	}

	namespace aim
	{
		extern bool		aim_tab;
		extern bool		aim_enabled;
		extern float	aim_fov;
		extern int		aim_hitbox;
		extern bool		aim_on_attack;
		extern bool		aim_auto_shoot;
		extern bool		aim_auto_stop;
		extern bool		aim_auto_scope;
		extern bool		aim_auto_revolver;
		extern bool		aim_trigger_bot; 
		extern bool		aim_silent;
		extern float	aim_smooth;
		extern float	aim_hitchance_amt;
		extern bool		aim_target_teammates;
		extern bool		aim_ignore_jumping;
		extern int		aim_baim_after_x_shots;
	}
	namespace cvars
	{
		extern bool cvar_tab;
	
	}
	namespace esp
	{
		extern bool		esp_tab;
		extern int		esp_enabled;
		extern bool		esp_enemy_only;
		extern int		esp_box;
		extern float	esp_fill;
		extern bool		esp_glow;
		extern int		esp_glow_style;
		extern bool		esp_name;
		extern int		esp_health;
		extern bool		esp_projectiles;
		extern bool		esp_steam_id;
		extern bool		esp_flags;
		extern bool		esp_weapon;
		extern bool		esp_money;
		extern bool		esp_bomb;
		extern bool		esp_index;
		extern int		esp_armor;
		extern bool		esp_distance;
		extern bool		esp_local_player;
	}

	namespace vis
	{

		extern bool		vis_tab;
		extern bool		vis_color_tab;
		extern bool		vis_viewmodel_tab;
		extern bool		vis_t_tab;
		extern bool		vis_ct_tab;
		extern bool		vis_local_tab;
		extern bool		vis_ambient_tab;
		extern bool		vis_fov_circle;
		extern int		vis_third_person;
		extern bool		vis_night_mode;
		extern float	vis_viewmodel_fov;
		extern float	vis_fov;
		extern bool		vis_no_vis_recoil;
		extern bool		vis_no_scope;
		extern bool		vis_recoil_crosshair;
		extern bool		vis_force_crosshair;
		extern bool		vis_hit_miss;
		extern bool		vis_preserve_killfeed;
		extern bool		vis_skeet_line;
		extern bool		vis_anti_aim_lines;
		extern bool		vis_lby_indicator;
		extern bool		vis_watermark;
		extern bool		vis_user;

		extern int t_r;
		extern int t_g;
		extern int t_b;
		extern int ct_r;
		extern int ct_g;
		extern int ct_b;
		extern int local_r;
		extern int local_g;
		extern int local_b;

		extern float offset_x;
		extern float offset_y;
		extern float offset_z;

		extern float ambient_r;
		extern float ambient_g;
		extern float ambient_b;

	}

	namespace hvh
	{
		extern bool		hvh_tab;
		extern bool		hvh_resolver;
		extern bool		hvh_anti_aim;
		extern int		hvh_fake_lag;
		extern bool		hvh_fake_duck;
		extern bool		hvh_air_stuck; 
		extern bool		hvh_fake_walk;
		extern float	hvh_yaw_add;
		extern float	hvh_jitter_range;
		extern int		hvh_pitch;
	}

	namespace misc
	{
		extern bool misc_tab;
		extern bool misc_auto_hop;
		extern bool misc_auto_strafe;
		extern bool misc_legitaa_slidefix;
		extern bool misc_anti_untrusted;
	}

	namespace ctags
	{
		extern bool ctag_tab; 
		
		extern int clan_tag_changer;
		extern int static_clantag_changer;
		extern bool time_clan_tag; 
	}


}

#endif // !VARS_H
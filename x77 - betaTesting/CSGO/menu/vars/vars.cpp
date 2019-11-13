#include "../../main.h"

namespace vars
{

	namespace menu
	{
		bool menu_active	= false;

		int total_items		= 0;
		int current_pos		= 0;
		int font_size		= 15;
		int menu_x			= 250;
		int menu_y			= 250;
		int bar_width		= 64;
		int bar_height		= 25;
	}

	namespace aim
	{
		bool	aim_tab					= false;
		bool	aim_enabled				= false;
		float	aim_fov					= 0.f;
		int		aim_hitbox				= 0;
		bool	aim_on_attack			= false;
		bool	aim_auto_shoot			= false;
		bool	aim_auto_stop			= false;
		bool	aim_auto_scope			= false;
		bool	aim_auto_revolver		= false;
		bool	aim_silent				= false;
		float	aim_smooth				= 0.f;
		float	aim_hitchance_amt		= 0.f;
		bool	aim_target_teammates	= false;
		bool	aim_ignore_jumping		= false;
		int		aim_baim_after_x_shots	= 0;
	}

	namespace esp
	{
		bool	esp_tab				= false;
		int		esp_enabled			= 0;
		bool	esp_enemy_only		= false;
		int		esp_box				= 0;
		float	esp_fill			= 0.f;
		bool	esp_glow			= false;
		int		esp_glow_style		= 0;
		bool	esp_name			= false;
		int		esp_health			= 0;
		bool	esp_projectiles		= false;
		bool	esp_steam_id		= false;
		bool	esp_flags			= false;
		bool	esp_weapon			= false;
		bool	esp_money			= false;
		bool	esp_index			= false;
		int		esp_armor			= 0;
		bool	esp_distance		= false;
		bool	esp_local_player	= false;
	}

	namespace vis
	{
		bool	vis_tab						= false;
		bool	vis_color_tab				= false;
		bool	vis_viewmodel_tab			= false;
		bool	vis_t_tab					= false;
		bool	vis_ct_tab					= false;
		bool	vis_local_tab				= false;
		bool	vis_ambient_tab				= false;
		bool	vis_fov_circle				= false;
		int		vis_third_person			= 0;
		bool	vis_night_mode				= false;
		float	vis_viewmodel_fov			= 0.f;
		float	vis_fov						= 0.f;
		bool	vis_no_vis_recoil			= false;
		bool	vis_anti_aim_lines			= false;
		bool	vis_lby_indicator			= false;
		bool	vis_no_scope				= false;
		bool	vis_force_crosshair			= false;
		bool	vis_recoil_crosshair		= false;
		bool	vis_preserve_killfeed		= false;
		bool	vis_user					= true; 
		bool	vis_watermark				= true; 

		int t_r		= 135;
		int t_g		= 40;
		int t_b		= 255;
		int ct_r	= 135;
		int ct_g	= 40;
		int ct_b	= 255;
		int local_r = 235;
		int local_g = 140;
		int local_b = 25;

		float offset_x = 1.5f;
		float offset_y = 1.5f;
		float offset_z = -1.5f;

		float ambient_r = 0.f;
		float ambient_g = 0.f;
		float ambient_b = 0.f;

	}

	namespace hvh
	{

		bool	hvh_tab					= false;
		bool	hvh_resolver			= false;
		bool	hvh_anti_aim			= false;
		int		hvh_fake_lag			= 1;
		bool	hvh_fake_duck			= false;
		bool	hvh_fake_walk			= false;
		float	hvh_yaw_add				= 0.f;
		float	hvh_jitter_range		= 0.f;
		int		hvh_pitch				= 0;
	}

	namespace misc
	{
		bool	misc_tab				= false;
		bool	misc_auto_hop			= false;
		bool	misc_clan_tag_changer	= false; 
		bool	misc_auto_strafe		= false;
		bool	misc_anti_untrusted		= true;
	}

	namespace ctags
	{

		bool	ctag_tab = false; 
		
		bool	clan_tag_changer = false; 
	}




}
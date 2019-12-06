#ifndef VISUALS_H
#define VISUALS_H
#ifdef _WIN32
#pragma once
#endif


namespace v
{
	extern void		vector_transform(const vector& some, const matrix3x4_t& matrix, vector& out);
	extern void		entity_loop();
	extern color	get_entity_color(c_baseentity* entity);
	extern void		projectiles(c_baseentity* entity, color col, unsigned long font);
	extern void		players(float x, float y, float w, float h, player_info_t info, c_baseentity* entity, color col, unsigned long font, vector min, vector max, vector pos);
	extern void     foot_history(float x, float y, float w, float h, player_info_t info, c_baseentity* entity, color col, unsigned long font, vector min, vector max, vector pos);
	extern void		fov_circle();
	extern void		third_person(client_frame_stage_t stage = FRAME_RENDER_START);
	extern void		third_person_angles(client_frame_stage_t stage = FRAME_RENDER_START);
	extern void		aa_indicator();
	extern void		night_mode();
	extern void		occlusion(client_frame_stage_t stage = FRAME_RENDER_START);
	extern void		lby_indicator();
	extern void		arrows();
	extern void		recoil_crosshair();
	extern void		user();
	extern void		watermark();
}

#endif // !VISUALS_H
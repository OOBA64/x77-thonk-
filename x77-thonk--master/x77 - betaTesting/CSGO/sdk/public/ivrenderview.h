#ifndef IVRENDERVIEW_H
#define IVRENDERVIEW_H
#ifdef _WIN32
#pragma once
#endif

class ivrenderview
{
public:

	virtual void draw_brush_model(
		PVOID			entity,
		model_t*		model,
		const vector&	origin,
		const vector&	angles,
		bool			unused) = 0;

	virtual void			draw_identity_brush_model(iworldrenderlist* list, model_t* model)	= 0;
	virtual void			touch_light(struct dlight_t* light)									= 0;
	virtual void			draw_3d_debug_overlays(void)										= 0;
	virtual void			set_blend(float blend)												= 0;
	virtual float			get_blend(void)														= 0;
	virtual void			set_color_modulation(float const* blend)							= 0;
	virtual void			get_color_modulation(float* blend)									= 0;

};

#endif // !IVRENDERVIEW_H
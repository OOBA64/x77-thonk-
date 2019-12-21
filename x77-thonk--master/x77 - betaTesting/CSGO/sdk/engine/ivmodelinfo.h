#ifndef IVMODELINFO_H
#define IVMODELINFO_H
#ifdef _WIN32
#pragma once
#endif

#define DECLARE_POINTER_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
DECLARE_POINTER_HANDLE(StudioDecalHandle_t);

enum renderabletranslucencytype_t
{
	RENDERABLE_IS_OPAQUE = 0,
	RENDERABLE_IS_TRANSLUCENT,
	RENDERABLE_IS_TWO_PASS,    // has both translucent and opaque sub-partsa
};

enum overridetype_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
};

struct draw_model_state
{
	studiohdr_t*		studio_hdr;
	studiohwdata_t*		studio_hw_data;
	client_renderable*	renderable;
	const matrix3x4_t*	model_to_world;
	StudioDecalHandle_t decals;
	int					draw_flags;
	int					lod;
};

struct model_render_info_t
{
	vector					origin;
	vector					angles;
	char					pad[0x4];
	client_renderable*		renderable;
	const model_t*			model;
	const matrix3x4_t*		model_to_world;
	const matrix3x4_t*		lighting_offset;
	const vector*			lighting_origin;
	int						flags;
	int						index;
	int						skin;
	int						body;
	int						hitboxset;
	model_instance_handle_t	instance;

	model_render_info_t()
	{
		model_to_world	= NULL;
		lighting_offset = NULL;
		lighting_origin = NULL;
	}

};

class imodelrender
{
public:
	void draw_model_execute(imatrendercontext* ctx, const draw_model_state& state, const model_render_info_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
	{
		using original_fn = void(__thiscall*)(PVOID, imatrendercontext*, const draw_model_state&, const model_render_info_t&, matrix3x4_t*);
		u::call_vfunc<original_fn>(this, 21)(this, ctx, state, pInfo, pCustomBoneToWorld);
	}

	void forced_material_override(imaterial* new_material, overridetype_t override_type = OVERRIDE_NORMAL)
	{
		using original_fn = void(__thiscall*)(PVOID, imaterial*, overridetype_t, int);
		u::call_vfunc<original_fn>(this, 1)(this, new_material, override_type, NULL);
	}
};

class ivmodelinfo
{
public:
	virtual                                 ~ivmodelinfo(void) {}
	virtual const model_t*					get_model(int index) const																																		= 0;
	virtual int                             get_model_index(const char* name) const																															= 0;
	virtual const char*						get_model_name(const model_t* model) const																														= 0;
	virtual vcollide_t*						get_v_collide(const model_t* model) const																														= 0;
	virtual vcollide_t*						get_v_collide(int index) const																																	= 0;
	virtual void                            get_model_bounds(const model_t* model, vector& mins, vector& maxs) const																						= 0;
	virtual void                            get_model_render_bounds(const model_t* model, vector& mins, vector& maxs) const																					= 0;
	virtual int                             get_model_frame_count(const model_t* model) const																												= 0;
	virtual int                             get_model_type(const model_t* model) const																														= 0;
	virtual PVOID							get_model_extra_data(const model_t* model)																														= 0;
	virtual bool                            model_has_material_proxy(const model_t* model) const																											= 0;
	virtual bool                            is_translucent(model_t const* model) const																														= 0;
	virtual bool                            is_translucent_two_pass(const model_t* model) const																												= 0;
	virtual void unused0() {};
	virtual void unused1() = 0;
	virtual void unused2() = 0;
	virtual renderabletranslucencytype_t    compute_translucency_type(const model_t* model, int skin, int body)																								= 0;
	virtual int                             get_model_material_count(const model_t* model) const																											= 0;
	virtual void                            get_model_materials(const model_t* model, int count, imaterial** material)																						= 0;
	virtual bool                            is_model_vertex_lit(const model_t* model) const																													= 0;
	virtual const char*						get_model_key_value_text(const model_t* model)																													= 0;
	virtual void unused3() = 0;
	virtual float							get_model_radius(const model_t* model)																															= 0;
	virtual cstudiohdr*						get_studio_hdr(mdlhandle_t handle)																																= 0;
	virtual const studiohdr_t*				find_model(const studiohdr_t* studio, void** cache, const char* name) const																						= 0;
	virtual const studiohdr_t*				find_mdl(void* cache) const																																		= 0;
	virtual virtualmodel_t*					get_virtual_model(const studiohdr_t* studio) const																												= 0;
	virtual uint8_t*						get_anim_block(const studiohdr_t* studio, int block) const																										= 0;
	virtual void							get_model_material_color_and_lighting(const model_t* model, vector const& origin, vector const& angles, trace_t* trace, vector& lighting, vector& color)		= 0;
	virtual void                            get_illumination_point(const model_t* model, client_renderable* renderable, vector const& origin, vector const& angles, vector* lighting)						= 0;
	virtual int                             get_model_contents(int index) const																																= 0;
	virtual studiohdr_t*					get_studio_model(const model_t* model)																															= 0;
	virtual int                             get_model_sprite_width(const model_t* model) const																												= 0;
	virtual int								get_model_spright_height(const model_t* model) const																											= 0;
	virtual void                            set_level_screen_fade_range(float min, float max)																												= 0;
	virtual void                            get_level_screen_fade_range(float* min, float* max) const																										= 0;
	virtual void                            set_view_screen_fade_range(float mine, float max)																												= 0;
	virtual unsigned char                   compute_level_screen_fade(const vector& origin, float radius, float scale) const																				= 0;
	virtual unsigned char                   compute_view_screen_fade(const vector& origin, float radius, float scale) const																					= 0;
	virtual int                             get_auto_player_list(const studiohdr_t* studio, unsigned short** list) const																					= 0;
	virtual PVOID							get_collide_for_virtual_terrain(int index)																														= 0;
	virtual bool                            is_using_fb_texture(const model_t* model, int skin, int body, client_renderable** renderable) const																= 0;
	virtual const model_t*					find_or_load_model(const char* name) const																														= 0;
	virtual mdlhandle_t                     get_cache_handle(const model_t* model) const																													= 0;
	virtual int                             get_brush_model_planeCount(const model_t* model) const																											= 0;
	virtual void                            get_brush_model_plane(const model_t* model, int index, plane_t& plane, vector* origin) const																	= 0;
	virtual int                             get_surface_props_for_virtual_terrain(int index)																												= 0;
	virtual bool                            uses_env_cubemap(const model_t* model) const																													= 0;
	virtual bool                            uses_static_lighting(const model_t* model) const																												= 0;
};

#endif // !IVMODELINFO_H
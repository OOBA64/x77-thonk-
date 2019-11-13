#ifndef IENGINETRACE_H
#define IENGINETRACE_H
#ifdef _WIN32
#pragma once
#endif

enum trace_type_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

struct plane_t
{
	vector  normal;
	float   dist;
	BYTE    type;
	BYTE    signbits;
	BYTE    pad[2];
};

struct surface_t
{
	const char*		name;
	short           surface_props;
	unsigned short  flags;
};

struct surfacephysicsparams_t
{
	float friction;
	float elasticity;
	float density;
	float thickness;
	float dampening;
};

struct surfaceaudioparams_t
{
	float reflectivity;				// like elasticity, but how much sound should be reflected by this surface
	float hardness_factor;			// like elasticity, but only affects impact sound choices
	float roughness_factor;			// like friction, but only affects scrape sound choices   
	float rough_threshold;			// surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
	float hard_threshold;			// surface hardness > this causes "hard" impacts, < this causes "soft" impacts
	float hard_velocity_threshold;	// collision velocity > this causes "hard" impacts, < this causes "soft" impacts   
	float high_pitch_occlusion;		// a value betweeen 0 and 100 where 0 is not occluded at all and 100 is silent (except for any additional reflected sound)
	float mid_pitch_occlusion;
	float low_pitch_occlusion;
};

struct surfacesoundnames_t
{
	unsigned short walk_step_left;
	unsigned short walk_step_right;
	unsigned short run_step_left;
	unsigned short run_step_right;
	unsigned short impact_soft;
	unsigned short impact_hard;
	unsigned short scrape_smooth;
	unsigned short scrape_rough;
	unsigned short bullet_impact;
	unsigned short rolling;
	unsigned short break_sound;
	unsigned short strain_sound;
};

struct surfacegameprops_t
{
public:
	float			max_speed_factor;
	float			jump_factor;
	float			penetration_modifier;
	float			damage_modifier;
	unsigned short	material;
	byte			climbable;
	char			pad00[0x4];

};

struct surfacedata_t
{
	surfacephysicsparams_t	physics;
	surfaceaudioparams_t	audio;
	surfacesoundnames_t		sounds;
	surfacegameprops_t		game;
};

class iphysicssurfaceprops
{
public:
	surfacedata_t* get_surface_data(int id)
	{
		using original_fn = surfacedata_t*(__thiscall*)(PVOID, int);
		return u::call_vfunc<original_fn>(this, 5)(this, id);
	}
};

class base_trace
{
public:

	vector			start_pos;
	vector			end_pos;
	plane_t			plane;
	float			fraction;
	int				contents;
	unsigned short	disp_flags;
	bool			all_solid;
	bool			start_solid;
};

class game_trace : public base_trace
{
public:

	float			fraction_left_solid;
	surface_t		surface;

	int				hitgroup;

	short			physics_bone;
	unsigned short	world_surface_index;

	c_baseentity*	ent;
	int				hitbox;

};

struct ray_t {

	vector_aligned		m_start;
	vector_aligned		m_delta;
	vector_aligned		m_start_offset;
	vector_aligned		m_extents;
	const matrix3x4_t*	m_world_axis_transform;
	bool				m_is_ray;
	bool				m_is_swept;

	ray_t() : m_world_axis_transform(NULL) {}

	ray_t(vector _start, vector _end)
	{
		init(_start, _end);
	}

	ray_t(vector _start, vector _end, vector _mins, vector _maxs)
	{
		init(_start, _end, _mins, _maxs);
	}

	void init(vector const& start, vector const& end) {

		m_delta = end - start;

		m_is_swept = (m_delta.length_sqr() != 0);

		m_extents.init();

		m_world_axis_transform = NULL;
		m_is_ray = true;

		m_start_offset.init();
		vector_copy(start, m_start);

	}

	void init(vector const& start, vector const& end, vector const& mins, vector const& maxs) {

		m_delta = end - start;

		m_world_axis_transform = NULL;
		m_is_swept = (m_delta.length_sqr() != 0);

		m_extents = maxs - mins;
		m_extents *= 0.5f;
		m_is_ray = (m_extents.length_sqr() < 1e-6);

		m_start_offset = maxs + mins;
		m_start_offset *= 0.5f;
		m_start = start + m_start_offset;
		m_start_offset *= -1.0f;

	}

};

class itracefilter
{
public:
	virtual bool			should_hit_entity(void* entity, int contents_mask)	= 0;
	virtual trace_type_t	get_trace_type() const								= 0;
};

class trace_filter : public itracefilter
{
public:

	explicit trace_filter(c_baseentity* entity, trace_type_t tracetype = TRACE_EVERYTHING)
	{
		skip = entity;
	}

	bool should_hit_entity(void* pEntityHandle, int contentsMask)
	{
		return (pEntityHandle != skip);
	}

	trace_type_t get_trace_type() const
	{
		return TRACE_EVERYTHING;
	}

	PVOID skip;
};

class ienginetrace
{
public:

	void trace_ray(const ray_t& ray, unsigned int mask, itracefilter* trace_filter, trace_t* trace)
	{
		using original_fn = void(__thiscall*)(PVOID, const ray_t&, unsigned int, itracefilter*, trace_t*);
		return u::call_vfunc<original_fn>(this, 5)(this, ray, mask, trace_filter, trace);
	}

	void clip_ray_to_entity(const ray_t& ray, unsigned int mask, c_baseentity* ent, trace_t* trace)
	{
		using original_fn = void(__thiscall*)(PVOID, const ray_t&, unsigned int, c_baseentity*, trace_t*);
		return u::call_vfunc<original_fn>(this, 3)(this, ray, mask, ent, trace);
	}

};

#endif // !IENGINETRACE_H

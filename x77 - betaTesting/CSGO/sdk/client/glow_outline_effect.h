#ifndef GLOW_OUTLINE_EFFECT_H
#define GLOW_OUTLINE_EFFECT_H
#ifdef _WIN32
#pragma once
#endif

#define END_OF_FREE_LIST	-1
#define ENTRY_IN_USE		-2

struct glow_object_definition_t
{
	glow_object_definition_t() { 
		memset(this, 0, sizeof(*this)); 
	}

	class c_baseentity* entity;
	union {
		vector glow_color;
		struct {
			float   red;
			float   green;
			float   blue;
		};
	};

	float   alpha;
	uint8_t pad_0014[4];
	float   some_float;
	uint8_t pad_001C[4];
	float   another_float;
	bool    render_when_occluded;
	bool    render_when_unoccluded;
	bool    full_bloom_render;
	uint8_t pad_0027[5];
	int32_t glow_style;
	int32_t split_screen_slot;
	int32_t next_free_slot;

	bool is_unused() const { 
		return next_free_slot != ENTRY_IN_USE; 
	}

};

class glow_object_manager
{
public:

	int register_glow_object(c_baseentity* entity, const vector& glow_color, float glow_alpha, bool render_when_occluded, bool render_when_unoccluded, int split_screen_slot)
	{

		int index;
		if (first_free_slot == END_OF_FREE_LIST) {
			index = -1;
		} else {
			index = first_free_slot;
			first_free_slot = glow_object_definitions[index].next_free_slot;
		}

		glow_object_definitions[index].entity					= entity;
		glow_object_definitions[index].glow_color				= glow_color;
		glow_object_definitions[index].alpha					= glow_alpha;
		glow_object_definitions[index].render_when_occluded		= render_when_occluded;
		glow_object_definitions[index].render_when_unoccluded	= render_when_unoccluded;
		glow_object_definitions[index].split_screen_slot		= split_screen_slot;
		glow_object_definitions[index].next_free_slot			= ENTRY_IN_USE;

		return index;

	}

	void unregister_glow_object(int glow_object_handle)
	{
		glow_object_definitions[glow_object_handle].next_free_slot	= first_free_slot;
		glow_object_definitions[glow_object_handle].entity			= NULL;
		first_free_slot												= glow_object_handle;
	}

	void set_entity(int glow_object_handle, c_baseentity* entity)
	{
		glow_object_definitions[glow_object_handle].entity = entity;
	}

	void set_color(int glow_object_handle, const vector& glow_color)
	{
		glow_object_definitions[glow_object_handle].glow_color = glow_color;
	}

	void set_alpha(int glow_object_handle, float alpha)
	{
		glow_object_definitions[glow_object_handle].alpha = alpha;
	}

	void set_render_flags(int glow_object_handle, bool render_when_occluded, bool render_when_unoccluded)
	{
		glow_object_definitions[glow_object_handle].render_when_occluded	= render_when_occluded;
		glow_object_definitions[glow_object_handle].render_when_unoccluded	= render_when_unoccluded;
	}

	int get_size()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0xC);
	}

	glow_object_definition_t* glow_object_definitions;
	int first_free_slot;

};

#endif // !GLOW_OUTLINE_EFFECT_H
#ifndef INPUT_H
#define INPUT_H
#ifdef _WIN32
#pragma once
#endif

#define MULTIPLAYER_BACKUP 150

class cinput
{
public:

	virtual void	init_all(void)																			= 0;
	virtual void	shutdown_all(void)																		= 0;
	virtual int		get_buttons_bits(int)																	= 0;
	virtual void	create_move(int sequence_number, float input_sample_frametime, bool active)				= 0;
	virtual void	extra_mouse_sample(float frametime, bool active)										= 0;
	virtual bool	writeusercmddeltatobuffer(int nSlot, void* buf, int from, int to, bool isnewcommand)	= 0;
	virtual void	encodeusercmdtobuffer(void* buf, int slot)												= 0;
	virtual void	decodeusercmdfrombuffer(void* buf, int slot)											= 0;

	char				pad_0x00[0x8];
	bool				track_ir_available;
	bool				mouse_initialized;
	bool				mouse_active;
	bool				joystick_advanced_init;
	char				pad_0x08[0x2C];
	PVOID				keys;
	char				pad1[0x10];
	float				keyboard_sample_time;
	char				pad2[0x58];
	bool				camera_intercepting_mouse;
	bool				camera_in_third_person;
	bool				camera_moving_with_mouse;
	vector				camera_offset;
	bool				camera_distance_move;
	int					camera_old_x;
	int					camera_old_y;
	int					camera_x;
	int					camera_y;
	bool				camera_is_orthographic;
	vector				previous_viewangles;
	vector				previous_viewangles_tilt;
	float				last_forward_move;
	int					clear_insput_state;
	user_cmd*			commands;
	verified_user_cmd*	cerified_commands;

	inline user_cmd*			get_user_cmd(int sequence_number);
	inline user_cmd*			get_user_cmd(int slot, int sequence_number);
	inline verified_user_cmd*	get_verified_cmd(int sequence_number);

};

user_cmd* cinput::get_user_cmd(int sequence_number)
{
	using original_fn = user_cmd*(__thiscall*)(void*, int, int);
	return u::call_vfunc<original_fn>(this, 8)(this, 0, sequence_number);
}

user_cmd* cinput::get_user_cmd(int slot, int sequence_number)
{
	using original_fn = user_cmd*(__thiscall*)(PVOID, int, int);
	return u::call_vfunc<original_fn>(this, 8)(this, slot, sequence_number);
}

verified_user_cmd* cinput::get_verified_cmd(int sequence_number)
{
	auto verified_commands = *(verified_user_cmd * *)(reinterpret_cast<uint32_t>(this) + 0xF8);
	return &verified_commands[sequence_number % MULTIPLAYER_BACKUP];
}

#endif // !INPUT_H
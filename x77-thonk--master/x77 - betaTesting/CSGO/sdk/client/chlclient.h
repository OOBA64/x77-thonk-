#ifndef CHLCLIENT_H
#define CHLCLIENT_H
#ifdef _WIN32
#pragma once
#endif

class client_class
{
public:
	create_client_class_fn	create_client_class;
	create_event_fn*		create_event;
	char*					network_name;
	RecvTable*				recv_table;
	client_class*			next;
	int						class_id;
};

class chlclient {};

class client_state
{
public:

	void force_full_update() {
		delta_tick = uint32_t(-1);
	}

	char		pad_0000[156];						//	0x0000
	uint32_t	net_channel;						//	0x009C
	uint32_t	challenge_nr;						//	0x00A0
	char		pad_00A4[100];						//	0x00A4
	uint32_t	sign_on_state;						//	0x0108
	char		pad_010C[8];						//	0x010C
	float		next_cmd_time;						//	0x0114
	uint32_t	server_count;						//	0x0118
	uint32_t	current_sequence;					//	0x011C
	char		pad_0120[8];						//	0x0120
	char		pad_0128[80];						//	0x0128
	uint32_t	delta_tick;							//	0x0178
	bool		paused;								//	0x017C
	char		pad_017D[3];						//	0x017D
	uint32_t	view_entity;						//	0x0180
	uint32_t	player_slot;						//	0x0184
	char		level_name[260];					//	0x0188
	char		level_name_short[40];				//	0x028C
	char		group_name[40];						//	0x02B4
	char		pad_02DC[52];						//	0x02DC
	uint32_t	max_clients;						//	0x0310
	char		pad_0314[18820];					//	0x0314
	float		last_server_tick_time;				//	0x4C98
	bool		in_simulation;						//	0x4C9C
	char		pad_4C9D[3];						//	0x4C9D
	uint32_t	old_tick_count;						//	0x4CA0
	float		tick_remainder;						//	0x4CA4
	float		frame_time;							//	0x4CA8
	uint32_t	mlast_outgoing_command;				//	0x4CAC
	uint32_t	choked_commands;					//	0x4CB0
	uint32_t	last_acknowledged_command;			//	0x4CB4
	uint32_t	command_acknowledged;				//	0x4CB8
	uint32_t	sound_sequence;						//	0x4CBC
	char		pad_4CC0[80];						//	0x4CC0
	vector		view_angles;						//	0x4D10
}; 

#endif // !CHLCLIENT_H

#ifndef IVENGINECLIENT_H
#define IVENGINECLIENT_H
#ifdef _WIN32
#pragma once
#endif

typedef struct player_info_s
{
	__int64				unknown;			//0x0000 
	union
	{
		__int64			steamid64;			//0x0008 - SteamID64
		struct
		{
			__int32     xuidlow;
			__int32     xuidhigh;
		};
	};
	char            name[128];				//0x0010 - Player Name
	int             user_id;				//0x0090 - Unique Server Identifier
	char            sz_steam_id[20];		//0x0094 - STEAM_X:Y:Z
	char            pad_0x00A8[0x10];		//0x00A8
	unsigned long   steam_id;				//0x00B8 - SteamID 
	char            friends_name[128];
	bool            fakeplayer;
	bool            ishltv;
	unsigned int    custom_files[4];
	unsigned char   files_downloaded;
} player_info_t;

class ivengineclient
{
public:

	int get_local_player()
	{
		using original_fn = int(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 12)(this);
	}

	bool is_in_game()
	{
		using original_fn = bool(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 26)(this);
	}

	bool is_connected()
	{
		using original_fn = bool(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 27)(this);
	}

	bool get_player_info(int i, player_info_t* info)
	{
		using original_fn = bool(__thiscall*)(PVOID, int, player_info_t*);
		return u::call_vfunc<original_fn>(this, 8)(this, i, info);
	}

	void get_view_angles(vector& ang)
	{
		using original_fn = void(__thiscall*)(PVOID, vector&);
		u::call_vfunc<original_fn>(this, 18)(this, ang);
	}

	void set_view_angles(vector& ang)
	{
		using original_fn = void(__thiscall*)(PVOID, vector&);
		u::call_vfunc<original_fn>(this, 19)(this, ang);
	}

	void get_screen_size(int& width, int& height)
	{
		using original_fn = void(__thiscall*)(PVOID, int&, int&);
		return u::call_vfunc<original_fn>(this, 5)(this, width, height);
	}

	inetchannel* get_net_channel()
	{
		using original_fn = inetchannel*(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 78)(this);
	}

	inetchannelinfo* get_net_channel_info()
	{
		using original_fn = inetchannelinfo*(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 78)(this);
	}

	bool is_voice_recordering()
	{
		using original_fn = bool(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 224)(this);
	}

	void execute_client_cmd(const char* cmd)
	{
		using original_fn = void(__thiscall*)(PVOID, const char*);
		return u::call_vfunc<original_fn>(this, 108)(this, cmd);
	}

	void client_cmd_unrestricted(const char* cmd)
	{
		using original_fn = void(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 114)(this);
	}

	int get_player_for_user_id(int id)
	{
		using original_fn = int(__thiscall*)(PVOID, int);
		return u::call_vfunc<original_fn>(this, 9)(this, id);
	}

};

#endif // !IVENGINECLIENT_H

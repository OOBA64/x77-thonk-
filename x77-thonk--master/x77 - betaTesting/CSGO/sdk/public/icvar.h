#ifndef ICVAR_H
#define ICVAR_H
#ifdef _WIN32
#pragma once
#endif

// ConVar Systems
#define FCVAR_UNREGISTERED		(1<<0)	// If this is set, don't add to linked list, etc.
#define FCVAR_DEVELOPMENTONLY	(1<<1)	// Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined.
#define FCVAR_GAMEDLL			(1<<2)	// defined by the game DLL
#define FCVAR_CLIENTDLL			(1<<3)  // defined by the client DLL
#define FCVAR_HIDDEN			(1<<4)	// Hidden. Doesn't appear in find or autocomplete. Like DEVELOPMENTONLY, but can't be compiled out.

// ConVar only
#define FCVAR_PROTECTED			(1<<5)  // It's a server cvar, but we don't send the data since it's a password, etc.  Sends 1 if it's not bland/zero, 0 otherwise as value
#define FCVAR_SPONLY			(1<<6)  // This cvar cannot be changed by clients connected to a multiplayer server.
#define	FCVAR_ARCHIVE			(1<<7)	// set to cause it to be saved to vars.rc
#define	FCVAR_NOTIFY			(1<<8)	// notifies players when changed
#define	FCVAR_USERINFO			(1<<9)	// changes the client's info string
#define FCVAR_CHEAT				(1<<14) // Only useable in singleplayer / debug / multiplayer & sv_cheats

#define FCVAR_PRINTABLEONLY		(1<<10)  // This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
#define FCVAR_UNLOGGED			(1<<11)  // If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log
#define FCVAR_NEVER_AS_STRING	(1<<12)  // never try to print that cvar

// It's a ConVar that's shared between the client and the server.
// At signon, the values of all such ConVars are sent from the server to the client (skipped for local
//  client, of course )
// If a change is requested it must come from the console (i.e., no remote client changes)
// If a value is changed while a server is active, it's replicated to all connected clients
#define FCVAR_REPLICATED		(1<<13)	// server setting enforced on clients, TODO rename to FCAR_SERVER at some time
#define FCVAR_DEMO				(1<<16)  // record this cvar when starting a demo file
#define FCVAR_DONTRECORD		(1<<17)  // don't record these command in demofiles
#define FCVAR_RELOAD_MATERIALS	(1<<20)	// If this cvar changes, it forces a material reload
#define FCVAR_RELOAD_TEXTURES	(1<<21)	// If this cvar changes, if forces a texture reload

#define FCVAR_NOT_CONNECTED				(1<<22)	// cvar cannot be changed by a client that is connected to a server
#define FCVAR_MATERIAL_SYSTEM_THREAD	(1<<23)	// Indicates this cvar is read from the material system thread
#define FCVAR_ARCHIVE_XBOX				(1<<24)	// cvar written to config.cfg on the Xbox

#define FCVAR_ACCESSIBLE_FROM_THREADS	(1<<25)	// used as a debugging tool necessary to check material system thread convars

#define FCVAR_SERVER_CAN_EXECUTE	(1<<28)		// the server is allowed to execute this command on clients via ClientCommand/NET_StringCmd/CBaseClientState::ProcessStringCmd.
#define FCVAR_SERVER_CANNOT_QUERY	(1<<29)		// If this is set, then the server is not allowed to query this cvar's value (via IServerPluginHelpers::StartQueryCvarValue).
#define FCVAR_CLIENTCMD_CAN_EXECUTE	(1<<30)		// IVEngineClient::ClientCmd is allowed to execute this command. 
												// Note: IVEngineClient::ClientCmd_Unrestricted can run any client command.

class iappsystem
{
public:
	virtual ~iappsystem()
	{
	}

	virtual void func0() = 0;
	virtual void func1() = 0;
	virtual void func2() = 0;
	virtual void func3() = 0;
	virtual void func4() = 0;
	virtual void func5() = 0;
	virtual void func6() = 0;
	virtual void func7() = 0;
	virtual void func8() = 0;
	virtual void func9() = 0;
};

class convar
{
public:

	void set_value(const char* name)
	{
		using original_fn = void(__thiscall*)(PVOID, const char*);
		return u::call_vfunc<original_fn>(this, 14)(this, name);
	}

	void set_value(float value)
	{
		using original_fn = void(__thiscall*)(PVOID, float);
		return u::call_vfunc<original_fn>(this, 15)(this, value);
	}

	void set_value(int value)
	{
		using original_fn = void(__thiscall*)(PVOID, int);
		return u::call_vfunc<original_fn>(this, 16)(this, value);
	}

	char* get_base_name()
	{
		using original_fn = char*(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 6)(this);
	}

	float get_float()
	{
		using original_fn = float(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 12)(this);
	}

	int get_int(void) const {
		return parent->nvalue;
	}

	const char* GetString(void) const {
		return parent->default_value;
	}

	char	pad_0x0000[0x4];	// 0x0000
	convar* next;				// 0x0004 
	__int32 registered;			// 0x0008 
	char*	name;				// 0x000C 
	char*	help_string;		// 0x0010 
	__int32 flags;				// 0x0014 
	char	pad_0x0018[0x4];	// 0x0018
	convar* parent;				// 0x001C 
	char*	default_value;		// 0x0020 
	char*	string;				// 0x0024 
	__int32 string_length;		// 0x0028 
	float	fvalue;				// 0x002C 
	__int32 nvalue;				// 0x0030 
	__int32 has_min;			// 0x0034 
	float	min_val;			// 0x0038 
	__int32 has_max;			// 0x003C 
	float	max_val;			// 0x0040 
	PVOID	change_callback;	// 0x0044 

};

class icvar : public iappsystem
{
public:
	virtual void			func10() = 0;
	virtual void			register_con_command(convar* pCommandBase) = 0;
	virtual void			unregister_con_command(convar* pCommandBase) = 0;
	virtual void			func13() = 0;
	virtual convar*			find_var(const char* var_name) = 0;
	virtual void			func15() = 0;
	virtual void			func16() = 0;
	virtual void			func17() = 0;
	virtual void			func18() = 0;
	virtual void			func19() = 0;
	virtual void			func20() = 0;
};

#endif // !ICVAR_H
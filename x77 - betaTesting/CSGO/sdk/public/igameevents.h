#ifndef IGAMEEVENTS_H
#define IGAMEEVENTS_H
#ifdef _WIN32
#pragma once
#endif

class igameevent
{
public:
	virtual ~igameevent() {};
	virtual const char*			get_name() const																		= 0;
	virtual bool				is_reliable() const																		= 0;
	virtual bool				is_local() const																		= 0;
	virtual bool				is_empty(const char* key_name = NULL)													= 0;
	virtual bool				get_bool(const char* key_name = NULL, bool default_value = false)						= 0;
	virtual int					get_int(const char* key_name = NULL, int default_value = 0)								= 0;
	virtual unsigned long long	get_unsigned_int64(char const* key_name = NULL, unsigned long long default_value = 0)	= 0;
	virtual float				get_float(const char* key_name = NULL, float default_value = 0.0f)						= 0;
	virtual const char*			get_string(const char* key_name = NULL, const char* default_value = "")					= 0;
	virtual const wchar_t*		get_w_string(char const* key_name = NULL, const wchar_t* default_value = L"")			= 0;
	virtual void				set_bool(const char* key_name, bool value)												= 0;
	virtual void				set_int(const char* key_name, int value)												= 0;
	virtual void				set_unsigned_int64(const char* key_name, unsigned long long value)						= 0;
	virtual void				set_float(const char* key_name, float value)											= 0;
	virtual void				set_sring(const char* key_name, const char* value)										= 0;
	virtual void				set_w_string(const char* key_name, const wchar_t* value)								= 0;
};

class cevent
{
public:
	uint8_t	__pad0[4];
	float	delay;
	uint8_t	__pad1[48];
	cevent*	next;
};

class igameeventlistener
{
public:
	virtual ~igameeventlistener() {}
	virtual void fire_game_event(igameevent* event) = 0;

	virtual int get_event_debug_id()
	{
		return 42;
	}
};

class igameeventmanager
{
public:
	virtual int			__unkw1(int* unknown)															= 0;
	virtual int			load_events_from_file(const char* filename)										= 0;
	virtual void		reset()																			= 0;
	virtual bool		add_listener(igameeventlistener* listener, const char* name, bool server_side)	= 0;
	virtual bool		find_listener(igameeventlistener* listener, const char* name)					= 0;
	virtual int			remove_listener(igameeventlistener* listener)									= 0;
	virtual igameevent* create_event(const char* name, bool force, unsigned int unknown)				= 0;
	virtual bool		fire_event(igameevent* event, bool dont_broadcast = false)						= 0;
	virtual bool		fire_event_client_side(igameevent* event)										= 0;
	virtual igameevent* duplicate_event(igameevent* event)												= 0;
	virtual void		free_event(igameevent* event)													= 0;
	virtual bool		serialize_event(igameevent* event, bf_write* buf)								= 0;
	virtual igameevent* unserialize_event(bf_read* buf)													= 0;
};

#endif // !IGAMEEVENTS_H
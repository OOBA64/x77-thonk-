#ifndef HOOKS_H
#define HOOKS_H
#ifdef _WIN32
#pragma once
#endif

class events
{

	class player_hurt_listener
		: public igameeventlistener
	{
	public:
		void start();
		void stop();

		void fire_game_event(igameevent* event) override
		{
			events::singleton()->on_fire_event(event);
		}

		int get_event_debug_id(void) override
		{
			return 42;
		}

	};

public:

	static events* singleton()
	{
		static events* instance = new events;
		return instance;
	}

	void initialize()
	{
		_listener.start();
	}

	void on_fire_event(igameevent* event);

private:
	player_hurt_listener _listener;
};

namespace h
{

	extern std::unique_ptr<vmt_hook> client_mode_hook;
	extern std::unique_ptr<vmt_hook> client_hook;
	extern std::unique_ptr<vmt_hook> panel_hook;
	extern std::unique_ptr<vmt_hook> model_hook;
	extern std::unique_ptr<vmt_hook> data_hook;

}

#endif // !HOOKS_H
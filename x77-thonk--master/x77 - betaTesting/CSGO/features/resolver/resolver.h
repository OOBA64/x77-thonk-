#ifndef RESOLVER_H
#define RESOLVER_H
#ifdef _WIN32
#pragma once
#endif

extern std::vector<std::pair<c_baseentity*, vector>> player_data;;

namespace resolver
{
	extern bool is_fake_ducking(c_baseentity* entity);
	extern void resolver(client_frame_stage_t stage = FRAME_NET_UPDATE_POSTDATAUPDATE_START);
}

#endif // !RESOLVER_H
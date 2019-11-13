#ifndef AIMBOT_H
#define AIMBOT_H
#ifdef _WIN32
#pragma once
#endif 

namespace a
{
	extern void do_auto_revolver();
	extern void	do_aimbot();
	extern void do_auto_stop();
	extern int	get_target();
	extern int	get_hitboxes(c_baseentity* target);
}

#endif // !AIMBOT_H
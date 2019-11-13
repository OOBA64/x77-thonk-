#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#ifdef _WIN32
#pragma once
#endif

class iinputsystem
{
public:

	bool is_button_down(buttoncode_t code)
	{
		using original_fn = bool(__thiscall*)(PVOID, buttoncode_t);
		return u::call_vfunc<original_fn>(this, 15)(this, code);
	}


};

#endif // !INPUTSYSTEM_H
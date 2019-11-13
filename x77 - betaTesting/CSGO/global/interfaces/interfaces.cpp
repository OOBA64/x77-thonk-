#include "../../main.h"

namespace i
{

	// client
	chlclient*				client{};
	icliententitylist*		entitylist{};
	iclientmodeshared*		clientmode{};
	glow_object_manager*	glow_manager{};
	cinput*					input{};

	// datacache
	imdlcache*				mdlcache{};

	// engine
	ivengineclient*			engineclient{};
	ivdebugoverlay*			debugoverlay{};
	ienginetrace*			enginetrace{};
	ienginevgui*			enginevgui{};
	client_state*			clientstate{};
	imodelrender*			modelrender{};
	ivmodelinfo*			modelinfo{};

	// vphysics
	iphysicssurfaceprops*	surfaceprops{};

	// public
	ivrenderview*			renderview;
	igameeventmanager*		eventmgr{};
	iinputsystem*			inputsystem{};
	global_vars_base*		globals{};
	icvar*					cvar{};

	// vgui
	isurface*				surface{};
	ipanel*					panel{};

}
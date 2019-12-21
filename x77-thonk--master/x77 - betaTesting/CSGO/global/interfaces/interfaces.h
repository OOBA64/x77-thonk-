#ifndef INTERFACES_H
#define INTERFACES_H
#ifdef _WIN32
#pragma once
#endif

namespace i
{

	// client
	extern chlclient*				client;
	extern icliententitylist*		entitylist;
	extern iclientmodeshared*		clientmode;
	extern glow_object_manager*		glow_manager;
	extern cinput*					input;

	// datacache
	extern imdlcache*				mdlcache;

	// engine
	extern ivengineclient*			engineclient;
	extern ivdebugoverlay*			debugoverlay;
	extern ienginetrace*			enginetrace;
	extern ienginevgui*				enginevgui;
	extern client_state*			clientstate;
	extern imodelrender*			modelrender;
	extern ivmodelinfo*				modelinfo;

	// vphysics
	extern iphysicssurfaceprops*	surfaceprops;

	// public
	extern ivrenderview*			renderview;
	extern igameeventmanager*		eventmgr;
	extern iinputsystem*			inputsystem;
	extern global_vars_base*		globals;
	extern icvar*					cvar;

	// vgui
	extern isurface*				surface;
	extern ipanel*					panel;

}

#endif // !INTERFACES_H
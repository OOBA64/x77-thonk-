#ifndef SDK_H
#define SDK_H
#ifdef _WIN32
#pragma once
#endif

// forward declarations
class	iworldrenderlist;
class	imaterial;
struct	cvar_dll_identifier_t;
class	imatrendercontext;
class	client_networkable;
class	client_renderable;
class	client_unknown;
struct	virtualmodel_t;
class	client_entity;
class	client_class;
class	c_baseentity;
struct	studiohdr_t;
struct	vcollide_t;
class	base_weapon;
class	inetchannel;
class	cstudiohdr;
class	game_trace;
class	view_setup;
class	imaterial;
class	bf_write;
class	bf_read;
struct	model_t;
struct	studiohwdata_t;

// type definitions
typedef client_networkable* (*create_client_class_fn)(int ent, int serial);
typedef PVOID				(*create_interface_fn)(const char* name, int* return_code);
typedef unsigned short		model_instance_handle_t;
typedef client_networkable* (*create_event_fn)();
typedef unsigned short		materialhandle_t;
typedef unsigned short		mdlhandle_t;
typedef float				matrix3x4_t[3][4];
typedef game_trace			trace_t;

#pragma region includes

// dt
#include "public/dt_recv.h"
#include "public/dt_common.h"

// misc
#include "misc/checksum_crc.h"
#include "misc/checksum_md5.h"

// client
#include "client/icliententitylist.h"
#include "client/iclientmodeshared.h"
#include "client/chlclient.h"
#include "client/c_baseentity/c_baseentity.h"
#include "client/user_cmd.h"
#include "client/glow_outline_effect.h"
#include "client/input.h"

// datacache
#include "datacache/imdlcache.h"

// public
#include "public/client_frame_stage.h"
#include "public/global_vars_base.h"
#include "public/ivrenderview.h"
#include "public/igameevents.h"
#include "public/inetchannel.h"
#include "public/buttoncode.h"
#include "public/inputsystem.h"
#include "public/bspflags.h"
#include "public/studio.h"
#include "public/icvar.h"

// engine
#include "engine/ivengineclient.h"
#include "engine/ivdebugoverlay.h"
#include "engine/ienginetrace.h"
#include "engine/ienginevgui.h"
#include "engine/ivmodelinfo.h"

// vgui
#include "vgui/isurface.h"
#include "vgui/ipanel.h"

#pragma endregion

#endif // !SDK_H
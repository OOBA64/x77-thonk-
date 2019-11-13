#ifndef IMDLCACHE_H
#define IMDLCACHE_H
#ifdef _WIN32
#pragma once
#endif

enum
{
	MDLHANDLE_INVALID = (mdlhandle_t)~0
};

enum mdlcachedatatype_t
{
	// Callbacks to get called when data is loaded or unloaded for these:
	MDLCACHE_STUDIOHDR = 0,
	MDLCACHE_STUDIOHWDATA,
	MDLCACHE_VCOLLIDE,

	// Callbacks NOT called when data is loaded or unloaded for these:
	MDLCACHE_ANIMBLOCK,
	MDLCACHE_VIRTUALMODEL,
	MDLCACHE_VERTEXES,
	MDLCACHE_DECODEDANIMBLOCK,
};

class imdlcache{};

#endif // !IMDLCACHE_H
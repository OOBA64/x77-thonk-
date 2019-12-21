#ifndef STUDIO_H
#define STUDIO_H
#ifdef _WIN32
#pragma once
#endif

typedef float quaternion[4];
typedef float radian_euler[3];

#define BONE_CALCULATE_MASK             0x1F
#define BONE_PHYSICALLY_SIMULATED       0x01
#define BONE_PHYSICS_PROCEDURAL         0x02
#define BONE_ALWAYS_PROCEDURAL          0x04
#define BONE_SCREEN_ALIGN_SPHERE        0x08 
#define BONE_SCREEN_ALIGN_CYLINDER      0x10

#define BONE_USED_MASK                  0x0007FF00
#define BONE_USED_BY_ANYTHING           0x0007FF00
#define BONE_USED_BY_HITBOX             0x00000100
#define BONE_USED_BY_ATTACHMENT         0x00000200
#define BONE_USED_BY_VERTEX_MASK        0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0        0x00000400
#define BONE_USED_BY_VERTEX_LOD1        0x00000800    
#define BONE_USED_BY_VERTEX_LOD2        0x00001000  
#define BONE_USED_BY_VERTEX_LOD3        0x00002000
#define BONE_USED_BY_VERTEX_LOD4        0x00004000
#define BONE_USED_BY_VERTEX_LOD5        0x00008000
#define BONE_USED_BY_VERTEX_LOD6        0x00010000
#define BONE_USED_BY_VERTEX_LOD7        0x00020000
#define BONE_USED_BY_BONE_MERGE         0x00040000

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define MAX_NUM_LODS 8
#define MAXSTUDIOBONES		128		// total bones actually used

#define BONE_TYPE_MASK                  0x00F00000
#define BONE_FIXED_ALIGNMENT            0x00100000    // bone can't spin 360 degrees, all interpolation is normalized around a fixed orientation

#define BONE_HAS_SAVEFRAME_POS          0x00200000    // Vector48
#define BONE_HAS_SAVEFRAME_ROT64        0x00400000    // Quaternion64
#define BONE_HAS_SAVEFRAME_ROT32        0x00800000    // Quaternion32

#define HITGROUP_GENERIC 0
#define HITGROUP_HEAD 1
#define HITGROUP_CHEST 2
#define HITGROUP_STOMACH 3
#define HITGROUP_LEFTARM 4    
#define HITGROUP_RIGHTARM 5
#define HITGROUP_LEFTLEG 6
#define HITGROUP_RIGHTLEG 7
#define HITGROUP_GEAR 10

enum modtype_t
{
	mod_bad = 0,
	mod_brush,
	mod_sprite,
	mod_studio
};

enum hitboxes
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_PELVIS,
	HITBOX_STOMACH,
	HITBOX_LOWER_CHEST,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};

struct mstudiobone_t
{
	int						nameindex;
	inline char* const		name(void) const { return ((char*)this) + nameindex; }
	int						parent;
	int						bonecontroller[6];
	vector					pos;
	quaternion				quat;
	radian_euler			rot;

	// compression scale
	vector	posscale;
	vector	rotscale;

	matrix3x4_t				posetobone;
	quaternion				alignment;
	int						flags;
	int						proctype;
	int						procindex;
	mutable int				physicsbone;
	inline PVOID			procedure() const { if (procindex == 0) return NULL; else return  (void*)(((byte*)this) + procindex); };
	int						surfacepropidx;
	inline char* const		surface_prop(void) const { return ((char*)this) + surfacepropidx; }
	inline int				get_surface_prop(void) const { return surface_prop_lookup; }

	int	contents;
	int	surface_prop_lookup;
	int	__pad01[7];

	mstudiobone_t() {}
private:
	mstudiobone_t(const mstudiobone_t& vOther);
};

struct mstudiobbox_t
{
	int		bone;
	int		group;
	vector	bbmin;
	vector	bbmax;
	int		szhitboxnameindex;
	int32_t	__pad01[3];
	float	radius;
	int32_t	__pad02[4];

	const char* get_name()
	{
		if (!szhitboxnameindex) return nullptr;
		return (const char*)((uint8_t*)this + szhitboxnameindex);
	}
};

struct mstudiohitboxset_t
{
	int	sznameindex;
	int	numhitboxes;
	int	hitboxindex;

	const char* get_name()
	{
		if (!sznameindex) return nullptr;
		return (const char*)((uint8_t*)this + sznameindex);
	}

	mstudiobbox_t* get_hitbox(int i)
	{
		if (i > numhitboxes) return nullptr;
		return (mstudiobbox_t*)((uint8_t*)this + hitboxindex) + i;
	}
};

struct model_t
{
	PVOID	handle;			//0x0000 
	char    name[260];		//0x0004 
	__int32 load_flags;		//0x0108 
	__int32 server_count;	//0x010C 
	__int32 type;			//0x0110 
	__int32 flags;			//0x0114 
	vector  mins;			//0x0118 
	vector  maxs;			//0x0124 
	float   radius;			//0x0130 
	char    pad[0x1C];		//0x0134
}; //Size=0x0150

class studiohdr_t
{
public:
	__int32 id;                     //0x0000 
	__int32 version;                //0x0004 
	long    checksum;               //0x0008 
	char    name[64];             //0x000C 
	__int32 length;                 //0x004C 
	vector  eye_pos;				//0x0050 
	vector  illum_pos;				//0x005C 
	vector  hul_min;				//0x0068 
	vector  hull_max;				//0x0074 
	vector  min;					//0x0080 
	vector  max;					//0x008C 
	__int32 flags;                  //0x0098 
	__int32 numbones;               //0x009C 
	__int32 boneindex;              //0x00A0 
	__int32 numbonecontrollers;     //0x00A4 
	__int32 bonecontrollerindex;    //0x00A8 
	__int32 numhitboxsets;          //0x00AC 
	__int32 hitboxsetindex;         //0x00B0 
	__int32 numlocalanim;           //0x00B4 
	__int32 localanimindex;         //0x00B8 
	__int32 numlocalseq;            //0x00BC 
	__int32 localseqindex;          //0x00C0 
	__int32 activitylistversion;    //0x00C4 
	__int32 eventsindexed;          //0x00C8 
	__int32 numtextures;            //0x00CC 
	__int32 textureindex;           //0x00D0

	mstudiohitboxset_t* get_hitbox_set(int i)
	{
		if (i > numhitboxsets) return nullptr;
		return (mstudiohitboxset_t*)((uint8_t*)this + hitboxsetindex) + i;
	}

	mstudiobone_t* get_bone(int i)
	{
		if (i > numbones) return nullptr;
		return (mstudiobone_t*)((uint8_t*)this + boneindex) + i;
	}

};//Size=0x00D4

#endif // !STUDIO_H
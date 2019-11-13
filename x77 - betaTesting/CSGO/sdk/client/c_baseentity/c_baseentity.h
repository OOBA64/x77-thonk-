#ifndef C_BASEENTITY_H
#define C_BASEENTITY_H
#ifdef _WIN32
#pragma once
#endif

enum movetype_t
{

	MOVETYPE_NONE = 0,		// never moves
	MOVETYPE_ISOMETRIC,		// For players -- in TF2 commander view, etc.
	MOVETYPE_WALK,			// Player only - moving on the ground
	MOVETYPE_STEP,			// gravity, special edge handling -- monsters use this
	MOVETYPE_FLY,			// No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY,	// flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS,		// uses VPHYSICS for simulation
	MOVETYPE_PUSH,			// no clip to world, push and crush
	MOVETYPE_NOCLIP,		// No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER,		// Used by players only when going onto a ladder
	MOVETYPE_OBSERVER,		// Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM,		// Allows the entity to describe its own physics

	// should always be defined as the last item in the list
	MOVETYPE_LAST = MOVETYPE_CUSTOM,

	MOVETYPE_MAX_BITS = 4

};

enum item_definition_index
{
	WEAPON_INVALID = -1,
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_MP5 = 23,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516,
	WEAPON_KNIFE_GYPSY = 520,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_WIDOWMAKER = 523,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA = 5035
};

enum classid_t {
	CAI_BaseNPC = 0,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBRC4Target,
	CBreachCharge,
	CBreachChargeProjectile,
	CBreakableProp,
	CBreakableSurface,
	CBumpMine,
	CBumpMineProjectile,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDangerZone,
	CDangerZoneController,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDrone,
	CDronegun,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvGasCanister,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFists,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CGrassBurn,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoMapRegion,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CItemCash,
	CItemDogtags,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMaterialModifyControl,
	CMelee,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParadropChopper,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPhysPropAmmoBox,
	CPhysPropLootCrate,
	CPhysPropRadarJammer,
	CPhysPropWeaponUpgrade,
	CPlantedC4,
	CPlasma,
	CPlayerPing,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropCounter,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSnowball,
	CSnowballPile,
	CSnowballProjectile,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CSurvivalSpawnChopper,
	CTablet,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponShield,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWorld,
	CWorldVguiText,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail,
};

struct c_animstate 
{
	char			pad_0x0000[0x28];				//0x0000
	float_t			time_moving;					//0x0028
	char			pad_0x002C[0x30];				//0x002C
	base_weapon*	weapon;							//0x005C
	c_baseentity*	entity;							//0x0060
	base_weapon*	active_weapon;					//0x0064 
	base_weapon*	last_active_weapon;				//0x0068 
	float_t			unknown_timer;					//0x006C 
	float			last_animation_sate_clear_time;
	char			pad_0x0074[0x4];				//0x0074
	float_t			eye_yaw;						//0x0078 
	float_t			eye_pitch;						//0x007C 
	float_t			goal_feet_yaw;					//0x0080
	float_t			current_feet_yaw;				//0x0084 
	bool			current_feet_yaw_initialized;	//0x0088 
	float_t			last_move_yaw;					//0x008C
	char			pad_0x0090[0x5C];				//0x0090
	float			velocity;
};

class animation_layer
{
public:
	char		pad_0000[20];
	uint32_t	order; //0x0014
	uint32_t	sequence; //0x0018
	float_t		prev_cycle; //0x001C
	float_t		weight; //0x0020
	float_t		weight_delta_rate; //0x0024
	float_t		playerback_rate; //0x0028
	float_t		cycle; //0x002C
	void*		owner; //0x0030 // player's thisptr
	char		pad_0038[4]; //0x0034
};

enum life_states
{
	LIFE_ALIVE,
	LIFE_DYING,
	LIFE_DEAD,
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY,
};

class c_baseentity
{
public:

	PVOID get_client_renderable()
	{
		return reinterpret_cast<PVOID>(uintptr_t(this) + 0x4);
	}

	PVOID get_client_networkable()
	{
		return reinterpret_cast<PVOID>(uintptr_t(this) + 0x8);
	}

	PVOID get_collideable()
	{
		using original_fn = PVOID(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 3)(this);
	}

	int get_flags()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0x104); // m_fFlags
	}

	int get_tick_base()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0x342C); // m_nTickBase
	}

	void set_flags(int flags)
	{
		*reinterpret_cast<int*>(uintptr_t(this) + 0x104) = flags;
	}

	bool setup_bones(matrix3x4_t* out, int max_bones, int bone_mask, float current_time)
	{

		PVOID renderable = get_client_renderable();

		if (!renderable)
			return false;

		using original_fn = bool(__thiscall*)(PVOID, matrix3x4_t*, int, int, float);
		return u::call_vfunc<original_fn>(renderable, 13)(renderable, out, max_bones, bone_mask, current_time);

	}

	bool is_immune() {
		return *reinterpret_cast<bool*>(uintptr_t(this) + 0x392C);
	}

	c_animstate* get_anim_state()
	{
		return *reinterpret_cast<c_animstate**>(uintptr_t(this) + 0x3900);
	}

	animation_layer& get_anim_overlay(int index)
	{
		return (*(animation_layer**)((DWORD)this + 0x2980))[index];
	}

	int get_health()
	{
		using original_fn = int(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 121)(this);
	}
	
	client_class* get_client_class()
	{
		using original_fn = client_class*(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(get_client_networkable(), 2)(get_client_networkable());
	}

	vector get_velocity()
	{
		return *reinterpret_cast<vector*>(uintptr_t(this) + 0x114);
	}

	model_t* get_model()
	{
		PVOID renderable = get_client_renderable();

		using original_fn = model_t*(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(renderable, 8)(renderable);
	}

	DWORD get_observer_target()
	{
		return (DWORD)this + 0x3388; // m_hObserverTarget
	}

	int get_max_health()
	{
		using original_fn = int(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 122)(this);
	}

	float get_lower_body_yaw()
	{
		return *reinterpret_cast<float*>(uintptr_t(this) + 0x3A78); // m_flLowerBodyYawTarget
	}

	int get_crosshair_index()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0xB3AC); // m_iCrosshairID
	}

	BYTE get_life_state()
	{
		return *reinterpret_cast<BYTE*>(uintptr_t(this) + 0x25F); // m_lifeState
	}

	int get_money()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0xB32C); // m_iAccount
	}

	int get_armor()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0xB340); // m_ArmorValue
	}

	bool has_helmet()
	{
		return *reinterpret_cast<bool*>(uintptr_t(this) + 0xB334); // m_bHasHelmet
	}

	float get_duck_amount()
	{
		return *reinterpret_cast<float*>(uintptr_t(this) + 0x2FAC); // m_flDuckAmount
	}

	float get_duck_speed()
	{
		return *reinterpret_cast<float*>(uintptr_t(this) + 0x2FB0); // m_flDuckSpeed
	}

	vector get_eye_angles()
	{
		return *reinterpret_cast<vector*>(uintptr_t(this) + 0xB344); // m_angEyeAngles[0]
	}

	vector* get_eye_angles_ptr()
	{
		return reinterpret_cast<vector*>(uintptr_t(this) + 0xB344); // m_angEyeAngles[0]
	}

	const char* get_armor_name()
	{
		if (get_armor() > 0) {
			if (has_helmet())
				return "HK";
			else
				return "K";
		} else {
			return " ";
		}
	}

	int get_team_num()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0xF4); // m_iTeamNum
	}

	bool is_scoped()
	{
		return *reinterpret_cast<bool*>(uintptr_t(this) + 0x3910); // m_bIsScoped
	}

	movetype_t get_move_type()
	{
		return *reinterpret_cast<movetype_t*>(uintptr_t(this) + 0x25C); // m_nMoveType
	}

	int get_index()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0x64);
	}

	int get_shots_fired()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0xA370); // m_iShotsFired
	}

	bool is_dormant()
	{
		using original_fn = bool(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(get_client_networkable(), 9)(get_client_networkable());
	}

	vector get_aim_punch_angle()
	{
		return *reinterpret_cast<vector*>(uintptr_t(this) + 0x302C); // m_aimPunchAngle
	}

	vector get_view_punch_angle()
	{
		return *reinterpret_cast<vector*>(uintptr_t(this) + 0x3020); // m_viewPunchAngle
	}

	vector& get_abs_origin()
	{
		using original_fn = vector&(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 10)(this);
	}

	vector& estimate_abs_velocity(vector vel)
	{
		using original_fn = vector&(__thiscall*)(PVOID, vector);
		return u::call_vfunc<original_fn>(this, 142)(this, vel);
	}

	bool is_freeze_period()
	{
		return *reinterpret_cast<bool*>(uintptr_t(this) + 0x20); // m_bFreezePeriod 
	}

	vector get_origin()
	{
		return *reinterpret_cast<vector*>(uintptr_t(this) + 0x138); // m_vecOrigin
	}

	vector get_view_offset()
	{
		return *reinterpret_cast<vector*>(uintptr_t(this) + 0x108); // m_vecViewOffset
	}

	vector& get_collideable_mins()
	{
		using original_fn = vector & (__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(get_collideable(), 1)(get_collideable());
	}

	vector& get_collideable_maxs()
	{
		using original_fn = vector & (__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(get_collideable(), 2)(get_collideable());
	}

	vector get_eye_position()
	{
		return *reinterpret_cast<vector*>(uintptr_t(this) + 0x108) + get_abs_origin(); // m_vecViewOffset[0]
	}

	float get_max_desync_delta()
	{

		auto animstate = uintptr_t(this->get_anim_state());

		float duckamount = *(float*)(animstate + 0xA4);

		float speedfraction = max(0, min(*reinterpret_cast<float*>(animstate + 0xF8), 1));
		float speedfactor	= max(0, min(1, *reinterpret_cast<float*> (animstate + 0xFC)));

		float unk1 = ((*reinterpret_cast<float*> (animstate + 0x11C) * -0.30000001) - 0.19999999) * speedfraction;
		float unk2 = unk1 + 1.f;
		float unk3;

		if (duckamount > 0)
			unk2 += ((duckamount * speedfactor) * (0.5f - unk2));

		unk3 = *(float*)(animstate + 0x334) * unk2;

		return unk3;

	}

	vector get_bone_position(int bone);

	base_weapon* get_active_weapon();

	int get_sequence_activity(int sequence);

};

class weapon_info {
public:
	int8_t	pad0[20];
	int32_t max_clip1;
	int8_t	pad1[12];
	int32_t max_reserved_ammo;
	int8_t	pad2[96];
	char*	hud_name;
	char*	weapon_name;
	int8_t	pad3[56];
	int32_t weapon_type;
	int8_t	pad4[4];
	int32_t weapon_price;
	int32_t kill_award;
	int8_t	pad5[20];
	uint8_t full_auto;
	int8_t	pad6[3];
	int32_t damage;
	float_t armor_ratio;
	int32_t bullets;
	float_t penetration;
	int8_t	pad7[8];
	float_t range;
	float_t range_modifier;
	int8_t	pad8[16];
	uint8_t has_silencer;
	int8_t	pad9[15];
	float_t spread;
	float_t spread_alt;
	int8_t	pad10[76];
	int32_t recoil_seed;
	int8_t	pad11[32];
};

enum weapon_type
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};

class base_weapon : public c_baseentity
{
public:

	short item_definition_index()
	{
		return *reinterpret_cast<short*>(uintptr_t(this) + 0x2FAA); // m_iItemDefinitionIndex
	}

	float next_primary_attack()
	{
		return *reinterpret_cast<float*>(uintptr_t(this) + 0x3218); // m_flNextPrimaryAttack
	}

	float get_fire_ready_time()
	{
		return *reinterpret_cast<float*>(uintptr_t(this) + 0x3328); // m_flPostponeFireReadyTime
	}

	float get_accuracy_penalty()
	{
		return *reinterpret_cast<float*>(uintptr_t(this) + 0x3310); // m_fAccuracyPenalty
	}

	int clip1()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0x3244); // m_iClip1
	}

	bool is_reloading()
	{
		static auto in_reload = *(uint32_t*)(u::find_signature("client_panorama.dll", "C6 87 ? ? ? ? ? 8B 06 8B CE FF 90") + 2);
		return *(bool*)((uintptr_t)this + in_reload);
	}

	weapon_info* get_cs_wpn_info() 
	{
		using original_fn = weapon_info*(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 456)(this);
	}

	bool is_gun()
	{
		switch (get_cs_wpn_info()->weapon_type) {
		case WEAPONTYPE_C4:
			return false;
		case WEAPONTYPE_GRENADE:
			return false;
		case WEAPONTYPE_KNIFE:
			return false;
		case WEAPONTYPE_UNKNOWN:
			return false;
		default:
			return true;
		}
	}

	float get_inaccuracy()
	{
		using original_fn = float(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 478)(this);
	}

	float get_spread()
	{
		using original_fn = float(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 448)(this);
	}

	void draw_crosshair()
	{
		using original_fn = void(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 393)(this);
	}

	std::string get_name()
	{
		return std::string(this->get_cs_wpn_info()->weapon_name);
	}

};

#endif // !C_BASEENTITY_H
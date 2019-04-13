/// CSGO SDK.hpp

#pragma once

// note: some (read "many") includes are here twice. this is just so the includes line up with how they were in the old sdk
// i'll remove it once this sdk is fully done

// Valve/CSGO SDK
#define COMPILER_MSVC 1
#define COMPILER_MSVC32 1
#define CLIENT_DLL

// for some reason, other files below do NOT include this section of files, but reference them. they are manually included here to compile.
// todo: look into it more. it's likely that those files im including actually need to be included after something else. perhaps an _on file?
//#include <winnt.h>
//#include "public/interfaces/interfaces.h" // todo: ensure this is a valve file // todo: all of these classes/interfaces need to be updated to the latest version of the game. probably dont work
//#include "public/tier0/platform.h"
#include "public/tier0/annotations.h"
#include "public/tier1/UtlSortVector.h"
#include "public/tier1/checksum_md5.h"
#include "public/bitvec.h"
#include "game/shared/shareddefs.h"
#include "game/shared/predictable_entity.h"
//#include "game/shared/predictioncopy.h"
#include "game/client/c_baseentity.h" // todo: should update this

// Math
#include "public/mathlib/vector2d.h" // Vector2D
#include "public/mathlib/vector.h" // Vector + QAngle
#include "public/mathlib/vector4d.h" // Vector4D
#include "public/mathlib/vmatrix.h" // VMatrix

// Types
#include "public/basehandle.h" // CBaseHandle
#include "game/shared/cstrike/cs_weapon_parse.h" // CCSWeaponInfo (todo: has child classes, such as AUG and stuff that inherit it. will implement later)
#include "public/edict.h" // CGlobalVars
#include "game/shared/ehandle.h" // CHandle
#include "public/tier1/characterset.h" // characterset
#include "public/tier1/checksum_crc.h" // checksum_crc
#include "public/tier1/checksum_md5.h" // checksum_md5
#include "public/client_class.h" // ClientClass
#include "public/Color.h" // Color
#include "public/tier1/convar.h" // ConVar
#include "game/shared/usercmd.h" // CUserCmd
// Enumerations {
#include "public/materialsystem/imaterial.h" // PreviewImageRetVal_t
#include "public/materialsystem/imaterial.h" // MaterialVarFlags_t
#include "game/shared/cstrike/cs_weapon_parse.h" // CSWeaponType
//#include ".h" // EClassID -- todo: this enum. not in sdk, maybe it's something i need to dump myself? if so, i'll make a class ids enum as a global file, similar to CNetChannel Extended. it'll be an hpp file
#include "game/shared/cstrike/cs_weapon_parse.h" // EItemDefinitionIndex
//#include ".h" // EItemQuality -- see todo from 2 lines up
//#include ".h" // ECSPlayerBones -- see todo from 1 line up; possibly get it dynamically??
//#include ".h" // EHitGroups -- see todo from 1 line up; possibly get it dynamically??
#include "game/shared/shareddefs.h" // EntityFlags
#include "public/const.h" // LifeState
#include "game/shared/weapon_parse.h" // WeaponSound_t
#include "public/const.h" // MoveType_t
// } Enumerations
#include "game/client/glow_outline_effect.h" // GlowOutlineEffect
//#include ".h" // IHandleEntity
//#include ".h" // PaintKit
//#include ".h" // platform
//#include ".h" // Recv
//#include ".h" // Studio
//#include ".h" // UtlBuffer
//#include ".h" // UtlMemory
//#include ".h" // UtlString
//#include ".h" // UtlVector

// Interfaces
#include "networksystem/netchannel.h"

// todo:
//	* types
//		x CBaseHandle
//		x CCSWeaponInfo
//		x CGlobalVars
//		x CHandle
//		x characterset
//		x checksum_crc
//		x checksum_md5
//		x ClientClass
//		x Color
//		x ConVar
//		x CUserCmd
//		x Enumerations
//		x GlowOutlineEffect
//		o IHandleEntity
//		o PaintKit
//		o platform
//		o Recv
//		o Studio
//		o UtlBuffer
//		o UtlMemory
//		o UtlString
//		o UtlVector
//	* interfaces
//		o CClientState
//		o CInput
//		o IAppSystem
//		o IBaseClientDll
//		o IBaseInterface
//		o IClientEntity
//		o IClientEntityList
//		o IClientMode
//		o IClientNetworkable
//		o IClientRenderable
//		o IClientThinkable
//		o IClientUnknown
//		o ICollideable
//		o IConVar
//		o ICVar
//		o IEngineSound
//		o IEngineTrace
//		o IFileSystem
//		o IGameEventManager
//		o IGameMovement
//		o IInputSystem
//		o ILocalize
//		o IMaterialSystem
//		o IMoveHelper
//		o IVEngineClient
//		o IViewRenderBeams
//		o IPanel
//		o IPrediction
//		o IRefCounted
//		o ISurface
//		o IVRenderView
//		o IVModelInfoClient
//		o IVModelRender

// Extension of SDK
#define EXTEND_SDK_CLASS( CClassName ) class PX_##CClassName: public CClassName
#define EXTENDED_SDK_CLASS( CClassName ) PX_##CClassName
#define EXTEND_SDK_STRUCT( SStructName ) class PX_##SStructName: public SStructName
#define EXTENDED_SDK_STRUCT( SStructName ) PX_##SStructName
#include "CNetChannel Extended.hpp"

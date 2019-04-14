/// CSGO SDK.hpp

#pragma once
#pragma warning( push, 0 )
#include <CodeAnalysis/Warnings.h>
#pragma warning( disable: ALL_CODE_ANALYSIS_WARNINGS )
#include "../../Framework/Code/Development Environment/Assembly ON.inl"

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
#include "public/tier1/mempool.h"
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
#include "public/ihandleentity.h" // IHandleEntity
//#include ".h" // PaintKit -- todo: see line 49
#include "public/tier0/platform.h" // platform
#include "public/dt_recv.h" // Recv
#include "public/studio.h" // Studio
#include "public/tier1/utlbuffer.h" // UtlBuffer
#include "public/tier1/utlmemory.h" // UtlMemory
#include "public/tier1/utlstring.h" // UtlString
#include "public/tier1/utlvector.h" // UtlVector

// Interfaces
#include "networksystem/netchannel.h"
#include "engine/client.h" // CClientState
#include "game/client/input.h" // CInput
#include "public/appframework/IAppSystem.h" // IAppSystem
#include "public/cdll_int.h" // IBaseClientDll
#include "public/tier1/interface.h" // IBaseInterface
#include "public/icliententity.h" // IClientEntity
#include "public/icliententitylist.h" // IClientEntityList
#include "game/client/iclientmode.h" // IClientMode
#include "public/iclientnetworkable.h" // IClientNetworkable
#include "public/iclientrenderable.h" // IClientRenderable
#include "public/iclientthinkable.h" // IClientThinkable
#include "public/iclientunknown.h" // IClientUnknown
#include "public/engine/ICollideable.h" // ICollideable
#include "public/tier1/iconvar.h" // IConVar
#include "public/icvar.h" // ICVar
#include "public/engine/IEngineSound.h" // IEngineSound
#include "public/engine/IEngineTrace.h" // IEngineTrace
#include "public/filesystem.h" // IFileSystem
#include "public/igameevents.h" // IGameEventManager
#include "game/shared/igamemovement.h" // IGameMovement
#include "public/inputsystem/iinputsystem.h" // IInputSystem
#include "public/localize/ilocalize.h" // ILocalize
#include "public/materialsystem/imaterialsystem.h" // IMaterialSystem
#include "game/shared/imovehelper.h" // IMoveHelper
#include "public/cdll_int.h" // IVEngineClient
#include "game/client/iviewrender_beams.h" // IViewRenderBeams
#include "public/vgui/IPanel.h" // IPanel
#include "public/iprediction.h" // IPrediction
#include "public/tier1/refcount.h" // IRefCounted
#include "vgui/ISurface.h" // ISurface
#include "public/ivrenderview.h" // IVRenderView
#include "public/engine/ivmodelinfo.h" // IVModelInfoClient
#include "public/engine/ivmodelrender.h" // IVModelRender

// Extension of SDK
#define EXTEND_SDK_CLASS( CClassName ) class PX_##CClassName: public CClassName
#define EXTENDED_SDK_CLASS( CClassName ) PX_##CClassName
#define EXTEND_SDK_STRUCT( SStructName ) class PX_##SStructName: public SStructName
#define EXTENDED_SDK_STRUCT( SStructName ) PX_##SStructName
#include "CNetChannel Extended.hpp"

#include "../../Framework/Code/Development Environment/Assembly OFF.inl"
#pragma warning( pop )

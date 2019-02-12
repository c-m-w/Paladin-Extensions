﻿/// Inclusion.hpp

#pragma once

#pragma warning( push, 0 )
#include <CodeAnalysis/Warnings.h>
#pragma warning( disable: ALL_CODE_ANALYSIS_WARNINGS )

#include "Types/CBaseHandle.hpp"
#include "Types/CCSWeaponInfo.hpp"
#include "Types/CGlobalVars.hpp"
#include "Types/CHandle.hpp"
#include "Types/characterset.hpp"
#include "Types/checksum_crc.hpp"
#include "Types/checksum_md5.hpp"
#include "Types/ClientClass.hpp"
#include "Types/Color.hpp"
#include "Types/ConVar.hpp"
#include "Types/CUserCmd.hpp"
#include "Types/Enumerations.hpp"
#include "Types/GlowOutlineEffect.hpp"
#include "Types/IHandleEntity.hpp"
#include "Types/PaintKit.hpp"
#include "Types/platform.hpp"
#include "Types/Recv.hpp"
#include "Types/Studio.hpp"
#include "Types/UtlBuffer.hpp"
#include "Types/UtlMemory.hpp"
#include "Types/UtlString.hpp"
#include "Types/UtlVector.hpp"

#include "Math/Vector2D.hpp"
#include "Math/QAngle.hpp"
#include "Math/Vector.hpp"
#include "Math/Vector4D.hpp"
#include "Math/VMatrix.hpp"

#include "Interfaces/CClientState.hpp"
#include "Interfaces/CInput.hpp"
#include "Interfaces/IAppSystem.hpp"
#include "Interfaces/IBaseClientDll.hpp"
#include "Interfaces/IBaseInterface.hpp"
#include "Interfaces/IClientEntity.hpp"
#include "Interfaces/IClientEntityList.hpp"
#include "Interfaces/IClientMode.hpp"
#include "Interfaces/IClientNetworkable.hpp"
#include "Interfaces/IClientRenderable.hpp"
#include "Interfaces/IClientThinkable.hpp"
#include "Interfaces/IClientUnknown.hpp"
#include "Interfaces/ICollideable.hpp"
#include "Interfaces/IConVar.hpp"
#include "Interfaces/ICVar.hpp"
#include "Interfaces/IEngineSound.hpp"
#include "Interfaces/IEngineTrace.hpp"
#include "Interfaces/IFileSystem.hpp"
#include "Interfaces/IGameEventManager.hpp"
#include "Interfaces/IGameMovement.hpp"
#include "Interfaces/IInputSystem.hpp"
#include "Interfaces/ILocalize.hpp"
#include "Interfaces/IMaterialSystem.hpp"
#include "Interfaces/IMoveHelper.hpp"
#include "Interfaces/IVEngineClient.hpp"
#include "Interfaces/IViewRenderBeams.hpp"
#include "Interfaces/IPanel.hpp"
#include "Interfaces/IPrediction.hpp"
#include "Interfaces/IRefCounted.hpp"
#include "Interfaces/ISurface.hpp"
#include "Interfaces/IVRenderView.hpp"
#include "Interfaces/IVModelInfoClient.hpp"
#include "Interfaces/IVModelRender.hpp"

#pragma warning( pop )
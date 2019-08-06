/// SDK.hpp

#pragma once

#pragma warning( push, 0 )
#pragma warning( disable: ALL_CODE_ANALYSIS_WARNINGS )
#include "../../Framework/Precompile.hpp"
#include "../../Framework/Code/Framework.hpp"
#include "Definitions.hpp"

#include "Valve/Types/Types.hpp"
#include "Valve/Interfaces/Interfaces.hpp"
#include "Valve/Math/Math.hpp"
#include "Memory.hpp"

using namespace Memory;
#pragma warning( pop )

namespace Linkage
{


	static inline std::string strCreateInterfaceImport
#if defined _DEBUG
		= ENC( "CreateInterface" )
#endif
		;
	static inline std::string strModules[ Modules::MODULE_MAX ]
#if defined _DEBUG
	{
		ENC( "client_panorama.dll" ),
		ENC( "engine.dll" ),
		ENC( "d3d9.dll" ),
		ENC( "shaderapidx9.dll" ),
		ENC( "GameOverlayRenderer.dll" ),
		ENC( "vguimatsurface.dll" ),
		ENC( "vgui2.dll" ),
		ENC( "inputsystem.dll" ),
		ENC( "materialsystem.dll" ),
		ENC( "vstdlib.dll" ),
		ENC( "localize.dll" ),
		ENC( "filesystem_stdio.dll" )
	}
#endif
	;

	static inline char* szClientBaseVersion = nullptr,
		* szEngineClientVersion = nullptr,
		* szEngineSoundClientVersion = nullptr;

	static inline pattern_t _ClientBaseVersion
#if defined _DEBUG
		= pattern_t( ENC( "68 ? ? ? ? FF 12 8B 07" ), &szClientBaseVersion, 1, [ & ]( )
	{
		szClientBaseVersion = *reinterpret_cast< decltype( szClientBaseVersion )* >( szClientBaseVersion );
	} )
#endif
		;
	static inline pattern_t _EngineClientVersion
#if defined _DEBUG
		= pattern_t( ENC( "6A 00 68 ? ? ? ? FF D6 83 C4 0C" ), &szEngineClientVersion, 3, [ & ]( )
	{
		szEngineClientVersion = *reinterpret_cast< decltype( szEngineClientVersion )* >( szEngineClientVersion );
	} )
#endif
		;
	static inline pattern_t _EngineSoundClientVersion
#if defined _DEBUG
		= pattern_t( ENC( "08 6A 00 68 ? ? ? ? FF D6 6A" ), &szEngineSoundClientVersion, 4, [ & ]( )
	{
		szEngineSoundClientVersion = *reinterpret_cast< decltype( szEngineSoundClientVersion )* >( szEngineSoundClientVersion );
	} )
#endif
		;
	static inline pattern_t _DevicePattern
#if defined _DEBUG
		= pattern_t( ENC( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ), &Interfaces::pDevice, 1, [ & ]( )
	{
		Interfaces::pDevice = **reinterpret_cast< decltype( Interfaces::pDevice ) * * >( Interfaces::pDevice );
	} )
#endif
		;
	static inline unsigned zReset
#if defined _DEBUG
		= 16u
#endif
		,
		zBeginScene
#if defined _DEBUG
		= 41u
#endif
		,
		zEndScene
#if defined _DEBUG
		= 42u
#endif
		;
}


#include "Types.hpp"
#include "Tools.hpp"

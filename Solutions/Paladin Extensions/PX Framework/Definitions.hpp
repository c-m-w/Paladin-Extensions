/// Definitions.hpp

#pragma once

// Compiler
#pragma warning( disable: 4098 4099 4100 4307 4309 4996 )
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

// Windows.h

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

// curl.h

#define CURL_STATICLIB

// nuklear.h

#if defined PX_NUKLEAR_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_IMPLEMENTATION
#define NK_D3D9_IMPLEMENTATION
#else
#define NK_PRIVATE
#endif

#if defined _DEBUG
	/** \brief Evaluates if parameter is equivalent to empty initialized version of parameter
		(false) and throws an exception if the evaluation succeeds */
	/** \param _ToAssert Value to assert. */
#define px_assert( _ToAssert ) \
		if ( ( _ToAssert ) == decltype( _ToAssert )( ) ) \
			throw std::exception( ( std::string( "Failed to assert " ) + #_ToAssert + " in function " + __func__ \
			+ " from line " + std::to_string( unsigned( __LINE__ ) ) + " in file " + ##( __FILE__ ) + "." ).c_str( ) )
#else
	/** \brief Evaluates if parameter is equivalent to empty initialized version of parameter
		(false) and returns if the evaluation succeeds */
	/** \param _ToAssert Value to assert. */
#define px_assert( _ToAssert ) \
		if ( ( _ToAssert ) == decltype( ( _ToAssert ) )( ) ) \
			return { }
#endif

// identifies variable as "Paladin Extensions" original
#define PX_SDK inline
// identifies function as "Paladin Extensions" original
#define PX_API __cdecl
// identifies constant as "Paladin Extensions" original
#define PX_DEF constexpr auto
// identifies instruct as "Paladin Extensions" original
#define PX_EXT extern

/** \brief Identifies a class as abstract. */
#define px_abstract_class class
/** \brief Identifies a function as abstract. */
#define px_abstract virtual
/** \brief Identifies an interface. */
#define px_interface class

/** \brief Path to appdata directory */
#define PX_APPDATA ( std::wstring( _wgetenv( PX_XOR( L"APPDATA" ) ) ) + PX_XOR( L"\\PX\\" ) )

/** \brief Maximum managed keys. */
#define PX_MAX_KEY 256

/** \brief Size of a memory page. */
#define PX_PAGE ( 1024 * 4 )

/** \brief Value of memory on the stack before it is assigned a value. */
#define PX_UNITIALIZED_STACK_MEMORY 0xCCCCCCCC

#define PX_MOV_EAX	0xB8
#define PX_MOV_EDX	0xBA
#define PX_PUSH		0x68

#define PX_EXTENSION_SECTIONS 7

// TODO: make this an enumerated type
#define PX_EXTENSION_NONE -1
#define PX_EXTENSION_MANAGER 1
#define PX_EXTENSION_CSGO 2
#define PX_EXTENSION_PUBG 3
#define PX_EXTENSION_RSIX 4
#define PX_EXTENSION_MAX 5

#if defined _DEBUG
#define PX_DEPENDENCIES_ESCAPE 1
#else
#define PX_DEPENDENCIES_ESCAPE 0
#endif

#if defined _DEBUG
#define D3D_DEBUG_INFO
#endif

#define PX_CUSTOM_FVF D3DFVF_XYZRHW | D3DFVF_DIFFUSE

// Encrypts string data on compile, then decrypts for access on run.
#if defined NDEBUG
#define PX_XOR( String ) ( PX::XOR::AXorString< PX::XOR::ACStringTraits< decltype( String ) >::char_trait_t, \
		PX::XOR::AConstructIndexList< ( sizeof( String ) - 1 ) / PX::XOR::ACStringTraits< decltype( String ) >::int_trait_t >::result_t >( String ).Decrypt( ) )
#else
#define PX_XOR( String ) ( String )
#endif

#if defined _DEBUG
// sets debug out line identifier as "Opening"
#define PX_OPN << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%H:%M:%S]" ) << \
		PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE ) << L" [OPN] " << \
		PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
// sets debug out line identifier as "Information"
#define PX_NFO << PX::dbg::newl << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%H:%M:%S]" ) << \
		PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE ) << L" [NFO] " << \
		PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
// sets debug out line identifier as "Debug"
#define PX_DBG << PX::dbg::newl << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%H:%M:%S]" ) << \
		PX::dbg::out_clr_t( FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE ) << L" [DBG] " << \
		PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
// sets debug out line identifier as "Success"
#define PX_SCS << PX::dbg::newl << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%H:%M:%S]" ) << \
		PX::dbg::out_clr_t( FOREGROUND_INTENSITY | !FOREGROUND_RED | FOREGROUND_GREEN | !FOREGROUND_BLUE ) << L" [SCS] " << \
		PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
// sets debug out line identifier as "Warning"
#define PX_WRN << PX::dbg::newl << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%H:%M:%S]" ) << \
		PX::dbg::out_clr_t( FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | !FOREGROUND_BLUE ) << L" [WRN] " << \
		PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
// sets debug out line identifier as "Error"
#define PX_ERR << PX::dbg::newl << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%H:%M:%S]" ) << \
		PX::dbg::out_clr_t( FOREGROUND_INTENSITY | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_BLUE ) << L" [ERR] " << \
		PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
// sets debug out line identifier as "Last Error Info"
#define PX_LER << PX::dbg::newl << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%H:%M:%S]" ) << \
		PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | !FOREGROUND_BLUE ) << L" [LER] " << \
		PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
#else
#define PX_DBG
#define PX_SCS
#define PX_WRN
#define PX_ERR
#define PX_LER
#endif

// Singleton access macros
/** \brief Input interface singleton access macro */
#define PX_INPUT PX::CInputManager::Get( )
/** \brief File manager class singleton access macro */
#define PX_FILES PX::Files::CConfig::Get( )
/** \brief Configuration access macro for convenience */
#define PX_CONFIG PX_FILES.jsCurrent
/** \brief Undocumented WINAPI Manager */
#define PX_WINAPI PX::sys::SWindowsAPI::Get( )
/** \brief Calls common AnalysisProtection functions */
#define PX_ANTI_ANALYSIS( ) \
		!PX::AnalysisProtection::DebuggerDetection::DebuggerPresence( ) && \
		!PX::AnalysisProtection::DebuggerDetection::ForceExceptions( ) && \
		!PX::AnalysisProtection::AnalysisSoftwareDetection::AnalysisToolsRunning( ) && \
		!( ) && \
		!( ) && \
		!( ) && \
		!( ) && \
		!( ) && \
		!( ) && \
		!( ) && \
		!( ) && \
		!( ) && \
		!( ) && \
/** \brief Calls common AnalysisProtection functions, including those for external processes */
#define PX_ANTI_ANALYSIS_EX( hExtension ) \
		PX_ANTI_ANALYSIS( ) && \
		!PX::AnalysisProtection::DebuggerDetection::DebuggerPresenceEx( hExtension ) && \
		!( ) && \
		!( ) && \
		!( ) && \
/** \brief Calls all AnalysisProtection functions, including those for external processes */
#define PX_ANTI_ANALYSIS_ALL( hExtension ) \
		PX_ANTI_ANALYSIS_EX( hExtension ) \
		!PX::AnalysisProtection::AnalysisSoftwareDetection::AnalysisToolsInstalled( ) && \
		!( ) && \
		!( ) && \
		!( ) && \

/// Definitions.hpp

#pragma once

#if defined PX_NO_COMPILE_DEFINITIONS
#else

// Compiler
#pragma warning( disable : 4307 4309 4996 )
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

// Windows.h

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

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

#endif

// identifies variable as "Paladin Extensions" original
#define PX_SDK inline
// identifies function as "Paladin Extensions" original
#define PX_API __cdecl
// identifies constant as "Paladin Extensions" original
#define PX_DEF constexpr auto
// identifies instruct as "Paladin Extensions" original
#define PX_EXT extern

// identifies class as abstract interface
#define PX_ABSTRACT_CLASS class
// identifies struct as abstract interface
#define PX_ABSTRACT_STRUCT struct

// maximum managed keys
#define PX_MAX_KEY 256

#if defined _DEBUG
#define PX_DEPENDENCIES_ESCAPE 3
#else
#define PX_DEPENDENCIES_ESCAPE
#endif


// Encrypts string data on compile, then decrypts for access on run.
#define PX_XOR( String ) ( PX::XOR::CXorString< PX::XOR::SCStringTraits< decltype( String ) >::char_trait_t, \
        PX::XOR::SConstructIndexList< ( sizeof( String ) - 1 ) / PX::XOR::SCStringTraits< decltype( String ) >::int_trait_t >::result_t >( String ).Decrypt( ) )

#if defined _DEBUG
// sets debug out line identifier as "Debug"
#define PX_DBG << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%H:%M:%S]" ) << \
        PX::dbg::out_clr_t( FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE ) << L" [DBG] " << \
        PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
// sets debug out line identifier as "Success"
#define PX_SCS << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%H:%M:%S]" ) << \
        PX::dbg::out_clr_t( FOREGROUND_INTENSITY | !FOREGROUND_RED | FOREGROUND_GREEN | !FOREGROUND_BLUE  ) << L" [SCS] " << \
        PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
// sets debug out line identifier as "Warning"
#define PX_WRN << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%H:%M:%S]" ) << \
        PX::dbg::out_clr_t( FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | !FOREGROUND_BLUE ) << L" [WRN] " << \
        PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
// sets debug out line identifier as "Error"
#define PX_ERR << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%H:%M:%S]" ) << \
        PX::dbg::out_clr_t( FOREGROUND_INTENSITY | FOREGROUND_RED | !FOREGROUND_GREEN | !FOREGROUND_BLUE ) << L" [ERR] " << \
        PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
// sets debug out line identifier as "Last Error Info"
#define PX_LER << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), L"[%H:%M:%S]" ) << \
        PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | !FOREGROUND_BLUE ) << L" [LER] " << \
        PX::dbg::out_clr_t( !FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
#elif
#define PX_DBG
#define PX_SCS
#define PX_WRN
#define PX_ERR
#define PX_LER
#endif

// Singleton access macros

// Input interface singleton access macro
#define PX_INPUT PX::CInputManager::Get( )
// File manager class singleton access macro
#define PX_FILES PX::CFileManager::Get( )


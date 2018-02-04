#pragma once

#include "public/cdll_int.h"
#include "public/engine/ivdebugoverlay.h"
#include "public/engine/IEngineTrace.h"
#include "public/gametrace.h"
#include "public/icliententitylist.h"
#include "public/iclientnetworkable.h"

inline CreateInterfaceFn GetModuleFactory( HMODULE hModule )
{
	return reinterpret_cast< CreateInterfaceFn >( GetProcAddress( hModule, "CreateInterface" ) );
}

template<typename xDatatype> void GetInterface( xDatatype *&xInterface, CreateInterfaceFn fnInterface, const char* szInterfaceVersion )
{
	xInterface = reinterpret_cast< xDatatype * >( fnInterface( szInterfaceVersion, nullptr ) );
}

inline unsigned char *ScanForPattern( void *vModule, const char *szSignature )
{
	static auto patternToByte = [ ]( const char* szPattern )
	{
		std::vector< int > veciBytes { };
		char *pchStart = const_cast< char* >( szPattern );
		char *pchEnd = const_cast< char* >( szPattern ) + strlen( szPattern );

		for ( char *pchCurrent = pchStart; pchCurrent < pchEnd; ++pchCurrent )
		{
			if ( *pchCurrent == '?' )
			{
				++pchCurrent;
				if ( *pchCurrent == '?' )
				{
					++pchCurrent;
				}
				veciBytes.push_back( -1 );
			}
			else
			{
				veciBytes.push_back( strtoul( pchCurrent, &pchCurrent, 16 ) );
			}
		}
		return veciBytes;
	};

	PIMAGE_DOS_HEADER dosHeader = PIMAGE_DOS_HEADER( vModule );
	PIMAGE_NT_HEADERS ntHeaders = PIMAGE_NT_HEADERS( static_cast< unsigned char* >( vModule ) + dosHeader->e_lfanew );

	auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = patternToByte( szSignature );
	auto scanBytes = reinterpret_cast<unsigned char*>( vModule );

	auto s = patternBytes.size( );
	auto d = patternBytes.data( );

	for ( unsigned long i = 0; i < sizeOfImage - s; ++i )
	{
		bool found = true;
		for ( auto j = 0ul; j < s; ++j )
		{
			if ( scanBytes[ i + j ] != d[ j ] && d[ j ] != -1 )
			{
				found = false;
				break;
			}
		}
		if ( found )
		{
			return &scanBytes[ i ];
		}
	}
	return nullptr;
}

IBaseClientDLL *CHLClient { };
CGlobalVarsBase *GlobalVars { };

inline void Initialize( )
{
	HMODULE dllClientBase = GetModuleHandle( L"client.dll" );

	CreateInterfaceFn facClientBase = GetModuleFactory( dllClientBase );

	GetInterface( CHLClient, facClientBase, "VClient018" );

	GlobalVars = **reinterpret_cast< CGlobalVarsBase*** >( ScanForPattern( dllClientBase, "A1 ? ? ? ? 5E 8B 40 10" ) + 1 );
}

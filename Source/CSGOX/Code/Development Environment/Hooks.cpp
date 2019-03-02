/// Hooks.cpp

#include "Precompile.hpp"

#define USE_INTERNAL_NAMESPACES
#define USE_INTERNAL_DEFINITIONS
#include "../CSGOX.hpp"

#define GET_MEMBER_ADDRESS( Variable, Member )		\
	__asm mov eax, Member							\
	__asm mov Variable, eax

bool CHooks::Initialize( )
{
	return _Device.Setup( );
}

void CHooks::Uninitialize( )
{
	_Device.Shutdown( );
}

bool CHooks::CDeviceHook::Initialize( )
{
	void *pReplacementReset = nullptr,
		*pReplacementBeginScene = nullptr,
		*pReplacementEndScene = nullptr;

	GET_MEMBER_ADDRESS( pReplacementReset, Reset )
	GET_MEMBER_ADDRESS( pReplacementBeginScene, BeginScene )
	GET_MEMBER_ADDRESS( pReplacementEndScene, EndScene )

	return Attach( pDevice )
		&& Replace( GAME_MEM.pReset, pReplacementReset )
		&& Replace( GAME_MEM.pBeginScene, pReplacementBeginScene )
		&& Replace( GAME_MEM.pEndScene, pReplacementEndScene );
}

void CHooks::CDeviceHook::Uninitialize( )
{
	Detach( );
}

HRESULT CHooks::CDeviceHook::Reset( D3DPRESENT_PARAMETERS *pPresentationParameters )
{
	return reinterpret_cast< HRESULT( __stdcall * )( void *, D3DPRESENT_PARAMETERS * ) >( GAME_MEM.pReset )( this, pPresentationParameters );
}

HRESULT CHooks::CDeviceHook::BeginScene( )
{
	return reinterpret_cast< HRESULT( __stdcall * )( void * ) >( GAME_MEM.pBeginScene )( this );
}

HRESULT CHooks::CDeviceHook::EndScene( )
{
	return reinterpret_cast< HRESULT( __stdcall * )( void * ) >( GAME_MEM.pEndScene )( this );
}

CHooks _Hooks;

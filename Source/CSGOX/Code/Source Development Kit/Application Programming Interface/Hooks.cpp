/// Hooks.cpp

#include "Precompile.hpp"

#define USE_INTERNAL_NAMESPACES
#define USE_INTERNAL_DEFINITIONS
#include "../../CSGOX.hpp"

#define GET_MEMBER_ADDRESS( Variable, Member )		\
	__asm mov eax, Member							\
	__asm mov Variable, eax

bool CHooks::Initialize( )
{
	return _Device.Setup( )
		&& _ClientMode.Setup( );
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
		&& Replace( pReset = GetOriginalFunction( GetFunctionIndex( FUNCTION_RESET ) ), pReplacementReset )
		&& Replace( pBeginScene = GetOriginalFunction( GetFunctionIndex( FUNCTION_BEGIN_SCENE ) ), pReplacementBeginScene )
		&& Replace( pEndScene = GetOriginalFunction( GetFunctionIndex( FUNCTION_END_SCENE ) ), pReplacementEndScene );
}

void CHooks::CDeviceHook::Uninitialize( )
{
	Detach( );
}

HRESULT CHooks::CDeviceHook::Reset( D3DPRESENT_PARAMETERS *pPresentationParameters )
{
	return reinterpret_cast< HRESULT( __stdcall * )( void *, D3DPRESENT_PARAMETERS * ) >( pReset )( this, pPresentationParameters );
}

HRESULT CHooks::CDeviceHook::BeginScene( )
{
	return reinterpret_cast< HRESULT( __stdcall * )( void * ) >( pBeginScene )( this );
}

HRESULT CHooks::CDeviceHook::EndScene( )
{
	return reinterpret_cast< HRESULT( __stdcall * )( void * ) >( pEndScene )( this );
}

bool CHooks::CClientModeHook::Initialize( )
{
	void *pReplacementCreateMove = nullptr;

	GET_MEMBER_ADDRESS( pReplacementCreateMove, CreateMove )

	return Attach( pDevice )
			&& Replace( pCreateMove = GetOriginalFunction( GetFunctionIndex( FUNCTION_CREATE_MOVE ) ), pReplacementCreateMove );
}

void CHooks::CClientModeHook::Uninitialize( )
{
	Detach( );
}

void CHooks::CClientModeHook::CreateMove( int iSequence, float flInputSampleFrametime, bool bActive )
{
	for ( auto &fnBeginCreateMove: vecBeginCreateMove )
		fnBeginCreateMove( );

	/*auto _Return = */reinterpret_cast< void( __stdcall * )( void *, int, float, bool ) >( pCreateMove )( this, iSequence, flInputSampleFrametime, bActive );

	for ( auto &fnEndCreateMove: vecEndCreateMove )
		fnEndCreateMove( );

	return /*_Return*/;
}

CHooks _Hooks;

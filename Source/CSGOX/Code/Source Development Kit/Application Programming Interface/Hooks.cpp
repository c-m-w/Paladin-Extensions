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

HRESULT CHooks::CDeviceHook::Present( const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion )
{
	SPresentContext _Context { };

	for ( auto &_2Hook: vecBeginHook[ FUNCTION_PRESENT ] )
	{
		UHookCallback< SPresentContext > _Hook;
		_Hook.p = ( *reinterpret_cast< void*** >( _2Hook.first ) )[ _2Hook.second ];
		_Hook.fn( _2Hook.first, &_Context );
	}

	auto _Return = reinterpret_cast< bool( __thiscall * )( void *, const RECT *, const RECT *, HWND , const RGNDATA * ) >( pPresent )( this, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
	
	for ( auto &_2Hook: vecEndHook[ FUNCTION_PRESENT ] )
	{
		UHookCallback< SPresentContext > _Hook;
		_Hook.p = ( *reinterpret_cast< void*** >( _2Hook.first ) )[ _2Hook.second ];
		_Hook.fn( _2Hook.first, &_Context );
	}

	return _Return;
}

HRESULT CHooks::CDeviceHook::DrawPrimitive( D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount )
{
	SDrawContext _Context { };

	for ( auto &_2Hook: vecBeginHook[ FUNCTION_DRAW_PRIMITIVE ] )
	{
		UHookCallback< SDrawContext > _Hook;
		_Hook.p = ( *reinterpret_cast< void*** >( _2Hook.first ) )[ _2Hook.second ];
		_Hook.fn( _2Hook.first, &_Context );
	}

	auto _Return = reinterpret_cast< bool( __thiscall * )( void *, D3DPRIMITIVETYPE, UINT, UINT ) >( pDrawPrimitive )( this, PrimitiveType, StartVertex, PrimitiveCount );
	
	for ( auto &_2Hook: vecEndHook[ FUNCTION_PRESENT ] )
	{
		UHookCallback< SDrawContext > _Hook;
		_Hook.p = ( *reinterpret_cast< void*** >( _2Hook.first ) )[ _2Hook.second ];
		_Hook.fn( _2Hook.first, &_Context );
	}

	return _Return;
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

	return Attach( pClientMode )
			&& Replace( pCreateMove = GetOriginalFunction( GetFunctionIndex( FUNCTION_CREATE_MOVE ) ), pReplacementCreateMove );
}

void CHooks::CClientModeHook::Uninitialize( )
{
	Detach( );
}

bool CHooks::CClientModeHook::CreateMove( int iSequenceNumber, float flInputSampleFrametime, bool bActive )
{
	SCreateMoveContext _Context
	{
		GetLocalPlayer( ),
		&( *( CUserCmd** )( ( DWORD )pInput + 0xEC ) )[ iSequenceNumber % 150 ],
		&( *( CVerifiedUserCmd** )( ( DWORD )pInput + 0xF0 ) )[ iSequenceNumber % 150 ]
	};

	for ( auto &_2Hook: vecBeginHook[ FUNCTION_CREATE_MOVE ] )
	{
		UHookCallback< SCreateMoveContext > _Hook;
		_Hook.p = ( *reinterpret_cast< void*** >( _2Hook.first ) )[ _2Hook.second ];
		_Hook.fn( _2Hook.first, &_Context );
	}

	auto _Return = reinterpret_cast< bool( __thiscall * )( void *, int, float, bool ) >( pCreateMove )( this, iSequenceNumber, flInputSampleFrametime, bActive );
	
	for ( auto &_2Hook: vecEndHook[ FUNCTION_CREATE_MOVE ] )
	{
		UHookCallback< SCreateMoveContext > _Hook;
		_Hook.p = ( *reinterpret_cast< void*** >( _2Hook.first ) )[ _2Hook.second ];
		_Hook.fn( _2Hook.first, &_Context );
	}

	return _Return;
}

CHooks _Hooks;

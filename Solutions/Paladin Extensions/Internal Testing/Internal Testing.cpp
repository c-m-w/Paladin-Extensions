/// PX Loader.cpp

#define PX_ENTRY_AS_WIN
#define PX_INSTANCE_ID L"Internal Testing"
#include <Jeremia-h/Entry Manager.hpp>

#include "Internal Testing.hpp"

using namespace PX;

class CVirtualTable
{
public:
	virtual void __thiscall	FunctionOne( )							= 0;
	virtual void __thiscall	FunctionTwo( const wchar_t* szText )	= 0;
	virtual void __thiscall	FunctionThree( unsigned uFlags )		= 0;
	virtual int	__thiscall	FunctionFour( )							= 0;
	virtual bool __thiscall	FunctionFive( bool bReturn )			= 0;
};

class CFunctions : public CVirtualTable
{
public:
	void __thiscall FunctionOne( ) override
	{ }

	void __thiscall FunctionTwo( const wchar_t* szText ) override
	{
		MessageBox( nullptr, szText, L"Message Box", MB_OK );
	}

	void __thiscall FunctionThree( unsigned uFlags ) override
	{
		MessageBox( nullptr, L"Message Box", L"Message Box", uFlags );
	}

	int __thiscall FunctionFour( ) override
	{
		return 10;
	}

	bool __thiscall FunctionFive( bool bReturn ) override
	{
		return !bReturn;
	}
};

hook_t* hHook;

using fn1_t = void( __thiscall* )( CFunctions* );
using fn2_t = void( __thiscall* )( CFunctions*, const wchar_t* );
using fn3_t = void( __thiscall* )( CFunctions*, unsigned );
using fn4_t = int( __thiscall* )( CFunctions* );
using fn5_t = bool( __thiscall* )( CFunctions*, bool );

void __fastcall hkFunctionTwo( CFunctions* pECX, int edx, const wchar_t *szText )
{
	static auto fnOriginal = hHook->GetOriginalFunction< fn2_t >( 1 );

	std::cout << "Intercepted function two with text " << szText << std::endl;
	fnOriginal( pECX, L"Hooked text!" );
}

void __fastcall hkFunctionThree( CFunctions* pECX, int edx, unsigned uFlags )
{
	static auto fnOriginal = hHook->GetOriginalFunction< fn3_t >( 2 );

	std::cout << "Intercepted function three with flags " << uFlags << std::endl;
	fnOriginal( pECX, MB_HELP | MB_CANCELTRYCONTINUE );
}

int __fastcall hkFunctionFour( CFunctions* pECX, int edx )
{
	static auto fnOriginal = hHook->GetOriginalFunction< fn4_t >( 3 );

	const auto iReturnValue = fnOriginal( pECX );
	std::cout << "Intercepted function four with rvalue " << iReturnValue << std::endl;
	return iReturnValue * 10;
}

void PX_API VirtualTableHookExample( )
{
	CFunctions obj;
	CVirtualTable* vftbl = &obj;

	hHook = new hook_t( vftbl, L"user32.dll" ); // example module
	hHook->HookIndex( 1, hkFunctionTwo );
	hHook->HookIndex( 2, hkFunctionThree );
	hHook->HookIndex( 3, hkFunctionFour );

	vftbl->FunctionTwo( L"Men" );
	vftbl->FunctionThree( MB_OK );
	const auto i = vftbl->FunctionFour( );

	delete hHook;

	vftbl->FunctionTwo( L"Men" );
}

void PX_API ThreadTest( )
{
	while ( true )
		Wait( 1 );
}

void messagebox( unsigned uFlags )
{
	MessageBox( nullptr, L"Thread has been hijacked!", L"Thread has been hijacked!", uFlags );
}

auto men = MB_OK | MB_ICONERROR;

__declspec( naked ) DWORD WINAPI ThreadHijack( )
{
	__asm
	{
		pushad
		pushfd
		push men
		call messagebox
		pop eax
		popfd
		popad
		ret
	}
}

void PX_API ThreadHijackExample( )
{
	DWORD dwThreadID;
	auto hThread = CreateThread( nullptr, 0, LPTHREAD_START_ROUTINE( ThreadTest ), nullptr, 0, &dwThreadID );

	CONTEXT ctxThread { CONTEXT_FULL };

	SuspendThread( hThread );
	GetThreadContext( hThread, &ctxThread );

	ctxThread.Esp -= 4;
	auto ptr = reinterpret_cast< ptr_t* >( ctxThread.Esp );
	*ptr = ctxThread.Eip;
	ctxThread.Eip = DWORD( ThreadHijack );

	SetThreadContext( hThread, &ctxThread );
	ResumeThread( hThread );
}

void PX_API OnLaunch( )
{
	VirtualTableHookExample( );

	system( "pause" );
}

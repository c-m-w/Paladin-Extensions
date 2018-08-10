/// Input Manager.hpp

#pragma once

namespace PX
{
	using namespace Tools;

	class CInputManager: public ASingleton< CInputManager >
	{
	public:
		enum EKeyState
		{
			UP,
			DOWN
		};
	private:
		EKeyState stateKeys[ PX_MAX_KEY ];
		moment_t mmtKeyDownTime[ PX_MAX_KEY ];
		unsigned uLastKeyPressed;
		std::vector< std::function< void( PX_API )( unsigned ) > > vecfnKeyCallback[ PX_MAX_KEY ];
		std::vector< std::function< void( PX_API )( unsigned ) > > vecfnGlobalCallbacks;

		void PX_API ProcessKey( unsigned, UINT );
		void PX_API ProcessMouseMessage( UINT, WPARAM, LPARAM );
		void PX_API ProcessKeyboardMessage( UINT, WPARAM, LPARAM );
	public:
		void PX_API OnEvent( HWND, UINT, WPARAM, LPARAM );

		EKeyState PX_API GetKeyState( unsigned );
		unsigned PX_API GetLastPressedKey( );
		moment_t PX_API TimeSinceKeyPress( unsigned );
		void PX_API AddKeyCallback( unsigned, std::function< void( int ) > );
		void PX_API AddGlobalCallback( std::function< void( unsigned ) > );
	};
}

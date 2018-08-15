/// Input Manager.hpp

#pragma once

namespace PX
{
	using namespace Tools;

	class CKeyState
	{
	public:
		enum EKeyState
		{
			UP,
			DOWN
		};

	private:
		EKeyState ksKeyState;

	public:

		CKeyState( ) = default;

		CKeyState( const EKeyState& _KeyState )
		{
			ksKeyState = _KeyState;
		}

		explicit operator bool( ) const
		{
			return ksKeyState == DOWN;
		}

		explicit operator int( ) const
		{
			return ksKeyState;
		}

		bool operator==( const bool& rhs ) const
		{
			return bool( *this ) == rhs;
		}

		bool operator!=( const bool& rhs ) const
		{
			return !( *this == rhs );
		}

		bool operator==( const int& rhs ) const
		{
			return int( *this ) == rhs;
		}

		bool operator!=( const int& rhs ) const
		{
			return !( *this == rhs );
		}
	};

	class CInputManager: public ASingleton< CInputManager >
	{
		CKeyState ksKeys[ PX_MAX_KEY ];
		moment_t mmtKeyDownTime[ PX_MAX_KEY ];
		unsigned uLastKeyPressed;
		std::vector< std::function< void( PX_API )( unsigned ) > > vecfnKeyCallback[ PX_MAX_KEY ];
		std::vector< std::function< void( PX_API )( unsigned ) > > vecfnGlobalCallbacks;

		void PX_API ProcessKey( unsigned, UINT );
		void PX_API ProcessMouseMessage( UINT, WPARAM, LPARAM );
		void PX_API ProcessKeyboardMessage( UINT, WPARAM, LPARAM );
	public:
		CInputManager( );

		void PX_API OnEvent( HWND, UINT, WPARAM, LPARAM );

		CKeyState PX_API GetKeyState( unsigned );
		unsigned PX_API GetLastPressedKey( );
		moment_t PX_API TimeSinceKeyPress( unsigned );
		void PX_API AddKeyCallback( unsigned, std::function< void( int ) > );
		void PX_API AddGlobalCallback( std::function< void( unsigned ) > );
	};
}

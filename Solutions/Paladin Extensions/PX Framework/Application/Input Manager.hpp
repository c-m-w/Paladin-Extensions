/// Input Manager.hpp

#pragma once

namespace PX
{
    PX_ABSTRACT_CLASS IInputManager: Utilities::ISingleton< IInputManager >
    {
	public:
		enum class EKeyState
		{
			UP,
			DOWN
		};
	private:
		EKeyState uKeyState[ PX_MAX_KEY ];
		unsigned long long ulKeyDownTime[ PX_MAX_KEY ];
		unsigned uLastKeyPressed;
		std::vector< std::function< void( unsigned ) > > vecKeyCallback[ PX_MAX_KEY ];

		void PX_API ProcessMouseMessage( UINT, WPARAM, LPARAM );
		void PX_API ProcessKeyboardMessage( UINT, WPARAM, LPARAM );
		void PX_API ProcessKey( unsigned, UINT );
	public:
		void PX_API OnEvent( HWND, UINT, WPARAM, LPARAM );

		EKeyState PX_API GetKeyState( unsigned );
		unsigned PX_API GetLastPressedKey( );
		Utilities::moment_t PX_API TimeSinceKeyPress( unsigned );
		void PX_API AddKeyCallback( unsigned, std::function< void( int ) > );
    };
}

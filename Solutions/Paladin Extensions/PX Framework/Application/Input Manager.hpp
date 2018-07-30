/// Input Manager.hpp
// TODO: document @Cole
#pragma once

namespace PX
{
    LRESULT WINAPI WndProc( HWND, UINT, WPARAM, LPARAM );

    PX_ABSTRACT_CLASS IInputManager: public Utilities::ISingleton< IInputManager >
    {
	public:
		enum EKeyState
		{
			UP,
			DOWN
		};
	private:
		EKeyState stateKeys[ PX_MAX_KEY ];
        Utilities::moment_t mmtKeyDownTime[ PX_MAX_KEY ];
		unsigned uLastKeyPressed;
		std::vector< std::function< void( unsigned ) > > vecfnKeyCallback[ PX_MAX_KEY ];

        void PX_API ProcessKey( unsigned, UINT );
		void PX_API ProcessMouseMessage( UINT, WPARAM, LPARAM );
		void PX_API ProcessKeyboardMessage( UINT, WPARAM, LPARAM );
	public:
		void PX_API OnEvent( HWND, UINT, WPARAM, LPARAM );

		EKeyState PX_API GetKeyState( unsigned );
		unsigned PX_API GetLastPressedKey( );
		Utilities::moment_t PX_API TimeSinceKeyPress( unsigned );
		void PX_API AddKeyCallback( unsigned, std::function< void( int ) > );
    };
}

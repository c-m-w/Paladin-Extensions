/// Input.hpp

#pragma once

#define MAX_KEY 256

namespace Paladin 
{
	enum class EKeyState : unsigned
	{
		UP,
		DOWN
	};

	class CWindowInput 
	{
		EKeyState uKeyState[ MAX_KEY ];
		unsigned long long ulKeyDownTime[ MAX_KEY ];
		unsigned uLastKeyPressed { };
		std::vector< std::function< void( unsigned ) > > vecKeyCallback[ MAX_KEY ];

		void ProcessMouseMessage( UINT, WPARAM, LPARAM );
		void ProcessKeyboardMessage( UINT, WPARAM, LPARAM );
		void ProcessKey( unsigned uKey, UINT uMessage );
	public:
		void OnEvent( HWND, UINT, WPARAM, LPARAM );

		EKeyState GetKeyState( unsigned );
		unsigned GetLastPressedKey( );
		moment_t TimeSinceKeyPress( unsigned );
		void AddKeyCallback( unsigned, std::function< void( int ) > );
	};
}

/// Input.hpp

#pragma once

namespace Paladin 
{
	enum class EKeyState : unsigned
	{
		UP,
		DOWN
	};

	class CWindowInput 
	{
#define M_MAX_KEY 256
		EKeyState uKeyState[ M_MAX_KEY ];
		unsigned long long ulKeyDownTime[ M_MAX_KEY ];
		unsigned uLastKeyPressed { };
		std::vector< std::function< void( unsigned ) > > vecKeyCallback[ M_MAX_KEY ];

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

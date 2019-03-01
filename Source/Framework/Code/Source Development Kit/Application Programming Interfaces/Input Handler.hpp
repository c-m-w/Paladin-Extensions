/// Input.hpp

#pragma once

class CInputHandler: public IBase
{
public:

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

		CKeyState( const EKeyState &_KeyState )
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

		bool operator==( const bool &rhs ) const
		{
			return bool( *this ) == rhs;
		}

		bool operator!=( const bool &rhs ) const
		{
			return !( *this == rhs );
		}

		bool operator==( const int &rhs ) const
		{
			return int( *this ) == rhs;
		}

		bool operator!=( const int &rhs ) const
		{
			return !( *this == rhs );
		}
	};

	/** \brief Used to hold the virtual key code of a key. */
	using key_t = unsigned char;
	/** \brief Callback for when a singular key state is changed.\n
				The parameter passed is the state of the key.\n
				Return true if the input was handled. */
	using key_callback_t = std::function< bool( CKeyState ) >;
	/** \brief Callback for when a singular key is typed.\n
				The parameter passed is the key that was pressed.\n
				Return true if the input was handled. */
	using key_typed_callback_t = std::function< bool( key_t ) >;
	/** \brief Callback for whenever a key state is changed.\n
				First parameter holds the virtual key code of the key.\n
				Second parameter is the state of the key.\n
				Return true if the input was handled. */
	using global_key_callback_t = std::function< bool( key_t, CKeyState ) >;
	/** \brief Callback for when the mouse is moved on the window.\n
				The parameter is the location that the mouse has moved to.\n
				Return true if the input was handled. */
	using mouse_move_callback_t = std::function< bool( int, int ) >;
	/** \brief Callback for when the mouse wheel is scrolled on the window.\n
				Parameters are respectively the scroll delta and location of scroll.\n
				Return true if the input was handled. */
	using scroll_callback_t = std::function< bool( short, int, int ) >;

private:

	bool Initialize( ) override;
	void Uninitialize( ) override;

	bool ProcessKey( key_t _Key, CKeyState _KeyState );
	bool ProcessMouseMessage( UINT uMsg, WPARAM wParam );
	bool ProcessKeyboardMessage( UINT uMsg, WPARAM wParam );

	int iMouseX, iMouseY;
	CKeyState _KeyStates[ UCHAR_MAX ];
	key_t _LastPressedKey;
	Utilities::moment_t mmtLastKeyPressTime[ UCHAR_MAX ];
	std::vector< key_callback_t > vecKeyCallbacks[ UCHAR_MAX ];
	std::vector< key_typed_callback_t > vecKeyTypedCallbacks;
	std::vector< global_key_callback_t > vecGlobalKeyCallbacks;
	std::vector< mouse_move_callback_t > vecMouseMoveCallbacks;
	std::vector< scroll_callback_t > vecScrollCallbacks;

public:

	bool HandleEvent( UINT uMsg, WPARAM wParam, LPARAM lParam );
	void AddCallback( const key_callback_t &_Callback, const key_t &_Key );
	void AddCallback( const key_typed_callback_t &_Callback );
	void AddCallback( const global_key_callback_t &_Callback );
	void AddCallback( const mouse_move_callback_t &_Callback );
	void AddCallback( const scroll_callback_t &_Callback );
	CKeyState GetKeyState( const key_t &_KeyCode );
	Utilities::location_t GetMouseLocation( );
	Utilities::moment_t GetTimeSinceKeyPress( const key_t &_Key );
	void GetMousePos( int &x, int &y );
} extern _Input;

using CKeyState = CInputHandler::CKeyState;
using key_t = CInputHandler::key_t;
using key_callback_t = CInputHandler::key_callback_t;
using key_typed_callback_t = CInputHandler::key_typed_callback_t;
using global_key_callback_t = CInputHandler::global_key_callback_t;

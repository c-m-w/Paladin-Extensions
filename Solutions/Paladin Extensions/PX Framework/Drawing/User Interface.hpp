/// User Interface.hpp

#pragma once

namespace PX
{
	namespace UI
	{
		namespace Manager
		{
			/** \brief Contains information regarding GUI drawing. */
			PX_SDK nk_context* pContext;
			/** \brief Title of the GUI window. */
			PX_SDK Types::cstr_t szNuklearWindowTitle;

			/** \brief Available fonts. */
			enum EFont
			{
				FONT_TAHOMA,
				FONT_TAHOMABOLD,
				FONT_ROBOTO,
				FONT_ROBOTOBOLD,
				FONT_ROBOTOSMALL,
				FONT_ROBOTOBOLDSMALL,
				FONT_ENVY,
				FONT_MAX
			};

			/** \brief Initialize the GUI for drawing interactable windows. */
			/**	\param szApplicationTitle The subtitle of the GUI window. */
			void PX_API Initialize( Types::cstr_t szApplicationTitle );
			/** \brief Clean up the GUI library for shutdown. */
			void PX_API OnRelease( );
			/** \brief Sets a new size for the GUI window. */
			void PX_API Resize( unsigned, unsigned );
			/** \brief Handles events to interact with the GUI. */
			bool PX_API OnEvent( HWND, UINT, WPARAM, LPARAM );
			/** \brief Render the GUI. */
			/**	\return true - GUI should be drawn again.\n false - GUI should not be drawn again. */
			bool PX_API Render( );
			/** \brief Called when widgets should be drawn onto the GUI window. */
			void PX_API SetLayout( );
		}

		namespace Widgets
		{
			/** \brief Used for buttons, to indicate which corners should and should not be rounded.\n
						LEFT - Rightmost corners will not be rounded, leftmost will be.\n
						CENTER - No corners will be rounded.\n
						RIGHT - Rightmost corners will be rounded, leftmost will not be. */
			enum class EPosition
			{
				LEFT,
				CENTER,
				RIGHT
			};

			/** \brief Type of row to begin.\n Dynamic - The width of each column varies and is determined by a ratio.\n
						Static - The width of each column is fixed and is determined by a static amount. It may be altered with SetRowWidth( ).\n
						Custom - Position and size of widgets may be altered using PushCustomRow( ). */
			enum ERowType
			{
				ROW_DYNAMIC,
				ROW_STATIC,
				ROW_CUSTOM,
				ROW_MAX
			};

			/** \brief Amount of widgets currently occupying the row. */
			PX_SDK int iCurrentRowUsedColumns;
			/** \brief Maximum amount of widgets the current row can hold. */
			PX_SDK int iCurrentRowMaxColumns;

			/** \brief Checks whether or not the mouse is hovering the next widget's render bounds. */
			/**	\return true - Mouse is hovering next widget.\n false - Mouse is not hovering next widget. */
			bool PX_API HoveringNextWidget( );
			nk_flags PX_API EditTextBox( struct nk_context* ctx, nk_flags flags, char* buffer, int max, nk_plugin_filter filter );
			/** \brief Creates a window header for the GUI window. */
			/**	\param szTitle Title of the window. */
			/**	\param szApplicationTitle Subtitle of the window. */
			/**	\param fnMinimizeCallback Called when the minimize button is pressed. */
			/**	\param fnCloseCallback Called when the close button is pressed. */
			void PX_API Header( Types::cstr_t szTitle, Types::cstr_t szApplicationTitle, Types::fn_callback_t fnMinimizeCallback, Types::fn_callback_t fnCloseCallback );
			/** \brief Draws a forum-theme rectangular button which is used for very general categories. */
			/**	\param szText Text the button will display. */
			/**	\param bActive Changes the color style of the button. Used for a toggle effect. */
			/**	\return true - Button was pressed.\n false - Button was not interacted with. */
			bool PX_API PrimaryTab( Types::cstr_t szText, bool bActive );
			/** \brief More specific than a primary tab, used for sections within a primary tab. */
			/**	\param szText Text the button will display. */
			/**	\param bActive Changes the color and style of the button. Used for a toggle effect. */
			/**	\return true - Button was pressed.\n false - Button was not interacted with. */
			bool PX_API SecondaryTab( Types::cstr_t szText, bool bActive );
			/** \brief Creates a rectangular space, to separate widgets vertically all the way across a GUI window. */
			/**	\param iRed Red amount. */
			/**	\param iGreen Green amount. */
			/**	\param iBlue Blue amount. */
			/**	\param uStartHeight Y value of where the separator should begin. */
			/**	\param bUpperBorder Whether or not a border should be drawn on the top of the separator, as a partial outline. */
			void PX_API Separator( int iRed, int iGreen, int iBlue, unsigned uStartHeight, bool bUpperBorder = false );
			/** \brief General purpose button. */
			/**	\param pPosition Position of the button which controls rounding. */
			/**	\param szText Text the button will display. */
			/**	\param bActive Changes the color and style of the button. Used for a toggle effect. */
			/**	\return true - Button was pressed.\n false - Button was not interacted with. */
			bool PX_API Button( EPosition pPosition, const char *szText, bool bActive );
			/** \brief Creates a checkbox with a label. */
			/**	\param szText Text the label will display. */
			/**	\param bActive Whether or not the checkbox is active. */
			void PX_API Checkbox( Types::cstr_t szText, bool *bActive );

			/** \brief Creates primary tabs for navigation, using previously defined widgets. */
			/**	\param uStartX X value at which the tabs should be rendered at. */
			/**	\param uStartY Y value at which the tabs should be rendered at. */
			/**	\param uButtonWidth Width of the tabs. */
			/**	\param uButtonHeight Height of the tabs. */
			/**	\param dqButtons Deque of the tabs to render. */
			/**	\param uActiveButton Current active button, for a toggle effect. */
			/**	\return -1 - No button was clicked.\n >= 0 - Index of the button that was clicked in the deque. */
			int PX_API Tabs( unsigned uStartX, unsigned uStartY, unsigned uButtonWidth, unsigned uButtonHeight, std::deque< Types::cstr_t > dqButtons, unsigned uActiveButton );
			/** \brief Creats subtabs for navigation, using previously defined widgets. */
			/**	\param uStartX X value at which the tabs should be rendered at. */
			/**	\param uStartY Y value at which the tabs should be rendered at. */
			/**	\param uButtonWidth Width of the tabs. */
			/**	\param uButtonHeight Height of the tabs. */
			/**	\param dqButtons Deque of the tabs to render. */
			/**	\param uActiveButton Current active button, for a toggle effect. */
			/**	\return -1 - No button was clicked.\n >= 0 - Index of the button that was clicked in the deque. */
			int PX_API Subtabs( unsigned uStartX, unsigned uStartY, unsigned uButtonWidth, unsigned uButtonHeight, std::deque< Types::cstr_t > dqButtons, unsigned uActiveButton );

			/** \brief Creates a groupbox for widget organization. */
			/**	\param uStartX X position of the groupbox. */
			/**	\param uStartY Y position of the groupbox. */
			/**	\param uBoxWidth Width of the groupbox. */
			/**	\param uBoxHeight Height of the groupbox. */
			/**	\param szTitle Title of the groupbox. */
			void PX_API BeginGroupbox( unsigned uStartX, unsigned uStartY, unsigned uBoxWidth, unsigned uBoxHeight, Types::cstr_t szTitle );
			/** \brief Ends a groupbox. Must be called after BeginGroupbox( ) else an exception will be thrown. */
			void PX_API EndGroupbox( );

			/** \brief Edit the color that was associated with the color button that was clicked, whose address was stored in a pointer.\n A popup window will be created above everything else and be handled at the end of Render( ) automatically. */
			void PX_API ColorPicker( );
			void PX_API ColorButton( Types::cstr_t, Types::byte_t* );

			int PX_API Combobox( unsigned, unsigned, Types::cstr_t, std::deque< Types::cstr_t >, unsigned );
			void PX_API ComboboxMulti( unsigned, unsigned, Types::cstr_t, std::deque< Types::cstr_t >, std::deque< bool >& );

			template< typename _t > _t PX_API Inputbox( unsigned, char* );

			int PX_API Slider( Types::cstr_t, char*, int, int, int, unsigned, unsigned, unsigned, unsigned, unsigned );
			float PX_API Slider( Types::cstr_t, char*, float, float, float, unsigned, unsigned, unsigned, unsigned, unsigned );

			void PX_API BeginRow( unsigned, unsigned, ERowType );

			void PX_API SetRowWidth( float );
			void PX_API Spacing( unsigned = 1 );
			void PX_API VerticalSpacing( unsigned = 5 );
			void PX_API PushCustomRow( unsigned, unsigned, unsigned, unsigned );
		}
	}
}

#include "User Interface.inl"

/// User Interface.hpp

#pragma once

namespace PX::UI
{
	/** \brief Used for managing the user interface. */
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
		/** \brief Calculates text dimensions with the current font. */
		/**	\param szText Text to calculate the bounds for. */
		/**	\param uRowHeight Height of the row that the text is in. */
		/**	\return Dimensions of the text. */
		struct nk_vec2 PX_API CalculateTextBounds( Types::cstr_t szText, unsigned uRowHeight /*= 30*/ );
		/** \brief Sets the font for rendering with Nuklear. */
		/**	\param fntDesiredFont Desired font enumeration index. */
		void PX_API SetFont( EFont fntDesiredFont );
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
		/** \brief Draws an example demonstrating usage of all widgets. */
		void PX_API Example( );
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

		/** \brief Type of row to begin.\n 
					Dynamic - The width of each column varies and is determined by a ratio.\n
					Static - The width of each column is fixed and is determined by a static amount. It may be altered with SetRowWidth( ).\n
					Custom - Position and size of widgets may be altered using PushCustomRow( ). */
		enum ERowType
		{
			ROW_DYNAMIC,
			ROW_STATIC,
			ROW_CUSTOM,
			ROW_MAX
		};

		// TODO: Add documentation about what each widget's row type requirement is.
		// TODO: Add checking for rows being full in all of the widget functions.

		/** \brief Amount of widgets currently occupying the row. */
		PX_SDK int iCurrentRowUsedColumns;
		/** \brief Maximum amount of widgets the current row can hold. */
		PX_SDK int iCurrentRowMaxColumns;
		/** \brief Color pointer that is being edited. */
		PX_SDK Types::color_t* pActiveEditColor = nullptr;

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
		/** \brief Draws a forum-theme rectangular button which is used for very general categories.\n Uses one column. */
		/**	\param szText Text the button will display. */
		/**	\param bActive Changes the color style of the button. Used for a toggle effect. */
		/**	\return true - Button was pressed.\n false - Button was not interacted with. */
		bool PX_API PrimaryTab( Types::cstr_t szText, bool bActive );
		/** \brief More specific than a primary tab, used for sections within a primary tab.\n Uses one column. */
		/**	\param szText Text the button will display. */
		/**	\param bActive Changes the color and style of the button. Used for a toggle effect. */
		/**	\return true - Button was pressed.\n false - Button was not interacted with. */
		bool PX_API SecondaryTab( Types::cstr_t szText, bool bActive );
		/** \brief Creates a rectangular space, to separate widgets vertically all the way across a GUI window.\n Not to be put in a row. */
		/**	\param iRed Red amount. */
		/**	\param iGreen Green amount. */
		/**	\param iBlue Blue amount. */
		/**	\param uStartHeight Y value of where the separator should begin. */
		/**	\param bUpperBorder Whether or not a border should be drawn on the top of the separator, as a partial outline. */
		void PX_API Separator( int iRed, int iGreen, int iBlue, unsigned uStartHeight, bool bUpperBorder = false );
		/** \brief General purpose button.\n Uses one column. */
		/**	\param pPosition Position of the button which controls rounding. */
		/**	\param szText Text the button will display. */
		/**	\param bActive Changes the color and style of the button. Used for a toggle effect. */
		/**	\return true - Button was pressed.\n false - Button was not interacted with. */
		bool PX_API Button( EPosition pPosition, const char *szText, bool bActive );
		/** \brief Creates a checkbox with a label.\n Uses two columns. */
		/**	\param szText Text the label will display. */
		/**	\param bActive Whether or not the checkbox is active. */
		void PX_API Checkbox( Types::cstr_t szText, bool *bActive );

		/** \brief Creates primary tabs for navigation, using previously defined widgets.\n Not to be put in a row. */
		/**	\param uStartX X value at which the tabs should be rendered at. */
		/**	\param uStartY Y value at which the tabs should be rendered at. */
		/**	\param dqButtons Deque of the tabs to render. */
		/**	\param uActiveButton Current active button, for a toggle effect. */
		/**	\return -1 - No button was clicked.\n >= 0 - Index of the button that was clicked in the deque. */
		int PX_API Tabs( unsigned uStartX, unsigned uStartY, const std::deque< Types::cstr_t >& dqButtons, unsigned uActiveButton );
		/** \brief Creats subtabs for navigation, using previously defined widgets.\n Not to be put in a row. */
		/**	\param uStartX X value at which the tabs should be rendered at. */
		/**	\param uStartY Y value at which the tabs should be rendered at. */
		/**	\param uButtonWidth Width of the tabs. */
		/**	\param uButtonHeight Height of the tabs. */
		/**	\param dqButtons Deque of the tabs to render. */
		/**	\param uActiveButton Current active button, for a toggle effect. */
		/**	\return -1 - No button was clicked.\n >= 0 - Index of the button that was clicked in the deque. */
		int PX_API SubTabs( unsigned uStartX, unsigned uStartY, unsigned uButtonWidth, unsigned uButtonHeight, const std::deque< Types::cstr_t >& dqButtons, unsigned uActiveButton );
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
		/** \brief Creates a color button that the user can set the color for if clicked.\n The color picker is handled automatically if the button is clicked.\n Uses one column. */
		/**	\param szSubject What the color is for. */
		/**	\param pColor Pointer to the color that will be edited if the button is clicked. */
		void PX_API ColorButton( Types::cstr_t szSubject, Types::color_t* pColor );

		/** \brief Creates a combobox for the user to select an option within.\n Uses one column. */
		/**	\param uButtonHeight Height of each of the buttons inside the combobox. */
		/** \param szTitle Title of the combobox. */
		/**	\param dqOptions Options that should be available inside the combobox. */
		/**	\param uSelectedOption Currently selected option. */
		/**	\return -1 - Nothing was selected.\n >= 0 - Something was selected, the index for the option inside the deque of options. */
		int PX_API Combobox( unsigned uButtonHeight, Types::cstr_t szTitle, const std::deque< Types::cstr_t >& dqOptions, unsigned uSelectedOption );
		/** \brief Creates a combobox with multiple options which can all be enabled or disabled.\n Uses one column. */
		/**	\param uButtonHeight Height of each of the buttons inside the combobox. */
		/**	\param szTitle Title of the combobox. */
		/**	\param dqOptions Options that should be available inside the combobox. */
		/**	\param dqEnabledOptions List of the options that are enabled in the combobox. */
		void PX_API ComboboxMulti( unsigned uButtonHeight, Types::cstr_t szTitle, const std::deque< Types::cstr_t >& dqOptions, std::deque< bool >& dqEnabledOptions );

		/** \brief Creates a box for the user to input data.\n Uses one column. */
		/**	\tparam _t Can be either float, char* or int. */
		/**	\param uMaxCharacters Maximum amount of characters for the inputbox to allow. */
		/**	\param szBuffer Buffer for the value of the text box. */
		/**	\return Value of the text box. */
		template< typename _t > _t PX_API Inputbox( unsigned uMaxCharacters, char* szBuffer );

		/** \brief Creates a slider whose value label can be clicked to manually input a value.\n It steps 1/20th of the slidable distance.\n Uses three columns. */
		/**	\param szTitle Title of the slider. */
		/**	\param szInputBuffer Buffer for the value of the slider. */
		/**	\param iMin Minimum value. */
		/**	\param iMax Maximum value. */
		/**	\param iCurrentValue Current value of the slider. */
		/**	\param uStartX X coordinate at which the slider should be rendered. */
		/**	\param uStartY Y coordinate at which the slider should be rendered. */
		/**	\param uWidth Width of the slider. */
		/**	\param uHeight Height of the slider. */
		/**	\return Value of the slider. */
		int PX_API Slider( Types::cstr_t szTitle, char *szInputBuffer, int iMin, int iMax, int iCurrentValue, unsigned uStartX, unsigned uStartY, unsigned uWidth, unsigned uHeight );
		/** \brief Creates a slider whose value label can be clicked to manually input a value.\n It steps 1/20th of the slidable distance.\n Uses three columns. */
		/**	\param szTitle Title of the slider. */
		/**	\param szInputBuffer Buffer for the value of the slider. */
		/**	\param flMin Minimum value. */
		/**	\param flMax Maximum value. */
		/**	\param flCurrentValue Current value of the slider. */
		/**	\param uStartX X coordinate at which the slider should be rendered. */
		/**	\param uStartY Y coordinate at which the slider should be rendered. */
		/**	\param uWidth Width of the slider. */
		/**	\param uHeight Height of the slider. */
		/**	\return Value of the slider. */
		float PX_API Slider( Types::cstr_t szTitle, char *szInputBuffer, float flMin, float flMax, float flCurrentValue, unsigned uStartX, unsigned uStartY, unsigned uWidth, unsigned uHeight, unsigned uDigits );

		/** \brief Begins a new row for widgets to be placed in. */
		/**	\param uRowHeight Initial height of the row.\n May be modified if the row type is custom. */
		/**	\param uColumns Amount of widgets the row can hold. */
		/**	\param rowType Type of row to begin. */
		void PX_API BeginRow( unsigned uRowHeight, unsigned uColumns, ERowType rowType );
		/** \brief Ends the row that was begun. */
		void PX_API EndRow( );

		/** \brief Sets the row width, which consequently will change the width of the widget in the next column. */
		/**	\param flRowWidth New width of the widget. */
		void PX_API SetRowWidth( float flRowWidth );
		/** \brief Creates a space in a row which uses up a column. */
		/**	\param uColumns Amount of columns to space. */
		void PX_API Spacing( unsigned uColumns = 1 );
		/** \brief Add vertical blank space between rows. */
		/**	\param uPixels Amount of pixels to space. */
		void PX_API VerticalSpacing( unsigned uPixels = 5 );
		/** \brief Modify a custom row's properties. */
		/**	\param uStartX X coordinate modification relative to where the next widget would be drawn if the row wasn't being modified. */
		/**	\param uStartY Y coordinate modification relative to where the next widget would be drawn if the row wasn't being modified. */
		/**	\param uWidth New width. */
		/**	\param uHeight New height. */
		void PX_API PushCustomRow( unsigned uStartX, unsigned uStartY, unsigned uWidth, unsigned uHeight );
	}
}

#include "User Interface.inl"

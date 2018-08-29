/// User Interface.hpp

#pragma once

namespace PX::UI
{
	/** \brief Used for managing the user interface. */
	namespace Manager
	{
		PX_DEF GROUPBOX_COLUMN_WIDTH = 150;
		PX_DEF CHECKBOX_ICON_WIDTH = 25;
		PX_DEF COLOR_BUTTON_WIDTH = 15;
		PX_DEF COLOR_BUTTON_PADDING = 2;
		PX_DEF KEYBIND_BUTTON_WIDTH = 60;
		PX_DEF KEYBIND_BUTTON_PADDING = 2;

		/** \brief Contains information regarding GUI drawing. */
		PX_SDK nk_context* pContext;
		/** \brief Title of the GUI window. */
		PX_SDK char* szNuklearWindowTitle;
		PX_SDK Render::ECursor curCurrent;
		PX_SDK bool bFoundHoverTarget = false;

		enum
		{
			TEXTURE_LOGO,
			TEXTURE_LOGO_LOADING,
			TEXTURE_ICON_CSGO,
			TEXTURE_ICON_PUBG,
			TEXTURE_ICON_RSIX,
			TEXTURE_CURSOR_ARROW,
			TEXTURE_CURSOR_HAND,
			TEXTURE_CURSOR_IBEAM,
			TEXTURE_MAX
		};

		struct texture_t
		{
			unsigned uWidth, uHeight;
			IDirect3DTexture9* pTexture;
			D3DXIMAGE_INFO iiImage;
			std::wstring wstrFileName;
			texture_t( unsigned _uWidth, unsigned _uHeight, std::wstring _wstrFileName, IDirect3DTexture9* _pTexture = nullptr ): iiImage( D3DXIMAGE_INFO( ) )
			{
				uWidth = _uWidth;
				uHeight = _uHeight;
				pTexture = _pTexture;
				wstrFileName = _wstrFileName;
			}
		};

		struct texture_queue_t
		{
			int iTexture;
			D3DXVECTOR3 vecLocation;
			D3DCOLOR clrColor;
			texture_queue_t( int _iTexture, D3DXVECTOR3 _vecLocation, D3DCOLOR _clrColor = D3DCOLOR_ARGB( 255, 255, 255, 255 ) )
			{
				iTexture = _iTexture;
				vecLocation = _vecLocation;
				clrColor = _clrColor;
			}
		};

		PX_SDK std::vector< texture_t > vecTextures;
		PX_SDK std::vector< texture_queue_t > vecImageQueue;

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

		void PX_API InitializeNuklear( );
		/** \brief Initialize the GUI for drawing interactable windows. */
		/**	\param _szApplicationTitle The subtitle of the GUI window. */
		/** \return true - Initialization was successful.\n false - Initialization was not successful. */
		bool PX_API InitializeUI( Types::cstr_t _szApplicationTitle, unsigned uWidth = Render::uWindowWidth, unsigned uHeight = Render::uWindowHeight );
		void PX_API Destruct( );
		/** \brief Calculates text dimensions with the current font. */
		/**	\param szText Text to calculate the bounds for. */
		/**	\param uRowHeight Height of the row that the text is in. */
		/**	\return Dimensions of the text. */
		struct nk_vec2 PX_API CalculateTextBounds( Types::cstr_t szText, unsigned uRowHeight /*= 30*/ );
		/** \brief Sets the font for rendering with Nuklear. */
		/**	\param fntDesiredFont Desired font enumeration index. */
		void PX_API SetFont( EFont fntDesiredFont );
		/** \brief Frees memory that needs to be before calling IDirect3DDevice9::Reset( ).\n
					Must be called before reset else it will fail. */
		void PX_API OnReset( );
		/** \brief Recreates textures once the IDirect3DDevice9::Reset( ) was successful.\n
					Must be called after reset succeeds or textures will not be drawn. */
		void PX_API OnSuccessfulReset( int iWidth, int iHeight );
		/** \brief Handles events to interact with the GUI. */
		bool PX_API HandleEvent( HWND, UINT, WPARAM, LPARAM );
		/** \brief Render the GUI. */
		/**	\return true - GUI should be drawn again.\n false - GUI should not be drawn again. */
		bool PX_API Render( );

		std::array< unsigned, 2 > PX_API GetCurrentWindowDimensions( );
		/** \brief Called when widgets should be drawn onto the GUI window. */
		void PX_API SetLayout( );
		/** \brief Draws an example demonstrating usage of all widgets. */
		void PX_API Example( );
		bool PX_API MouseHoveringRectangle( unsigned x, unsigned y, unsigned width, unsigned height );
		void PX_API SetWidgetPosition( unsigned x, unsigned y );
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
		PX_SDK Types::color_sequence_t* pActiveEditColor = nullptr;

		/** \brief Checks whether or not the mouse is hovering the next widget's render bounds. */
		/**	\return true - Mouse is hovering next widget.\n false - Mouse is not hovering next widget. */
		bool PX_API HoveringNextWidget( );
		nk_flags PX_API EditTextBox( struct nk_context* ctx, nk_flags flags, char* buffer, int max, nk_plugin_filter filter );
		void PX_API SetWidgetActive( Render::ECursor curSetCursor );
		void PX_API Tooltip( Types::cstr_t szText );
		/** \brief Creates a window header for the GUI window. */
		/**	\param szTitle Title of the window. */
		/**	\param _szApplicationTitle Subtitle of the window. */
		/**	\param fnMinimizeCallback Called when the minimize button is pressed. */
		/**	\param fnCloseCallback Called when the close button is pressed. */
		void PX_API Header( Types::cstr_t szTitle, Types::cstr_t _szApplicationTitle, unsigned uFillHeight = 102u, Types::callback_t fnMinimizeCallback = nullptr, Types::callback_t fnCloseCallback = nullptr );
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
		/** \brief Creates a rectangular space, to separate widgets vertically all the way across a GUI window.
			\n Not to be put in a row. */
		/**	\param iRed Red amount. */
		/**	\param iGreen Green amount. */
		/**	\param iBlue Blue amount. */
		/**	\param uStartHeight Y value of where the separator should begin. */
		/** \param pLinkList List of links to have in the separator for users to click for quick access to the site for convenience. */
		/**	\param bUpperBorder Whether or not a border should be drawn on the top of the separator, as a partial outline. */
		void PX_API Separator( int iRed, int iGreen, int iBlue, unsigned uStartHeight, const Types::links_t* pLinkList = nullptr, bool bUpperBorder = false );
			/** \brief General purpose button.\n Uses one column. */
		/**	\param pPosition Position of the button which controls rounding. */
		/**	\param szText Text the button will display. */
		/**	\param bActive Changes the color and style of the button. Used for a toggle effect. */
		/**	\param bActive Modifies the color and hoverability of the button. */
		/**	\return true - Button was pressed.\n false - Button was not interacted with. */
		bool PX_API Button( EPosition pPosition, const char *szText, bool bActive, bool bDisabled, Types::cstr_t szTooltip = nullptr );
		/** \brief Creates a checkbox with a label.\n Uses two columns. */
		/**	\param szText Text the label will display. */
		/**	\param bActive Whether or not the checkbox is active. */
		void PX_API Checkbox( Types::cstr_t szText, bool *bActive, Types::cstr_t szTooltip = nullptr );

		/** \brief Creates primary tabs for navigation, using previously defined widgets.
			\n Not to be put in a row. */
		/**	\param uStartX X value at which the tabs should be rendered at. */
		/**	\param uStartY Y value at which the tabs should be rendered at. */
		/**	\param dqButtons Deque of the tabs to render. */
		/**	\param uActiveButton Current active button, for a toggle effect. */
		/**	\return -1 - No button was clicked.\n >= 0 - Index of the button that was clicked in the deque. */
		int PX_API Tabs( unsigned uStartX, unsigned uStartY, const std::deque< Types::cstr_t >& dqButtons, unsigned uActiveButton );
		/** \brief Creats subtabs for navigation, using previously defined widgets.
			\n Not to be put in a row. */
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
		bool PX_API BeginGroupbox( unsigned uStartX, unsigned uStartY, unsigned uBoxWidth, unsigned uBoxHeight, Types::cstr_t szTitle );
		/** \brief Ends a groupbox. Must be called after BeginGroupbox( ) else an exception will be thrown. */
		void PX_API EndGroupbox( );

		/** \brief Edit the color that was associated with the color button that was clicked, whose address was stored in a pointer.\n A popup window will be created above everything else and be handled at the end of Render( ) automatically. */
		void PX_API ColorPicker( );
		/** \brief Creates a color button that the user can set the color for if clicked.
			\n The color picker is handled automatically if the button is clicked.
		'	\n Uses one column. */
		/**	\param szSubject What the color is for. */
		/**	\param pSequence Pointer to the color that will be edited if the button is clicked. */
		void PX_API ColorButton( Types::cstr_t szSubject, Types::color_sequence_t* pSequence );

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

		/** \brief Creates a box for the user to input data.
			\n Uses one column. */
		/**	\param uMaxCharacters Maximum amount of characters for the inputbox to allow. */
		/**	\param szBuffer Buffer for the value of the text box. */
		void PX_API Inputbox( unsigned uMaxCharacters, char* szBuffer );
		int PX_API InputboxInteger( unsigned uMaxCharacters, char* szBuffer );
		float PX_API InputboxFloat( unsigned uMaxCharacters, char* szBuffer );

		/** \brief Creates a slider whose value label can be clicked to manually input a value.
			\n It steps 1/20th of the slidable distance.\n Uses three columns. */
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
		int PX_API Slider( Types::cstr_t szTitle, char *szInputBuffer, int iMin, int iMax, int iCurrentValue, unsigned uStartX, unsigned uStartY, unsigned uWidth, unsigned uHeight, bool bIgnorePopup = false );
		/** \brief Creates a slider whose value label can be clicked to manually input a value.
			\n It steps 1/20th of the slidable distance.
			\n Uses three columns. */
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

		void PX_API Text( Types::cstr_t szText, Types::color_t clrText );

		void PX_API JustifiedText( Types::cstr_t szLeft, Types::cstr_t szRight, Types::color_t clrLeft, Types::color_t clrRight, unsigned uTotalLength );

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

#if defined PX_USE_NAMESPACES
using namespace PX::UI;
using namespace PX::UI::Manager;
using namespace PX::UI::Widgets;
#endif

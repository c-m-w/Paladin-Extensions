/// Interface.hpp

#pragma once

namespace Interface
{
	constexpr auto TITLE_HEIGHT = 16;
	constexpr auto WINDOW_ICON_HEIGHT = 18;
	constexpr auto STANDARD_HEIGHT = 12;
	constexpr auto CHECKBOX_TEXT_HEIGHT = 11.5f;

	inline const static color_t CLEAR = color_t( { 0, 0, 0, 0 } );
	inline const static color_t WHITE = color_t( { 255, 255, 255, 255 } );
	inline const static color_t SHADOW = color_t( { 0, 0, 0, 100 } );
	inline const static color_t BLACK = color_t( { 0, 0, 0, 255 } );
	inline const static color_t BACKGROUND_DARK = color_t( { 33, 36, 40, 255 } );
	inline const static color_t BACKGROUND_LIGHT = color_t( { 61, 65, 72, 255 } );
	inline const static color_t BACKGROUND_DEFAULT = color_t( { 45, 50, 56, 255 } );
	inline const static color_t BACKGROUND_DIM = color_t( { 0, 0, 0, 100 } );
	inline const static color_t OUTLINE_DARK = color_t( { 56, 60, 64, 255 } );
	inline const static color_t OUTLINE_LIGHT = color_t( { 73, 76, 83, 255 } );
	inline const static color_t TEXT_NORMAL = color_t( { 255, 255, 255, 255 } );
	inline const static color_t TEXT_DARK = color_t( { 175, 180, 187, 255 } );
	inline const static color_t BLUE = color_t( { 34, 145, 232, 255 } );
	inline const static color_t TRANSLUCENT_BLUE = color_t( { 34, 145, 232, 100 } );
	inline const static color_t VIVID_BLUE = color_t( { 13, 59, 95, 255 } );
	inline const static color_t VIVID_BLUE_ACTIVE = color_t( { 4, 56, 98, 255 } );
	inline const static color_t DARK_BLUE = color_t( { 43, 60, 75, 255 } );
	inline const static color_t BUTTON_TEXT = color_t( { 33, 150, 243, 255 } );
	inline const static color_t BUTTON_BACKGROUND_DORMANT = color_t( { 0, 0, 0, 0 } );
	inline const static color_t BUTTON_BACKGROUND_HOVER = color_t( { 33, 150, 243, 26 } );
	inline const static color_t BUTTON_BACKGROUND_ACTIVE = color_t( { 33, 150, 243, 51 } );
	static auto NO_CALLBACK = [ & ]( )
	{ };

	class IWidget;
	class IContainer;
	class CWindow;
	class CToolTip;
	typedef std::function< void( ) > callback_t;
	typedef std::function< void( IWidget * ) > invoke_callback_t;

	struct
	{
		std::deque< CWindow* > vecWindows { };
		IWidget *pHoveringWidget = nullptr, *pActiveWidget = nullptr;
		CWindow *pForegroundWindow = nullptr;
		Utilities::location_t locMouse { };

		void BringWidgetContainingWindowToFront( IWidget *pWidget );
		CWindow *GetForegroundWindow( );
		void DoToolTip( );
		void ApplyCursor( );
		void UpdateContainerWidgets( IContainer *pContainer );
	} extern _WidgetContext;

	enum
	{
		POSITION_TOP,
		POSITION_RIGHT,
		POSITION_BOTTOM,
		POSITION_LEFT,
		POSITION_MAX
	};

	struct padding_t
	{
		float flPadding[ POSITION_MAX ];

		padding_t( );
		padding_t( float *pPadding );
		padding_t( float flTop, float flRight, float flBottom, float flLeft );

		float Horizontal( );
		float Vertical( );
	};

	struct row_t
	{
		static constexpr auto DEFAULT_HEIGHT = 30.f;

		padding_t padBorder;
		float flLeftFill, flRightFill;
		rectangle_t recLocation;
		IContainer *pParent;
		int iRowNumber;

		row_t( );
		row_t( padding_t _padBorder, float _flHeight );
	};

	class IWidget
	{
		bool IsCovered( );

	protected:

		std::vector< polygon_buffer_t > vecGeometry { };

	public:

		enum
		{
			ACTIVE,
			HOVER,
			DORMANT,
			STATE_MAX
		};

		enum
		{
			LEFT,
			RIGHT
		};

		enum
		{
			CONTAINER,
			POPUP,
			IMAGE,
			LABEL,
			BUTTON_ICON,
			BUTTON,
			INPUTBOX,
			SLIDER,
			SCROLLBAR,
			COMBOBOX
		};

		static constexpr auto DEFAULT_ALIGNMENT = LEFT;

		int iType, iCursor;
		unsigned uState;
		color_t clrForeground[ STATE_MAX ], clrBackground[ STATE_MAX ], *pCurrentForeground, *pCurrentBackground;
		int iAlignment;
		rectangle_t recLocation;
		padding_t padBorder;
		bool bPressing;
		CToolTip *pToolTip;
		IWidget *pParentContainer = nullptr;
		int iRow = -1;

		IWidget( ) = default;
		IWidget( int _iType, int _iCursor, CToolTip *_pToolTip );
		IWidget( int _iType, int _iCursor, padding_t _padBorder, color_t clrForegroundActive, color_t clrForegroundHover, color_t clrForegroundDormant, color_t clrBackgroundActive, color_t clrBackgroundHover, color_t clrBackgroundDormant, CToolTip *_pToolTip );
		IWidget( int _iType, int _iCursor, padding_t _padBorder, color_t clrColor, CToolTip *_pToolTip );

		virtual void Initialize( );
		virtual void NoLongerActive( );
		virtual void SetRectangle( rectangle_t recNew );
		virtual void MouseMove( Utilities::location_t locMouse );
		virtual void KeyTyped( unsigned uKey );
		virtual void Event( unsigned uKey, CKeyState ksState );
		virtual bool Scroll( short sDelta );

		virtual void Draw( ) = 0;
		virtual void InitializeDrawingInformation( ) = 0;
		void Setup( );
		void ModifyActivity( int iState );
		void PreDraw( );
		rectangle_t GetAbsoluteLocation( );
		rectangle_t GetRelativeLocation( );
		CWindow *GetContainingWindow( );
		bool IsActive( );
		void SetActive( );
		void SetHovered( );
	};

	class CLabel: public IWidget
	{
	public:

		text_t *txtLabel;
		EFontFlags ffFlags;
		callback_t cbOnClick;

		CLabel( ) = default;
		CLabel( padding_t padBorder, text_t *_txtLabel, color_t clrForegroundActive, color_t clrForegroundHover, color_t clrForegroundDormant, color_t clrBackgroundActive, color_t clrBackgroundHover, color_t clrBackgroundDormant, EFontFlags _ffFlags, callback_t _cbOnClick = nullptr );
		CLabel( padding_t padBorder, text_t *_txtLabel, color_t clrBackground, color_t clrText, EFontFlags _ffFlags, callback_t _cbOnClick = nullptr );
		CLabel( padding_t padBorder, text_t *_txtLabel, color_t clrText, EFontFlags _ffFlags, callback_t _cbOnClick = nullptr );

		void Event( unsigned uKey, CKeyState ksState ) override;
		void Draw( ) override;
		void InitializeDrawingInformation( ) override;
	};

	class CButtonLabel: public IWidget
	{
	public:

		text_t *txtLabel;
		invoke_callback_t cbOnClick;
		int iIndex;

		CButtonLabel( padding_t padBorder, text_t *_txtLabel, color_t clrForegroundActive, color_t clrForegroundHover, color_t clrForegroundDormant, color_t clrBackgroundActive, color_t clrBackgroundHover, color_t clrBackgroundDormant, invoke_callback_t _cbOnClick, int _iIndex );

		void Event( unsigned uKey, CKeyState ksState ) override;
		void Draw( ) override;
		void InitializeDrawingInformation( ) override;
	};

	class CButtonIcon: public IWidget
	{
	public:

		void Draw( ) override;
		void Event( unsigned uKey, CKeyState ksState ) override;
	};

	class CButton: public IWidget
	{
	public:

		enum
		{
			LEFT,
			RIGHT,
			CENTER,
			STANDALONE
		};

		constexpr static auto ROUNDING = 0.2f;

		text_t *txtLabel;
		int iType;
		callback_t cbClick;

		CButton( int _iOrientation, const char *szLabel, callback_t cbOnClick, CToolTip *pToolTip = nullptr );

		void InitializeDrawingInformation( ) override;
		void Event( unsigned uKey, CKeyState ksState ) override;
		void Draw( ) override;
	};

	class CImage: public IWidget
	{
	public:

		int iTextureID;

		CImage( ) = default;
		CImage( int _iTextureID );

		void Draw( ) override;
		void InitializeDrawingInformation( ) override;
	};

	class CInputBox: public IWidget
	{
		rectangle_t GetTextSpace( );
		float GetCursorX( );
		float GetSelectionX( );
		void CorrectPosition( );
		void ClampSelection( );
		int GetEndOfNextWord( bool bLeftward );
		void RemoveSelected( );
		int GetHoveringPosition( );

		padding_t padText;
		Utilities::location_t locClick;

	public:

		enum
		{
			NONE,
			ALPHANUMERIC,
			INTEGER,
			FLOAT,
			MAX
		};

		inline static const std::function< bool( char, const char *, int ) > FILTERS[ MAX ]
		{
			[ ]( char chNewCharacter, const char *szCurrent, int iPosition ) // NONE
			{
				return true;
			},
			[ ]( char chNewCharacter, const char *szCurrent, int iPosition ) // LETTER
			{
				return chNewCharacter >= 'a' && chNewCharacter <= 'z'
						|| chNewCharacter >= 'A' && chNewCharacter <= 'Z'
						|| chNewCharacter >= '0' && chNewCharacter <= '9'
						|| chNewCharacter == ' ';
			},
			[ ]( char chNewCharacter, const char *szCurrent, int iPosition ) // INTEGER
			{
				return chNewCharacter == '-' && iPosition == 0 && strchr( szCurrent, '-' ) == nullptr
						|| chNewCharacter >= '0' && chNewCharacter <= '9';
			},
			[ ]( char chNewCharacter, const char *szCurrent, int iPosition ) // FLOAT
			{
				return chNewCharacter == '-' && iPosition == 0 && strchr( szCurrent, '-' ) == nullptr
						|| chNewCharacter == '.' && strchr( szCurrent, '.' ) == nullptr
						|| chNewCharacter >= '0' && chNewCharacter <= '9';
			}
		};
		static constexpr auto ROUND_RATIO = .1f;
		static constexpr auto TEXT_SIZE = 12;

		int iFont, iFilter;
		std::size_t sMaxCharacters;
		std::string strBuffer;
		int iPosition, iSelection, iDisplayBegin;
		float flCharacterWidth, flCharacterHeight;
		callback_t cbOnValueEntered, cbNoLongerActive;

		CInputBox( );
		CInputBox( padding_t padBorder, padding_t _padText, int _iFont, int _iFilter, std::string strStartValue, callback_t _cbOnValueEntered = NO_CALLBACK, callback_t _cbcbNoLongerActive = NO_CALLBACK );

		void NoLongerActive( ) override;
		void InitializeDrawingInformation( ) override;
		void Draw( ) override;
		void MouseMove( Utilities::location_t locMouse ) override;
		void KeyTyped( unsigned uKey ) override;
		void Event( unsigned uKey, CKeyState ksState ) override;
		std::string StringValue( );
		int IntValue( );
		float FloatValue( );
	};

	template< typename _t > class CSlider: public IWidget
	{ };

	template< > class CSlider< int >: public IWidget
	{
	public:

		int iMinimum, iMaximum, iCurrent;

		CSlider( padding_t padBorder, int _iMinimum, int _iMaximum, int _iCurrent );

		void Draw( ) override;
		void MouseMove( Utilities::location_t locMouse ) override;
		void Event( unsigned uKey, CKeyState ksState ) override;
		void InitializeDrawingInformation( ) override;
		bool Scroll( short sDelta ) override;
	};

	template< > class CSlider< float >: public IWidget
	{
	public:

		float flMinimum, flMaximum, flCurrent;

		CSlider( padding_t padBorder, float _flMinimum, float _flMaximum, float _flCurrent );

		void Draw( ) override;
		void MouseMove( Utilities::location_t locMouse ) override;
		void Event( unsigned uKey, CKeyState ksState ) override;
		void InitializeDrawingInformation( ) override;
		bool Scroll( short sDelta ) override;
	};

	class CColorButton: public IWidget
	{
	public:

		static constexpr auto ROUNDING = 0.25f;

		color_t *pColor;

		CColorButton( padding_t padBorder, color_t *_pColor );

		void Draw( ) override;
		void InitializeDrawingInformation( ) override;
	};

	class CScrollbar: public IWidget
	{
		Utilities::location_t locDragStart { };

	public:

		constexpr static auto DEFAULT_SCROLL_FACTOR = 0.4f;
		constexpr static auto DEFAULT_DURATION = 1500ull;
		constexpr static auto DEFAULT_WIDTH = 4.f,
							  DEFAULT_PADDING = 4.f;

		CScrollbar( );

		void Draw( ) override;
		void InitializeDrawingInformation( ) override;
		void Event( unsigned uKey, CKeyState ksState ) override;
		bool Scroll( short sDelta ) override;
		void MouseMove( Utilities::location_t locMouse ) override;
	};

	class CCombobox: public IWidget
	{
		std::vector< text_t* > vecText;
		std::vector< CButtonLabel* > vecOptions;

	public:

		constexpr static auto ROUNDING = 0.1f,
			TRIANGLE_WIDTH = 8.f,
			TRIANGLE_HEIGHT = 5.f;

		text_t *txtTitle;
		int iValue;

		CCombobox( text_t *_txtTitle, std::initializer_list< text_t* > initOptions );

		void Draw( ) override;
		void InitializeDrawingInformation( ) override;
		void Event( unsigned uKey, CKeyState ksState ) override;
	};

	class IContainer: public IWidget
	{
		float flUsedVerticalSpace = 0.f;
		int iRowCount = 0;

	protected:
		CScrollbar sbScrollbar { };

	public:

		enum EContainerFlags
		{
			FLAG_CONTAINER_NONE = 0,
			FLAG_CONTAINER_SCROLLABLE = 1 << 0,
		};

		std::vector< row_t > vecRows;
		std::vector< IWidget* > vecWidgets { };
		unsigned cfFlags;
		float flScrollAmount = 0.f;
		bool bUpdate = false;

		IContainer( ) = default;
		IContainer( unsigned _cfFlags, padding_t padBorder, color_t clrContainer );
		IContainer( unsigned _cfFlags, padding_t padBorder, color_t clrContainer, rectangle_t _recWindowLocation );
		virtual ~IContainer( ) = default;

		bool Scroll( short sDelta ) override;

		void AddRow( row_t rowNew );
		void ClearRow( int iRow );
		void AddWidgetToRow( IWidget *pWidget, float flWidth, int iRow );
		void AddWidget( IWidget *pWidget, rectangle_t recRelative );
		void RemoveWidget( IWidget *pWidget );
		void VerticalSpacing( float flAmount );
		void Popup( CWindow *_pPopup );

		friend class CScrollbar;
	};

	class CPanel: public IContainer
	{
	public:

		CPanel( padding_t padBorder, color_t clrPanel );

		void Draw( ) override;
		void InitializeDrawingInformation( ) override;
	};

	class CFileSelector: public IContainer
	{
		CLabel lblSubject;
		CInputBox inputFile;
		CButton btnBrowse;
		const char *szExtension;

	public:

		constexpr static char *FILE_EXTENSION_NONE = nullptr;

		CFileSelector( callback_t cbOnFileSelected, const char *szSubject, const char *szFileExtension = FILE_EXTENSION_NONE );

		void Initialize( ) override;
		void InitializeDrawingInformation( ) override;
		void Draw( ) override;
		std::string GetFile( );
	};

	template< typename _t > class CEditLabel: public IContainer
	{
	public:

		CLabel lblDisplay;
		CInputBox inputEdit;
		bool bEditing;

		CEditLabel( padding_t padBorder, padding_t padText );
	};

	template< > class CEditLabel< int >: public IContainer
	{
	public:

		CLabel lblDisplay;
		CInputBox inputEdit;
		bool bEditing;
		int iValue;

		CEditLabel( padding_t _padBorder, padding_t padText, int iFont, int iStartValue );

		void Initialize( ) override;
		void InitializeDrawingInformation( ) override;
		void Draw( ) override;
	};

	template< > class CEditLabel< float >: public IContainer
	{
	public:

		CLabel lblDisplay;
		CInputBox inputEdit;
		bool bEditing;
		int iDigits;
		float flValue;

		CEditLabel( padding_t _padBorder, padding_t padText, int iFont, int _iDigits, float flStartValue );

		void Initialize( ) override;
		void InitializeDrawingInformation( ) override;
		void Draw( ) override;
	};

	class CGroupbox: public IContainer
	{
	public:

		static constexpr auto ROUNDING = 0.05f;

		text_t *txtTitle;

		CGroupbox( padding_t _padBorder, const char *szTitle );

		void InitializeDrawingInformation( ) override;
		void Initialize( ) override;
		void Draw( ) override;
	};

	class CCheckbox: public IContainer
	{
	public:

		static constexpr auto COLOR_BUTTON_WIDTH = 15.f;
		bool *pEnabled;
		CLabel lblIconActive, lblIconDormant, lblLabel;
		std::vector< CColorButton* > vecColors;

		CCheckbox( padding_t padBorder, const char *szLabel, bool *_pEnabled, std::initializer_list< CColorButton* > l );

		void InitializeDrawingInformation( ) override;
		void Initialize( ) override;
		void Draw( ) override;
	};

	class CHeaderPanel: public IContainer
	{
	public:

		int iIconTexture;
		CImage imgIcon;
		CLabel lblTitle, lblSubtitle, lblMinimize, lblClose;
		Utilities::location_t locDragStart;

		CHeaderPanel( );
		CHeaderPanel( const char *szTitle, const char *szSubtitle, callback_t _cbMinimize, callback_t _cbClose, const char *szMinimize, const char *szClose );
		CHeaderPanel( const char *szTitle, const char *szSubtitle, const char *szClose );

		void InitializeDrawingInformation( ) override;
		void Initialize( ) override;
		void Draw( ) override;
		void Event( unsigned uKey, CKeyState ksKeyState ) override;
		void MoveParentWindow( int x, int y );
	};

	class CWindow: public IContainer
	{
	public:

		enum EWindowFlags
		{
			FLAG_WINDOW_NONE = 0,
			FLAG_WINDOW_OUTLINE_ALWAYS = 1 << 0,
			FLAG_WINDOW_OUTLINE_COVERED = 1 << 1,
			FLAG_WINDOW_DIM_BACKGROUND = 1 << 2,
			FLAG_WINDOW_ROUND_CORNERS = 1 << 3,
			FLAG_WINDOW_ANCHOR = 1 << 4,
			FLAG_WINDOW_NONBLOCK = 1 << 5
		};

		static constexpr auto WINDOW_ROUNDING = 0.03f;
		static constexpr auto DEFAULT_FLAGS = FLAG_WINDOW_OUTLINE_COVERED | FLAG_WINDOW_ROUND_CORNERS,
							  POPUP_FLAGS = FLAG_WINDOW_ROUND_CORNERS | FLAG_WINDOW_DIM_BACKGROUND | FLAG_WINDOW_ANCHOR,
							  TOOLTIP_FLAGS = FLAG_WINDOW_OUTLINE_ALWAYS | FLAG_WINDOW_NONBLOCK;

		CHeaderPanel *pHeader;
		CWindow *pPopup;
		unsigned wfFlags;

		// For regular windows
		CWindow( unsigned _wfFlags, rectangle_t _recLocation, const char *szTitle, const char *szSubtitle, callback_t _cbMinimize, callback_t _cbClose );
		// For popup windows, no icon, close will be defined to end the popup and minimize will not exist.
		CWindow( unsigned _wfFlags, rectangle_t _recLocation, const char *szTitle, const char *szSubtitle );
		// Comboboxes, tooltips, etc.
		CWindow( unsigned _wfFlags, rectangle_t _recLocation );
		~CWindow( );

		void InitializeDrawingInformation( ) override;
		void Draw( ) override;
		void Popup( CWindow *_pPopup );
		void ClosePopup( bool bResetWidgets );
		void Pack( );
	};

	class CPathExplorer: public CWindow
	{
		std::string strSelectedPath;
		std::string strDesiredExtension;
		callback_t cbOnPathSelected;
		int iMode;

	public:

		static constexpr char *NO_EXTENSION = nullptr;

		enum EMode
		{
			FILE,
			FOLDER
		};

		CPathExplorer( const char *szSubject, const char *szExtension, callback_t cbOnFileSelected );
		CPathExplorer( const char *szSubject, callback_t cbOnFolderSelected );

		void InitializeDrawingInformation( ) override;
		void Draw( ) override;
		void Initialize( ) override;
	};

	class CToolTip: public CWindow
	{
	public:

		static constexpr float TRIANGLE_WIDTH = 10.f, TRIANGLE_HEIGHT = 6.f;
		inline static const padding_t TEXT_PADDING { 5.f, 5.f, 5.f, 5.f };

		std::vector< CLabel > vecText;
		float flWidgetRatio;

		CToolTip( text_t *_txtToolTip );

		void InitializeDrawingInformation( ) override;
		void Draw( ) override;
	};

	void InitializeInterface( );
	void Shutdown( );
	bool Recreate( );
	void DrawWindows( );
	void AddWindow( CWindow *pWindow );
}

#include "Graphical User Interface.inl"

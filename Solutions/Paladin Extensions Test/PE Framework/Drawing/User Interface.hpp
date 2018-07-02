/// User Interface.hpp

#pragma once

namespace Paladin
{
    class CUserInterface: public CRender, public CWindowInput
    {
	    nk_context *pContext;
        nk_font_atlas *pAtlas;
		struct nk_font *pTahoma, *pTahomaBold, *pRoboto, *pRobotoBold, *pRobotoSmall, *pRobotoBoldSmall;
        const char *szNuklearWindowTitle;
		const char *szApplicationTitle;
		bool bFoundHoverTarget;

    public:
		struct panel_t
    	{
			panel_t( struct nk_rect rcPanelDimensions ) 
			{
				rcPanel = rcPanelDimensions;
			}
			struct nk_rect rcPanel;
			struct nk_context pContext;
		};

		ECursor curFoundCursorType;

		enum class EFont : int
		{
			TAHOMA,
			TAHOMABOLD,
			ROBOTO,
			ROBOTOBOLD,
			ROBOTOSMALL,
			ROBOTOBOLDSMALL
		};

		struct nk_color clrColors[ NK_COLOR_COUNT ];
		nk_color clrTextDormant, clrTextActive;
		nk_style_button btnTopActive, btnTop, btnRegularActive, btnRegular, btnSpecialActive, btnSpecial;

        CUserInterface( const char *, const char *, unsigned *, const wchar_t * = nullptr );
	    void Shutdown( );

    private:
		nk_font *AddFont( std::string, unsigned, struct nk_font_config, unsigned = 0 );
        void InitializeNuklear( );
        bool HandleWindowInput( );
        void RenderUserInterface( );
		bool HoverCheck( ECursor curSetCursor );
		void ResetHoverState( );

    public:
        void InitializeUserInterface( );
        void SetLayout( );
        bool DrawUserInterface( );
		void SetFont( EFont );
		
		class CWidgets
    	{
			struct nk_rect rcLastWidgetLocation;
			bool bBeganRow = false;
			const char *szColorPickerSubject;

		public:
			px_color_t *pActiveEditColor = nullptr;
			enum class EPosition: int
			{
				LEFT,
				CENTER,
				RIGHT
			};

			bool Header( const char *, const char *, unsigned );
			void Separator( unsigned char, unsigned char, unsigned char, unsigned, unsigned = 3, bool = false );
			bool TopButton( const char *, bool );
			bool RegularButton( const char *, bool );
			bool SpecialButton( EPosition, const char *, bool );
			void Checkbox( const char *, unsigned, bool * );
			int Tabs( unsigned, unsigned, unsigned, unsigned, std::deque< const char * >, unsigned );
			int Sidebar( unsigned, unsigned, unsigned, unsigned, std::deque< const char * >, unsigned );
			void BeginGroupbox( unsigned, unsigned, unsigned, unsigned, const char *, unsigned );
			void EndGroupbox( );
			void ColorButton( const char *, px_color_t * );
			void ColorPicker( );
			void NewRow( unsigned = 30, unsigned = 3 );
			void BeginRow( unsigned = 30, unsigned = 6 );
			void SetRowWidth( float );
			void EndRow( );
			void NewStaticRow( unsigned, unsigned = 30, unsigned = 3 );
			void BeginCustomRow( unsigned = 30, unsigned = 3 );
			void PushCustomRow( unsigned, unsigned, unsigned, unsigned );
			void Spacing( unsigned = 1 );
			int menfuck( );
		} wdg;

    private:
        bool bShouldDrawInterface = true;
    } inline *ui;
}

#define M_ITEM_WIDTH 15
#define M_ITEM_PADDING 5
#define M_ITEM_HEIGHT 25 - M_ITEM_PADDING
#define M_DYNAMIC_HEIGHT 25 - M_ITEM_PADDING
#define M_TOOLTIP_DELAY 20

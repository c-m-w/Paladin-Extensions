/// User Interface.hpp

#pragma once

namespace Paladin
{
    class CUserInterface: public CRender, public CWindowInput
    {
	    nk_context *pContext;
        nk_font_atlas *pAtlas;
		struct nk_font *pTahoma, *pTahomaBold, *pRoboto, *pRobotoBold, *pRobotoBoldSmall;
        const char *szNuklearWindowTitle;
		const char *szApplicationTitle;
		bool bFoundHoverTarget;

    public:
		ECursor curFoundCursorType;

		enum class EFont : int
		{
			TAHOMA,
			TAHOMABOLD,
			ROBOTO,
			ROBOTOBOLD,
			ROBOTOBOLDSMALL
		};

		struct nk_color clrColors[ NK_COLOR_COUNT ];
		nk_color clrTextDormant, clrTextActive;
		nk_style_button btnRegularActive, btnRegular, btnSpecialActive, btnSpecial;

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
		public:
			enum class EPosition: int
			{
				LEFT,
				CENTER,
				RIGHT
			};

			bool Header( const char *, const char *, unsigned );
			bool RegularButton( const char *, bool );
			bool SpecialButton( EPosition, const char *, bool );
			void NewRow( unsigned = 30, unsigned = 3 );
			void NewStaticRow( unsigned, unsigned = 30, unsigned = 3 );
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

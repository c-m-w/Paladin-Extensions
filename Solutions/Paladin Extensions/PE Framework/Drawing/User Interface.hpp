/// User Interface.hpp

#pragma once

namespace Paladin
{
    class CUserInterface: public CRender, public CWindowInput
    {
        nk_context *pContext;
        nk_font_atlas *pAtlas;
        struct nk_font *pFontAwesome, *pTahoma, *pRoboto;
        const char *szNuklearWindowTitle;

    public:
        CUserInterface( const char *, unsigned *, const wchar_t * = nullptr );
	    void Shutdown( );

    private:
        void InitializeNuklear( );
        bool HandleWindowInput( );
        void RenderUserInterface( );

    public:
        void InitializeUserInterface( );
        void SetLayout( );
        bool DrawUserInterface( );

    private:
        bool bShouldDrawInterface = true;
    } inline *ui;
}

#define M_ITEM_WIDTH 15
#define M_ITEM_PADDING 5
#define M_ITEM_HEIGHT 25 - M_ITEM_PADDING
#define M_DYNAMIC_HEIGHT 25 - M_ITEM_PADDING
#define M_TOOLTIP_DELAY 20

/// User Interface.hpp

#pragma once

namespace Paladin
{
    class CUserInterface: public CRender, public CWindowInput
    {
        nk_context *pContext { };
        struct nk_font_config *fcFontConfiguration { };
        nk_font_atlas *pAtlas { };
        struct nk_font *pFontAwesome { }, *pTahoma { }, *pRoboto { };
        const char *szNuklearWindowTitle;

    public:
        CUserInterface( const char *,unsigned *, const wchar_t * = nullptr );
	    void Shutdown( );
    private:
        void InitializeNuklear( );
        bool HandleWindowInput( );
        void RenderUserInterface( );
    public:
        void InitializeUserInterface( );
        bool DrawUserInterface( );

		bool bShouldDrawInterface = true;
    } inline *ui;
}

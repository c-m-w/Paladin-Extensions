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
        CUserInterface( const char *, unsigned * );
    private:
        void InitializeNuklear( );
        void HandleWindowInput( );
        virtual void RenderUserInterface( );
    public:
        virtual void InitializeUserInterface( );
        virtual void DrawUserInterface( );
    } inline *ui;
}

/// User Interface.hpp

#pragma once

namespace Paladin
{
    class CUserInterface: public CRender, public CWindowInput
    {
        nk_context *pContext;
        struct nk_font_config *fcFontConfiguration;
        nk_font_atlas *pAtlas;
        struct nk_font *pFontAwesome, *pTahoma, *pRoboto;
        const char *szNuklearWindowTitle;

    public:
        struct SWidget
        {
            enum EWidgetType
            {
                NONE,
                LABEL,
                BUTTON,
                TEXT_BOX,
                CHECK_BOX,
                COMBO_BOX,
                COLOR_PICKER,
                INT_SLIDER,
                FLOAT_SLIDER
            };

            EWidgetType wgtWidgetType = NONE;

            std::string strText;
            std::string strTooltip;

            // Text box
            SWidget( std::string, std::string );

            // Label
            SWidget( std::string, std::string, unsigned );
            unsigned uAlignment;

            // Button
            SWidget( std::string, std::string, std::function< void( ) > );
            std::function< void( ) > fnCallback;
            
            // Check box
            SWidget( std::string, std::string, int * );
            int *pActive;
            
            // Combo box
            SWidget( std::string, std::string, const char *[ ], int, int );
            const char **pItems;
            int iItems;
            int iSelected;

            // Color picker
            SWidget( std::string, std::string, bool, BYTE * );
            bool bUseAlpha;
            BYTE bColor[ 4 ];

            // Int slider
            SWidget( std::string, std::string, int, int, int, int );
            int iMinimum, iValue, iMaximum, iStep;

            // Float slider
            SWidget( std::string, std::string, float, float, float, float );
            float flMinimum, flValue, flMaximum, flStep;

        };
        std::deque< SWidget > dqWidgets;

        CUserInterface( const char *, unsigned *, const wchar_t * = nullptr );
	    void Shutdown( );
    private:
        void InitializeNuklear( );
        bool HandleWindowInput( );
        void RenderUserInterface( );
    public:
        void InitializeUserInterface( );
        bool DrawUserInterface( );

    private:
        bool bShouldDrawInterface = true;
    } inline *ui;
}

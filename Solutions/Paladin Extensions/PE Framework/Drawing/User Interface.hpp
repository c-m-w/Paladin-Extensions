/// User Interface.hpp

#pragma once

namespace Paladin
{
	class CUserInterface: public CRender
	{
		nk_context            *pContext { };
		struct nk_font_config *fcFontConfiguration { };
		nk_font_atlas		  *pAtlas { };
		struct nk_font		  *pFontAwesome { }, *pTahoma { }, *pRoboto { };
		const char			  *szNuklearWindowTitle;

	public:
		CUserInterface( const char *, unsigned[ 2 ] );
	private:
		void InitializeNuklear( );
		void HandleWindowInput( );
		virtual void RenderUserInterface( );
	public:
		virtual void InitializeUserInterface( );
		virtual void DrawUserInterface( );
	} extern *ui;
}

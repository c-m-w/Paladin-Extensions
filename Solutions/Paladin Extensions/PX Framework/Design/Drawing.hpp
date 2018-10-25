/// Drawing.hpp

#pragma once

namespace PX::Drawing
{
	enum class ED3DFont: int
	{
		FNT_TAHOMA,
		FNT_ROBOTO,
		//FONT_ICON,
		FNT_MAX
	};

	PX_SDK ID3DXFont* pFonts[ ED3DFont::FNT_MAX ];

	bool PX_API InitializeDrawing( );
	void PX_API Destruct( );

	void PX_API Polygon( Types::vertex_t* pVertices, std::size_t zVertexCount, std::size_t zPrimitiveCount, D3DPRIMITIVETYPE ptDrawingType = D3DPT_TRIANGLEFAN );
	void PX_API Line( const D3DXVECTOR2* pPoints, std::size_t sPointCount, float flWidth, DWORD dwColor );
	void PX_API Text( ED3DFont iFont, int x, int y, const wchar_t *wszText, bool bOutlined, DWORD dwFlags, DWORD dwColor, DWORD dwOutline = 0 );
	RECT PX_API GetTextSize( ED3DFont iFont, const wchar_t *wszText );
	void PX_API DrawQueue( );
}

#if defined PX_USE_NAMESPACES
using namespace PX::Drawing;
#endif

/// Drawing.hpp

#pragma once

namespace PX::Drawing
{
	// Must place points in clockwise order, starting with top leftmost point.
	void PX_API Polygon( Types::vertex_t* pVertices, std::size_t sVertexCount, std::size_t sPrimitiveCount, D3DPRIMITIVETYPE ptDrawingType = D3DPT_TRIANGLEFAN );
	void BoxFilled( float x, float y, float w, float h, DWORD color );
	void PX_API Line( const D3DXVECTOR2* pPoints, std::size_t sPointCount, float flWidth, DWORD dwColor, BOOL bAntiAlias = TRUE );
}

#if defined PX_USE_NAMESPACES
using namespace PX::Drawing;
#endif

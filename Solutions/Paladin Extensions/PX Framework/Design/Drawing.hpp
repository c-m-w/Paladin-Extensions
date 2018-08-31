/// Drawing.hpp

#pragma once

namespace PX::Drawing
{
	void PX_API Polygon( Types::vertex_t* pVertices, std::size_t zVertexCount, std::size_t zPrimitiveCount, D3DPRIMITIVETYPE ptDrawingType = D3DPT_TRIANGLEFAN );
	void PX_API Line( const D3DXVECTOR2* pPoints, std::size_t sPointCount, float flWidth, DWORD dwColor, BOOL bAntiAlias = TRUE );
	void PX_API Draw( );
}

#if defined PX_USE_NAMESPACES
using namespace PX::Drawing;
#endif

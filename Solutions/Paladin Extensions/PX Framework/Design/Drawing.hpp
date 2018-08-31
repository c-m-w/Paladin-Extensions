/// Drawing.hpp

#pragma once

namespace PX::Drawing
{
	void PX_API Polygon( Types::vertex_t* pVertices, std::size_t zVertexCount, std::size_t zPrimitiveCount, D3DPRIMITIVETYPE ptDrawingType = D3DPT_TRIANGLEFAN );
	void BoxFilled( float x, float y, float w, float h, DWORD color );
	void PX_API Line( std::deque< D3DXVECTOR2 > dqPoints, float flWidth, DWORD dwColor, BOOL bAntiAlias = TRUE );
}

#if defined PX_USE_NAMESPACES
using namespace PX::Drawing;
#endif

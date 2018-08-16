/// Drawing.hpp

#pragma once

namespace PX::Drawing
{
	void PX_API Rectangle( unsigned uX, unsigned uY, unsigned uWidth, unsigned uHeight, DWORD dwColor );
	void PX_API Line( std::deque< D3DXVECTOR2 > dqPoints, float flWidth, DWORD dwColor, BOOL bAntiAlias = TRUE );
}

#if defined PX_USE_NAMESPACES
using namespace PX::Drawing;
#endif

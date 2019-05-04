/// Drawing.inl

#pragma once

inline CDrawing::CDrawable< vertex_t >::CDrawable( vertex_t * pVertices, std::size_t zVertices, std::size_t zPrimitives, D3DPRIMITIVETYPE _DrawType ) : 
	zPrimitives( zPrimitives ), _DrawType( _DrawType )
{
	vecVertices.resize( zVertices );
	memcpy( &vecVertices[ 0 ], pVertices, zVertices * sizeof( vertex_t ) );
}

inline CDrawing::CDrawable< vertex_t >::CDrawable( std::vector< vertex_t > vecVertices, std::size_t zPrimitives, D3DPRIMITIVETYPE _DrawType ) : 
	vecVertices( vecVertices ), zPrimitives( zPrimitives ), _DrawType( _DrawType )
{ }

inline bool CDrawing::CDrawable<CDrawing::vertex_t>::Create( )
{
	if ( bCreated )
		return;

	return bCreated = _Drawing.ConstructPolygon( &vecVertices[0], vecVertices.size( ) ) != nullptr;
}

inline void CDrawing::CDrawable<CDrawing::vertex_t>::Draw( )
{
	if ( !Create( ) )
		return;

	if ( D3D_OK == pDevice->SetStreamSource( NULL, pVertexBuffer, NULL, sizeof( vertex_t ) ) )
		pDevice->DrawPrimitive( _DrawType, 0, zPrimitives ), pDevice->SetStreamSource( NULL, nullptr, NULL, 0 );
}

inline void CDrawing::CDrawable<CDrawing::vertex_t>::Destroy( )
{
	if ( !bCreated )
		return;

	pVertexBuffer->Release( );

	bCreated = false;
}

inline CDrawing::CDrawable< std::string >::CDrawable( const std::string &strText, int iFont, int iSize, int iHorizontalAlignment, int iVerticalAlignment ) :
	strText( strText ), iFont( iFont ), iSize( iSize ), iHorizontalAlignment( iHorizontalAlignment ), iVerticalAlignment( iVerticalAlignment )
{ }

inline bool CDrawing::CDrawable< std::string >::Create( )
{
	
}

inline void CDrawing::CDrawable< std::string >::Draw( )
{
	
}

inline void CDrawing::CDrawable< std::string >::Destroy( )
{
	
}

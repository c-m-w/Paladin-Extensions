/// Drawing.hpp

#pragma once

class CDrawing: IBase
{
private:

	static constexpr auto FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

	bool Initialize( ) override;

	bool CreateState( );

	CWindow *pTarget = nullptr;
	IDirect3D9 *pD3DInstance = nullptr;
	D3DPRESENT_PARAMETERS pParameters { };
	IDirect3DDevice9 *pDevice = nullptr;
	IDirect3DStateBlock9 *pState = nullptr;

public:

	struct triangle_t
	{
		enum
		{
			TOP,
			RIGHT,
			LEFT,
			MAX
		};

		Utilities::location_t locLocation;
		float flBaseLength;
		float flRotation;

		triangle_t( ) = default;
		triangle_t( Utilities::location_t _locLocation, float _flBaseLength, float _flRotation );

		Utilities::location_t GetPoint( int iPoint );
	};

	struct rectangle_t
	{
		enum
		{
			TOP_LEFT,
			TOP_RIGHT,
			BOTTOM_RIGHT,
			BOTTOM_LEFT,
			MAX
		};

		float x, y, flWidth, flHeight;

		explicit rectangle_t( ) = default;
		explicit rectangle_t( float _x, float _y, float _flWidth, float _flHeight );
		explicit rectangle_t( RECT recNew );

		void operator+=( const rectangle_t &rhs );

		void Clamp( const rectangle_t &recClamp );
		bool LocationInRectangle( const Utilities::location_t &locLocation ) const;
		bool InRectangle( const rectangle_t &recLocation ) const;
		RECT ToRect( ) const;
	};

	struct vertex_t
	{
		float flVectors[ 4 ] { };
		DWORD dwColor { };

		vertex_t( ) = default;
		vertex_t( float x, float y, DWORD _dwColor );

		vertex_t operator+( const vertex_t &rhs );
		vertex_t operator/( float flDivisor );

		void Rotate( float flAngle, D3DXVECTOR2 vecRotationPoint );
		vertex_t Round( );
	};

	struct circle_t
	{
		Utilities::location_t locLocation;
		float flRadius;
		std::size_t sResolution;

		circle_t( ) = default;
		circle_t( Utilities::location_t _locLocation, float _flRadius, std::size_t _sResolution );

		vertex_t *GetPoints( float flStartAngle, float flRatio ) const;
	};

	struct polygon_buffer_t
	{
		IDirect3DVertexBuffer9 *pVertexBuffer;
		std::size_t sPrimitives;
		D3DPRIMITIVETYPE ptDraw;

		polygon_buffer_t( IDirect3DVertexBuffer9 *_pVertexBuffer, std::size_t _sPrimitives, D3DPRIMITIVETYPE _ptDraw );
	};

	struct polygon_t
	{
		std::vector< vertex_t > vecVertices;
		std::size_t sPrimitives;

		polygon_t( );
		polygon_t( vertex_t *pVertices, std::size_t sVertices, std::size_t _sPrimitives );
		polygon_t( std::vector< vertex_t > _vecVertices, std::size_t _sPrimitives );

		void Join( const polygon_t &other );

		void Draw( );
		void Draw( rectangle_t recRelative );
		polygon_buffer_t GetBuffer( D3DPRIMITIVETYPE ptDraw = D3DPT_TRIANGLEFAN );
		void Draw( rectangle_t recRelative, color_t clrColor );
	};

	void Shutdown( ) override;

	void SetTarget( CWindow *pWindow );
	void SetTarget( IDirect3DDevice9 *pNewDevice );
	bool SetState( );
	bool BeginFrame( );
	bool EndFrame( );
	void PreReset( );
	void PostReset( );

	void Polygon( vertex_t *pVertices, std::size_t sVertices, std::size_t sPrimitives );
	IDirect3DVertexBuffer9 *ConstructPolygon( vertex_t *pVertices, std::size_t sVertices );
	void DrawPolygon( const polygon_buffer_t &pbPolygon, bool bRelease = false );

	polygon_t Rectangle( rectangle_t recLocation, color_t clrColor );
	polygon_t Rectangle( rectangle_t recLocation, color_t *clrColor/*[LOCATION_MAX]*/ );
	polygon_t OutlineRectangle( rectangle_t recLocation, color_t clrColor );
	polygon_t RoundedRectangle( rectangle_t recLocation, color_t clrColor, bool *bRounding/*[ LOCATION_MAX ]*/, float flRounding );
	polygon_t OutlineRoundedRectangle( rectangle_t recLocation, color_t clrColor, bool *bRounding/*[ LOCATION_MAX ]*/, float flRounding );
	polygon_t OutlineSpacedRoundedRectangle( rectangle_t recLocation, color_t clrColor, bool *bRounding, float flRounding, float flSpacing );
	polygon_t RoundedRectangle( rectangle_t recLocation, color_t *clrColor/*[LOCATION_MAX]*/, bool *bRounding/*[ LOCATION_MAX ]*/, float flRounding );
	polygon_t Triangle( Utilities::location_t locFirst, Utilities::location_t locSecond, Utilities::location_t locThird, color_t clrColor );
	polygon_t Triangle( triangle_t trLocation, color_t *clrColor/*[triangle_t::MAX]*/ );
	polygon_t Circle( circle_t circle, color_t clrColor, float flStartAngle, float flRatio = 1.f );
	polygon_t OutlineCircle( circle_t circle, color_t clrColor, float flStartAngle, float flRatio = 1.f );
	polygon_t Circle( circle_t circle, color_t clrCenter, color_t clrOuter, float flStartAngle, float flRatio = 1.f );
	polygon_t Circle( circle_t circle, color_t *pColors, float flStartAngle, float flRatio = 1.f );
	polygon_t Line( Utilities::location_t locStart, Utilities::location_t locEnd, float flThickness, color_t clrColor );
};

using triangle_t = CDrawing::triangle_t;
using rectangle_t = CDrawing::rectangle_t;
using vertex_t = CDrawing::vertex_t;
using circle_t = CDrawing::circle_t;
using polygon_buffer_t = CDrawing::polygon_buffer_t;
using polygon_t = CDrawing::polygon_t;

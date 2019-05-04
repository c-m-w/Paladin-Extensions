/// Drawing.hpp

#pragma once

class CDrawing: public IBase
{
public:

	struct texture_t;

	enum EFont
	{
		TAHOMA,
		TAHOMA_BOLD,
		ROBOTO,
		ROBOTO_BOLD,
		ENVY,
		FA,
		FONT_MAX
	};

	enum EFontFlags
	{
		NONE		= 0 << 0,
		DROPSHADOW	= 1 << 0,
		UNDERLINE	= 1 << 1,
		OUTLINE		= 1 << 2,
		ICON		= 1 << 3
	};

	enum ECursor
	{
		ARROW,
		HAND,
		IBEAM,
		CURSOR_MAX
	};

	enum ETextures
	{
		TEXTURE_ARROW,
		TEXTURE_HAND,
		TEXTURE_IBEAM,
		TEXTURE_LOGO,
		TEXTURE_MAX
	};

	enum ETextAlignment
	{
		LEFT,
		CENTER,
		RIGHT,
		TOP = 0,
		BOTTOM = 2
	};

private:

	static constexpr auto FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

	bool Initialize( ) override;
	void Uninitialize( ) override;

	bool CreateD3D( );
	bool CreateState( );
	void AddTexture( const texture_t &texNew );
	bool Create( );

	bool bReleaseDevice = false;
	CApplicationWindow *pTarget = nullptr;
	IDirect3D9 *pD3DInstance = nullptr;
	D3DPRESENT_PARAMETERS pParameters { };
	IDirect3DDevice9 *pDevice = nullptr;
	IDirect3DStateBlock9 *pState = nullptr;
	ID3DXSprite *pSprite = nullptr;
	int iCursorTextureIndicies[ CURSOR_MAX ] { };
	FT_Library libInstance { };
	std::vector< FT_Face > vecFonts;
	static inline std::string strFontDirectory { };
	static inline std::string strFontFileNames[ FONT_MAX ] { };

public:

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

		Utilities::vector2_t vecLocation { }, vecSize { };
		double dWidth = 0.0, dHeight = 0.0;

		explicit rectangle_t( ) = default;
		explicit rectangle_t( double x, double y, double dWidth, double dHeight );
		explicit rectangle_t( RECT recNew );

		void operator+=( const rectangle_t &rhs );
		void operator-=( const rectangle_t &rhs );
		void operator*=( double rhs );
		void operator/=( double rhs );

		double GetX( );
		double GetY( );
		double GetW( );
		double GetH( );
		void PutX( double x );
		void PutY( double y );
		void PutW( double w );
		void PutH( double h );
		void Clamp( const rectangle_t &recClamp );
		bool LocationInRectangle( const Utilities::vector2_t &vecLocation ) const;
		bool InRectangle( const rectangle_t &recLocation ) const;
		RECT ToRect( ) const;

		__declspec( property( get = GetX, put = PutX ) ) double x;
		__declspec( property( get = GetY, put = PutY ) ) double y;
		__declspec( property( get = GetW, put = PutW ) ) double w;
		__declspec( property( get = GetH, put = PutH ) ) double h;
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
		Utilities::vector2_t vecLocation;
		float flRadius;
		std::size_t sResolution;

		circle_t( ) = default;
		circle_t( Utilities::vector2_t vecLocation, float flRadius, std::size_t sResolution );

		vertex_t *GetPoints( float flStartAngle, float flRatio ) const;
	};

	class IBaseDrawable
	{
	protected:

		bool bCreated = false;

	public:

		virtual bool Create( )	= 0;
		virtual void Draw( )	= 0;
		virtual void Destroy( )	= 0;
	};

	template< typename _t >
	class CDrawable< _t > : public IBaseDrawable
	{ };

	template< >
	class CDrawable< vertex_t > : public IBaseDrawable
	{
	private:

		std::vector< vertex_t > vecVertices { };
		std::size_t zPrimitives = 0;
		D3DPRIMITIVETYPE _DrawType = D3DPT_TRIANGLESTRIP;
		IDirect3DVertexBuffer9* pVertexBuffer = nullptr;

	public:

		CDrawable( vertex_t* pVertices, std::size_t zVertices, std::size_t zPrimitives, D3DPRIMITIVETYPE _DrawType );
		CDrawable( std::vector< vertex_t > vecVertices, std::size_t zPrimitives, D3DPRIMITIVETYPE _DrawType );

		bool Create( ) override;
		void Draw( ) override;
		void Destroy( ) override;
	};

	template< >
	class CDrawable< std::string > : public IBaseDrawable
	{
	private:

		std::string strText { };
		int iFont = 0, iSize = 0, iHorizontalAlignment = 0, iVerticalAlignment = 0;
		Utilities::vector2_t vecDimensions;
		IDirect3DTexture9* pTexture = nullptr;

	public:

		CDrawable( const std::string &strText, int iFont, int iSize, int iHorizontalAlignment, int iVerticalAlignment );

		bool Create( ) override;
		void Draw( ) override;
		void Destroy( ) override;
	};

	/// TODO IMAGE clASS
	//template< >
	//class CDrawable< IDirect3DTexture9* > : public IBaseDrawable
	//{
	//private:
	//
	//	IDirect3DTexture9* pTexture = nullptr;
	//
	//public:
	//
	//	CDrawable( vertex_t* pVertices, std::size_t zVertices, std::size_t zPrimitives );
	//	CDrawable( std::vector< vertex_t > vecVertices, std::size_t zPrimitives );
	//
	//	void Create( ) override;
	//	void Draw( ) override;
	//	void Destroy( ) override;
	//};

	struct glyph_t
	{
		FT_GlyphSlotRec_ glGlyph { };
		float flHorizontalOffset = 0.f;
		unsigned char *bBitmapBuffer = nullptr;

		glyph_t( FT_GlyphSlotRec_ glCurrent, float flTotalAdvance, unsigned char *bData, std::size_t sDataSize );
	};

	struct glyph_row_t
	{
		std::vector< glyph_t > vecGlyphs;
		Utilities::vector2_t vecRowSize;
		int iVerticalOffset;
		int iVerticalAddition;

		glyph_row_t( );

		void AddGlyph( FT_GlyphSlotRec_ glCurrent, float flTargetSize );
		void AddKerning( float flMagnitude );
	};

	struct text_t
	{

		std::string strText;
		int iFont, iSize, iHorizontalAlignment, iVerticalAlignment;
		Utilities::vector2_t vecDimensions;
		IDirect3DTexture9 *pText;

		text_t( );
		text_t( const std::string &_strText, int iFont, int _iSize, int _iHorizontalAlignment, int _iVerticalAlignment );
		~text_t( );

		bool Initialize( const color_t &clrText, EFontFlags ffFlags );
		void ChangeText( const text_t &txtNew, const color_t &clrText, EFontFlags ffFlags );
		Utilities::vector2_t GetDimensions( ) const;
		float GetWidth( ) const;
		float GetHeight( ) const;
		bool Initialized( ) const;
		void Draw( const Utilities::vector2_t &vecLocation );
		void Draw( const rectangle_t &recUsableSpace );
		void Destruct( );
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

	struct texture_t
	{
		unsigned uWidth = 0u, uHeight = 0u;
		std::string strName { };

		texture_t( ) = default;
		texture_t( unsigned _uWidth, unsigned _uHeight, const std::string &_strName );
	};

	using texture_renderable_t = std::pair< texture_t, std::pair< D3DXIMAGE_INFO, IDirect3DTexture9* > >;

private:

	std::vector< std::pair< texture_t, std::pair< D3DXIMAGE_INFO, IDirect3DTexture9* > > > vecTextures { };
	rectangle_t recRenderTarget { };
	std::stack< rectangle_t > recSource { };

public:

	void SetTarget( CApplicationWindow *pWindow );
	void SetTarget( IDirect3DDevice9 *pNewDevice );
	bool SetState( );
	bool BeginFrame( );
	bool EndFrame( );
	bool PreReset( );
	bool AddFont( const std::string &strFilename );
	bool RemoveFont( std::size_t sFont );
	void ApplyCursor( int iCursorType );
	bool IsAreaVisible( const rectangle_t &recArea );
	texture_renderable_t &GetTexture( int iTextureID );
	void RenderTexture( int iTextureID, const Utilities::vector2_t &vecTexture );
	RECT GetDrawingSpace( );
	void PushDrawingSpace( rectangle_t recSpace );
	void PopDrawingSpace( );

	Utilities::vector2_t GetTextDimensions( const char *szText, float flSize, std::size_t sFont );
	IDirect3DTexture9 *CreateTextTexture( const char *szText, float flSize, std::size_t sFont, const color_t &clrText, Utilities::vector2_t &vecDimensions, EFontFlags ffFlags, float flMaxWidth = -1.f );
	void Polygon( vertex_t *pVertices, std::size_t sVertices, std::size_t sPrimitives );
	IDirect3DVertexBuffer9 *ConstructPolygon( vertex_t *pVertices, std::size_t sVertices );
	void DrawTexture( IDirect3DTexture9 *pTexture, const Utilities::vector2_t &vecLocation );
	void DrawTexture( int iTextureID, Utilities::vector2_t vecLocation );

	polygon_t Rectangle( rectangle_t recLocation, color_t clrColor );
	polygon_t Rectangle( rectangle_t recLocation, color_t *clrColor/*[LOCATION_MAX]*/ );
	polygon_t OutlineRectangle( rectangle_t recLocation, color_t clrColor );
	polygon_t RoundedRectangle( rectangle_t recLocation, color_t clrColor, bool *bRounding/*[ LOCATION_MAX ]*/, float flRounding );
	polygon_t OutlineRoundedRectangle( rectangle_t recLocation, color_t clrColor, bool *bRounding/*[ LOCATION_MAX ]*/, float flRounding );
	polygon_t OutlineSpacedRoundedRectangle( rectangle_t recLocation, color_t clrColor, bool *bRounding, float flRounding, float flSpacing );
	polygon_t RoundedRectangle( rectangle_t recLocation, color_t *clrColor/*[LOCATION_MAX]*/, bool *bRounding/*[ LOCATION_MAX ]*/, float flRounding );
	polygon_t Triangle( Utilities::vector2_t vecFirst, Utilities::vector2_t vecSecond, Utilities::vector2_t vecThird, color_t clrColor );
	polygon_t Circle( circle_t circle, color_t clrColor, float flStartAngle, float flRatio = 1.f );
	polygon_t OutlineCircle( circle_t circle, color_t clrColor, float flStartAngle, float flRatio = 1.f );
	polygon_t Circle( circle_t circle, color_t clrCenter, color_t clrOuter, float flStartAngle, float flRatio = 1.f );
	polygon_t Circle( circle_t circle, color_t *pColors, float flStartAngle, float flRatio = 1.f );
	polygon_t Line( Utilities::vector2_t vecStart, Utilities::vector2_t vecEnd, float flThickness, color_t clrColor );
} extern _Drawing;

using EFont = CDrawing::EFont;
using EFontFlags = CDrawing::EFontFlags;
using ECursor = CDrawing::ECursor;
using ETextures = CDrawing::ETextures;
using ETextAlignment = CDrawing::ETextAlignment;
using rectangle_t = CDrawing::rectangle_t;
using vertex_t = CDrawing::vertex_t;
using circle_t = CDrawing::circle_t;
using text_t = CDrawing::text_t;
using polygon_buffer_t = CDrawing::polygon_buffer_t;
using polygon_t = CDrawing::polygon_t;
using texture_t = CDrawing::texture_t;
using texture_renderable_t = CDrawing::texture_renderable_t;

#include "Drawing.inl"

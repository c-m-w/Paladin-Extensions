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

		explicit rectangle_t( ) = default;
		explicit rectangle_t( double x, double y, double dWidth, double dHeight );
		explicit rectangle_t( RECT recNew );

		void operator+=( const rectangle_t &rhs );
		void operator-=( const rectangle_t &rhs );
		void operator*=( double rhs );
		void operator/=( double rhs );

		double GetX( ) const;
		double GetY( ) const;
		double GetW( ) const;
		double GetH( ) const;
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

	struct texture_t
	{
		Utilities::vector2_t vecDimensions { };
		std::string strFileName { };

		texture_t( ) = default;
		texture_t( Utilities::vector2_t vecDimensions, const std::string &strFileName );
	};

	class IBaseDrawable
	{
	protected:

		bool bCreated = false;

	public:

		virtual bool Create( )	= 0;
		virtual void Draw( )	= 0;
		virtual void Destroy( )	= 0;
		
		friend class CDrawing;
	};

	template< typename _t >
	class CDrawable : public IBaseDrawable
	{
	public:

		bool Create( ) override;
		void Draw( ) override;
		void Destroy( ) override;
	};

	template< >
	class CDrawable< vertex_t > : public IBaseDrawable
	{
	private:

		std::vector< vertex_t > vecVertices { };
		std::size_t zPrimitives = 0;
		D3DPRIMITIVETYPE _DrawType = D3DPT_TRIANGLEFAN;
		IDirect3DVertexBuffer9* pVertexBuffer = nullptr;

	public:

		CDrawable( ) = default;

		bool Create( ) override;
		void Draw( ) override;
		void Destroy( ) override;

		void SetDrawingType( D3DPRIMITIVETYPE _New );
		void Rectangle( rectangle_t recLocation, color_t clrColor );
		void Rectangle( rectangle_t recLocation, color_t *clrColor/*[LOCATION_MAX]*/ );
		void OutlineRectangle( rectangle_t recLocation, color_t clrColor );
		void Line( Utilities::vector2_t vecStart, Utilities::vector2_t vecEnd, float flThickness, color_t clrColor );

		friend class CDrawing;
	};

	template< >
	class CDrawable< std::string > : public IBaseDrawable
	{
	private:

		std::string strText { };
		int iFont = 0, iSize = 0, iHorizontalAlignment = 0, iVerticalAlignment = 0;
		color_t clrText { };
		EFontFlags ffFlags = NONE;
		Utilities::vector2_t vecDimensions { }, vecDrawingLocation { };
		IDirect3DTexture9* pTexture = nullptr;

	public:

		CDrawable( const std::string &strText, int iFont, int iSize, int iHorizontalAlignment, int iVerticalAlignment, const color_t& clrText, EFontFlags ffFlags );

		bool Create( ) override;
		void Draw( ) override;
		void Destroy( ) override;

		void SetDrawingLocation( const Utilities::vector2_t& vecNew );
		void SetDrawingLocation( const rectangle_t& recUsableSpace );
		void SetColor( const color_t& clrNew );
		double GetWidth( );
		double GetHeight( );

		friend class CDrawing;
	};

	template< >
	class CDrawable< texture_t > : public IBaseDrawable
	{
	private:

		texture_t _TextureInfo { };
		Utilities::vector2_t vecDrawingLocation { };
		IDirect3DTexture9 *pTexture = nullptr;
		D3DXIMAGE_INFO _ImageInfo { };

	public:

		CDrawable( const texture_t &_TextureInfo );

		bool Create( ) override;
		void Draw( ) override;
		void Destroy( ) override;

		void SetDrawingLocation( const Utilities::vector2_t& vecNew );

		friend class CDrawing;
	};

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

private:

	std::vector< IBaseDrawable* > vecDrawables { };
	std::vector< CDrawable< texture_t >* > vecTextures { };
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
	CDrawable< texture_t >* GetTexture( int iTextureID );
	RECT GetDrawingSpace( );
	void PushDrawingSpace( rectangle_t recSpace );
	void PopDrawingSpace( );
	bool RegisterDrawable( IBaseDrawable* pDrawable );
	bool UnregisterDrawable( IBaseDrawable* pDrawable );

	Utilities::vector2_t GetTextDimensions( const char *szText, float flSize, std::size_t sFont );
	IDirect3DTexture9 *CreateTextTexture( const char *szText, float flSize, std::size_t sFont, const color_t &clrText, Utilities::vector2_t &vecDimensions, EFontFlags ffFlags, float flMaxWidth = -1.f );
	void Polygon( vertex_t *pVertices, std::size_t sVertices, std::size_t sPrimitives );
	IDirect3DVertexBuffer9 *ConstructPolygon( vertex_t *pVertices, std::size_t sVertices );
	void DrawTexture( IDirect3DTexture9 *pTexture, Utilities::vector2_t vecLocation );
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
using texture_t = CDrawing::texture_t;

#include "Drawing.inl"

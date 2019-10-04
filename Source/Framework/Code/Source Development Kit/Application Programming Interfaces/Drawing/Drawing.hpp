/// Drawing.hpp

#pragma once

enum EAlignment
{
	ALIGNMENT_TOP,
	ALIGNMENT_CENTER,
	ALIGNMENT_BOTTOM,
	ALIGNMENT_LEFT = 0,
	ALIGNMENT_RIGHT = 2,
	ALIGNMENT_MAX
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

	Utilities::vector2_t vecLocation { }, vecSize { };

	rectangle_t( ) = default;
	rectangle_t( double x, double y, double w, double h );
	rectangle_t( const Utilities::vector2_t &vecLocation, const Utilities::vector2_t &vecSize );
	rectangle_t( RECT recNew );

	rectangle_t &operator=( const RECT &rhs );
	rectangle_t operator+( const rectangle_t &rhs );
	rectangle_t operator-( const rectangle_t &rhs );
	rectangle_t operator*( const rectangle_t &rhs );
	rectangle_t operator/( const rectangle_t &rhs );
	void operator+=( const rectangle_t &rhs );
	void operator-=( const rectangle_t &rhs );
	void operator*=( double rhs );
	void operator/=( double rhs );

	[[ nodiscard ]] double GetX( ) const;
	[[ nodiscard ]] double GetY( ) const;
	[[ nodiscard ]] double GetW( ) const;
	[[ nodiscard ]] double GetH( ) const;
	void PutX( double x );
	void PutY( double y );
	void PutW( double w );
	void PutH( double h );
	void Clamp( const rectangle_t &recClamp );
	[ [ nodiscard ] ] rectangle_t ToPixels( ) const;
	[[ nodiscard ]] rectangle_t ToInches( ) const;
	[[ nodiscard ]] bool LocationInRectangle( const Utilities::vector2_t &vecLocation ) const;
	[[ nodiscard ]] bool InRectangle( const rectangle_t &recLocation ) const;
	[[ nodiscard ]] RECT ToRect( ) const;
	[[ nodiscard ]] Utilities::vector2_t FindSpace( const Utilities::vector2_t &vecTargetSize, EAlignment _Horizontal, EAlignment _Vertical ) const;

	__declspec( property( get = GetX, put = PutX ) ) double x;
	__declspec( property( get = GetY, put = PutY ) ) double y;
	__declspec( property( get = GetW, put = PutW ) ) double w;
	__declspec( property( get = GetH, put = PutH ) ) double h;
};

struct vertex_t
{
	float x = 0.f, y = 0.f, z = 0.f,
		  u = 0.f, v = 0.f;
	D3DXCOLOR clrVertex { };

	static Utilities::vector2_t PixelToRatio( const Utilities::vector2_t &vecLocation );
	static Utilities::vector2_t RatioToPixel( const Utilities::vector2_t &vecRatio );

	vertex_t( ) = default;
	vertex_t( const Utilities::vector2_t &vecRatio, color_t clrVertex );
	vertex_t( const Utilities::vector2_t &vecRatio, const Utilities::vector2_t &vecTextureRatio, color_t clrVertex );

	void Rotate( double dAngle, const Utilities::vector2_t &vecRotationPoint );
};

class CDrawable
{
private:

	bool bCreated = false;
	bool bFillDrawing = true;
	bool bAntiAlias = true;
	double dRotation = 0.0;
	Utilities::vector2_t vecRotationPoint { };
	unsigned uVertexHash = 0u, uIndexHash = 0u;
	std::vector< vertex_t > vecVertices { };
	std::vector< unsigned > vecIndices { };
	D3D_PRIMITIVE_TOPOLOGY _Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	ID3D11Buffer *pVertexBuffer = nullptr, *pIndexBuffer = nullptr;
	ID3D11ShaderResourceView *pTexture = nullptr;
	ID3D11Texture2D *pRenderedTexture = nullptr;

public:

	CDrawable( ) = default;

	bool Create( );
	void Draw( );
	void Destroy( );
	void SetRotation( double dNewRotation );
	void SetRotationPoint( const Utilities::vector2_t &vecNewRotationPoint );
	void SetDrawingType( D3D_PRIMITIVE_TOPOLOGY _New );
	void SetAntiAlias( bool bNewAntiAlias );
	void SetTexture( const std::string &strResourceName );
	void SetTexture( const std::string &strSVGResourceName, Utilities::vector2_t vecSize, unsigned char **bImageDataOutput = nullptr );
	void SetTexture( unsigned char *bBitmap, Utilities::vector2_t vecSize );
	void SetTexture( ID3D11Texture2D *pNewTexture );
	void SetTexture( const bitmap_t &_Bitmap, const color_t &clrText );
	void SetTexture( const bitmap_t &_Bitmap, ID3D11Texture2D *pColorTexture );
	void SetTexture( const bitmap_t &_Bitmap, const std::string &strResourceName );
	void RemoveTexture( );
	void Rectangle( rectangle_t recLocation, color_t clrColor );
	void Rectangle( rectangle_t recLocation, color_t *clrColor/*[LOCATION_MAX]*/ );
	void Rectangle( rectangle_t recLocation, color_t clrColor, color_t clrCenter );
	void Rectangle( rectangle_t recLocation, color_t *clrColor/*[LOCATION_MAX]*/, color_t clrCenter );
	void RoundedRectangle( rectangle_t recLocation, color_t clrColor, double dbRoundingRatio );
	void RoundedRectangle( rectangle_t recLocation, color_t clrColor, color_t clrCenter, double dbRoundingRatio );
	void RoundedRectangle( rectangle_t recLocation, color_t *clrColor/*[ rectangle_t::MAX ]*/, color_t clrCenter, double dbRoundingRatio );
	void RoundedRectangle( rectangle_t recLocation, bool *bCornerRounding/*[ rectangle_t::MAX ]*/, color_t clrColor, double dbRoundingRatio );
	void RoundedRectangle( rectangle_t recLocation, bool *bCornerRounding/*[ rectangle_t::MAX ]*/, color_t clrColor, color_t clrCenter, double dbRoundingRatio );
	void RoundedRectangle( rectangle_t recLocation, bool *bCornerRounding/*[ rectangle_t::MAX ]*/, color_t *clrColor/*[ rectangle_t::MAX ]*/, color_t clrCenter, double dbRoundingRatio );
	void Line( Utilities::vector2_t vecStart, Utilities::vector2_t vecEnd, double dThickness, color_t clrColor );
	void Line( Utilities::vector2_t vecStart, Utilities::vector2_t vecEnd, double dThickness, color_t clrBegin, color_t clrEnd );
	void Circle( const Utilities::vector2_t &vecCenter, double dbRadius, color_t clrColor, std::size_t zResolution = 0 );
	void Circle( const Utilities::vector2_t &vecCenter, double dbRadius, color_t clrPerimeter, color_t clrCenter, std::size_t zResolution = 0 );
	void PostShapeChange( const decltype( vecVertices ) &vecProposedVertices, const decltype( vecIndices ) &vecProposedIndices );
	ID3D11Texture2D *RenderToTexture( );

	friend class CDrawing;
};

class CDrawing: public IBase
{
private:

	constexpr static auto SAMPLER_SAMPLES = 1;
	constexpr static auto SAMPLER_QUALITY_DEFAULT = 0;

	bool Initialize( ) override;
	void Uninitialize( ) override;

	void SetDrawingSpace( const rectangle_t &recSpace );
	NSVGimage *GetSVG( const std::string &strResourcePath );

	CApplicationWindow *pTarget = nullptr;

	IDXGISwapChain *pSwapChain = nullptr;
	ID3D11Device *pDevice = nullptr;
	ID3D11DeviceContext *pContext = nullptr;
	ID3D11RenderTargetView *pRenderTargetView = nullptr;
	ID3D11RenderTargetView *pSecondaryRenderTargetView = nullptr;
	ID3D11Texture2D *pRenderedTextureBuffer = nullptr;
	ID3D11Texture2D *pBackBufferTexture = nullptr;
	ID3D11Texture2D *pDepthStencilBuffer = nullptr;
	ID3D11DepthStencilView *pDepthStencilView = nullptr;
	ID3D11DepthStencilState *pDepthStencilState = nullptr;
	ID3D11SamplerState *pSamplerState = nullptr;
	ID3D11BlendState *pBlendState = nullptr;
	ID3D10Blob *pVertexShaderBuffer = nullptr;
	ID3D10Blob *pStandardPixelShaderBuffer = nullptr,
			   *pTexturedPixelShaderBuffer = nullptr;
	ID3D11VertexShader *pVertexShader = nullptr;
	ID3D11PixelShader *pStandardPixelShader = nullptr,
					  *pTexturedPixelShader = nullptr;
	ID3D11InputLayout *pVertexLayout = nullptr;
	ID3D11RasterizerState *pRasterizer = nullptr;

	std::vector< CDrawable* > vecDrawables { };
	rectangle_t recRenderTarget { };
	std::stack< rectangle_t > stkSource { };
	std::map< unsigned, NSVGimage* > _Images { };

public:

	bool ChangeTarget( CApplicationWindow *pNewTarget );
	bool Create( );
	bool Destroy( );
	void BeginFrame( );
	bool EndFrame( );
	bool BeginRenderingToTexture( );
	ID3D11Texture2D *EndRenderingToTexture( );
	bool ConvertTexture( IDirect3DDevice9 *pD3D9Device, IDirect3DTexture9 **pDestination, ID3D11Texture2D *pSource );
	const char *GetTextureContents( ID3D11Texture2D *pTexture );
	void PushDrawingSpace( const rectangle_t &recSpace );
	void PopDrawingSpace( );
	bool IsAreaVisible( const rectangle_t &recArea );
	bool RegisterDrawable( CDrawable *pDrawable );
	bool UnregisterDrawable( CDrawable *pDrawable );
	DXGI_SAMPLE_DESC GetMaxSamplerQuality( );
	bool ValidLocation( const Utilities::vector2_t &vecLocation );
	CApplicationWindow *GetTarget( );

	friend struct vertex_t;
	friend class CDrawable;
} extern _Drawing;

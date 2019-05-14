/// Drawing.hpp

#pragma once

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
	explicit rectangle_t( double x, double y, double w, double h );
	explicit rectangle_t( RECT recNew );

	rectangle_t& operator=( const RECT& rhs );
	void operator+=( const rectangle_t& rhs );
	void operator-=( const rectangle_t& rhs );
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
	void Clamp( const rectangle_t& recClamp );
	[[ nodiscard ]] bool LocationInRectangle( const Utilities::vector2_t& vecLocation ) const;
	[[ nodiscard ]] bool InRectangle( const rectangle_t& recLocation ) const;
	[[ nodiscard ]] RECT ToRect( ) const;

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

	static Utilities::vector2_t PixelToRatio( const Utilities::vector2_t& vecLocation );
	static Utilities::vector2_t RatioToPixel( const Utilities::vector2_t& vecRatio );

	vertex_t( ) = default;
	vertex_t( const Utilities::vector2_t& vecRatio, color_t clrVertex );
	vertex_t( const Utilities::vector2_t& vecRatio, const Utilities::vector2_t& vecTextureRatio, color_t clrVertex );

	void Rotate( double dAngle, const Utilities::vector2_t& vecRotationPoint );
};

class IBaseDrawable
{
protected:

	bool bCreated = false;

public:

	virtual bool Create( ) = 0;
	virtual void Draw( ) = 0;
	virtual void Destroy( ) = 0;

	friend class CDrawing;
};

template< typename _t >
class CDrawable: public IBaseDrawable
{
public:

	bool Create( ) override;
	void Draw( ) override;
	void Destroy( ) override;
};

template< >
class CDrawable< vertex_t >: public IBaseDrawable
{
private:

	std::vector< vertex_t > vecVertices { };
	std::vector< unsigned > vecIndices { };
	D3D_PRIMITIVE_TOPOLOGY _Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	ID3D11Buffer* pVertexBuffer = nullptr, * pIndexBuffer = nullptr;
	ID3D11ShaderResourceView* pTexture = nullptr;

public:

	CDrawable( ) = default;

	bool Create( ) override;
	void Draw( ) override;
	void Destroy( ) override;

	void SetDrawingType( D3D_PRIMITIVE_TOPOLOGY _New );
	void AddTexture( const std::string& strResourceName );
	void RemoveTexture( );
	void Rectangle( rectangle_t recLocation, color_t clrColor );
	void Rectangle( rectangle_t recLocation, color_t* clrColor/*[LOCATION_MAX]*/ );
	void OutlineRectangle( rectangle_t recLocation, color_t clrColor );
	void Line( Utilities::vector2_t vecStart, Utilities::vector2_t vecEnd, double dThickness, color_t clrColor );

	friend class CDrawing;
};

class CDrawing: public IBase
{
private:

	bool Initialize( ) override;
	void Uninitialize( ) override;

	CApplicationWindow* pTarget = nullptr;

	IDXGISwapChain*			pSwapChain					= nullptr;
	ID3D11Device*			pDevice						= nullptr;
	ID3D11DeviceContext*	pContext					= nullptr;
	ID3D11RenderTargetView* pRenderTargetView			= nullptr;
	ID3D11Texture2D*		pDepthStencilBuffer			= nullptr;
	ID3D11DepthStencilView* pDepthStencilView			= nullptr;
	ID3D11SamplerState*		pSamplerState				= nullptr;
	ID3D11BlendState*		pBlendState					= nullptr;
	ID3D10Blob*				pVertexShaderBuffer			= nullptr;
	ID3D10Blob*				pStandardPixelShaderBuffer	= nullptr,
			*				pTexturedPixelShaderBuffer	= nullptr;
	ID3D11VertexShader*		pVertexShader				= nullptr;
	ID3D11PixelShader*		pStandardPixelShader		= nullptr,
					*		pTexturedPixelShader		= nullptr;
	ID3D11InputLayout*		pVertexLayout				= nullptr;
	ID3D11RasterizerState*	pRasterizer					= nullptr;

	std::vector< IBaseDrawable* > vecDrawables { };
	rectangle_t recRenderTarget { };
	std::stack< rectangle_t > recSource { };

public:

	bool ChangeTarget( CApplicationWindow* pNewTarget );
	bool Create( );
	bool Destroy( );
	void BeginFrame( );
	bool EndFrame( );
	bool IsAreaVisible( const rectangle_t &recArea );
	bool RegisterDrawable( IBaseDrawable* pDrawable );
	bool UnregisterDrawable( IBaseDrawable* pDrawable );

	friend struct vertex_t;
	friend class CDrawable< vertex_t >;
} extern _Drawing;

#include "Drawing.inl"

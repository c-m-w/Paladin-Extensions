/// Shaders.hlsl

struct vertex_t
{
	float4 flPosition : SV_POSITION;
	float2 flTextureCoordinates : TEXCOORD0;
	float4 flColor : COLOR;
};

Texture2D texShader;
SamplerState ssSamplerType;

vertex_t StandardVertexShader( float4 flPosition : POSITION, float2 flTextureCoordinates : TEXCOORD0, float4 flColor : COLOR )
{
	vertex_t vtxOutput;

	vtxOutput.flPosition = flPosition;
	vtxOutput.flTextureCoordinates = flTextureCoordinates;
	vtxOutput.flColor = flColor;

	return vtxOutput;
}

float4 StandardPixelShader( vertex_t vtxInput ) : SV_TARGET
{
	return vtxInput.flColor;
}

float4 TexturedPixelShader( vertex_t vtxInput ) : SV_TARGET
{
	float4 flTextureColor = texShader.Sample( ssSamplerType, vtxInput.flTextureCoordinates );
	return float4( flTextureColor[ 0 ] * vtxInput.flColor[ 0 ], flTextureColor[ 1 ] * vtxInput.flColor[ 1 ], flTextureColor[ 2 ] * vtxInput.flColor[ 2 ], flTextureColor[ 3 ] * vtxInput.flColor[ 3 ] );
}

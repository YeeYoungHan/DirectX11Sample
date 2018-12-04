struct DirectionalLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Direction;
	float pad;
};

struct Material
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular; // w = SpecPower
	float4 Reflect;
};

cbuffer cbPerFrame
{
	DirectionalLight gDirLight;
	float3 gEyePosW;
	bool	 gUseTexture;
};

cbuffer cbPerObject
{
	float4x4 gWorldViewProj;
	float4x4 gWorld;
	float4x4 gWorldInvTranspose;
	Material gMaterial;
};

Texture2D gShaderResVar;

SamplerState samAnisotropic
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};

struct VertexIn
{
	float3 PosL    : POSITION;
	float3 NormalL : NORMAL;
	float2 Tex     : TEXCCORD;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
	float3 PosW    : POSITION;
	float3 NormalW : NORMAL;
	float2 Tex     : TEXCCORD;
};

VertexOut VS( VertexIn vin )
{
	VertexOut vout;
	
	// Transform to world space space.
	vout.PosW    = mul(float4(vin.PosL, 1.0f), gWorld).xyz;
	vout.NormalW = mul(vin.NormalL, (float3x3)gWorldInvTranspose);
		
	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);

	vout.Tex = vin.Tex;
	
	return vout;
}
  
float4 PS( VertexOut pin ) : SV_Target
{
	return gShaderResVar.Sample( samAnisotropic, pin.Tex );
}

technique11 ColorTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_5_0, PS() ) );
	}
}

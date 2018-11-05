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

// mat     : 재질의 Ambient, Diffuse, Specular Light
// L       : 평행광의 Ambient, Diffuse, Specular Light
// normal  : 정점 법선
// toEye   : 정점에서 시아로 향하는 벡터
// ambient : [out] Ambient Light 출력
// diffuse : [out] Diffuse Light 출력
// spec    : [out] Specular Light 출력
void ComputeDirectionalLight( Material mat, DirectionalLight L, float3 normal, float3 toEye, out float4 ambient, out float4 diffuse, out float4 spec )
{
	// 출력을 초기화한다.
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// 빛 벡터는 입사광의 반대 방향이다. 즉, 사물의 표면에서 광원으로 가는 벡터이다.
	float3 lightVec = -L.Direction;

	// Ambient Light (주변광,환경광) 를 더한다.
	ambient = mat.Ambient * L.Ambient;	

	// Diffuse Light (분산광,난반사광) 의 세기는 빛 벡터와 표면 법선 벡터의 내적으로 계산한다.
	// 내적은 cosine 이므로 빛 벡터와 표면 법선 벡터가 0 도이면 최대값이고 90 도이면 빛의 세기는 0 이 된다.
	float diffuseFactor = dot(lightVec, normal);

	[flatten]
	if( diffuseFactor > 0.0f )
	{
		// 분산광 세기가 존재하면 분산광을 계산한다.
		diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;

		// Specular Light (반영광,정반사광)을 계산한다.
		// r = 반사벡터
		// toEye = 시아벡터 : 정점에서 시아로 향하는 벡터
		// 반사벡터와 시아벡터의 내적으로 반사벡터와 시아벡터의 cosine 을 구한 후, mat.Specular.w 지수 거듭제곱한다.
		float3 r         = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(r, toEye), 0.0f), mat.Specular.w);

		spec    = specFactor * mat.Specular * L.Specular;
	}
}

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
	// Interpolating normal can unnormalize it, so normalize it.
	pin.NormalW = normalize(pin.NormalW); 

	float3 toEyeW = normalize(gEyePosW - pin.PosW);

	// Start with a sum of zero. 
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 texColor = gShaderResVar.Sample( samAnisotropic, pin.Tex );

	// Sum the light contribution from each light source.
	float4 A, D, S;

	ComputeDirectionalLight(gMaterial, gDirLight, pin.NormalW, toEyeW, A, D, S);
	ambient += A;  
	diffuse += D;
	spec    += S;
	   
	float4 litColor = texColor * ( ambient + diffuse ) + spec;

	// Common to take alpha from diffuse material.
	litColor.a = gMaterial.Diffuse.a;

	return litColor;
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

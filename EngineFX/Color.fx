cbuffer cbPerObject
{
	float4x4 gWorldViewProj;
};

struct VertexIn
{
	float3 posL : POSITION;
	float4 color : COLOR;
};

struct VertexOut
{
	float4 posH : SV_POSITION;
	float4 color : COLOR;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	//Transform to homogenous clip space
	vout.posH = mul(float4(vin.posL, 1.0f), gWorldViewProj);

	//Just Pass the vertex color into the pixel shader
	vout.color = vin.color;
	return vout;
}

float4 PS(VertexOut vout) :SV_TARGET
{
	return vout.color;
}

/*RasterizerState WireframeRS()
{
	FillMode = Wireframe;
	CullMode = Back;
	FrontCounterClockwise = false;
};*/

technique11 ColorTech
{
	pass p0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));

	}
}
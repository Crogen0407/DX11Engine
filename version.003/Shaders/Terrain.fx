matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;
uint Address;

struct VertexInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
	
    output.uv = input.uv;
	
    return output;
}
// Filter = 확대/축소 일어났을 때 중간값을 처리하는 방식
// Address = UV가 1보다 컸을 때, 나머지 부분을 어떻게 처리할지에 대해 결정

SamplerState Sampler0
{
    AddressU = Wrap;
    AddressV = Wrap;
};

RasterizerState FillModeWireFrame
{
    FillMode = WireFrame;
};

float4 PS(VertexOutput input) : SV_TARGET
{
    return Texture0.Sample(Sampler0, input.uv);
}

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
    pass P1
    {
        SetRasterizerState(FillModeWireFrame);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
};
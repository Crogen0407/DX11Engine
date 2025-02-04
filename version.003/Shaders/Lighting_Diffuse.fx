#include "Global.fx"

float3 LightDir;
float4 LightDiffuse;
float4 MaterialDiffuse;
Texture2D Texture0;

VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
    output.position = mul(input.position, W);
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)W);
    
    return output;
}
// Filter = Ȯ��/��� �Ͼ�� �� �߰����� ó���ϴ� ���
// Address = UV�� 1���� ���� ��, ������ �κ��� ��� ó�������� ���� ����


// Diffuse (�л걤)
// ��ü�� ǥ�鿡�� �л�Ǿ� ������ �ٷ� ������ ��
// ������ ���� ��Ⱑ �ٸ���(Lambert Light)
float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = Texture0.Sample(LinearSampler, input.uv);
    
    float value = dot(-LightDir, normalize(input.normal));
    
    color = color * value * LightDiffuse * MaterialDiffuse;
    
    return color;
}

technique11 T0
{
    PASS_VP(P0, VS, PS)
};
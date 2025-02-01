#include "Global.fx"

float3 LightDir;
float4 LightSpecular;
float4 MaterialSpecular;
Texture2D Texture0;

MeshOutput VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, W);
    output.worldPosition = input.position;
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

// Specular (�ݻ籤)
// �ѹ������� ������ �ݻ�Ǵ� ��(Phong)
float4 PS(MeshOutput input) : SV_TARGET
{
    float3 R = reflect(LightDir, input.normal);
    R = normalize(R);
    
    float3 cameraPosition = -V._41_42_43;
    float3 E = normalize(cameraPosition - input.worldPosition);
    
    float value = saturate(dot(R, E));
    float specular = pow(value, 10);
    
    float4 color = LightSpecular * MaterialSpecular * specular;
    
    return color;
}

technique11 T0
{
    PASS_VP(P0, VS, PS)
};
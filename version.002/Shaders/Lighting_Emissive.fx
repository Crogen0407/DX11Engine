#include "Global.fx"

float4 MaterialEmissive;
Texture2D Texture0;

MeshOutput VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, W);
    output.worldPosition = output.position;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)W);
    
    return output;
}
// Filter = 확대/축소 일어났을 때 중간값을 처리하는 방식
// Address = UV가 1보다 컸을 때, 나머지 부분을 어떻게 처리할지에 대해 결정


// Emissive
// 외곽선 구할 때 사용
// (Lim Light)
float4 PS(MeshOutput input) : SV_TARGET
{
    float3 cameraPosition = -V._41_42_43;
    float3 E = normalize(cameraPosition - input.worldPosition);
    
    float value = saturate(dot(E, input.normal));
    float emissive = 1.0f - value;
    
    emissive = smoothstep(0.0f, 1.0f, emissive);
    emissive = pow(emissive, 3);
    
    float4 color = MaterialEmissive * emissive;
    
    return color;
}

technique11 T0
{
    PASS_VP(P0, VS, PS)
};
float4x4 World;
float4x4 WorldViewProj;
float4x4 WorldInverseTranspose;
float3 LightDir;
float3 CameraPos;
float4 Diffuse;
float4 Specular;
float4 Ambient;

void VertexShader_Main(
    in float3 inPos : POSITION0,
    in float3 inNormal : NORMAL0,
    in float2 inTexture : TEXCOORD0,

    out float4 outPos : POSITION0,
    out float4 outNormal : TEXCOORD2,
    out float2 outTexture : TEXCOORD0,
    out float4 outPos_world: TEXCOORD1
)
{
    outPos_world = mul(float4(inPos, 1.0f), World);
    outPos = mul(float4(inPos, 1.0f), WorldViewProj);
    outNormal = normalize(mul(float4(inNormal, 0.0f), WorldInverseTranspose));
    outTexture = inTexture;
}

texture Tex;
sampler TexSampler = sampler_state
{
    Texture = (Tex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

void PixelShader_Texture_Main(
    in float3 inPos_world : TEXCOORD1,
    in float3 inNormal : TEXCOORD2,
    in float2 inTexture :TEXCOORD0,

    out float4 outColor : COLOR0
)
{
    inNormal = normalize(inNormal);
    float3 PostoCamera = normalize(CameraPos - inPos_world);
    float3 normalizeLightDir = normalize(LightDir);
    float3 reflectLight = normalize(reflect(normalizeLightDir, inNormal));

    float4 diff = Diffuse * (dot(inNormal, -normalizeLightDir) / 2 + 0.5f);
    float4 spec = Specular * pow(max(dot(reflectLight, PostoCamera), 0.0f), 50);
    float4 ambi = Ambient;

    outColor = (diff + spec + ambi) * tex2D(TexSampler, inTexture);
}

void PixelShader_NoTexture_Main(
    in float3 inPos_world : TEXCOORD1,
    in float3 inNormal : TEXCOORD2,

    out float4 outColor : COLOR0
)
{
    inNormal = normalize(inNormal);
    float3 PostoCamera = normalize(CameraPos - inPos_world);
    float3 normalizeLightDir = normalize(LightDir);
    float3 reflectLight = normalize(reflect(normalizeLightDir, inNormal));

    float4 diff = Diffuse * (dot(inNormal, -normalizeLightDir) / 2 + 0.5f);
    float4 spec = Specular * pow(max(dot(reflectLight, PostoCamera), 0.0f), 50);
    float4 ambi = Ambient;

    outColor = (diff + spec + ambi);
    
}

technique TexterTech
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 VertexShader_Main();
        PixelShader = compile ps_3_0 PixelShader_Texture_Main();
    }
}

technique NoTexterTech
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 VertexShader_Main();
        PixelShader = compile ps_3_0 PixelShader_NoTexture_Main();
    }
}
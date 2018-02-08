float4x4 World;
float4x4 ViewProj;

texture Tex;
sampler2D TexSampler = sampler_state
{
    Texture = (Tex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

texture PosInput;
sampler2D PosInputSampler = sampler_state
{
    Texture = (PosInput);
    MipFilter = NONE;
    MinFilter = POINT;
    MagFilter = POINT;
};

texture PosOutput;
sampler2D PosOutputSampler = sampler_state
{
    Texture = (PosOutput);
    MipFilter = NONE;
    MinFilter = POINT;
    MagFilter = POINT;
};

texture SpeedInput;
sampler2D SpeedInputSampler = sampler_state
{
    Texture = (SpeedInput);
    MipFilter = NONE;
    MinFilter = POINT;
    MagFilter = POINT;
};

texture SpeedOutput; 
sampler2D SpeedOutputSampler = sampler_state
{
    Texture = (SpeedOutput);
    MipFilter = NONE;
    MinFilter = POINT;
    MagFilter = POINT;
};

struct ATTRACTIONSHADER_STEP1_IN_PIXEL
{
    float3 PosW : TEXCOORD3;
    float PSize : TEXCOORD4;
    float3 Speed : TEXCOORD1;
    float2 UV : TEXCOORD0;
};

struct ATTRACTIONSHADER_STEP1_OUT_PIXEL
{
    float4 PosW : COLOR0;
    float4 Speed : COLOR1;
};

//ATTRACTIONSHADER_STEP1_OUT_VERTEX AttractionShader_VertexShader_Step1_Main(ATTRACTIONSHADER_STEP1_IN_VERTEX iv)
//{
//    float3 AttractionTargetPoint = float3(0.0f, 5.0f, 0.0f);
//    ATTRACTIONSHADER_STEP1_OUT_VERTEX ov;
//    float3 posW = mul(float4(iv.PosL, 1.0f), World).xyz;
//    float3 acc = (AttractionTargetPoint - posW) * 0.01f;
//    float3 speed_old = tex2Dlod(SpeedInputSampler, float4(iv.InfoUV, 0.0f, 0.0f));
//    ov.Speed = speed_old + acc;
//    float3 pos_old = tex2Dlod(PosInputSampler, float4(iv.InfoUV.x, iv.InfoUV.y + 1.0f / 1024.0f, 0.0f, 0.0f));
//    ov.PosW = pos_old + ov.Speed;
//    ov.PSize = iv.PSize;
//    ov.PosH = mul(float4(ov.PosW, 1.0f), ViewProj);
//    return ov;
//}

ATTRACTIONSHADER_STEP1_OUT_PIXEL AttractionShader_PixelShader_Step1_Main(ATTRACTIONSHADER_STEP1_IN_PIXEL ip)
{
    ATTRACTIONSHADER_STEP1_OUT_PIXEL op;
    op.PosW = float4(ip.PosW,1.0f);
    op.Speed = float4(ip.Speed,1.0f);
    return op;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ATTRACTIONSHADER_STEP2_IN_VERTEX
{
    float3 PosL : POSITION0;
    float PSize : PSIZE0;
    float4 Color : COLOR0;
    float3 Speed : TEXCOORD1;
    float2 InfoUV : TEXCOORD2;
};

struct ATTRACTIONSHADER_STEP2_OUT_VERTEX
{
    float4 PosH : POSITION0;
    float PSize : PSIZE0;
    float4 Color : COLOR0;
};

struct ATTRACTIONSHADER_STEP2_IN_PIXEL
{
    float4 PosH : POSITION0;
    float4 Color : COLOR0;
    float2 UV : TEXCOORD0;
};

ATTRACTIONSHADER_STEP2_OUT_VERTEX AttractionShader_VertexShader_Step2_Main(ATTRACTIONSHADER_STEP2_IN_VERTEX iv)
{
    ATTRACTIONSHADER_STEP2_OUT_VERTEX ov;

    float3 PosW = tex2Dlod(PosOutputSampler, float4(iv.InfoUV, 0.0f, 0.0f)).xyz;
    PosW += tex2Dlod(SpeedOutputSampler, float4(iv.InfoUV, 0.0f, 0.0f)).xyz;
    ov.PosH = mul(float4(PosW, 1.0f), ViewProj);
    ov.PSize = iv.PSize;
    ov.Color = iv.Color;
    return ov;
}

float4 AttractionShader_PixelShader_Step2_Main(ATTRACTIONSHADER_STEP2_IN_PIXEL ip) : COLOR0
{
    return ip.Color * tex2D(TexSampler, ip.UV);
}

technique AttractionShader_Step2
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 AttractionShader_VertexShader_Step2_Main();
        PixelShader = compile ps_3_0 AttractionShader_PixelShader_Step2_Main();
    }
}
float4x4 World;
float4x4 ViewProj;
float3 AttractionTargetPoint;

texture Tex;
sampler TexSampler = sampler_state
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
sampler PosOutputSampler = sampler_state
{
    Texture = (PosOutput);
    MipFilter = NONE;
    MinFilter = POINT;
    MagFilter = POINT;
};

texture SpeedInput;
sampler SpeedInputSampler = sampler_state
{
    Texture = (SpeedInput);
    MipFilter = NONE;
    MinFilter = POINT;
    MagFilter = POINT;
};

texture SpeedOutput; 
sampler SpeedOutputSampler = sampler_state
{
    Texture = (SpeedOutput);
    MipFilter = NONE;
    MinFilter = POINT;
    MagFilter = POINT;
};

struct ATTRACTIONSHADER_STEP1_IN_PIXEL
{
    float2 UV : TEXCOORD0;
};

struct ATTRACTIONSHADER_STEP1_OUT_PIXEL
{
    float4 PosW : COLOR0;
    float4 Speed : COLOR1;
    float4 Force : COLOR2;
};

ATTRACTIONSHADER_STEP1_OUT_PIXEL AttractionShader_PixelShader_Step1_Main(ATTRACTIONSHADER_STEP1_IN_PIXEL ip)
{
    ATTRACTIONSHADER_STEP1_OUT_PIXEL op;
    float3 pos_old = tex2D(PosInputSampler, ip.UV).xyz;
    float3 speed_old = tex2D(SpeedInputSampler, ip.UV).xyz;

    float3 dir = AttractionTargetPoint - pos_old;
    float dirlen = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    
    float pct = max(1 - dirlen / 100.0f, 0.3f);
    float scale = 0.1f;
    dir = normalize(dir);
    op.Force = float4( dir * scale * pct, 1.0f);
    op.Speed = float4(speed_old + op.Force.xyz, 1.0f);
    op.PosW = float4(pos_old + op.Speed.xyz, 1.0f);

    return op;
}

technique AttractionShader_Step1
{
    pass Pass0
    {
        PixelShader = compile ps_3_0 AttractionShader_PixelShader_Step1_Main();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ATTRACTIONSHADER_STEP2_IN_VERTEX
{
    float3 PosL : POSITION0;
    float PSize : PSIZE0;
    float4 Color : COLOR0;
    float2 InfoUV : TEXCOORD1;
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
    ov.PosH = mul(float4(PosW, 1.0f), ViewProj);
    ov.PSize = iv.PSize;
    ov.Color = iv.Color;
    return ov;
}

float4 AttractionShader_PixelShader_Step2_Main(ATTRACTIONSHADER_STEP2_IN_PIXEL ip) : COLOR0
{
    return ip.Color * tex2D(TexSampler,ip.UV);
}

technique AttractionShader_Step2
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 AttractionShader_VertexShader_Step2_Main();
        PixelShader = compile ps_3_0 AttractionShader_PixelShader_Step2_Main();
    }
}
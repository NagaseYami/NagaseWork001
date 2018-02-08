float4x4 WorldViewProj;
float Time;

texture Tex;
sampler TexSampler = sampler_state
{
    Texture = (Tex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

struct BASICSHADER_IN_VERTEX
{
    float3 PosL : POSITION0;
    float PSize : PSIZE0;
    float4 Color : COLOR0;
    float3 DirL : TEXCOORD1;
};


struct BASICSHADER_OUT_VERTEX
{
    float4 PosH : POSITION0;
    float4 Color : COLOR0;
    float PSize : PSIZE0;
};

struct BASICSHADER_IN_PIXEL
{
    float4 PosH : POSITION0;
    float4 Color : COLOR0;
    float PSize : PSIZE0;
    float2 UV : TEXCOORD0;
};

BASICSHADER_OUT_VERTEX BasicShader_VertexShader_Main(BASICSHADER_IN_VERTEX iv)
{
    BASICSHADER_OUT_VERTEX ov;
    ov.Color = iv.Color;   
    iv.DirL *= 0.1f;
    ov.PosH = mul(float4(iv.PosL + iv.DirL * Time, 1.0f), WorldViewProj);
    ov.PSize = iv.PSize;
    return ov;
}

float4 BasicShader_PixelShader_Texture_Main(BASICSHADER_IN_PIXEL ip) : COLOR0
{
    return ip.Color;
}

float4 BasicShader_PixelShader_NoTexture_Main(BASICSHADER_IN_PIXEL ip) : COLOR0
{
    return ip.Color;
}

technique BasicShader_TexterTech
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 BasicShader_VertexShader_Main();
        PixelShader = compile ps_3_0 BasicShader_PixelShader_Texture_Main();
    }
}

technique BasicShader_NoTexterTech
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 BasicShader_VertexShader_Main();
        PixelShader = compile ps_3_0 BasicShader_PixelShader_NoTexture_Main();
    }
}
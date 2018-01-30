float4x4 World;
float4x4 WorldInverse;
float4x4 WorldViewProj;
float4x4 WorldInverseTranspose;
float4x4 LightWVP;
float3 LightDirW;
float3 EyePosW;
float4 Diffuse;
float4 Specular;
float4 Ambient;
float Far;

texture Tex;
sampler TexSampler = sampler_state
{
    Texture = (Tex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

texture Bump;
sampler BumpSampler = sampler_state
{
    Texture = (Bump);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

texture Toon;
sampler ToonSampler = sampler_state
{
    Texture = (Toon);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

texture Depth;
sampler DepthSampler = sampler_state
{
    Texture = (Depth);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};
//BasicShader*****************************************************************************

struct BASICSHADER_IN_VERTEX
{
    float3 PosL : POSITION0;
    float3 NormalL : NORMAL0;
    float2 UV : TEXCOORD0;
};


struct BASICSHADER_OUT_VERTEX
{
    float4 PosH : POSITION0;    
    float2 UV : TEXCOORD0;
    float3 PosW : TEXCOORD1;
    float3 NormalW : TEXCOORD2;
    float4 LightPosH : TEXCOORD3;
    float DepthWV : TEXCOORD4;
};

BASICSHADER_OUT_VERTEX BasicShader_VertexShader_Main(BASICSHADER_IN_VERTEX iv)
{
    BASICSHADER_OUT_VERTEX ov;

    ov.PosW = mul(float4(iv.PosL, 1.0f), World).xyz;
    ov.PosH = mul(float4(iv.PosL, 1.0f), WorldViewProj);
    ov.NormalW = mul(float4(iv.NormalL, 0.0f), WorldInverseTranspose).xyz;
    ov.UV = iv.UV;

    ov.LightPosH = mul(float4(iv.PosL, 1.0f), LightWVP);
    ov.DepthWV = ov.LightPosH.z / ov.LightPosH.w;

    return ov;
}

float4 BasicShader_PixelShader_Texture_Main(BASICSHADER_OUT_VERTEX ip) : COLOR0
{
    ip.NormalW = normalize(ip.NormalW);

    float3 PostoCamera = normalize(EyePosW - ip.PosW);
    float3 normalizeLightDir = normalize(LightDirW);
    float3 reflectLight = normalize(reflect(normalizeLightDir, ip.NormalW));

    ip.LightPosH.x = ip.LightPosH.x * 0.5f + 0.5f;
    ip.LightPosH.y = ip.LightPosH.y * (-0.5f) + 0.5f;
    ip.LightPosH.xy /= ip.LightPosH.w;
    float lightDepthWV = tex2D(DepthSampler, ip.LightPosH.xy).r;
    float shadow = (lightDepthWV + 0.008f) < ip.DepthWV && dot(ip.NormalW, -normalizeLightDir) >= 0.145f ? 0.0f : 1.0f;

    float4 diff = Diffuse * (dot(ip.NormalW, -normalizeLightDir) / 2 + 0.5f);
    float4 spec = Specular * pow(max(dot(reflectLight, PostoCamera), 0.0f), 100);
    float4 ambi = Ambient;
    diff.rgb *= min(shadow + 0.1f, 1.0f);
    spec.rgb *= shadow;

    float3 PointLightW[4];
    float3 PointLightColor[4];
    float4 LightColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

    PointLightW[0] = float3(30.0f, 3.0f, 0.0f);
    PointLightW[1] = float3(-30.0f, 3.0f, 0.0f);
    PointLightW[2] = float3(0.0f, 3.0f, 30.0f);
    PointLightW[3] = float3(0.0f, 3.0f, -30.0f);

    PointLightColor[0] = float3(1.0f, 1.0f, 0.0f);
    PointLightColor[1] = float3(0.0f, 1.0f, 1.0f);
    PointLightColor[2] = float3(1.0f, 0.0f, 1.0f);
    PointLightColor[3] = float3(0.0f, 1.0f, 0.0f);

    for (int i = 0; i < 4; i++)
    {
        float d = distance(ip.PosW, PointLightW[i]) / 10.0f;
        float3 vecPointLightW = normalize(ip.PosW - PointLightW[i]);
        float l = max(dot(ip.NormalW, -vecPointLightW), 0.0f);
        LightColor += float4(PointLightColor[i] * l / d, 0.0f);
    }

    return (diff + spec + ambi + LightColor) * tex2D(TexSampler, ip.UV);
}

float4 BasicShader_PixelShader_NoTexture_Main(BASICSHADER_OUT_VERTEX ip) : COLOR0
{
    ip.NormalW = normalize(ip.NormalW);

    float3 PostoCamera = normalize(EyePosW - ip.PosW);
    float3 normalizeLightDir = normalize(LightDirW);
    float3 reflectLight = normalize(reflect(normalizeLightDir, ip.NormalW));

    ip.LightPosH.x = ip.LightPosH.x * 0.5f + 0.5f;
    ip.LightPosH.y = ip.LightPosH.y * (-0.5f) + 0.5f;
    ip.LightPosH.xy /= ip.LightPosH.w;
    float lightDepthWV = tex2D(DepthSampler, ip.LightPosH.xy).r;
    float shadow = (lightDepthWV + 0.008f) < ip.DepthWV && dot(ip.NormalW, -normalizeLightDir) >= 0.145f ? 0.0f : 1.0f;

    float4 diff = Diffuse * (dot(ip.NormalW, -normalizeLightDir) / 2 + 0.5f);
    float4 spec = Specular * pow(max(dot(reflectLight, PostoCamera), 0.0f), 100);
    float4 ambi = Ambient;
    diff.rgb *= min(shadow + 0.1f, 1.0f);
    spec.rgb *= shadow;

    float3 PointLightW[4];
    float3 PointLightColor[4];
    float4 LightColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

    PointLightW[0] = float3(30.0f, 3.0f, 0.0f);
    PointLightW[1] = float3(-30.0f, 3.0f, 0.0f);
    PointLightW[2] = float3(0.0f, 3.0f, 30.0f);
    PointLightW[3] = float3(0.0f, 3.0f, -30.0f);

    PointLightColor[0] = float3(1.0f, 1.0f, 0.0f);
    PointLightColor[1] = float3(0.0f, 1.0f, 1.0f);
    PointLightColor[2] = float3(1.0f, 0.0f, 1.0f);
    PointLightColor[3] = float3(0.0f, 1.0f, 0.0f);

    for (int i = 0; i < 4; i++)
    {
        float d = distance(ip.PosW, PointLightW[i])/10.0f;
        float3 vecPointLightW = normalize(ip.PosW - PointLightW[i]);
        float l = max(dot(ip.NormalW, -vecPointLightW), 0.0f);
        LightColor += float4(PointLightColor[i] * l , 0.0f);
    }

    return diff + spec + ambi + LightColor;
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

//BumpMapShader**********************************************************************************

struct BUMPMAPSHADER_IN_VERTEX
{
    float3 PosL : POSITION0;
    float2 UV : TEXCOORD0;
    float3 TangentL : TANGENT0;
    float3 BinormalL : BINORMAL0;
    float3 NormalL : NORMAL0;
};

struct BUMPMAPSHADER_OUT_VERTEX
{
    float4 PosH : POSITION0;
    float2 UV : TEXCOORD0;
    float3 toEyeT : TEXCOORD1;
    float3 LightDirT : TEXCOORD2;
};

BUMPMAPSHADER_OUT_VERTEX BumpMapShader_VertexShader_Main(BUMPMAPSHADER_IN_VERTEX iv)
{
    BUMPMAPSHADER_OUT_VERTEX ov;

    ov.PosH = mul(float4(iv.PosL, 1.0f), WorldViewProj);

    ov.UV = iv.UV;

    float3x3 mtxTBN;
    mtxTBN[0] = iv.TangentL;
    mtxTBN[1] = iv.BinormalL;
    mtxTBN[2] = iv.NormalL;

    float3x3 mtxTBN_Inverse = transpose(mtxTBN);

    float3 LightDirL = mul(float4(LightDirW, 0.0f), WorldInverse).xyz;
    float3 EyePosL = mul(float4(EyePosW, 1.0f), WorldInverse).xyz;
    ov.LightDirT = mul(LightDirL, mtxTBN_Inverse);
    ov.toEyeT = mul(EyePosL - iv.PosL, mtxTBN_Inverse);

    return ov;
}

float4 BumpMapShader_PixelShader_Texture_Main(BUMPMAPSHADER_OUT_VERTEX ip) : COLOR0
{
    ip.toEyeT = normalize(ip.toEyeT);
    ip.LightDirT = normalize(ip.LightDirT);

    float3 normalT = normalize(tex2D(BumpSampler, ip.UV).xyz * 2.0f - 1.0f);
    float3 reflectLightT = normalize(reflect(ip.LightDirT, normalT));

    float4 diff = float4(Diffuse.xyz * max(dot(normalT, -ip.LightDirT), 0.0f), Diffuse.w);
    float4 spec = Specular * pow(max(dot(reflectLightT, ip.toEyeT), 0.0f), 25);
    float4 ambi = Ambient;

    return (diff + spec + ambi) * tex2D(TexSampler, ip.UV);
}

float4 BumpMapShader_PixelShader_NoTexture_Main(BUMPMAPSHADER_OUT_VERTEX ip) : COLOR0
{
    ip.toEyeT = normalize(ip.toEyeT);
    ip.LightDirT = normalize(ip.LightDirT);

    float3 normalT = normalize(tex2D(BumpSampler, ip.UV).xyz * 2.0f - 1.0f);
    float3 reflectLightT = normalize(reflect(ip.LightDirT, normalT));

    float4 diff = float4(Diffuse.xyz * max(dot(normalT, -ip.LightDirT), 0.0f), Diffuse.w);
    float4 spec = Specular * pow(max(dot(reflectLightT, ip.toEyeT), 0.0f), 25);
    float4 ambi = Ambient;

    return (diff + spec + ambi);
}

technique BumpMapShader_TexterTech
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 BumpMapShader_VertexShader_Main();
        PixelShader = compile ps_3_0 BumpMapShader_PixelShader_Texture_Main();
    }
}

technique BumpMapShader_NoTexterTech
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 BumpMapShader_VertexShader_Main();
        PixelShader = compile ps_3_0 BumpMapShader_PixelShader_NoTexture_Main();
    }
}

//ToonShader**************************************************************************************

struct TOONSHADER_2D_IN_VERTEX
{
    float3 PosL : POSITION0;
    float2 UV : TEXCOORD0;
};

struct TOONSHADER_2D_OUT_VERTEX
{
    float4 PosH : POSITION0;
    float2 UV : TEXCOORD0;
};

TOONSHADER_2D_OUT_VERTEX ToonShader_2d_VertexShader_Main(TOONSHADER_2D_IN_VERTEX iv)
{
    TOONSHADER_2D_OUT_VERTEX ov;

    ov.PosH = mul(float4(iv.PosL, 1.0f), WorldViewProj);

    ov.UV = iv.UV;

    return ov;
}

float4 ToonShader_2d_PixelShader_Texture_Main(TOONSHADER_2D_OUT_VERTEX ip) : COLOR0
{
    float2 offsetUV = 1.0f / float2(1920.0f, 1080.0f);
    float4 n1 = tex2D(TexSampler, ip.UV + offsetUV * float2(-1, -1));
    float4 n2 = tex2D(TexSampler, ip.UV + offsetUV * float2(1, 1));
    float4 n3 = tex2D(TexSampler, ip.UV + offsetUV * float2(-1, 1));
    float4 n4 = tex2D(TexSampler, ip.UV + offsetUV * float2(1, -1));

    float4 diagonalDelta = abs(n1 - n2) + abs(n3 - n4);
    float normalDelta = dot(diagonalDelta.xyz, 1.0f);
    float depthDelta = diagonalDelta.w;
    normalDelta = saturate((normalDelta - 0.5f) * 5.0f);
    depthDelta = saturate((depthDelta - 0.2f) * 1.0f);
    float edgeAmount = saturate( normalDelta) * 1.0f;
    return float4((float3) 1.0f - edgeAmount, 1.0f) * tex2D(TexSampler, ip.UV);
}

float4 ToonShader_2d_PixelShader_NoTexture_Main(TOONSHADER_2D_OUT_VERTEX ip) : COLOR0
{
    float2 offsetUV = 1.0f / float2(1280.0f, 720.0f);
    float4 n1 = tex2D(TexSampler, ip.UV + offsetUV * float2(-1, -1));
    float4 n2 = tex2D(TexSampler, ip.UV + offsetUV * float2(1, 1));
    float4 n3 = tex2D(TexSampler, ip.UV + offsetUV * float2(-1, 1));
    float4 n4 = tex2D(TexSampler, ip.UV + offsetUV * float2(1, -1));

    float4 diagonalDelta = abs(n1 - n2) + abs(n3 - n4);
    float normalDelta = dot(diagonalDelta.xyz, 1.0f);
    float depthDelta = diagonalDelta.w;
    normalDelta = saturate((normalDelta - 0.5f) * 5.0f);
    depthDelta = saturate((depthDelta - 0.2f) * 1.0f);
    float edgeAmount = saturate(depthDelta + normalDelta) * 1.0f;
    return float4((float3) 1.0f - edgeAmount, 1.0f);
}

technique ToonShader_2d_TexterTech
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 ToonShader_2d_VertexShader_Main();
        PixelShader = compile ps_3_0 ToonShader_2d_PixelShader_Texture_Main();
    }
}

technique ToonShader_2d_NoTexterTech
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 ToonShader_2d_VertexShader_Main();
        PixelShader = compile ps_3_0 ToonShader_2d_PixelShader_NoTexture_Main();
    }
}

//ToonShader**************************************************************************************

struct TOONSHADER_MODEL_IN_VERTEX
{
    float3 PosL : POSITION0;
    float3 NormalL : NORMAL0;
    float2 UV : TEXCOORD0;
};

struct TOONSHADER_MODEL_OUT_VERTEX
{
    float4 PosH : POSITION0;
    float3 PosW : TEXCOORD1;
    float3 NormalW : TEXCOORD2;
    float2 UV : TEXCOORD0;
};

TOONSHADER_MODEL_OUT_VERTEX ToonShader_Model_VertexShader_Main(TOONSHADER_MODEL_IN_VERTEX iv)
{
    TOONSHADER_MODEL_OUT_VERTEX ov;

    ov.PosW = mul(float4(iv.PosL, 1.0f), World).xyz;
    ov.PosH = mul(float4(iv.PosL, 1.0f), WorldViewProj);
    ov.NormalW = mul(float4(iv.NormalL, 0.0f), WorldInverseTranspose).xyz;
    ov.UV = iv.UV;

    return ov;
}

float4 ToonShader_Model_PixelShader_Texture_Main(TOONSHADER_MODEL_OUT_VERTEX ip) : COLOR0
{
    ip.NormalW = normalize(ip.NormalW);

    float3 PostoCamera = normalize(EyePosW - ip.PosW);
    float3 normalizeLightDir = normalize(LightDirW);
    float3 reflectLight = normalize(reflect(normalizeLightDir, ip.NormalW));

    float4 diff = Diffuse * tex2D(ToonSampler, float2(dot(ip.NormalW, -normalizeLightDir) / 2 + 0.5f, 0.5f));
    float4 spec = Specular * pow(max(dot(reflectLight, PostoCamera), 0.0f), 50);
    float4 ambi = Ambient;

    return (diff + ambi) * tex2D(TexSampler, ip.UV);
}

float4 ToonShader_Model_PixelShader_NoTexture_Main(TOONSHADER_MODEL_OUT_VERTEX ip) : COLOR0
{
    ip.NormalW = normalize(ip.NormalW);

    float3 PostoCamera = normalize(EyePosW - ip.PosW);
    float3 normalizeLightDir = normalize(LightDirW);
    float3 reflectLight = normalize(reflect(normalizeLightDir, ip.NormalW));

    float4 diff = Diffuse * tex2D(ToonSampler, float2(dot(ip.NormalW, -normalizeLightDir) / 2 + 0.5f, 0.5f));
    float4 spec = Specular * pow(max(dot(reflectLight, PostoCamera), 0.0f), 50);
    float4 ambi = Ambient;

    return (diff + ambi);
}

technique ToonShader_Model_TexterTech
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 ToonShader_Model_VertexShader_Main();
        PixelShader = compile ps_3_0 ToonShader_Model_PixelShader_Texture_Main();
    }
}

technique ToonShader_Model_NoTexterTech
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 ToonShader_Model_VertexShader_Main();
        PixelShader = compile ps_3_0 ToonShader_Model_PixelShader_NoTexture_Main();
    }
}

//ZShadow*****************************************************
struct ZSHADOWSHADER_IN_VERTEX
{
    float3 PosL : POSITION0;
};

struct ZSHADOWSHADER_OUT_VERTEX
{
    float4 PosH : POSITION0;
    float DepthWV : TEXCOORD0;
};

ZSHADOWSHADER_OUT_VERTEX ZShadowShader_VertexShader_Main(ZSHADOWSHADER_IN_VERTEX iv)
{
    ZSHADOWSHADER_OUT_VERTEX ov;
    ov.PosH = mul(float4(iv.PosL, 1.0f), LightWVP);
    ov.DepthWV = ov.PosH.z / ov.PosH.w;
    return ov;
}

float4 ZShadowShader_PixelShader_Main(ZSHADOWSHADER_OUT_VERTEX ip) : COLOR0
{
    return float4(ip.DepthWV, 0.0f, 0.0f, 1.0f);
}

technique ZShadowShader_Tech
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 ZShadowShader_VertexShader_Main();
        PixelShader = compile ps_3_0 ZShadowShader_PixelShader_Main();
    }
}
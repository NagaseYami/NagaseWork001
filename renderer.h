#pragma once

// 頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_TEX1|D3DFVF_DIFFUSE|D3DFVF_NORMAL)
/*
D3DFVF_XYZ						3D空間の頂点座標。D3DFVF_XYZRHWとは排他。
D3DFVF_XYZRHW					スクリーン上の頂点座標。D3DFVF_XYZ、D3DFVF_NORMALとは排他。
D3DFVF_XYZB1 ～ D3DFVF_XYZB5	頂点ブレンディングをする場合の重み。
D3DFVF_LASTBETA_UBYTE4			インデックスつき頂点ブレンディングを使用する場合のインデックスデータ。
D3DFVF_NORMAL					頂点法線。ライティングに使用される。D3DFVF_XYZRHWとは排他。
D3DFVF_DIFFUSE					頂点のディフューズカラー。普通の色。
D3DFVF_SPECULAR					頂点のスペキュラカラー。反射色、といえばいいのかな？
D3DFVF_TEX0 ～ D3DFVF_TEX8		テクスチャ（UV）座標。使用する数だけ指定する。
*/

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 上記頂点フォーマットに合わせた構造体を定義

class Renderer 
{
public:
	static HRESULT Init(HWND hWnd);
	static void Uninit();
	static void Update();
	static void DrawRenderTargetBegin();
	static void DrawRenderTargetEnd();
	static void DrawBackBufferBegin();
	static void DrawBackBufferEnd();

	static LPDIRECT3DDEVICE9 GetDevice();
	static LPDIRECT3DSURFACE9 GetBackDepthSurface() 
	{
		return m_pBackDepthSurface;
	}
	static LPDIRECT3DSURFACE9 GetBackBufferSurface() {
		return m_pBackBufferSurface;
	}
private:
	static LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	static LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	static LPDIRECT3DSURFACE9		m_pBackBufferSurface;
	static LPDIRECT3DSURFACE9		m_pBackDepthSurface;
	
};
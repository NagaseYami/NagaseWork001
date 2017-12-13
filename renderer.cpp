#include "main.h"
#include "renderer.h"

LPDIRECT3D9				Renderer::m_pD3D = NULL;
LPDIRECT3DDEVICE9		Renderer::m_pD3DDevice = NULL;
LPDIRECT3DSURFACE9		Renderer::m_BackBufferSurface = NULL;

HRESULT Renderer::Init(HWND hWnd)
{
	// DirectXのバージョン確認です、バージョンが違うと失敗します。
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		MessageBox(NULL, "DirectXのバージョン確認に問題が発生しました。", "ERROR from rendererDX.cpp", MB_OK);
		return E_FAIL;
	}

	//ディスプレイモード
	D3DDISPLAYMODE d3ddm;
	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	// デバイスのプレゼンテーションパラメータ
	D3DPRESENT_PARAMETERS d3dpp;
	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));										// ワークをゼロクリア
	d3dpp.Windowed = true;													// TRUEにするとWindowモード、FALSEにするとフルスクリーンモード
	d3dpp.BackBufferWidth = SCREEN_WIDTH;									// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;									// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;									// バックバッファのピクセルフォーマット。D3DFORMAT 列挙型のメンバ
	d3dpp.BackBufferCount = 1;												// バックバッファの数。0 は 1 とみなされる
	d3dpp.EnableAutoDepthStencil = TRUE;									// Zバッファ、ステンシルバッファを使用する場合はTRUE。普通は使用しますね
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;							// 24ビットZバッファ8ビットステンシルバッファ作成
	//d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;						 // D3DPRESENTFLAG_LOCKABLE_BACKBUFFER を指定するとバックバッファがロック可能になります
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;								// 映像信号に同期してフリップする	
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;						// マルチサンプリングのタイプ。ビデオボードによっては対応している
	d3dpp.hDeviceWindow = NULL;												// ターゲットウィンドウ。NULLにすればフォーカスウィンドウになるので、普通はNULLでいいです
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;				// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;				// インターバル	

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				MessageBox(NULL, "DirectXのデバイス生成に問題が発生しました。", "ERROR from rendererDX.cpp", MB_OK);
				return E_FAIL;
			}
		}
	}

	if (FAILED(m_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, d3ddm.Format, d3dpp.Windowed,
		D3DMULTISAMPLE_8_SAMPLES, NULL))) {
		// 生成失敗
		MessageBox(NULL, "アンチエイリアスの確認に問題が発生しました。\nD3DMULTISAMPLE_TYPEが一致してるかどうかを確認してください。", "ERROR from rendererDX.cpp", MB_OK);
		return E_FAIL;
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// カリングを行わない
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);							// Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);					// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定
	//m_pD3DDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);				// アンチエイリアシングを使用

	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// テクスチャＵ値の繰り返し設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// テクスチャＶ値の繰り返し設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// テクスチャ拡大時の補間設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// テクスチャ縮小時の補間設定

	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// アルファブレンディング処理(初期値はD3DTOP_SELECTARG1)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// 最初のアルファ引数(初期値はD3DTA_TEXTURE、テクスチャがない場合はD3DTA_DIFFUSE)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);		// ２番目のアルファ引数(初期値はD3DTA_CURRENT)

	
	m_pD3DDevice->GetRenderTarget(0, &m_BackBufferSurface);

	return S_OK;
}

void Renderer::Uninit()
{
	// デバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	if (m_BackBufferSurface)
	{
		m_BackBufferSurface->Release();
		m_BackBufferSurface = NULL;
	}
}

void Renderer::Update()
{

}

void Renderer::DrawRenderTargetBegin(LPDIRECT3DSURFACE9 surface)
{
	m_pD3DDevice->SetRenderTarget(0, surface);
	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 0), 1.0f, 0);
	// Direct3Dによる描画の開始
	m_pD3DDevice->BeginScene();
}

void Renderer::DrawRenderTargetEnd()
{
	// Direct3Dによる描画の終了
	m_pD3DDevice->EndScene();	
}

void Renderer::DrawBackBufferBegin()
{
	m_pD3DDevice->SetRenderTarget(0, m_BackBufferSurface);
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);
	m_pD3DDevice->BeginScene();
}

void Renderer::DrawBackBufferEnd()
{
	// Direct3Dによる描画の終了
	m_pD3DDevice->EndScene();
	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	
}

LPDIRECT3DDEVICE9 Renderer::GetDevice()
{
	return m_pD3DDevice;
}

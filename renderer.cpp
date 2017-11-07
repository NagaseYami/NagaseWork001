#include "main.h"
#include "renderer.h"

LPDIRECT3D9				Renderer::m_pD3D = NULL;
LPDIRECT3DDEVICE9		Renderer::m_pD3DDevice = NULL;

HRESULT Renderer::Init(HWND hWnd)
{
	// DirectX�̃o�[�W�����m�F�ł��A�o�[�W�������Ⴄ�Ǝ��s���܂��B
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		MessageBox(NULL, "DirectX�̃o�[�W�����m�F�ɖ�肪�������܂����B", "ERROR from rendererDX.cpp", MB_OK);
		return E_FAIL;
	}

	//�f�B�X�v���C���[�h
	D3DDISPLAYMODE d3ddm;
	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
	D3DPRESENT_PARAMETERS d3dpp;
	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));										// ���[�N���[���N���A
	d3dpp.Windowed = true;													// TRUE�ɂ����Window���[�h�AFALSE�ɂ���ƃt���X�N���[�����[�h
	d3dpp.BackBufferWidth = SCREEN_WIDTH;									// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;									// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;									// �o�b�N�o�b�t�@�̃s�N�Z���t�H�[�}�b�g�BD3DFORMAT �񋓌^�̃����o
	d3dpp.BackBufferCount = 1;												// �o�b�N�o�b�t�@�̐��B0 �� 1 �Ƃ݂Ȃ����
	d3dpp.EnableAutoDepthStencil = TRUE;									// Z�o�b�t�@�A�X�e���V���o�b�t�@���g�p����ꍇ��TRUE�B���ʂ͎g�p���܂���
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;								// �f�v�X�o�b�t�@�Ƃ���16bit���g��
																			//d3dpp.Flags						 = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;  // D3DPRESENTFLAG_LOCKABLE_BACKBUFFER ���w�肷��ƃo�b�N�o�b�t�@�����b�N�\�ɂȂ�܂�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;								// �f���M���ɓ������ăt���b�v����	
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;						// �}���`�T���v�����O�̃^�C�v�B�r�f�I�{�[�h�ɂ���Ă͑Ή����Ă���
	d3dpp.hDeviceWindow = NULL;												// �^�[�Q�b�g�E�B���h�E�BNULL�ɂ���΃t�H�[�J�X�E�B���h�E�ɂȂ�̂ŁA���ʂ�NULL�ł����ł�
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;					// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;				// �C���^�[�o��	


	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				MessageBox(NULL, "DirectX�̃f�o�C�X�����ɖ�肪�������܂����B", "ERROR from rendererDX.cpp", MB_OK);
				return E_FAIL;
			}
		}
	}

	if (FAILED(m_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, d3ddm.Format, d3dpp.Windowed,
		D3DMULTISAMPLE_8_SAMPLES, NULL))) {
		// �������s
		MessageBox(NULL, "�A���`�G�C���A�X�̊m�F�ɖ�肪�������܂����B\nD3DMULTISAMPLE_TYPE����v���Ă邩�ǂ������m�F���Ă��������B", "ERROR from rendererDX.cpp", MB_OK);
		return E_FAIL;
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// �J�����O���s��Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);							// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);					// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ���f�X�e�B�l�[�V�����J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);				// �A���`�G�C���A�V���O���g�p

	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// �e�N�X�`���u�l�̌J��Ԃ��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// �e�N�X�`���g�厞�̕�Ԑݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// �e�N�X�`���k�����̕�Ԑݒ�
																				// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// �A���t�@�u�����f�B���O����(�����l��D3DTOP_SELECTARG1)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// �ŏ��̃A���t�@����(�����l��D3DTA_TEXTURE�A�e�N�X�`�����Ȃ��ꍇ��D3DTA_DIFFUSE)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);		// �Q�Ԗڂ̃A���t�@����(�����l��D3DTA_CURRENT)

	return S_OK;
}

void Renderer::Uninit()
{
	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

void Renderer::Update()
{

}

void Renderer::DrawBegin()
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(127, 127, 127, 255), 1.0f, 0);
	// Direct3D�ɂ��`��̊J�n
	m_pD3DDevice->BeginScene();
}

void Renderer::DrawEnd()
{
	// Direct3D�ɂ��`��̏I��
	m_pD3DDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 Renderer::GetDevice()
{
	return m_pD3DDevice;
}

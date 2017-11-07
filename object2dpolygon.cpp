#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2dpolygon.h"

void Object2DPolygon::Init()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//���_�쐬*******************************************************************************

	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,	//�쐬���������_�o�b�t�@�̃T�C�Y�i��̃T�C�Y*���_���j
		D3DUSAGE_WRITEONLY,				//VertexBuffer�̎g�p���@
		FVF_VERTEX_2D,					//�����Ȃ��Ă����v
		D3DPOOL_MANAGED,				//�������Ǘ����@(�f�o�C�X�ɂ��C��)
		&m_pVtxBuff,
		NULL
	))) {
		MessageBox(NULL, "���_�o�b�t�@�̐����ɖ�肪�������܂���", "ERROR from object2dpolygon.cpp", MB_OK | MB_ICONWARNING);
	}
}

void Object2DPolygon::Uninit()
{
	m_pTexture = NULL;
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void Object2DPolygon::FixedUpdate()
{
}

void Object2DPolygon::Update()
{
}

void Object2DPolygon::LateUpdate()
{
	// �|���S���̈ʒu��ݒ�**************************************************************************************
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//����
	pVtx[0].pos = Vector3(m_Pos.x, m_Pos.y, 0.0f);
	pVtx[1].pos = Vector3(m_Pos.x + m_Size.x, m_Pos.y, 0.0f);
	pVtx[2].pos = Vector3(m_Pos.x, m_Pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = Vector3(m_Pos.x + m_Size.x, m_Pos.y + m_Size.y, 0.0f);

	//rhw�̐ݒ�(�K��1.0f)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�(0~255�̐����l)
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�f�[�^��UV�f�[�^�̒ǉ�
	pVtx[0].tex = Vector2(0.0f, 0.0f);
	pVtx[1].tex = Vector2(1.0f, 0.0f);
	pVtx[2].tex = Vector2(0.0f, 1.0f);
	pVtx[3].tex = Vector2(1.0f, 1.0f);

	//���b�N����
	m_pVtxBuff->Unlock();
}

void Object2DPolygon::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

#pragma once

// ���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_TEX1|D3DFVF_DIFFUSE|D3DFVF_NORMAL)
/*
D3DFVF_XYZ						3D��Ԃ̒��_���W�BD3DFVF_XYZRHW�Ƃ͔r���B
D3DFVF_XYZRHW					�X�N���[����̒��_���W�BD3DFVF_XYZ�AD3DFVF_NORMAL�Ƃ͔r���B
D3DFVF_XYZB1 �` D3DFVF_XYZB5	���_�u�����f�B���O������ꍇ�̏d�݁B
D3DFVF_LASTBETA_UBYTE4			�C���f�b�N�X�����_�u�����f�B���O���g�p����ꍇ�̃C���f�b�N�X�f�[�^�B
D3DFVF_NORMAL					���_�@���B���C�e�B���O�Ɏg�p�����BD3DFVF_XYZRHW�Ƃ͔r���B
D3DFVF_DIFFUSE					���_�̃f�B�t���[�Y�J���[�B���ʂ̐F�B
D3DFVF_SPECULAR					���_�̃X�y�L�����J���[�B���ːF�A�Ƃ����΂����̂��ȁH
D3DFVF_TEX0 �` D3DFVF_TEX8		�e�N�X�`���iUV�j���W�B�g�p���鐔�����w�肷��B
*/

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`

struct VERTEX_2D 
{
	Vector3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	Vector2 tex;	// �e�N�X�`�����W
} ;

struct VERTEX_3D 
{
	Vector3 pos;
	Vector3 normal;
	D3DCOLOR color;
	Vector2 tex;
};

class Renderer 
{
public:
	static HRESULT Init(HWND hWnd);
	static void Uninit();
	static void Update();
	static void DrawBegin();
	static void DrawEnd();

	static LPDIRECT3DDEVICE9 GetDevice();
private:
	static LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	static LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
};
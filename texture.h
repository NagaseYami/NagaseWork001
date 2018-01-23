#pragma once
class Object;
class Texture {
public:
	enum TEXTURE_TYPE
	{
		NORMAL = 0,
		RENDERTARGET,
		SHADOWMAP
	};
	Texture();
	static Texture * LoadTextureFromFile(LPCSTR fileName);
	static Texture * CreateEmptyTexture(string name, Vector2 size, TEXTURE_TYPE type = RENDERTARGET, D3DFORMAT format = D3DFMT_A8R8G8B8, bool COLORWRITEENABLE = true);
	static void AddObjectToRenderTargetTexture(Object *obj, string name);
	static void DrawAllRenderTargetTexture();
	static void DestoryAllTexture();

	//Getter
	static Texture * GetTexture(string name);
	LPDIRECT3DTEXTURE9 GetDXTexture() {
		return m_Texture;
	}
	LPDIRECT3DSURFACE9 GetDXSurface() {
		return m_Surface;
	}

	//Setter
	void SetDXTexture(LPDIRECT3DTEXTURE9 tex) {
		m_Texture = tex;
	}
	void SetDXSurface(LPDIRECT3DSURFACE9 sur) {
		m_Surface = sur;
	}
private:
	static void DrawRenderTargetTextureRecursion(Texture * tex);

	static map<string, Texture*> m_Manager;

	TEXTURE_TYPE m_Type = NORMAL;
	bool m_ColorWriteEnable = true;
	LPDIRECT3DTEXTURE9 m_Texture = NULL;
	LPDIRECT3DSURFACE9 m_Surface = NULL;
	list<Object*> m_RenderTargetObj;
};
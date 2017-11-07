#pragma once
class Texture {
public:
	static LPDIRECT3DTEXTURE9 LoadTexture(LPCSTR fileName);
	static void DestoryAllTexture();
	static LPDIRECT3DTEXTURE9 GetTexture(string name);
private:
	static map<string, LPDIRECT3DTEXTURE9> Manager;
};
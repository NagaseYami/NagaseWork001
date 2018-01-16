#pragma once
class Texture;
class Object {
public:
	enum OBJECT_TAG
	{
		UNKNOW_TAG = 0
	};

	enum OBJECT_LAYER
	{
		BACKGROUND_LAYER = 0,
		POLYGON3D_LAYER,
		STENCILSHADOW_LAYER,
		XMODEL_LAYER,
		POLYGON2D_LAYER,
		UNKNOW_LAYER
	};

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Draw() = 0;
	void DestoryFlag(bool flag);

	Object();
	static void FixedUpdateAll();
	static void UpdateAll();
	static void LateUpdateAll();
	static void DrawAllBackBufferObject();
	static void UninitNotBeingUsedObject();
	static void UninitAll();

	bool isDestory() const;

	//Getter
	vector<Texture*> GetTexture() {
		return m_TextureList;
	}
	//Setter
	void SetRenderTarget(bool value) {
		m_isRenderTarget = value;
	}
protected:
	OBJECT_TAG m_Tag = OBJECT_TAG::UNKNOW_TAG;
	OBJECT_LAYER m_Layer = OBJECT_LAYER::UNKNOW_LAYER;
	vector<Texture*> m_TextureList;
	bool m_isRenderTarget = false;
	bool m_bDestory = false;
private:
	static vector<Object*> m_pManager;
};
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
	void DontDrawThisOnBackBuffer(bool value) {
		m_DontDrawThisOnBackBuffer = value;
	}
	void SetShader(string shaderfilepath, string tech_tex, string tech_notex ) {
		m_ShaderFilePath = shaderfilepath;
		m_Technique_Tex = tech_tex;
		m_Technique_NoTex = tech_notex;
	}
	void SetVariableToShaderFn(function<void(LPD3DXEFFECT)> fn) {
		m_VariableToShaderFn = fn;
	}
protected:
	OBJECT_TAG m_Tag = OBJECT_TAG::UNKNOW_TAG;
	OBJECT_LAYER m_Layer = OBJECT_LAYER::UNKNOW_LAYER;
	vector<Texture*> m_TextureList;
	bool m_DontDrawThisOnBackBuffer = false;
	bool m_bDestory = false;
	string m_ShaderFilePath = "data/Shader/BasicShader.fx";
	string m_Technique_Tex = "BasicShader_TexterTech";
	string m_Technique_NoTex = "BasicShader_NoTexterTech";
	function<void(LPD3DXEFFECT)> m_VariableToShaderFn = nullptr;
private:
	static vector<Object*> m_pManager;
};
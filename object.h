#pragma once
class Object {
public:
	enum OBJECT_TAG
	{
		UNKNOW_TAG = 0
	};

	enum OBJECT_LAYER
	{
		BACKGROUND_LAYER = 0,
		SHADOW_LAYER,
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
	static void DrawAll();
	static void UninitAll();

	bool operator<(const Object & right) const;
	bool operator>(const Object & right) const;

	bool isDestory() const;

protected:
	OBJECT_TAG m_Tag = OBJECT_TAG::UNKNOW_TAG;
	OBJECT_LAYER m_Layer = OBJECT_LAYER::UNKNOW_LAYER;
	bool m_bDestory = false;
private:
	static list<Object*> m_pManager;
};
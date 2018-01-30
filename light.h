#pragma once
class Light
{
public:
	Light();
	static Vector3 GetSun() {
		return m_Sun;
	}
private:
	static Vector3 m_Sun;
	Vector3 m_Tra = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Color = Vector3(0.0f, 0.0f, 0.0f);
};
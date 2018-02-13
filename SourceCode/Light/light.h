#pragma once
#include "../Main/main.h"
class Light
{
public:
	Light();
	static Vector3 GetSun() {
		return m_Sun;
	}

	//Getter
	Vector3 GetTra() {
		return m_Tra;
	}
	Vector3 GetColor() {
		return m_Color;
	}
	float GetAttenuation() {
		return m_Attenuation;
	}
	//Setter
	void SetTra(Vector3 value) {
		m_Tra = value;
	}
	void SetColor(Vector3 value) {
		m_Color = value;
	}
	void SetAttenuation(float value) {
		m_Attenuation = value;
	}
private:
	static Vector3 m_Sun;
	Vector3 m_Tra = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Color = Vector3(0.0f, 0.0f, 0.0f);
	float m_Attenuation = 10.0f;
};
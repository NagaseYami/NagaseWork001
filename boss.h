#pragma once
class Boss {
public:
	void Init();
	void UpdateMain();
protected:
	struct BossMotion
	{
		bool CanbeBreak;
		vector<KEY> MotionList[10];
	};
	void XModelInit();
	void ParentInit();
	void TransformInit();
	void MotionInit();
	void LoadMotionFromFile(string filename, bool canbebreak);
	void ChangeMotion(string motionname);

	void MotionUpdate();
	void TimeUpdate(int limit);
	void SetModelTimer(int time);

	ObjectXModel * pPart[7];
	Vector3 m_Dir;
	map<string, BossMotion> m_Motion;
	string m_PlayingMotion = "Null";
	int m_Timer = 0;
	bool m_EndofMotion = true;
};
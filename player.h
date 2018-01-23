#pragma once
class ObjectXModel;
struct KEY;
class Player {
public:
	static void Init();
	static void Update();

	//Getter
	static Vector3 GetTra()
	{
		return m_Tra;
	}
private:
	struct PlayerMotion
	{
		bool CanbeBreak;
		vector<KEY> MotionList[10];
	};

	static void XModelInit();
	static void ParentInit();
	static void TransformInit(); 
	static void MotionInit();
	static void LoadMotionFromFile(string filename,bool canbebreak);
	static void ChangeMotion(string motionname);

	static void ControllerUpdate();
	static void MotionUpdate();
	static void TimeUpdate(int limit);
	static void SetModelTimer(int time);

	static ObjectXModel * pPart[10];
	static Vector3 m_Tra;
	static Vector3 m_Dir;
	static map<string,PlayerMotion> m_Motion;
	static string m_PlayingMotion;
	static int m_Timer;
	static bool m_EndofMotion;
};
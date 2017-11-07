#include <math.h>
#include <time.h>
#include "d3dx9.h"
#include "KM_Math.h"
#ifdef BULLET_ENGINE
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#endif
namespace Kuma {
	float RandomRange(float l_fMin, float l_fMax)
	{
		srand((unsigned int)time(NULL));
		return l_fMin + (rand() / float(RAND_MAX))*(l_fMax - l_fMin);
	}
	int RandomRange(int l_nMin, int l_nMax)
	{
		srand((unsigned int)time(NULL));
		return l_nMin + (rand() % (l_nMax - l_nMin));
	}
	double Noise(int x, int y)
	{
		int n = x + y * 57;
		n = (n << 13) ^ n;
		return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
	}
	double SmoothedNoise(int x, int y)
	{
		double corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16;
		double sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8;
		double center = Noise(x, y) / 4;
		return corners + sides + center;
	}
	double Cosine_Interpolate(double a, double b, double x)
	{
		double ft = x * 3.1415927;
		double f = (1 - cos(ft)) * 0.5;
		return a*(1 - f) + b*f;
	}
	double InterpolatedNoise(float x, float y)
	{
		int integer_X = int(x);
		float  fractional_X = x - integer_X;
		int integer_Y = int(y);
		float fractional_Y = y - integer_Y;
		double v1 = SmoothedNoise(integer_X, integer_Y);
		double v2 = SmoothedNoise(integer_X + 1, integer_Y);
		double v3 = SmoothedNoise(integer_X, integer_Y + 1);
		double v4 = SmoothedNoise(integer_X + 1, integer_Y + 1);
		double i1 = Cosine_Interpolate(v1, v2, fractional_X);
		double i2 = Cosine_Interpolate(v3, v4, fractional_X);
		return Cosine_Interpolate(i1, i2, fractional_Y);
	}
	double PerlinNoise(float x, float y, double persistence, int number_of_octaves)
	{
		float total = 0.0f;
		double p = persistence;
		int n = number_of_octaves;
		for (int i = 0; i<n; i++)
		{
			double frequency = pow(2, i);
			double amplitude = pow(p, i);
			total = total + (float)InterpolatedNoise(x * frequency, y * frequency) * (float)amplitude;
		}

		return (double)total;
	}
	float Vector3Dot(const Vector3 & l_vec1, const Vector3 & l_vec2)
	{
		return l_vec1.x*l_vec2.x + l_vec1.y*l_vec2.y + l_vec1.z*l_vec2.z;
	}
	void Kuma::Vector3Cross(Vector3 * l_output, Vector3 * l_vec1, Vector3 * l_vec2)
	{
		Vector3 output;
		output.x = l_vec1->y*l_vec2->z - l_vec1->z * l_vec2->y;
		output.y = l_vec1->z*l_vec2->x - l_vec1->x * l_vec2->z;
		output.z = l_vec1->x*l_vec2->y - l_vec1->y * l_vec2->x;
		*l_output = output;
	}
	void Vector3Normalize(Vector3 * l_output, Vector3 * l_input)
	{
		*l_output = *l_input / l_input->Length();
	}
	void Vector3RotationAxis(Vector3 * l_input, const Vector3 & l_axis, const float & l_theta)
	{
		Vector3 output;
		output.x = l_input->x * l_axis.x*l_axis.x*(1 - cosf(l_theta)) + cosf(l_theta) +
			l_input->y * l_axis.x*l_axis.y*(1 - cosf(l_theta)) - l_axis.z*sinf(l_theta) +
			l_input->z * l_axis.z*l_axis.x*(1 - cosf(l_theta)) + l_axis.y*sinf(l_theta);

		output.y = l_input->x * l_axis.x*l_axis.y*(1 - cosf(l_theta)) + l_axis.z*sinf(l_theta) +
			l_input->y * l_axis.y*l_axis.y*(1 - cosf(l_theta)) + cosf(l_theta) +
			l_input->z * l_axis.y*l_axis.z*(1 - cosf(l_theta)) - l_axis.x*sinf(l_theta);

		output.z = l_input->x * l_axis.z*l_axis.x*(1 - cosf(l_theta)) - l_axis.y*sinf(l_theta) +
			l_input->y * l_axis.y*l_axis.z*(1 - cosf(l_theta)) + l_axis.x*sinf(l_theta) +
			l_input->z * l_axis.z*l_axis.z*(1 - cosf(l_theta)) + cosf(l_theta);

		*l_input = output;
	}
	float Vector2Dot(Vector2 * l_vec1, Vector2 * l_vec2)
	{
		return l_vec1->x*l_vec2->x + l_vec1->y*l_vec2->y;
	}
	void Vector2Cross(float * l_output, Vector2 * l_vec1, Vector2 * l_vec2)
	{
		*l_output = l_vec1->x*l_vec2->y - l_vec2->x*l_vec1->y;
	}
	float AngleBetween2Vector2(Vector2 & l_vec1, Vector2 & l_vec2)
	{
		//DXŒn
		float cross,dot;
		Vector2Cross(&cross, &l_vec1, &l_vec2);
		dot = Vector2Dot(&l_vec1, &l_vec2);

		float angle = acosf(Vector2Dot(&l_vec1, &l_vec2) / l_vec1.Length() / l_vec2.Length());

		if (cross>0)
		{
			return angle;
		}
		else 
		{
			return -angle;
		}
	}
	void VectorQuaternionIdentity(Vector4 * l_pVector4)
	{
		l_pVector4->x = l_pVector4->y = l_pVector4->z = 0.0f;
		l_pVector4->z = 1.0f;
	}
	void VectorQuaterniontoEuler(const Vector4 & l_input, Vector3 * l_output)
	{
		float roll = atan2f(2 * (l_input.w*l_input.x + l_input.y*l_input.z), 1 - 2 * (l_input.x*l_input.x + l_input.y*l_input.y));
		float yaw = asinf(2 * (l_input.w*l_input.y - l_input.z*l_input.x));
		float picth = atan2f(2 * (l_input.w*l_input.z + l_input.x*l_input.y), 1 - 2 * (l_input.z*l_input.z + l_input.y*l_input.y));
		*l_output = Vector3(roll, yaw, picth);
	}
#ifdef BULLET_ENGINE
	void btMatrix3x3toAngle(const btMatrix3x3 & Mat, Vector3 * l_output)
	{
		float threshold = 0.001f;
		if (abs(Mat.getRow(2).y() - 1.0) < threshold) { // R(2,1) = sin(x) = 1‚ÌŽž
			*l_output = Vector3(3.141592653f / 2.0f, 0.0f, atan2(Mat.getRow(1).x(), Mat.getRow(0).x()));
		}
		else if (abs(Mat.getRow(2).y() + 1.0) < threshold) { // R(2,1) = sin(x) = -1‚ÌŽž
			*l_output = Vector3(-3.141592653f / 2.0f, 0.0f, atan2(Mat.getRow(1).x(), Mat.getRow(0).x()));
		}
		else {
			*l_output = Vector3(asin(Mat.getRow(2).y()), -atan2(-Mat.getRow(2).x(), Mat.getRow(2).z()), atan2(-Mat.getRow(0).y(), Mat.getRow(1).y()));
		}
	}
#endif
}
#pragma once
class btMatrix3x3;
#define CLAMP(x , min , max) ((x) > (max) ? (max) : ((x) < (min) ? (min) : x))
namespace Kuma {

	class Vector2 {
	public:
		float x, y;

		Vector2() :x(0.0f), y(0.0f) {}
		Vector2(float l_x, float l_y) {
			this->x = l_x;
			this->y = l_y;
		}

		float Length(void) {
			return sqrtf(x*x + y*y);
		}
		Vector2 Normalize(void) {
			return (Vector2(x, y) / Vector2::Length());
		}

		operator D3DXVECTOR2() const {
			D3DXVECTOR2 l_DXVector2;
			l_DXVector2.x = this->x;
			l_DXVector2.y = this->y;
			return l_DXVector2;
		}

		Vector2 operator+() const {
			Vector2 l_Result;
			l_Result.x = this->x;
			l_Result.y = this->y;
			return l_Result;
		}
		Vector2 operator-() const {
			Vector2 l_Result;
			l_Result.x = -this->x;
			l_Result.y = -this->y;
			return l_Result;
		}

		Vector2 operator+(const float & l_Float) const {
			Vector2 l_Result;
			l_Result.x = this->x + l_Float;
			l_Result.y = this->y + l_Float;
			return l_Result;
		}
		Vector2 operator-(const float & l_Float) const {
			Vector2 l_Result;
			l_Result.x = this->x - l_Float;
			l_Result.y = this->y - l_Float;
			return l_Result;
		}
		Vector2 operator*(const float & l_Float) const {
			Vector2 l_Result;
			l_Result.x = this->x * l_Float;
			l_Result.y = this->y * l_Float;
			return l_Result;
		}
		Vector2 operator/(const float & l_Float) const {
			Vector2 l_Result;
			l_Result.x = this->x / l_Float;
			l_Result.y = this->y / l_Float;
			return l_Result;
		}

		Vector2 operator+(const Vector2 & l_Vector2) const {
			Vector2 l_Result;
			l_Result.x = this->x + l_Vector2.x;
			l_Result.y = this->y + l_Vector2.y;
			return l_Result;
		}
		Vector2 operator-(const Vector2 & l_Vector2) const {
			Vector2 l_Result;
			l_Result.x = this->x - l_Vector2.x;
			l_Result.y = this->y - l_Vector2.y;
			return l_Result;
		}
		Vector2 operator*(const Vector2 & l_Vector2) const {
			Vector2 l_Result;
			l_Result.x = this->x * l_Vector2.x;
			l_Result.y = this->y * l_Vector2.y;
			return l_Result;
		}
		Vector2 operator/(const Vector2 & l_Vector2) const {
			Vector2 l_Result;
			l_Result.x = this->x / l_Vector2.x;
			l_Result.y = this->y / l_Vector2.y;
			return l_Result;
		}

		Vector2& operator+=(const Vector2 & l_Vector2) {
			this->x += l_Vector2.x;
			this->y += l_Vector2.y;
			return *this;
		}
		Vector2& operator-=(const Vector2 & l_Vector2) {
			this->x -= l_Vector2.x;
			this->y -= l_Vector2.y;
			return *this;
		}
		Vector2& operator*=(const Vector2 & l_Vector2) {
			this->x *= l_Vector2.x;
			this->y *= l_Vector2.y;
			return *this;
		}
		Vector2& operator/=(const Vector2 & l_Vector2) {
			this->x /= l_Vector2.x;
			this->y /= l_Vector2.y;
			return *this;
		}

		bool operator==(const Vector2 & l_Vector2) const {
			if (this->x == l_Vector2.x && this->y == l_Vector2.y)
			{
				return true;
			}
			return false;
		}
		bool operator!=(const Vector2 & l_Vector2) const {
			if (this->x != l_Vector2.x && this->y != l_Vector2.y)
			{
				return true;
			}
			return false;
		}
	};

	class Vector3 {
	public:
		float x, y, z;

		Vector3() :x(0.0f), y(0.0f), z(0.0f) {}
		Vector3(float l_x, float l_y, float l_z) {
			this->x = l_x;
			this->y = l_y;
			this->z = l_z;
		}

		float Length(void) {
			return sqrtf(x*x + y*y + z*z);
		}
		Vector3 Normalize(void) {
			return (Vector3(x, y, z) / Vector3::Length());
		}

		operator D3DXVECTOR3() const {
			D3DXVECTOR3 l_DXVector3;
			l_DXVector3.x = this->x;
			l_DXVector3.y = this->y;
			l_DXVector3.z = this->z;
			return l_DXVector3;
		}
		operator D3DVECTOR() const {
			D3DVECTOR l_DXVector3;
			l_DXVector3.x = this->x;
			l_DXVector3.y = this->y;
			l_DXVector3.z = this->z;
			return l_DXVector3;
		}

		Vector3 operator+() const {
			Vector3 l_Result;
			l_Result.x = this->x;
			l_Result.y = this->y;
			l_Result.z = this->z;
			return l_Result;
		}
		Vector3 operator-() const {
			Vector3 l_Result;
			l_Result.x = -this->x;
			l_Result.y = -this->y;
			l_Result.z = -this->z;
			return l_Result;
		}

		Vector3 operator+(const float & l_Float) const {
			Vector3 l_Result;
			l_Result.x = this->x + l_Float;
			l_Result.y = this->y + l_Float;
			l_Result.z = this->z + l_Float;
			return l_Result;
		}
		Vector3 operator-(const float & l_Float) const {
			Vector3 l_Result;
			l_Result.x = this->x - l_Float;
			l_Result.y = this->y - l_Float;
			l_Result.z = this->z - l_Float;
			return l_Result;
		}
		Vector3 operator*(const float & l_Float) const {
			Vector3 l_Result;
			l_Result.x = this->x * l_Float;
			l_Result.y = this->y * l_Float;
			l_Result.z = this->z * l_Float;
			return l_Result;
		}
		Vector3 operator/(const float & l_Float) const {
			Vector3 l_Result;
			l_Result.x = this->x / l_Float;
			l_Result.y = this->y / l_Float;
			l_Result.z = this->z / l_Float;
			return l_Result;
		}

		Vector3& operator+=(const float & l_Float) {
			this->x += l_Float;
			this->y += l_Float;
			this->z += l_Float;
			return *this;
		}
		Vector3& operator-=(const float & l_Float) {
			this->x -= l_Float;
			this->y -= l_Float;
			this->z -= l_Float;
			return *this;
		}
		Vector3& operator*=(const float & l_Float) {
			this->x *= l_Float;
			this->y *= l_Float;
			this->z *= l_Float;
			return *this;
		}
		Vector3& operator/=(const float & l_Float) {
			this->x /= l_Float;
			this->y /= l_Float;
			this->z /= l_Float;
			return *this;
		}

		Vector3 operator+(const Vector3 & l_Vector3) const {
			Vector3 l_Result;
			l_Result.x = this->x + l_Vector3.x;
			l_Result.y = this->y + l_Vector3.y;
			l_Result.z = this->z + l_Vector3.z;
			return l_Result;
		}
		Vector3 operator-(const Vector3 & l_Vector3) const {
			Vector3 l_Result;
			l_Result.x = this->x - l_Vector3.x;
			l_Result.y = this->y - l_Vector3.y;
			l_Result.z = this->z - l_Vector3.z;
			return l_Result;
		}
		Vector3 operator*(const Vector3 & l_Vector3) const {
			Vector3 l_Result;
			l_Result.x = this->x * l_Vector3.x;
			l_Result.y = this->y * l_Vector3.y;
			l_Result.z = this->z * l_Vector3.z;
			return l_Result;
		}
		Vector3 operator/(const Vector3 & l_Vector3) const {
			Vector3 l_Result;
			l_Result.x = this->x / l_Vector3.x;
			l_Result.y = this->y / l_Vector3.y;
			l_Result.z = this->z / l_Vector3.z;
			return l_Result;
		}

		Vector3& operator+=(const Vector3 & l_Vector3) {
			this->x += l_Vector3.x;
			this->y += l_Vector3.y;
			this->z += l_Vector3.z;
			return *this;
		}
		Vector3& operator-=(const Vector3 & l_Vector3) {
			this->x -= l_Vector3.x;
			this->y -= l_Vector3.y;
			this->z -= l_Vector3.z;
			return *this;
		}
		Vector3& operator*=(const Vector3 & l_Vector3) {
			this->x *= l_Vector3.x;
			this->y *= l_Vector3.y;
			this->z *= l_Vector3.z;
			return *this;
		}
		Vector3& operator/=(const Vector3 & l_Vector3) {
			this->x /= l_Vector3.x;
			this->y /= l_Vector3.y;
			this->z /= l_Vector3.z;
			return *this;
		}

		bool operator==(const Vector3 & l_Vector3) const {
			if (this->x == l_Vector3.x &&
				this->y == l_Vector3.y &&
				this->z == l_Vector3.z)
			{
				return true;
			}
			return false;
		}
		bool operator!=(const Vector3 & l_Vector3) const {
			if (this->x != l_Vector3.x &&
				this->y != l_Vector3.y &&
				this->z != l_Vector3.z)
			{
				return true;
			}
			return false;
		}
	};

	class Vector4 {
	public:
		float x, y, z, w;

		Vector4() :x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		Vector4(float l_x, float l_y, float l_z, float l_w) {
			this->x = l_x;
			this->y = l_y;
			this->z = l_z;
			this->w = l_w;
		}

		float Length(void) {
			return sqrtf(x*x + y*y + z*z + w*w);
		}
		Vector4 Normalize(void) {
			return (Vector4(x, y, z, w) / Vector4::Length());
		}

		operator D3DXVECTOR4() const {
			D3DXVECTOR4 l_DXVector4;
			l_DXVector4.x = this->x;
			l_DXVector4.y = this->y;
			l_DXVector4.z = this->z;
			l_DXVector4.w = this->w;
			return l_DXVector4;
		}
		operator D3DXQUATERNION() const {
			D3DXQUATERNION l_DXQuaternion;
			l_DXQuaternion.x = this->x;
			l_DXQuaternion.y = this->y;
			l_DXQuaternion.z = this->z;
			l_DXQuaternion.w = this->w;
			return l_DXQuaternion;
		}
		operator D3DCOLORVALUE() const {
			D3DCOLORVALUE l_DXVector4;
			l_DXVector4.r = this->x;
			l_DXVector4.g = this->y;
			l_DXVector4.b = this->z;
			l_DXVector4.a = this->w;
			return l_DXVector4;
		}

		Vector4 operator+() const {
			Vector4 l_Result;
			l_Result.x = this->x;
			l_Result.y = this->y;
			l_Result.z = this->z;
			l_Result.w = this->w;
			return l_Result;
		}
		Vector4 operator-() const {
			Vector4 l_Result;
			l_Result.x = -this->x;
			l_Result.y = -this->y;
			l_Result.z = -this->z;
			l_Result.w = -this->w;
			return l_Result;
		}

		Vector4 operator+(const float & l_Float) const {
			Vector4 l_Result;
			l_Result.x = this->x + l_Float;
			l_Result.y = this->y + l_Float;
			l_Result.z = this->z + l_Float;
			l_Result.w = this->w + l_Float;
			return l_Result;
		}
		Vector4 operator-(const float & l_Float) const {
			Vector4 l_Result;
			l_Result.x = this->x - l_Float;
			l_Result.y = this->y - l_Float;
			l_Result.z = this->z - l_Float;
			l_Result.w = this->w - l_Float;
			return l_Result;
		}
		Vector4 operator*(const float & l_Float) const {
			Vector4 l_Result;
			l_Result.x = this->x * l_Float;
			l_Result.y = this->y * l_Float;
			l_Result.z = this->z * l_Float;
			l_Result.w = this->w * l_Float;
			return l_Result;
		}
		Vector4 operator/(const float & l_Float) const {
			Vector4 l_Result;
			l_Result.x = this->x / l_Float;
			l_Result.y = this->y / l_Float;
			l_Result.z = this->z / l_Float;
			l_Result.w = this->w / l_Float;
			return l_Result;
		}

		Vector4 operator+(const Vector4 & l_Vector4) const {
			Vector4 l_Result;
			l_Result.x = this->x + l_Vector4.x;
			l_Result.y = this->y + l_Vector4.y;
			l_Result.z = this->z + l_Vector4.z;
			l_Result.w = this->w + l_Vector4.w;
			return l_Result;
		}
		Vector4 operator-(const Vector4 & l_Vector4) const {
			Vector4 l_Result;
			l_Result.x = this->x - l_Vector4.x;
			l_Result.y = this->y - l_Vector4.y;
			l_Result.z = this->z - l_Vector4.z;
			l_Result.w = this->w - l_Vector4.w;
			return l_Result;
		}
		Vector4 operator*(const Vector4 & l_Vector4) const {
			Vector4 l_Result;
			l_Result.x = this->x * l_Vector4.x;
			l_Result.y = this->y * l_Vector4.y;
			l_Result.z = this->z * l_Vector4.z;
			l_Result.w = this->w * l_Vector4.w;
			return l_Result;
		}
		Vector4 operator/(const Vector4 & l_Vector4) const {
			Vector4 l_Result;
			l_Result.x = this->x / l_Vector4.x;
			l_Result.y = this->y / l_Vector4.y;
			l_Result.z = this->z / l_Vector4.z;
			l_Result.w = this->w / l_Vector4.w;
			return l_Result;
		}

		Vector4& operator+=(const Vector4 & l_Vector4) {
			this->x += l_Vector4.x;
			this->y += l_Vector4.y;
			this->z += l_Vector4.z;
			this->w += l_Vector4.w;
			return *this;
		}
		Vector4& operator-=(const Vector4 & l_Vector4) {
			this->x -= l_Vector4.x;
			this->y -= l_Vector4.y;
			this->z -= l_Vector4.z;
			this->w -= l_Vector4.w;
			return *this;
		}
		Vector4& operator*=(const Vector4 & l_Vector4) {
			this->x *= l_Vector4.x;
			this->y *= l_Vector4.y;
			this->z *= l_Vector4.z;
			this->w *= l_Vector4.w;
			return *this;
		}
		Vector4& operator/=(const Vector4 & l_Vector4) {
			this->x /= l_Vector4.x;
			this->y /= l_Vector4.y;
			this->z /= l_Vector4.z;
			this->w /= l_Vector4.w;
			return *this;
		}

		bool operator==(const Vector4 & l_Vector4) const {
			if (this->x == l_Vector4.x &&
				this->y == l_Vector4.y &&
				this->z == l_Vector4.z &&
				this->w == l_Vector4.w)
			{
				return true;
			}
			return false;
		}
		bool operator!=(const Vector4 & l_Vector4) const {
			if (this->x != l_Vector4.x &&
				this->y != l_Vector4.y &&
				this->z != l_Vector4.z &&
				this->w != l_Vector4.w)
			{
				return true;
			}
			return false;
		}
	};
	
	/*--------------------------------------------------------------------------------------------------------------------------------------*/
	float RandomRange(float l_fMin, float l_fMax); 
	
	int RandomRange(int l_nMin, int l_nMax); 
	/*--------------------------------------------------------------------------------------------------------------------------------------*/
	
	/*--------------------------------------------------------------------------------------------------------------------------------------*/
	double Noise(int x, int y);    // 根据(x,y)获取一个初步噪声值  
	double SmoothedNoise(int x, int y);   //光滑噪声  	
	double Cosine_Interpolate(double a, double b, double x);  // 余弦插值  
	double InterpolatedNoise(float x, float y);  // 获取插值噪声  
	double PerlinNoise(float x, float y, double persistence, int number_of_octaves);    // 最终调用：根据(x,y)获得其对应的PerlinNoise值  	
	/*--------------------------------------------------------------------------------------------------------------------------------------*/

	/*--------------------------------------------------------------------------------------------------------------------------------------*/
	float Vector2Dot(Vector2 * l_vec1, Vector2 * l_vec2);
	void Vector2Cross(float * l_output, Vector2 * l_vec1, Vector2 * l_vec2);
	float AngleBetween2Vector2(Vector2 & l_vec1, Vector2 & l_vec2);
	/*--------------------------------------------------------------------------------------------------------------------------------------*/

	/*--------------------------------------------------------------------------------------------------------------------------------------*/
	float Vector3Dot(const Vector3 & l_vec1,const Vector3 & l_vec2);
	void Vector3Cross(Vector3 * l_output, Vector3 * l_vec1, Vector3 * l_vec2);
	void Vector3Normalize(Vector3 * l_output, Vector3 * l_input);
	void Vector3RotationAxis(Vector3 * l_input, const Vector3 & l_axis, const float & l_length);
	/*--------------------------------------------------------------------------------------------------------------------------------------*/

	/*--------------------------------------------------------------------------------------------------------------------------------------*/
	void VectorQuaternionIdentity(Vector4 * l_pVector4);
	void VectorQuaterniontoEuler(const Vector4 & l_input, Vector3 * l_output);
	void btMatrix3x3toAngle(const btMatrix3x3 & Mat, Vector3 * l_output);
	/*--------------------------------------------------------------------------------------------------------------------------------------*/
	

}
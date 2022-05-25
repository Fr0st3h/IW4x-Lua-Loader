#pragma once
#include <vector>
#include <math.h>
//==========================================================================================
#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)
typedef float matrix3x4[3][4];
//==========================================================================================
#define M_PI		3.14159265358979323846	
#define M_PI_F		((float)(M_PI))	
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
//==========================================================================================
class Vector
{
public:
	float x, y, z;
	//==========================================================================================
	__forceinline float LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (this->x * this->x + this->y * this->y + this->z * this->z);
	}
	//==========================================================================================
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance&&
			y > -tolerance && y < tolerance&&
			z > -tolerance && z < tolerance);
	}
	//==========================================================================================
	inline float sqrt2(float sqr)
	{
		float root = 0;

		__asm
		{
			sqrtss xmm0, sqr
			movss root, xmm0
		}

		return root;
	}
	//==========================================================================================
	Vector VectorCrossProduct(const Vector& a, const Vector& b) const
	{
		return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}
	//==========================================================================================
	inline void Init(float ix, float iy, float iz)
	{
		x = ix; y = iy; z = iz;
		CHECK_VALID(*this);
	}
	//==========================================================================================
	inline void Init2(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
	{
		x = ix; y = iy; z = iz;
	}
	//==========================================================================================
	inline Vector(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
		CHECK_VALID(*this);
	}
	//==========================================================================================
	inline Vector(void) {}
	//==========================================================================================
	inline void Zero()
	{
		x = y = z = 0.0f;
	}
	//==========================================================================================
	inline void Rotate2D(const float& f)
	{
		float _x, _y;

		float s, c;

		float r = f * M_PI / 180.0;
		s = sin(r);
		c = cos(r);

		_x = x;
		_y = y;

		x = (_x * c) - (_y * s);
		y = (_x * s) + (_y * c);
	}
	//==========================================================================================
	inline void VectorClear(Vector& a)
	{
		a.x = a.y = a.z = 0.0f;
	}
	//==========================================================================================
	inline Vector& operator=(const Vector& vOther)
	{
		CHECK_VALID(vOther);
		x = vOther.x; y = vOther.y; z = vOther.z;
		return *this;
	}
	//==========================================================================================
	inline float& operator[](int i)
	{
		Assert((i >= 0) && (i < 3));
		return ((float*)this)[i];
	}
	//==========================================================================================
	inline float operator[](int i) const
	{
		Assert((i >= 0) && (i < 3));
		return ((float*)this)[i];
	}
	//==========================================================================================
	inline bool operator==(const Vector& src) const
	{
		CHECK_VALID(src);
		CHECK_VALID(*this);
		return (src.x == x) && (src.y == y) && (src.z == z);
	}
	//==========================================================================================
	inline bool operator!=(const Vector& src) const
	{
		CHECK_VALID(src);
		CHECK_VALID(*this);
		return (src.x != x) || (src.y != y) || (src.z != z);
	}
	//==========================================================================================
	__forceinline void VectorCopy(const Vector& src, Vector& dst)
	{
		CHECK_VALID(src);
		dst.x = src.x;
		dst.y = src.y;
		dst.z = src.z;
	}
	//==========================================================================================
	__forceinline  Vector& operator+=(const Vector& v)
	{
		CHECK_VALID(*this);
		CHECK_VALID(v);
		x += v.x; y += v.y; z += v.z;
		return *this;
	}
	//==========================================================================================
	__forceinline  Vector& operator-=(const Vector& v)
	{
		CHECK_VALID(*this);
		CHECK_VALID(v);
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}
	//==========================================================================================
	__forceinline  Vector& operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		z *= fl;
		CHECK_VALID(*this);
		return *this;
	}
	//==========================================================================================
	__forceinline  Vector& operator*=(const Vector& v)
	{
		CHECK_VALID(v);
		x *= v.x;
		y *= v.y;
		z *= v.z;
		CHECK_VALID(*this);
		return *this;
	}
	//==========================================================================================
	__forceinline Vector& operator+=(float fl)
	{
		x += fl;
		y += fl;
		z += fl;
		CHECK_VALID(*this);
		return *this;
	}
	//==========================================================================================
	__forceinline Vector& operator-=(float fl)
	{
		x -= fl;
		y -= fl;
		z -= fl;
		CHECK_VALID(*this);
		return *this;
	}
	//==========================================================================================
	__forceinline  Vector& operator/=(float fl)
	{
		Assert(fl != 0.0f);
		float oofl = 1.0f / fl;
		x *= oofl;
		y *= oofl;
		z *= oofl;
		CHECK_VALID(*this);
		return *this;
	}
	//==========================================================================================
	__forceinline  Vector& operator/=(const Vector& v)
	{
		CHECK_VALID(v);
		Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
		x /= v.x;
		y /= v.y;
		z /= v.z;
		CHECK_VALID(*this);
		return *this;
	}
	//==========================================================================================
	inline float Length(void) const
	{
		CHECK_VALID(*this);

		float root = 0.0f;

		float sqsr = x * x + y * y + z * z;

		__asm sqrtss xmm0, sqsr
		__asm movss root, xmm0

		return root;
	}
	//==========================================================================================
	inline float Length2D(void) const
	{
		CHECK_VALID(*this);

		float root = 0.0f;

		float sqst = x * x + y * y;

		__asm
		{
			sqrtss xmm0, sqst
			movss root, xmm0
		}

		return root;
	}
	//==========================================================================================
	inline float Length2DSqr(void) const
	{
		return (x * x + y * y);
	}
	//==========================================================================================
	inline Vector Angle(Vector* up)
	{
		if (!x && !y)
			return Vector(0, 0, 0);

		float roll = 0;

		if (up)
		{
			Vector left = (*up).Cross(*this);
			roll = atan2f(left.z, (left.y * x) - (left.x * y)) * 180.0f / M_PI;
		}

		return Vector(atan2f(-z, sqrt2(x * x + y * y)) * 180.0f / M_PI, atan2f(y, x) * 180.0f / M_PI, roll);
	}
	//==========================================================================================
	inline Vector CrossProduct(const Vector& a, const Vector& b)
	{
		return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}
	//==========================================================================================
	float DistToSqr(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}
	//==========================================================================================
	float DistTo(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.Length();
	}
	//==========================================================================================
	float Dist(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.Length();
	}
	//==========================================================================================
	inline Vector Cross(const Vector& vOther) const
	{
		Vector res;
		return VectorCrossProduct(*this, vOther);
	}
	//==========================================================================================
	inline Vector Normalize()
	{
		Vector vector;
		float length = this->Length();

		if (length != 0)
		{
			vector.x = x / length;
			vector.y = y / length;
			vector.z = z / length;
		}
		else
			vector.x = vector.y = 0.0f; vector.z = 1.0f;

		return vector;
	}
	//==========================================================================================
	inline float NormalizeInPlace()
	{
		Vector& v = *this;

		float iradius = 1.f / (this->Length() + 1.192092896e-07F);

		v.x *= iradius;
		v.y *= iradius;
		v.z *= iradius;

		return v.Length();
	}
	//==========================================================================================
	inline float VectorNormalize(Vector& v)
	{
		Assert(v.IsValid());
		float l = v.Length();
		if (l != 0.0f)
		{
			v /= l;
		}
		else
		{
			v.x = v.y = 0.0f; v.z = 1.0f;
		}
		return l;
	}
	//==========================================================================================
	inline float VectorNormalize(float* v)
	{
		return VectorNormalize(*(reinterpret_cast<Vector*>(v)));
	}
	//==========================================================================================
	Vector Normalized() const
	{
		Vector res = *this;
		float l = res.Length();
		if (l != 0.0f) {
			res /= l;
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}
	//==========================================================================================
	inline Vector operator+(const Vector& v) const
	{
		Vector res;
		res.x = x + v.x;
		res.y = y + v.y;
		res.z = z + v.z;
		return res;
	}
	//==========================================================================================
	inline Vector operator-(const Vector& v) const
	{
		Vector res;
		res.x = x - v.x;
		res.y = y - v.y;
		res.z = z - v.z;
		return res;
	}
	//==========================================================================================
	inline Vector operator*(float fl) const
	{
		Vector res;
		res.x = x * fl;
		res.y = y * fl;
		res.z = z * fl;
		return res;
	}
	//==========================================================================================
	inline Vector operator*(const Vector& v) const
	{
		Vector res;
		res.x = x * v.x;
		res.y = y * v.y;
		res.z = z * v.z;
		return res;
	}
	//==========================================================================================
	inline Vector operator/(float fl) const
	{
		Vector res;
		res.x = x / fl;
		res.y = y / fl;
		res.z = z / fl;
		return res;
	}
	//==========================================================================================
	inline Vector operator/(const Vector& v) const
	{
		Vector res;
		res.x = x / v.x;
		res.y = y / v.y;
		res.z = z / v.z;
		return res;
	}
	//==========================================================================================
	inline float Dot(const Vector& vOther) const
	{
		const Vector& a = *this;

		return(a.x * vOther.x + a.y * vOther.y + a.z * vOther.z);
	}
	//==========================================================================================
	inline float Dot(const float* fOther) const
	{
		const Vector& a = *this;

		return(a.x * fOther[0] + a.y * fOther[1] + a.z * fOther[2]);
	}
	//==========================================================================================
	inline float* Base()
	{
		return (float*)this;
	}
	//==========================================================================================
	inline float const* Base() const
	{
		return (float const*)this;
	}
	//==========================================================================================
};
//==========================================================================================
class Vector2D
{
public:
	float x, y;
	//==========================================================================================
	Vector2D() { x = 0; y = 0; };
	Vector2D(float X, float Y) { x = X; y = Y; };
	Vector2D(Vector vec) { x = vec.x; y = vec.y; }
	//==========================================================================================
	inline Vector2D operator*(const float n) const { return Vector2D(x * n, y * n); }
	inline Vector2D operator+(const Vector2D& v) const { return Vector2D(x + v.x, y + v.y); }
	inline Vector2D operator-(const Vector2D& v) const { return Vector2D(x - v.x, y - v.y); }
	//==========================================================================================
	inline void operator+=(const Vector2D& v)
	{
		x += v.x;
		y += v.y;
	}
	//==========================================================================================
	inline void operator-=(const Vector2D& v)
	{
		x -= v.x;
		y -= v.y;
	}
	//==========================================================================================
	bool operator==(const Vector2D& v) const { return (v.x == x && v.y == y); }
	bool operator!=(const Vector2D& v) const { return (v.x != x || v.y != y); }
	//==========================================================================================
	inline float length()
	{
		return sqrt((x * x) + (y * y));
	}
	//==========================================================================================
};
//==========================================================================================


class Vector
{
public:

	Vector(void) : x(0.0f), y(0.0f), z(0.0f)
	{

	}

	Vector(float X, float Y, float Z)
		: x(X), y(Y), z(Z)
	{

	}

	Vector(float* p)
	{
		*this = p;
	};

	Vector(const Vector& in)
	{
		x = in.x;
		y = in.y;
		z = in.z;
	};

	~Vector()
	{

	}


	/*inline Vector(float XYZ)
		: x(XYZ), y(XYZ), z(XYZ)
	{
	}*/

	inline Vector& operator= (const Vector& in);
	inline Vector& operator= (float* p);
	inline Vector& operator= (float f);

	inline float& operator[] (int i) const;

	inline bool operator! (void) const;

	inline bool operator== (const Vector& other) const;

	inline bool operator!= (const Vector& other) const;

	inline Vector& operator+= (const Vector& other);
	inline Vector& operator+= (float* p);
	inline Vector& operator+= (float f);

	inline Vector& operator-= (const Vector& other);
	inline Vector& operator-= (float* p);
	inline Vector& operator-= (float f);

	inline Vector& operator*= (const Vector& other);
	inline Vector& operator*= (float* p);
	inline Vector& operator*= (float f);

	inline Vector& operator/= (const Vector& other);
	inline Vector& operator/= (float* p);
	inline Vector& operator/= (float f);

	inline Vector operator+ (const Vector& other) const;
	inline Vector operator+ (float* p) const;
	inline Vector operator+ (float f) const;

	inline Vector operator- (const Vector& other) const;
	inline Vector operator- (float* p) const;
	inline Vector operator- (float f) const;
	inline Vector operator- (void) const;

	inline Vector operator* (const Vector& other) const;
	inline Vector operator* (float* p) const;
	inline Vector operator* (float f) const;

	inline Vector operator/ (const Vector& other) const;
	inline Vector operator/ (float* p) const;
	inline Vector operator/ (float f) const;

	operator float* () { return &x; }
	operator const float* () const { return &x; }

	inline bool IsZero(void) const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	inline bool IsZero2D(void)
	{
		return x == 0.0f && y == 0.0f;
	}

	inline Vector& Clear(void)
	{
		x = y = z = 0;

		return *this;
	}

	inline Vector& Init(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	inline Vector& Init(float* p)
	{
		*this = p;

		return *this;
	}

	inline Vector& Negate(void)
	{
		x = -x;
		y = -y;
		z = -z;

		return *this;
	}

	inline float Dot(const Vector& other)
	{
		return x * other.x + y * other.y + z * other.z;
	}
	inline float Dot2D(const Vector& other)
	{
		return x * other.x + y * other.y;
	}

	inline float Length(void)
	{
		float Length = 0;

		Length = sqrt(LengthSqr());

		return Length;
	}

	inline float Length2D(void)
	{
		float Length = 0;

		Length = sqrt(LengthSqr2D());

		return Length;
	}

	inline float LengthSqr(void)
	{
		return x * x + y * y + z * z;
	}

	inline float LengthSqr2D(void)
	{
		return x * x + y * y;
	}

	inline float Distance(Vector& ToVector)
	{
		return (ToVector - *this).Length();
	}

	inline float Distance2D(Vector& ToVector)
	{
		return (ToVector - *this).Length2D();
	}

	inline float Normalize(void)
	{
		float RecipLength, VectorLength;

		VectorLength = Length();

		if (VectorLength != 0)
		{
			RecipLength = 1 / VectorLength;

			x *= RecipLength;
			y *= RecipLength;
			z *= RecipLength;
		}

		return VectorLength;
	}

	inline Vector Normalized(void)
	{
		float flLen = Length();
		if (flLen == 0) return Vector(0, 0, 1);
		flLen = 1 / flLen;
		return Vector(x * flLen, y * flLen, z * flLen);
	}

	inline float Normalize2D(void)
	{
		float Length = LengthSqr2D();
		float RecipLength;

		if (Length != 0)
		{
			RecipLength = 1 / Length;

			x *= RecipLength;
			y *= RecipLength;
		}

		return Length;
	}

#define IM_PII           3.14159265358979323846f

	inline float AngleBetween(Vector& other)
	{
		other.Normalize();
		Normalize();

		return acos(Dot(other)) * static_cast<float>(180.0 / IM_PII);
	}

	Vector& CrossProduct(const Vector& a, const Vector& b)
	{
		x = (a.y * b.z) - (a.z * b.y);
		y = (a.z * b.x) - (a.x * b.z);
		z = (a.x * b.y) - (a.y * b.x);

		return *this;
	}
	

	void VectorVectors(Vector& Right, Vector& Up)
	{
		Vector tmp;

		if (x == 0 && y == 0)
		{
			Right[0] = 1;
			Right[1] = 0;
			Right[2] = 0;
			Up[0] = -z;
			Up[1] = 0;
			Up[2] = 0;
			return;
		}

		tmp[0] = 0; tmp[1] = 0; tmp[2] = 1.0;
		CrossProduct(tmp, Right);
		Right.Normalize();
		Right.CrossProduct(*this, Up);
		Up.Normalize();
	}

	inline bool IsValid()
	{
		return isfinite(x) && isfinite(y) && isfinite(z);
	}

public:

	float x, y, z;
};
class Vector3
{
public:
	double x, y, z;

	inline Vector3() {
		x = y = z = 0.0;
	}
	static Vector3 Zero() {
		return Vector3(0.0, 0.0, 0.0);
	}
	Vector3 midPoint(Vector3 v2) { return Vector3((x + v2.x) / 2, (y + v2.y) / 2, (z + v2.z) / 2); }
	inline Vector3(double X, double Y, double Z) {
		x = X; y = Y; z = Z;
	}

	inline double operator[](int i) const {
		return ((double*)this)[i];
	}

	inline Vector3& operator-=(double v) {
		x -= v; y -= v; z -= v; return *this;
	}

	inline Vector3 operator*(double v) const {
		return Vector3(x * v, y * v, z * v);
	}

	inline Vector3 operator/(double v) const
	{
		return Vector3(x / v, y / v, z / v);
	}

	inline Vector3& operator-=(const Vector3& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	inline Vector3& operator+=(const Vector3& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	inline bool operator!=(const Vector3& v) {
		return x != v.x && y != v.y && z != v.z;
	}
	inline bool operator==(const Vector3& v) {
		return x == v.x && y == v.y && z == v.z;
	}

	inline Vector3 operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	double dot(const Vector3& vector)
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}
	inline double Length() {
		return sqrt(x * x + y * y + z * z);
	}
	Vector3 normalize() {
		double len = Length();
		return Vector3(x / len, y / len, z / len);
	}
	bool empty() const {
		return x == 0.0 && y == 0.0 && z == 0.0;
	}
	double magnitude() {
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}
	double MagnitudeXZ(Vector3 v)
	{
		return sqrt(v.x * v.x + v.z * v.z);
	}
	double Magnitude2D(Vector3 v)
	{
		return v.MagnitudeXZ(v);
	}
	double distance(Vector3 input) const {

		auto real_dist = (*this - input).Length();
		return real_dist * 0.01;
	}
	static float DistSquared(const Vector3& V1, const Vector3& V2)
	{
		auto DistX = V2.x - V1.x;
		auto DistY = V2.y - V1.y;
		auto DistZ = V2.z - V1.z;

		return DistX * DistX + DistY * DistY + DistZ * DistZ;
	}
	double Magnitude() { return sqrt(this->x * this->x + this->y * this->y + this->z * this->z); }
	Vector3 Normalized() { double num = this->Magnitude(); if (num > 9.99999974737875E-06) { return { this->x / num, this->y / num, this->z / num }; } return Vector3(); }

	static Vector3 MoveTowards(Vector3 current, Vector3 target, double maxDistanceDelta)
	{
		double num = target.x - current.x;
		double num2 = target.y - current.y;
		double num3 = target.z - current.z;
		double num4 = num * num + num2 * num2 + num3 * num3;
		bool flag = num4 == 0.0 || (maxDistanceDelta >= 0.0 && num4 <= maxDistanceDelta * maxDistanceDelta);
		Vector3 result;
		if (flag)
		{
			result = target;
		}
		else
		{
			double num5 = sqrt((double)num4);
			maxDistanceDelta *= current.distance(target) / num5;
			result = Vector3(current.x + num / num5 * maxDistanceDelta, current.y + num2 / num5 * maxDistanceDelta, current.z + num3 / num5 * maxDistanceDelta);
		}
		return result;
	}



};

class Vector2 {
public:
	float x, y;

	inline Vector2() {
		x = y = 0.0f;
	}

	inline Vector2 operator/(float v) const {
		return Vector2(x / v, y / v);
	}
	inline Vector2(float X, float Y) {
		x = X; y = Y;
	}

	inline Vector2 operator-(const Vector2& v) const {
		return Vector2(x - v.x, y - v.y);
	}
	inline Vector2& operator-=(const Vector2& v) {
		x -= v.x; y -= v.y; return *this;
	}
	inline Vector2 operator+(const Vector2& v) const {
		return Vector2(x + v.x, y + v.y);
	}

	inline Vector2& operator+=(const Vector2& v) {
		x += v.x; y += v.y; return *this;
	}

	inline bool IsEmpty() {
		return this->x == 0 && this->y == 0;
	}

	inline bool Zero() const {
		return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f);
	}
};

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4()
	{}

	Vector4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{}

	Vector3 forward()
	{
		Vector3  point = { 0, 0, 1 };
		float num = x * 2;
		float num2 = y * 2;
		float num3 = z * 2;
		float num4 = x * num;
		float num5 = y * num2;
		float num6 = z * num3;
		float num7 = x * num2;
		float num8 = x * num3;
		float num9 = y * num3;
		float num10 = w * num;
		float num11 = w * num2;
		float num12 = w * num3;
		Vector3  result;
		result.x = (1 - (num5 + num6)) * point.x + (num7 - num12) * point.y +
			(num8 + num11) * point.z;
		result.y = (num7 + num12) * point.x + (1 - (num4 + num6)) * point.y +
			(num9 - num10) * point.z;
		result.z = (num8 - num11) * point.x + (num9 + num10) * point.y +
			(1 - (num4 + num5)) * point.z;
		return result;
	}


	inline float dot(const Vector4& vector)
	{
		return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
	}

	inline float distance(const Vector4& vector)
	{
		return sqrtf(
			(x - vector.x) * (x - vector.x) +
			(y - vector.y) * (y - vector.y) +
			(z - vector.z) * (z - vector.z) +
			(w - vector.w) * (w - vector.w));
	}

	bool operator==(const Vector4& vector) const
	{
		return x == vector.x && y == vector.y && z == vector.z && w == vector.w;
	}

	bool operator!=(const Vector4& vector) const
	{
		return x != vector.x || y != vector.y || z != vector.z || w != vector.w;
	}

	Vector4 operator+(const Vector4& vector) const
	{
		return Vector4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
	}

	Vector4 operator-(const Vector4& vector) const
	{
		return Vector4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
	}

	Vector4 operator-() const
	{
		return Vector4(-x, -y, -z, -w);
	}

	Vector4 operator*(float number) const
	{
		return Vector4(x * number, y * number, z * number, w * number);
	}

	Vector4 operator/(float number) const
	{
		return Vector4(x / number, y / number, z / number, w / number);
	}

	Vector4& operator+=(const Vector4& vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		w += vector.w;
		return *this;
	}

	Vector4& operator-=(const Vector4& vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		w -= vector.w;
		return *this;
	}

	Vector4& operator*=(float number)
	{
		x *= number;
		y *= number;
		z *= number;
		w *= number;
		return *this;
	}

	Vector4& operator/=(float number)
	{
		x /= number;
		y /= number;
		z /= number;
		w /= number;
		return *this;
	}
};

class Quaternion {
public:
	float x, y, z, w;

	Quaternion() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	}

	Quaternion(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion operator*(Quaternion rhs) {
		return Quaternion(
			this->w * rhs.x + this->x * rhs.w + this->y * rhs.z - this->z * rhs.y,
			this->w * rhs.y + this->y * rhs.w + this->z * rhs.x - this->x * rhs.z,
			this->w * rhs.z + this->z * rhs.w + this->x * rhs.y - this->y * rhs.x,
			this->w * rhs.w - this->x * rhs.x - this->y * rhs.y - this->z * rhs.z
		);
	}

	float Dot(Quaternion b) {
		return x * x + y * y + z * z + w * w;
	}

	Vector3 operator*(Vector3 point) {
		float num = this->x * 2.f;
		float num2 = this->y * 2.f;
		float num3 = this->z * 2.f;
		float num4 = this->x * num;
		float num5 = this->y * num2;
		float num6 = this->z * num3;
		float num7 = this->x * num2;
		float num8 = this->x * num3;
		float num9 = this->y * num3;
		float num10 = this->w * num;
		float num11 = this->w * num2;
		float num12 = this->w * num3;
		Vector3 result;
		result.x = (1.f - (num5 + num6)) * point.x + (num7 - num12) * point.y + (num8 + num11) * point.z;
		result.y = (num7 + num12) * point.x + (1.f - (num4 + num6)) * point.y + (num9 - num10) * point.z;
		result.z = (num8 - num11) * point.x + (num9 + num10) * point.y + (1.f - (num4 + num5)) * point.z;
		return result;
	}
};


class VMatrix
{
public:
	VMatrix()
		: m{ { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 } }
	{}

	VMatrix(const VMatrix&) = default;

	VMatrix transpose() {
		VMatrix m;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m.m[i][j] = this->m[j][i];

		return m;
	}

	bool is_empty() {
		if (!m[3][0] && !m[3][1] && !m[3][2] && !m[2][1] && !m[2][0] && !m[2][2])
			return true;

		return false;
	}

	Vector3 operator*(const Vector3& vec) {
		VMatrix m;

		m[3][0] = vec.x;
		m[3][1] = vec.y;
		m[3][2] = vec.z;

		m[0][0] = 1;
		m[1][1] = 1;
		m[2][2] = 1;


		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;

		auto result = m * (*this);

		return Vector3{ result[3][0], result[3][1], result[3][2] };
	}

	VMatrix operator*(const VMatrix& _m2) {
		auto _m = *this;

		VMatrix out;
		out[0][0] = _m[0][0] * _m2[0][0] + _m[0][1] * _m2[1][0] + _m[0][2] * _m2[2][0] + _m[0][3] * _m2[3][0];
		out[0][1] = _m[0][0] * _m2[0][1] + _m[0][1] * _m2[1][1] + _m[0][2] * _m2[2][1] + _m[0][3] * _m2[3][1];
		out[0][2] = _m[0][0] * _m2[0][2] + _m[0][1] * _m2[1][2] + _m[0][2] * _m2[2][2] + _m[0][3] * _m2[3][2];
		out[0][3] = _m[0][0] * _m2[0][3] + _m[0][1] * _m2[1][3] + _m[0][2] * _m2[2][3] + _m[0][3] * _m2[3][3];
		out[1][0] = _m[1][0] * _m2[0][0] + _m[1][1] * _m2[1][0] + _m[1][2] * _m2[2][0] + _m[1][3] * _m2[3][0];
		out[1][1] = _m[1][0] * _m2[0][1] + _m[1][1] * _m2[1][1] + _m[1][2] * _m2[2][1] + _m[1][3] * _m2[3][1];
		out[1][2] = _m[1][0] * _m2[0][2] + _m[1][1] * _m2[1][2] + _m[1][2] * _m2[2][2] + _m[1][3] * _m2[3][2];
		out[1][3] = _m[1][0] * _m2[0][3] + _m[1][1] * _m2[1][3] + _m[1][2] * _m2[2][3] + _m[1][3] * _m2[3][3];
		out[2][0] = _m[2][0] * _m2[0][0] + _m[2][1] * _m2[1][0] + _m[2][2] * _m2[2][0] + _m[2][3] * _m2[3][0];
		out[2][1] = _m[2][0] * _m2[0][1] + _m[2][1] * _m2[1][1] + _m[2][2] * _m2[2][1] + _m[2][3] * _m2[3][1];
		out[2][2] = _m[2][0] * _m2[0][2] + _m[2][1] * _m2[1][2] + _m[2][2] * _m2[2][2] + _m[2][3] * _m2[3][2];
		out[2][3] = _m[2][0] * _m2[0][3] + _m[2][1] * _m2[1][3] + _m[2][2] * _m2[2][3] + _m[2][3] * _m2[3][3];
		out[3][0] = _m[3][0] * _m2[0][0] + _m[3][1] * _m2[1][0] + _m[3][2] * _m2[2][0] + _m[3][3] * _m2[3][0];
		out[3][1] = _m[3][0] * _m2[0][1] + _m[3][1] * _m2[1][1] + _m[3][2] * _m2[2][1] + _m[3][3] * _m2[3][1];
		out[3][2] = _m[3][0] * _m2[0][2] + _m[3][1] * _m2[1][2] + _m[3][2] * _m2[2][2] + _m[3][3] * _m2[3][2];
		out[3][3] = _m[3][0] * _m2[0][3] + _m[3][1] * _m2[1][3] + _m[3][2] * _m2[2][3] + _m[3][3] * _m2[3][3];

		return out;
	}

	float* operator[](size_t i) { return m[i]; }
	const float* operator[](size_t i) const { return m[i]; }

	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

namespace Math
{
#define M_PI 3.14159265358979323846f
#define M_RADPI	57.295779513082f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
#define DEG2RAD(x) ((float)(x) * (float)(M_PI_F / 180.f))
#define atan2(a, b) ((float)atan2((double)(a), (double)(b)))
static volatile const double Tiny = 0x1p-1022;
static volatile const double Infinity = INFINITY;
typedef struct { double d0, d1; } double2;

static inline double2 Mul112(double a, double b)
{
	static const double c = 0x1p27 + 1;

	double
		ap = a * c, bp = b * c,
		a0 = (a - ap) + ap, b0 = (b - bp) + bp,
		a1 = a - a0, b1 = b - b0,
		d0 = a * b,
		d1 = a0 * b0 - d0 + a0 * b1 + a1 * b0 + a1 * b1;
	return double2{ d0, d1 };
}

static inline double2 Mul222(double2 a, double2 b)
{
	static const double c = 0x1p27 + 1;

	double
		ap = a.d0 * c, bp = b.d0 * c,
		a0 = (a.d0 - ap) + ap, b0 = (b.d0 - bp) + bp,
		a1 = a.d0 - a0, b1 = b.d0 - b0,
		m0 = a.d0 * b.d0,
		m1 = a0 * b0 - m0 + a0 * b1 + a1 * b0 + a1 * b1 + (a.d0 * b.d1 + a.d1 * b.d0),
		d0 = m0 + m1,
		d1 = m0 - d0 + m1;
	return double2{ d0, d1 };
}

static inline double Mul121Special(double a, double2 b)
{
	static const double c = 0x1p27 + 1;

	double
		ap = a * c, bp = b.d0 * c,
		a0 = (a - ap) + ap, b0 = (b.d0 - bp) + bp,
		a1 = a - a0, b1 = b.d0 - b0,
		m1 = a0 * b0 - 1 + a0 * b1 + a1 * b0 + a1 * b1 + a * b.d1;
	return m1;
}

static inline double2 Add212RightSmaller(double2 a, double b)
{
	double
		c0 = a.d0 + b,
		c1 = a.d0 - c0 + b + a.d1,
		d0 = c0 + c1,
		d1 = c0 - d0 + c1;
	return double2{ d0, d1 };
}

static inline double Add221RightSmaller(double2 a, double2 b)
{
	double
		c0 = a.d0 + b.d0,
		c1 = a.d0 - c0 + b.d0 + b.d1 + a.d1,
		d0 = c0 + c1;
	return d0;
}

static double Tail(double x)
	{
		if (1 <= x)
			return 1 == x
			// If x is 1, generate inexact and return Pi/2 rounded down.
			? 0x3.243f6a8885a308d313198a2e03707344ap-1 + Tiny
			// If x is outside the domain, generate invalid and return NaN.
			: Infinity - Infinity;

		static const double p01 = 0.2145993335526539017488949;
		static const double p02 = -0.0890259194305537131666744;
		static const double p03 = 0.0506659694457588602631748;
		static const double p04 = -0.0331919619444009606270380;
		static const double p05 = 0.0229883479552557203133368;
		static const double p06 = -0.0156746038587246716524035;
		static const double p07 = 0.0097868293573384001221447;
		static const double p08 = -0.0052049731575223952626203;
		static const double p09 = 0.0021912255981979442677477;
		static const double p10 = -0.0006702485124770180942917;
		static const double p11 = 0.0001307564187657962919394;
		static const double p12 = -0.0000121189820098929624806;

		double polynomial = ((((((((((((
			+p12) * x
			+ p11) * x
			+ p10) * x
			+ p09) * x
			+ p08) * x
			+ p07) * x
			+ p06) * x
			+ p05) * x
			+ p04) * x
			+ p03) * x
			+ p02) * x
			+ p01) * x;

#if UseLongDouble
		static const long double HalfPi = 0x3.243f6a8885a308d313198a2ep-1L;
		static const long double p00 = -1.5707961988153774692344105L;

		return HalfPi + sqrtl(1 - x) * (polynomial + p00);
#else	// #if UseLongDouble
		static const double2
			HalfPi = { 0x1.921fb54442d18p+0, 0x1.1a62633145c07p-54 },
			p00 = { -0x1.921fb31e97d96p0, +0x1.eab77149ad27cp-54 };

		// Estimate 1 / sqrt(1-x).
		double e = 1 / sqrt(1 - x);

		double2 ex = Mul112(e, 1 - x);		// e * x.
		double e2x = Mul121Special(e, ex);	// e**2 * x - 1.

		// Set t0 to an improved approximation of sqrt(1-x) with Newton-Raphson.
		double2 t0 = Add212RightSmaller(ex, ex.d0 * -.5 * e2x);

		// Calculate pi/2 + sqrt(1-x) * p(x).
		return Add221RightSmaller(HalfPi, Mul222(
			t0,
			Add212RightSmaller(p00, polynomial)));
#endif	// #if UseLongDouble
	}


float abs(float a) {
	if (a < 0.f) return -a;
	else return a;
}

float asin(float x) {
	float negate = float(x < 0);
	x = abs(x);
	float ret = -0.0187293;
	ret *= x;
	ret += 0.0742610;
	ret *= x;
	ret -= 0.2121144;
	ret *= x;
	ret += 1.5707288;
	ret = 3.14159265358979 * 0.5 - sqrt(1.0 - x) * ret;
	return ret - 2 * negate * ret;
}

	__forceinline float Dot(const Vector3 & Vec1, const Vector3 & Vec2) {
		return Vec1[0] * Vec2[0] + Vec1[1] * Vec2[1] + Vec1[2] * Vec2[2];
	}

	__forceinline float Calc3D_Dist(const Vector3& Src, const Vector3& Dst) {
		return sqrtf(pow((Src.x - Dst.x), 2) + pow((Src.y - Dst.y), 2) + pow((Src.z - Dst.z), 2));
	}

	__forceinline float Calc2D_Dist(const Vector2& Src, const Vector2& Dst) {
		return sqrt(powf(Src.x - Dst.x, 2) + powf(Src.y - Dst.y, 2));
	}
	__forceinline Vector2 CalcAngle(const Vector3& Src, const Vector3& Dst) {
		Vector3 dir = Src - Dst;
		return Vector2{ RAD2DEG(asin(dir.y / dir.Length())), RAD2DEG(-atan2(dir.x, -dir.z)) };
	}
	float Clamp01(float value)
	{
		float result;
		if (value < 0.f)
		{
			result = 0.f;
		}
		else if (value > 1.f)
		{
			result = 1.f;
		}
		else
		{
			result = value;
		}
		return result;
	}
	float Lerp(Vector3 in)
	{
		return in.x + (in.y - in.x) * Clamp01(in.z);
	}
	float normalize_angle(float angle) {
		while (angle > 360.0f) {
			angle -= 360.0f;
		}
		while (angle < 0.0f) {
			angle += 360.0f;
		}
		return angle;
	}
	Vector3 normalize_angles(Vector3 angles) {
		angles.x = normalize_angle(angles.x);
		angles.y = normalize_angle(angles.y);
		angles.z = normalize_angle(angles.z);
		return angles;
	}
	Vector3 euler_angles(Vector4 q1) {
		float num = q1.w * q1.w;
		float num2 = q1.x * q1.x;
		float num3 = q1.y * q1.y;
		float num4 = q1.z * q1.z;
		float num5 = num2 + num3 + num4 + num;
		float num6 = q1.x * q1.w - q1.y * q1.z;
		Vector3 vector;
		if (num6 > 0.4995f * num5) {
			vector.y = 2.0f * std::atan2f(q1.y, q1.x);
			vector.x = 1.57079637f;
			vector.z = 0.0f;
			return normalize_angles(vector * 57.2958f);
		}
		if (num6 < -0.4995f * num5) {
			vector.y = -2.0f * std::atan2f(q1.y, q1.x);
			vector.x = -1.57079637f;
			vector.z = 0.0f;
			return normalize_angles(vector * 57.2958f);
		}
		Vector4 quaternion = Vector4(q1.w, q1.z, q1.x, q1.y);
		vector.y = std::atan2f(2.0f * quaternion.x * quaternion.w + 2.0f * quaternion.y * quaternion.z, 1.0f - 2.0f * (quaternion.z * quaternion.z + quaternion.w * quaternion.w));
		vector.x = std::asin(2.0f * (quaternion.x * quaternion.z - quaternion.w * quaternion.y));
		vector.z = std::atan2f(2.0f * quaternion.x * quaternion.y + 2.0f * quaternion.z * quaternion.w, 1.0f - 2.0f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z));
		return normalize_angles(vector * 57.2958f);
	}
	Vector3 rotate_point(Vector3 center, Vector3 origin, float angle) {
		float num = angle * 0.0174532924f;
		float num2 = -std::sin(num);
		float num3 = std::cos(num);
		origin.x -= center.x;
		origin.z -= center.z;
		float num4 = origin.x * num3 - origin.z * num2;
		float num5 = origin.x * num2 + origin.z * num3;
		float num6 = num4 + center.x;
		num5 += center.z;
		return Vector3(num6, origin.y, num5);
	}

	Vector3 monkey_normalize(Vector3 value)
	{
		float mag = value.Magnitude();
		if (mag > 0.00001F)
		{
			return Vector3(value.x / mag, value.y / mag, value.z / mag);
		}
		else
		{
			return Vector3(0, 0, 0);
		}
	}

	Vector3 Cross(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
	}

	Vector4 QuaternionLookRotation(Vector3 forward, Vector3 up)
	{
		monkey_normalize(forward);

		Vector3 vector = monkey_normalize(forward);
		Vector3 vector2 = monkey_normalize(Cross(up, vector));
		Vector3 vector3 = Cross(vector, vector2);
		auto m00 = vector2.x;
		auto m01 = vector2.y;
		auto m02 = vector2.z;
		auto m10 = vector3.x;
		auto m11 = vector3.y;
		auto m12 = vector3.z;
		auto m20 = vector.x;
		auto m21 = vector.y;
		auto m22 = vector.z;


		float num8 = (m00 + m11) + m22;
		auto quaternion = Vector4();
		if (num8 > 0.0f)
		{
			auto num = static_cast<float>(std::sqrt(num8 + 1.0f));
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = (m12 - m21) * num;
			quaternion.y = (m20 - m02) * num;
			quaternion.z = (m01 - m10) * num;

			return quaternion;
		}
		if ((m00 >= m11) && (m00 >= m22))
		{
			auto num7 = static_cast<float>(std::sqrt(((1.0f + m00) - m11) - m22));
			auto num4 = 0.5f / num7;
			quaternion.w = 0.5f * num7;
			quaternion.y = (m01 + m10) * num4;
			quaternion.z = (m02 + m20) * num4;
			quaternion.w = (m12 - m21) * num4;

			return quaternion;
		}
		if (m11 > m22)
		{
			auto num6 = static_cast<float>(std::sqrt(((1.0f + m11) - m00) - m22));
			auto num3 = 0.5f / num6;
			quaternion.x = (m10 + m01) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = (m21 + m12) * num3;
			quaternion.w = (m20 - m02) * num3;

			return quaternion;
		}
		auto num5 = static_cast<float>(std::sqrt(((1.0f + m22) - m00) - m11));
		auto num2 = 0.5f / num5;
		quaternion.x = (m20 + m02) * num2;
		quaternion.y = (m21 + m12) * num2;
		quaternion.z = 0.5f * num5;
		quaternion.w = (m01 - m10) * num2;

		return quaternion;
	}

	float Clamp(float value, float min, float max)
	{
		bool flag = value < min;
		if (flag)
		{
			value = min;
		}
		else
		{
			bool flag2 = value > max;
			if (flag2)
			{
				value = max;
			}
		}
		return value;
	}

}


struct Ammo {
	int id[2];
	float speed;
};
struct Weapon {
	int id;
	const char* name;
	Ammo ammo[4];
	int category; //-3 - hammer, -2 - bows, -1 - eoka, 0-nopatch, 1 - meele, 2 - semiautomatic, 3 - automatic
};
Weapon info228[]{
Weapon{1588298435, xorstr("Bolt Action Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 656}, Ammo{{1712070256} /*HV 5.56*/, 788 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 394}}, 2 },
Weapon{-778367295, xorstr("L96 Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 1125}, Ammo{{1712070256} /*HV 5.56*/, 1350 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 675}}, 2 },
Weapon{-2069578888, xorstr("M249"), { Ammo{{-1211166256}/*normal 5.56*/, 488}, Ammo{{1712070256} /*HV 5.56*/, 585 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 293}}, 3 },

Weapon{1318558775, xorstr("MP5A4"), { Ammo{{785728077}/*normal pistol*/, 240}, Ammo{{-1691396643} /*HV pistol*/, 320}, Ammo{{51984655} /*inc pistol*/, 180}}, 3 },
Weapon{1796682209, xorstr("Custom SMG"), { Ammo{{785728077}/*normal pistol*/, 240}, Ammo{{-1691396643} /*HV pistol*/, 320}, Ammo{{51984655} /*inc pistol*/, 180}}, 3 },

Weapon{-1367281941, xorstr("Waterpipe Shotgun"), { Ammo{{-727717969, -1685290200}/*green, red*/, 225}, Ammo{{588596902, -1036635990}/*gray, blue*/, 100}}, 2 },
Weapon{-765183617, xorstr("Double Barrel Shotgun"), { Ammo{{-727717969, -1685290200}/*green, red*/, 225}, Ammo{{588596902, -1036635990}/*gray, blue*/, 100}}, 2 },
Weapon{-41440462, xorstr("Spas-12 Shotgun"), { Ammo{{-727717969, -1685290200}/*green, red*/, 225}, Ammo{{588596902, -1036635990}/*gray, blue*/, 100}}, 2 },
Weapon{795371088, xorstr("Pump Shotgun"), { Ammo{{-727717969, -1685290200}/*green, red*/, 225}, Ammo{{588596902, -1036635990}/*gray, blue*/, 100}}, 2 },
Weapon{-75944661, xorstr("Eoka Pistol"), { Ammo{{-727717969, -1685290200}/*green, red*/, 225}, Ammo{{588596902, -1036635990}/*gray, blue*/, 100}}, -1 },


Weapon{28201841, xorstr("M39 Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 469}, Ammo{{1712070256} /*HV 5.56*/, 563 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 281}}, 2 },

Weapon{1965232394, xorstr("Crossbow"), { Ammo{{-1234735557}/*normal arrow*/, 75.f}, Ammo{{14241751} /*fire arrow*/, 60}, Ammo{{215754713} /*bone arrow*/, 68}, Ammo{{-1023065463} /*HV arrow*/, 120}}, 2 },
Weapon{884424049, xorstr("Compound Bow"), { Ammo{{-1234735557}/*normal arrow*/, 50}, Ammo{{14241751} /*fire arrow*/, 40}, Ammo{{215754713} /*bone arrow*/, 45}, Ammo{{-1023065463} /*HV arrow*/, 80}}, 2 }, //TODO on zoom velocity x2
Weapon{1443579727, xorstr("Hunting Bow"), { Ammo{{-1234735557}/*normal arrow*/, 50.f}, Ammo{{14241751} /*fire arrow*/, 40}, Ammo{{215754713} /*bone arrow*/, 45}, Ammo{{-1023065463} /*HV arrow*/, 80} }, -2 },


Weapon{649912614, xorstr("Revolver"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol*/, 225}}, 2 },
Weapon{818877484, xorstr("Semi-Automatic Pistol"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol*/, 225}}, 2 },
Weapon{-852563019, xorstr("M92 Pistol"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol*/, 225}}, 2 },
Weapon{1373971859, xorstr("Python Revolver"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol 225*/, 210}}, 2 },
Weapon{-1758372725, xorstr("Thompson"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol*/, 225}}, 3 },

Weapon{-1812555177, xorstr("LR-300 Assault Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 375}, Ammo{{1712070256} /*HV 5.56*/, 450 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 225}}, 3 },
Weapon{-904863145, xorstr("Semi-Automatic Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 375}, Ammo{{1712070256} /*HV 5.56*/, 450 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 225}}, 2 },
Weapon{1545779598, xorstr("Assault Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 375}, Ammo{{1712070256} /*HV 5.56*/, 450 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 225}}, 3 },


Weapon{1090916276, xorstr("Pitchfork"), {Ammo{{0}, 25}}, 1 },
Weapon{1540934679, xorstr("Wooden Spear"), {Ammo{{0}, 20}}, 1 },
Weapon{1814288539, xorstr("Bone Knife"), {Ammo{{0}, 20}}, 1 },
Weapon{-363689972, xorstr("Snowball"), {Ammo{{0}, 20}}, 1 },
Weapon{1789825282, xorstr("Candy Cane Club"), {Ammo{{0}, 20}}, 1 },
Weapon{-1137865085, xorstr("Machete"), {Ammo{{0}, 20}}, 1 },
Weapon{1711033574, xorstr("Bone Club"), {Ammo{{0}, 20}}, 1 },
Weapon{-1966748496, xorstr("Mace"), {Ammo{{0}, 18}}, 1 },
Weapon{-194509282, xorstr("Butcher Knife"), {Ammo{{0}, 20}}, 1 },
Weapon{1326180354, xorstr("Salvaged Sword"), {Ammo{{0}, 20}}, 1 },
Weapon{-1469578201, xorstr("Longsword"), {Ammo{{0}, 18}}, 1 },
Weapon{-1978999529, xorstr("Salvaged Cleaver"), {Ammo{{0}, 18}}, 1 },
Weapon{1602646136, xorstr("Stone Spear"), {Ammo{{0}, 25}}, 1 },
Weapon{2040726127, xorstr("Combat Knife"), {Ammo{{0}, 30}}, 1 },
Weapon{963906841, xorstr("Rock"), {Ammo{{0}, 18}}, 1 },

Weapon{1953903201, xorstr("Nailgun"), { Ammo{{-2097376851}/*nails*/, 50}}, 2 },
Weapon{-1123473824, xorstr("Multiple Grenade Launcher"), { Ammo{{915408809, 349762871}/*smoke, exp*/, 100}, Ammo{{1055319033}, 225}/*shotgun*/}, 2 },
Weapon{442886268, xorstr("Rocket Launcher"), 0, 0 },
Weapon{-1215753368, xorstr("Flame Thrower"), 0, 0 },
Weapon{200773292, xorstr("Hammer"), {0}, -3 }
};

union FloatIntUnion {
	int in;
	float f;
	double d;
	uint32_t i;
	unsigned __int64 e;
};

inline int COERCE_INT(float value) {
	return static_cast<int>(std::round(value));
}

inline float COERCE_FLOAT(uint32_t int_value) {
	FloatIntUnion converter;
	converter.i = int_value;
	return converter.f;
}

inline double COERCE_DOUBLE(unsigned __int64 int64_value) {
	FloatIntUnion converter;
	converter.e = int64_value;
	return converter.d;
}

inline uint32_t ConvertFloat(float value) {
	FloatIntUnion converter;
	converter.f = value;
	return converter.i;
}

unsigned __int8 BITTEST(const uint32_t base, unsigned int bit)
{
	// Get the byte and bit position
	unsigned int index = bit / 32;
	unsigned int bit_pos = bit % 32;

	// Check if the bit is set
	return ((base >> bit_pos) & 1) != 0;
}

unsigned __int8 TEST_BITD(const long long* base, unsigned int bit)
{
	// Get the byte and bit position
	unsigned int index = bit / 64;
	unsigned int bit_pos = bit % 64;

	// Check if the bit is set
	return ((*base >> bit_pos) & 1) != 0;
}

struct box_bounds {
	float left, right, top, bottom;

	bool empty() {
		if (this->left == 0 && this->right == 0 && this->top == 0 && this->bottom == 0)
			return true;

		if (this->left == FLT_MAX || this->right == FLT_MIN || this->top == FLT_MAX || this->bottom == FLT_MIN)
			return true;

		return false;
	}
	static box_bounds null() {
		return { 0, 0, 0, 0 };
	}
};


struct Matrix
{
	float m[4][4];

	Matrix() { ZeroMemory(this, sizeof(Matrix)); }
	Matrix(const Vector3& rotation, const Vector3& origin = { 0.0, 0.0, 0.0 })
	{
		float radPitch = rotation.x * IM_PII / 180.f;
		float radYaw = rotation.y * IM_PII / 180.f;
		float radRoll = rotation.z * IM_PII / 180.f;

		float SP = std::sinf(radPitch);
		float CP = std::cosf(radPitch);
		float SY = std::sinf(radYaw);
		float CY = std::cosf(radYaw);
		float SR = std::sinf(radRoll);
		float CR = std::cosf(radRoll);

		m[0][0] = CP * CY;
		m[0][1] = CP * SY;
		m[0][2] = SP;
		m[0][3] = 0.f;
		m[1][0] = SR * SP * CY - CR * SY;
		m[1][1] = SR * SP * SY + CR * CY;
		m[1][2] = -SR * CP;
		m[1][3] = 0.f;
		m[2][0] = -(CR * SP * CY + SR * SY);
		m[2][1] = CY * SR - CR * SP * SY;
		m[2][2] = CR * CP;
		m[2][3] = 0.f;
		m[3][0] = origin.x;
		m[3][1] = origin.y;
		m[3][2] = origin.z;
		m[3][3] = 1.f;
	}

	Matrix operator*(const Matrix& m2) const
	{
		Matrix out;
		for (byte r = 0; r < 4; r++)
		{
			for (byte c = 0; c < 4; c++)
			{
				float sum = 0.f;

				for (byte i = 0; i < 4; i++)
					sum += m[r][i] * m2.m[i][c];

				out.m[r][c] = sum;
			}
		}

		return out;
	}
	__forceinline void operator*=(const Matrix& m2) { *this = this->operator*(m2); }
};


namespace EngineUtils {
	

	template<typename T>
	struct TArray
	{
		friend struct FString;

		TArray(std::uint64_t addr = 0)
		{
			if (addr)
			{
				Data = mem_read(addr, uint64_t);
				Count = mem_read(addr + 0x8, uint32_t);
				Max = mem_read(addr + 0xC, uint32_t);
			}
		}

		[[nodiscard]] constexpr auto Num() const noexcept
		{
			return Count;
		};

		[[nodiscard]] constexpr T operator[](std::int32_t i) noexcept
		{
			return mem_read(Data + (i * 0x8), T);
		};

		[[nodiscard]] constexpr const T operator[](std::int32_t i) const noexcept
		{
			mem_read(Data + (i * 0x8), T);
		};

		[[nodiscard]] constexpr auto IsValidIndex(std::int32_t i) const noexcept
		{
			return i < Num();
		}

		T Cast(int index)
		{
			if (Count < index)
				return T();
			return mem_read(Data + (index * 0x8), T);
		}

		std::uint64_t Data;
		std::int32_t Count;
		std::int32_t Max;
	};

	struct FString
	{
		TArray<wchar_t> data;

		FString() {};

		FString(uint64_t offset)
		{
			data = offset;
		}

		std::string ToString() const
		{
			wchar_t* tempStr = new wchar_t[data.Count * 2];
			drv::read_memory(drv::sock, oPID, data.Data, uint64_t(&tempStr), data.Count * 2);
			std::string str(data.Count * 2, '\0');
			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(tempStr, tempStr + (data.Count * 2), '?', &str[0]);

			return str;
		}

		std::wstring ToWString()
		{
			wchar_t* tempStr = new wchar_t[data.Count * 2];
			drv::read_memory(drv::sock, oPID, data.Data, uint64_t(&tempStr), data.Count * 2);
			return tempStr;
		}
	};


	class FName
	{
	public:
		// GNames - either of type TNameEntryArray [<4.23] or FNamePool [>=4.23]
		static inline void* GNames = nullptr;

		// Members of FName - depending on configuration [WITH_CASE_PRESERVING_NAME | FNAME_OUTLINE_NUMBER]
		uint32_t ComparisonIndex;
		uint32_t Number;


		// GetDisplayIndex - returns the Id of the string depending on the configuration [default: ComparisonIndex, WITH_CASE_PRESERVING_NAME: DisplayIndex]
		inline uint32_t GetDisplayIndex() const
		{
			return ComparisonIndex;
		}

		inline bool operator==(const FName& Other) const
		{
			return ComparisonIndex == Other.ComparisonIndex && Number == Other.Number;
		}

		inline bool operator!=(const FName& Other) const
		{
			return ComparisonIndex != Other.ComparisonIndex || Number != Other.Number;
		}
	};

}
 

namespace zalupMatrix {
	typedef struct _D3DMATRIX {
		union {
			struct {
				float        _11, _12, _13, _14;
				float        _21, _22, _23, _24;
				float        _31, _32, _33, _34;
				float        _41, _42, _43, _44;

			};
			float m[4][4];
		};
	} D3DMATRIX;
}

struct FQuat { double x, y, z, w; };
struct FTransform
{
	FQuat rot;
	Vector3 translation;
	//char pad[4];
	Vector3 scale;
	//char pad1[4];
	zalupMatrix::D3DMATRIX to_matrix_with_scale()
	{
		zalupMatrix::D3DMATRIX m{};
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;
		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;
		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;
		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;
		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;
		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;
		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;
		return m;
	}
};
 

zalupMatrix::D3DMATRIX matrix_multiplication(zalupMatrix::D3DMATRIX pm1, zalupMatrix::D3DMATRIX pm2)
{
	zalupMatrix::D3DMATRIX pout{};
	pout._11 = pm1._11 * pm2._11 + pm1._12 * pm2._21 + pm1._13 * pm2._31 + pm1._14 * pm2._41;
	pout._12 = pm1._11 * pm2._12 + pm1._12 * pm2._22 + pm1._13 * pm2._32 + pm1._14 * pm2._42;
	pout._13 = pm1._11 * pm2._13 + pm1._12 * pm2._23 + pm1._13 * pm2._33 + pm1._14 * pm2._43;
	pout._14 = pm1._11 * pm2._14 + pm1._12 * pm2._24 + pm1._13 * pm2._34 + pm1._14 * pm2._44;
	pout._21 = pm1._21 * pm2._11 + pm1._22 * pm2._21 + pm1._23 * pm2._31 + pm1._24 * pm2._41;
	pout._22 = pm1._21 * pm2._12 + pm1._22 * pm2._22 + pm1._23 * pm2._32 + pm1._24 * pm2._42;
	pout._23 = pm1._21 * pm2._13 + pm1._22 * pm2._23 + pm1._23 * pm2._33 + pm1._24 * pm2._43;
	pout._24 = pm1._21 * pm2._14 + pm1._22 * pm2._24 + pm1._23 * pm2._34 + pm1._24 * pm2._44;
	pout._31 = pm1._31 * pm2._11 + pm1._32 * pm2._21 + pm1._33 * pm2._31 + pm1._34 * pm2._41;
	pout._32 = pm1._31 * pm2._12 + pm1._32 * pm2._22 + pm1._33 * pm2._32 + pm1._34 * pm2._42;
	pout._33 = pm1._31 * pm2._13 + pm1._32 * pm2._23 + pm1._33 * pm2._33 + pm1._34 * pm2._43;
	pout._34 = pm1._31 * pm2._14 + pm1._32 * pm2._24 + pm1._33 * pm2._34 + pm1._34 * pm2._44;
	pout._41 = pm1._41 * pm2._11 + pm1._42 * pm2._21 + pm1._43 * pm2._31 + pm1._44 * pm2._41;
	pout._42 = pm1._41 * pm2._12 + pm1._42 * pm2._22 + pm1._43 * pm2._32 + pm1._44 * pm2._42;
	pout._43 = pm1._41 * pm2._13 + pm1._42 * pm2._23 + pm1._43 * pm2._33 + pm1._44 * pm2._43;
	pout._44 = pm1._41 * pm2._14 + pm1._42 * pm2._24 + pm1._43 * pm2._34 + pm1._44 * pm2._44;
	return pout;
}
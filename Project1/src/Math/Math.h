#pragma once
#include <cmath>

constexpr float Epsilon = 0.0001f;
constexpr float Pi = 3.1415926f;

//Floats:
bool FloatEqual(float a, float b);
inline float FloatSquare(float n);

//Vectors:
struct Vector {

	float x;
	float y;
	float z;
	float w;

	Vector();
	Vector(float x, float y, float z, float w);
	Vector(const Vector& v);
	~Vector();

	Vector& operator = (const Vector& v);
	Vector& operator += (const Vector& v);
	Vector& operator -= (const Vector& v);
	Vector& operator *= (float f);
	Vector& operator /= (float f);
	Vector operator - () const;
};

Vector operator +(const Vector& v1, const Vector& v2);
Vector operator -(const Vector& v1, const Vector& v2);
Vector operator *(const Vector& v, float f);
Vector operator *(float f, const Vector& v);
Vector operator /(const Vector& v, float f);
bool operator ==(const Vector& v1, const Vector& v2);

float VectorLengthSquared(const Vector& v);
float VectorLength(const Vector& v);
Vector VectorNormalize(const Vector& v);

float VectorDot(const Vector& v1, const Vector& v2);
Vector VectorCross(const Vector& v1, const Vector& v2);
Vector VectorHadamard(const Vector& v1, const Vector& v2);

Vector VectorPoint(float x, float y, float z);
Vector VectorDirection(float x, float y, float z);

//Quaternions:
struct Quaternion {
	float w;
	float x;
	float y;
	float z;

	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(const Quaternion& q);
	~Quaternion();

	Quaternion& operator = (const Quaternion& q);
	Quaternion& operator *= (const Quaternion& q);
	Quaternion& operator *= (const Vector& v);
	Quaternion operator - ();
};

Quaternion operator * (const Quaternion& q1, const Quaternion q2);
Quaternion operator * (const Quaternion& q, const Vector& v);
Quaternion operator * (const Vector& v, const Quaternion& q);
bool operator == (const Quaternion& q1, const Quaternion& q2);

float QuaternionLengthSquared(const Quaternion& q);
float QuaternionLength(const Quaternion& q);
Quaternion QuaternionNormalize(const Quaternion& q);

//Matricies (Column Major):
struct Matrix4x4 {
	float r1c1; float r1c2; float r1c3; float r1c4;
	float r2c1; float r2c2; float r2c3; float r2c4;
	float r3c1; float r3c2; float r3c3; float r3c4;
	float r4c1; float r4c2; float r4c3; float r4c4;

	Matrix4x4();
	Matrix4x4(float a11, float a12, float a13, float a14, float a21, float a22, float a23, float a24, float a31, float a32, float a33, float a34, float a41, float a42, float a43, float a44);
	Matrix4x4(const Vector& v1, const Vector& v2, const Vector& v3, const Vector& v4);
	Matrix4x4(const Matrix4x4& m);
	~Matrix4x4();

	Matrix4x4& operator = (const Matrix4x4& m);
	Matrix4x4& operator += (const Matrix4x4 m);
	Matrix4x4& operator -= (const Matrix4x4 m);
	Matrix4x4& operator *= (float f);
	Matrix4x4& operator /= (float f);
	Matrix4x4 operator - ();
};

Matrix4x4 operator + (const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator - (const Matrix4x4& m1, const Matrix4x4& m2);
Vector operator * (const Matrix4x4& m, const Vector& v);
Matrix4x4 operator * (const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator * (const Matrix4x4 m, float f);
Matrix4x4 operator * (float f, const Matrix4x4 m);
Matrix4x4 operator / (const Matrix4x4 m, float f);
bool operator == (const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 MatrixTranspose(const Matrix4x4& m);
Matrix4x4 MatrixInverse(const Matrix4x4& m);

Matrix4x4 IdentityMatrix();
Matrix4x4 TranslationMatrix(const Vector& v);
Matrix4x4 ScalingMatrix(const Vector& v);
Matrix4x4 RotationMatrix(const Quaternion& q);
Matrix4x4 PerspectiveProjectionMatrix(float fovDegree, float aspectRatio, float zFar, float zNear);

//Colours:
struct Colour {
	float r;
	float g;
	float b;
	float a;

	Colour();
	Colour(float r, float g, float b, float a);
	Colour(const Colour& c);
	~Colour();

	Colour& operator = (const Colour& c);
	Colour& operator += (const Colour& c);
	Colour& operator -= (const Colour& c);
	Colour& operator *= (float f);
	Colour& operator /= (float f);
	Colour operator - () const;
};

Colour operator + (const Colour& c1, const Colour& c2);
Colour operator - (const Colour& c1, const Colour& c2);
Colour operator * (const Colour& c1, const Colour& c2);
Colour operator * (const Colour& c, float f);
Colour operator * (float f, const Colour& c);
Colour operator / (const Colour& c, float f);
bool operator == (const Colour& c1, const Colour c2);

int ColourToInt(const Colour& c);

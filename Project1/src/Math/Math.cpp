#include "Math.h"

bool FloatEqual(float a, float b) { return abs(a - b) < Epsilon; }

inline float FloatSquare(float n) { return n * n; }

Vector operator+(const Vector& v1, const Vector& v2) {
	return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

Vector operator-(const Vector& v1, const Vector& v2) {
	return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

Vector operator*(const Vector& v, float f) {
	return Vector(v.x * f, v.y * f, v.z * f, v.w);
}

Vector operator*(float f, const Vector& v) {
	return Vector(f * v.x, f * v.y, f * v.z, v.w);
}

Vector operator/(const Vector& v, float f) {
	return Vector(v.x / f, v.y / f, v.z / f, v.w);
}

bool operator==(const Vector& v1, const Vector& v2) {
	return (FloatEqual(v1.x, v2.z) && FloatEqual(v1.y, v2.y) && FloatEqual(v1.z, v2.z) && FloatEqual(v1.w, v2.w));
}

float VectorLengthSquared(const Vector& v) { return FloatSquare(v.x) + FloatSquare(v.y) + FloatSquare(v.z); }

float VectorLength(const Vector& v) { return sqrt(VectorLengthSquared(v)); }

Vector VectorNormalize(const Vector& v) { return Vector(v) / VectorLength(v); }

float VectorDot(const Vector& v1, const Vector& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

Vector VectorCross(const Vector& v1, const Vector& v2) {
	return Vector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x, 0.0f);
}

Vector VectorHadamard(const Vector& v1, const Vector& v2) {
	return Vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

Vector VectorPoint(float x, float y, float z) { return Vector(x, y, z, 1.0f); }

Vector VectorDirection(float x, float y, float z) { return Vector(x, y, z, 0.0f); }

Quaternion operator*(const Quaternion& q1, const Quaternion q2) {
	float _w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	float _x = q1.x * q2.w + q1.w * q2.x + q1.y * q2.z - q1.z * q2.y;
	float _y = q1.y * q2.w + q1.w * q2.y + q1.z * q2.x - q1.x * q2.z;
	float _z = q1.z * q2.w + q1.w * q2.z + q1.x * q2.y - q1.y * q2.x;

	return Quaternion(_w, _x, _y, _z);
}

Quaternion operator*(const Quaternion& q, const Vector& v) {
	float _w = -q.x * v.x - q.y * v.y - q.z * v.z;
	float _x = q.w * v.x + q.y * v.z - q.z * v.y;
	float _y = q.w * v.y + q.z * v.x - q.x * v.z;
	float _z = q.w * v.z + q.x * v.y - q.y * v.x;

	return Quaternion(_w, _x, _y, _z);
}

Quaternion operator*(const Vector& v, const Quaternion& q) {
	float _w = -q.x * v.x - q.y * v.y - q.z * v.z;
	float _x = q.w * v.x + q.y * v.z - q.z * v.y;
	float _y = q.w * v.y + q.z * v.x - q.x * v.z;
	float _z = q.w * v.z + q.x * v.y - q.y * v.x;

	return Quaternion(_w, _x, _y, _z);
}

bool operator==(const Quaternion& q1, const Quaternion& q2) {
	return (FloatEqual(q1.w, q2.w) && FloatEqual(q1.x, q2.x) && FloatEqual(q1.y, q2.y) && FloatEqual(q1.z, q2.z));
}

float QuaternionLengthSquared(const Quaternion& q) { return FloatSquare(q.x) + FloatSquare(q.y) + FloatSquare(q.z) + FloatSquare(q.w); }

float QuaternionLength(const Quaternion& q) { return sqrt(QuaternionLengthSquared(q)); }

Quaternion QuaternionNormalize(const Quaternion& q) {
	float length = QuaternionLength(q);
	return Quaternion(q.w / length, q.x / length, q.y / length, q.z / length);
}

Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) {
	return Matrix4x4(
		m1.r1c1 + m2.r1c1, m1.r1c2 + m2.r1c2, m1.r1c3 + m2.r1c3, m1.r1c4 + m2.r1c4,
		m1.r2c1 + m2.r2c1, m1.r2c2 + m2.r2c2, m1.r2c3 + m2.r2c3, m1.r2c4 + m2.r2c4,
		m1.r3c1 + m2.r3c1, m1.r3c2 + m2.r3c2, m1.r3c3 + m2.r3c3, m1.r3c4 + m2.r3c4,
		m1.r4c1 + m2.r4c1, m1.r4c2 + m2.r4c2, m1.r4c3 + m2.r4c3, m1.r4c4 + m2.r4c4
	);
}

Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) {
	return Matrix4x4(
		m1.r1c1 - m2.r1c1, m1.r1c2 - m2.r1c2, m1.r1c3 - m2.r1c3, m1.r1c4 - m2.r1c4,
		m1.r2c1 - m2.r2c1, m1.r2c2 - m2.r2c2, m1.r2c3 - m2.r2c3, m1.r2c4 - m2.r2c4,
		m1.r3c1 - m2.r3c1, m1.r3c2 - m2.r3c2, m1.r3c3 - m2.r3c3, m1.r3c4 - m2.r3c4,
		m1.r4c1 - m2.r4c1, m1.r4c2 - m2.r4c2, m1.r4c3 - m2.r4c3, m1.r4c4 - m2.r4c4
	);
}

Vector operator*(const Matrix4x4& m, const Vector& v) {

	return Vector(
		m.r1c1 * v.x + m.r1c2 * v.y + m.r1c3 * v.z + m.r1c4 * v.w,
		m.r2c1 * v.x + m.r2c2 * v.y + m.r2c3 * v.z + m.r2c4 * v.w,
		m.r3c1 * v.x + m.r3c2 * v.y + m.r3c3 * v.z + m.r3c4 * v.w,
		m.r4c1 * v.x + m.r4c2 * v.y + m.r4c3 * v.z + m.r4c4 * v.w
	);
}

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
	Vector v1 = Vector(m2.r1c1, m2.r2c1, m2.r3c1, m2.r4c1);
	Vector v2 = Vector(m2.r1c2, m2.r2c2, m2.r3c2, m2.r4c2);
	Vector v3 = Vector(m2.r1c3, m2.r2c3, m2.r3c3, m2.r4c3);
	Vector v4 = Vector(m2.r1c4, m2.r2c4, m2.r3c4, m2.r4c4);

	return Matrix4x4(m1 * v1, m1 * v2, m1 * v3, m1 * v4);
}

Matrix4x4 operator*(const Matrix4x4 m, float f) {
	return Matrix4x4(
		m.r1c1 * f, m.r1c2 * f, m.r1c3 * f, m.r1c4 * f,
		m.r2c1 * f, m.r2c2 * f, m.r2c3 * f, m.r2c4 * f,
		m.r3c1 * f, m.r3c2 * f, m.r3c3 * f, m.r3c4 * f,
		m.r4c1 * f, m.r4c2 * f, m.r4c3 * f, m.r4c4 * f
	);
}

Matrix4x4 operator*(float f, const Matrix4x4 m) {
	return Matrix4x4(
		m.r1c1 * f, m.r1c2 * f, m.r1c3 * f, m.r1c4 * f,
		m.r2c1 * f, m.r2c2 * f, m.r2c3 * f, m.r2c4 * f,
		m.r3c1 * f, m.r3c2 * f, m.r3c3 * f, m.r3c4 * f,
		m.r4c1 * f, m.r4c2 * f, m.r4c3 * f, m.r4c4 * f
	);
}

Matrix4x4 operator/(const Matrix4x4 m, float f) {
	return Matrix4x4(
		m.r1c1 / f, m.r1c2 / f, m.r1c3 / f, m.r1c4 / f,
		m.r2c1 / f, m.r2c2 / f, m.r2c3 / f, m.r2c4 / f,
		m.r3c1 / f, m.r3c2 / f, m.r3c3 / f, m.r3c4 / f,
		m.r4c1 / f, m.r4c2 / f, m.r4c3 / f, m.r4c4 / f
	);
}

bool operator==(const Matrix4x4& m1, const Matrix4x4& m2) {
	return (
		FloatEqual(m1.r1c1, m2.r1c1) && FloatEqual(m1.r1c2, m2.r1c2) && FloatEqual(m1.r1c3, m2.r1c3) && FloatEqual(m1.r1c4, m2.r1c4) &&
		FloatEqual(m1.r2c1, m2.r2c1) && FloatEqual(m1.r2c2, m2.r2c2) && FloatEqual(m1.r2c3, m2.r2c3) && FloatEqual(m1.r2c4, m2.r2c4) &&
		FloatEqual(m1.r3c1, m2.r3c1) && FloatEqual(m1.r3c2, m2.r3c2) && FloatEqual(m1.r3c3, m2.r3c3) && FloatEqual(m1.r3c4, m2.r3c4) &&
		FloatEqual(m1.r4c1, m2.r4c1) && FloatEqual(m1.r4c2, m2.r4c2) && FloatEqual(m1.r4c3, m2.r4c3) && FloatEqual(m1.r4c4, m2.r4c4)
		);
}

Matrix4x4 MatrixTranspose(const Matrix4x4& m) {
	return Matrix4x4(
		m.r1c1, m.r2c1, m.r3c1, m.r4c1,
		m.r1c2, m.r2c2, m.r3c2, m.r4c2,
		m.r1c3, m.r2c3, m.r3c3, m.r4c3,
		m.r1c4, m.r2c4, m.r3c4, m.r4c4
	);
}

Matrix4x4 MatrixInverse(const Matrix4x4& m) {
	auto Determinant3x3 = [](float a, float b, float c, float d, float e, float f, float g, float h, float i) { return (a * e * i) + (b * f * g) + (c * d * h) - (c * e * g) - (a * f * h) - (b * d * i); };

	float determinant =
		m.r1c1 * Determinant3x3(m.r2c2, m.r2c3, m.r2c4, m.r3c2, m.r3c3, m.r3c4, m.r4c2, m.r4c3, m.r4c4)
		- m.r1c2 * Determinant3x3(m.r2c1, m.r2c3, m.r2c4, m.r3c1, m.r3c3, m.r3c4, m.r4c1, m.r4c3, m.r4c4)
		+ m.r1c3 * Determinant3x3(m.r2c1, m.r2c2, m.r2c4, m.r3c1, m.r3c2, m.r3c4, m.r4c1, m.r4c2, m.r4c4)
		- m.r1c4 * Determinant3x3(m.r2c1, m.r2c2, m.r2c3, m.r3c1, m.r3c2, m.r3c3, m.r4c1, m.r4c2, m.r4c3)
		;

	float a11 = -(m.r2c4 * m.r3c3 * m.r4c2) + (m.r2c3 * m.r3c4 * m.r4c2) + (m.r2c4 * m.r3c2 * m.r4c3) - (m.r2c2 * m.r3c4 * m.r4c3) - (m.r2c3 * m.r3c2 * m.r4c4) + (m.r2c2 * m.r3c3 * m.r4c4);
	float a12 = (m.r1c4 * m.r3c3 * m.r4c2) - (m.r1c3 * m.r3c4 * m.r4c2) - (m.r1c4 * m.r3c2 * m.r4c3) + (m.r1c2 * m.r3c4 * m.r4c3) + (m.r1c3 * m.r3c2 * m.r4c4) - (m.r1c2 * m.r3c3 * m.r4c4);
	float a13 = -(m.r1c4 * m.r2c3 * m.r4c2) + (m.r1c3 * m.r2c4 * m.r4c2) + (m.r1c4 * m.r2c2 * m.r4c3) - (m.r1c2 * m.r2c4 * m.r4c3) - (m.r1c3 * m.r2c2 * m.r4c4) + (m.r1c2 * m.r2c3 * m.r4c4);
	float a14 = (m.r1c4 * m.r2c3 * m.r3c2) - (m.r1c3 * m.r2c4 * m.r3c2) - (m.r1c4 * m.r2c2 * m.r3c3) + (m.r1c2 * m.r2c4 * m.r3c3) + (m.r1c3 * m.r2c2 * m.r3c4) - (m.r1c2 * m.r2c3 * m.r3c4);
	float a21 = (m.r2c4 * m.r3c3 * m.r4c1) - (m.r2c3 * m.r3c4 * m.r4c1) - (m.r2c4 * m.r3c1 * m.r4c3) + (m.r2c1 * m.r3c4 * m.r4c3) + (m.r2c3 * m.r3c1 * m.r4c4) - (m.r2c1 * m.r3c3 * m.r4c4);
	float a22 = -(m.r1c4 * m.r3c3 * m.r4c1) + (m.r1c3 * m.r3c4 * m.r4c1) + (m.r1c4 * m.r3c1 * m.r4c3) - (m.r1c1 * m.r3c4 * m.r4c3) - (m.r1c3 * m.r3c1 * m.r4c4) + (m.r1c1 * m.r3c3 * m.r4c4);
	float a23 = (m.r1c4 * m.r2c3 * m.r4c1) - (m.r1c3 * m.r2c4 * m.r4c1) - (m.r1c4 * m.r2c1 * m.r4c3) + (m.r1c1 * m.r2c4 * m.r4c3) + (m.r1c3 * m.r2c1 * m.r4c4) - (m.r1c1 * m.r2c3 * m.r4c4);
	float a24 = -(m.r1c4 * m.r2c3 * m.r3c1) + (m.r1c3 * m.r2c4 * m.r3c1) + (m.r1c4 * m.r2c1 * m.r3c3) - (m.r1c1 * m.r2c4 * m.r3c3) - (m.r1c3 * m.r2c1 * m.r3c4) + (m.r1c1 * m.r2c3 * m.r3c4);
	float a31 = -(m.r2c4 * m.r3c2 * m.r4c1) + (m.r2c2 * m.r3c4 * m.r4c1) + (m.r2c4 * m.r3c1 * m.r4c2) - (m.r2c1 * m.r3c4 * m.r4c2) - (m.r2c2 * m.r3c1 * m.r4c4) + (m.r2c1 * m.r3c2 * m.r4c4);
	float a32 = (m.r1c4 * m.r3c2 * m.r4c1) - (m.r1c2 * m.r3c4 * m.r4c1) - (m.r1c4 * m.r3c1 * m.r4c2) + (m.r1c1 * m.r3c4 * m.r4c2) + (m.r1c2 * m.r3c1 * m.r4c4) - (m.r1c1 * m.r3c2 * m.r4c4);
	float a33 = -(m.r1c4 * m.r2c2 * m.r4c1) + (m.r1c2 * m.r2c4 * m.r4c1) + (m.r1c4 * m.r2c1 * m.r4c2) - (m.r1c1 * m.r2c4 * m.r4c2) - (m.r1c2 * m.r2c1 * m.r4c4) + (m.r1c1 * m.r2c2 * m.r4c4);
	float a34 = (m.r1c4 * m.r2c2 * m.r3c1) - (m.r1c2 * m.r2c4 * m.r3c1) - (m.r1c4 * m.r2c1 * m.r3c2) + (m.r1c1 * m.r2c4 * m.r3c2) + (m.r1c2 * m.r2c1 * m.r3c4) - (m.r1c1 * m.r2c2 * m.r3c4);
	float a41 = (m.r2c3 * m.r3c2 * m.r4c1) - (m.r2c2 * m.r3c3 * m.r4c1) - (m.r2c3 * m.r3c1 * m.r4c2) + (m.r2c1 * m.r3c3 * m.r4c2) + (m.r2c2 * m.r3c1 * m.r4c3) - (m.r2c1 * m.r3c2 * m.r4c3);
	float a42 = -(m.r1c3 * m.r3c2 * m.r4c1) + (m.r1c2 * m.r3c3 * m.r4c1) + (m.r1c3 * m.r3c1 * m.r4c2) - (m.r1c1 * m.r3c3 * m.r4c2) - (m.r1c2 * m.r3c1 * m.r4c3) + (m.r1c1 * m.r3c2 * m.r4c3);
	float a43 = (m.r1c3 * m.r2c2 * m.r4c1) - (m.r1c2 * m.r2c3 * m.r4c1) - (m.r1c3 * m.r2c1 * m.r4c2) + (m.r1c1 * m.r2c3 * m.r4c2) + (m.r1c2 * m.r2c1 * m.r4c3) - (m.r1c1 * m.r2c2 * m.r4c3);
	float a44 = -(m.r1c3 * m.r2c2 * m.r3c1) + (m.r1c2 * m.r2c3 * m.r3c1) + (m.r1c3 * m.r2c1 * m.r3c2) - (m.r1c1 * m.r2c3 * m.r3c2) - (m.r1c2 * m.r2c1 * m.r3c3) + (m.r1c1 * m.r2c2 * m.r3c3);

	Matrix4x4 adj = Matrix4x4(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44);

	if (determinant != 0) { return adj / determinant; }
	else { return Matrix4x4(); }
}

Matrix4x4 IdentityMatrix() {
	return Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 TranslationMatrix(const Vector& v) {
	return Matrix4x4(
		1.0f, 0.0f, 0.0f, v.x,
		0.0f, 1.0f, 0.0f, v.y,
		0.0f, 0.0f, 1.0f, v.z,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 ScalingMatrix(const Vector& v) {
	return Matrix4x4(
		v.x, 0.0f, 0.0f, 0.0f,
		0.0f, v.y, 0.0f, 0.0f,
		0.0f, 0.0f, v.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 RotationMatrix(const Quaternion& q) {
	return Matrix4x4(
		1 - 2 * (q.y * q.y + q.z * q.z), 2 * (q.x * q.y - q.z * q.w), 2 * (q.x * q.z + q.y * q.w), 0,
		2 * (q.x * q.y + q.z * q.w), 1 - 2 * (q.x * q.x + q.z * q.z), 2 * (q.y * q.z - q.x * q.w), 0,
		2 * (q.x * q.z - q.y * q.w), 2 * (q.x * q.z + q.x * q.w), 1 - 2 * (q.x * q.x + q.y * q.y), 0,
		0, 0, 0, 1
	);
}

Matrix4x4 PerspectiveProjectionMatrix(float fovDegree, float aspectRatio, float zFar, float zNear) {
	float fovRadian = fovDegree * 0.01745329f;

	return Matrix4x4(
		aspectRatio / tan(fovRadian / 2.0f), 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f / (tan(fovRadian / 2.0f)), 0.0f, 0.0f,
		0.0f, 0.0f, zFar / (zFar - zNear), 1.0f,
		0.0f, 0.0f, zFar * zNear / (zFar - zNear), 0.0f
	);
}

Colour operator+(const Colour& c1, const Colour& c2) {
	return Colour(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a);
}

Colour operator-(const Colour& c1, const Colour& c2) {
	return Colour(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b, c1.a - c2.a);
}

Colour operator*(const Colour& c1, const Colour& c2) {
	return Colour(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b, c1.a * c2.a);
}

Colour operator*(const Colour& c, float f) {
	return Colour(c.r * f, c.g * f, c.b * f, c.a * f);
}

Colour operator*(float f, const Colour& c) {
	return Colour(c.r * f, c.g * f, c.b * f, c.a * f);
}

Colour operator/(const Colour& c, float f) {
	return Colour(c.r / f, c.g / f, c.b / f, c.a / f);
}

bool operator==(const Colour& c1, const Colour c2) {
	return (FloatEqual(c1.r, c2.r) && FloatEqual(c1.g, c2.g) && FloatEqual(c1.b, c2.b) && FloatEqual(c1.a, c2.a));
}

int ColourToInt(const Colour& c) {
	int colour = 0;

	unsigned char p = char(c.a * 255.0f);
	unsigned char r = char(c.r * 255.0f);
	unsigned char g = char(c.g * 255.0f);
	unsigned char b = char(c.b * 255.0f);

	colour = p;
	colour <<= 8;
	colour |= r;
	colour <<= 8;
	colour |= g;
	colour <<= 8;
	colour |= b;

	return colour;
}



Vector::Vector() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }

Vector::Vector(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }

Vector::Vector(const Vector& v) : x(v.x), y(v.y), z(v.z), w(v.w) { }

Vector::~Vector() {}

Vector& Vector::operator=(const Vector& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

Vector& Vector::operator+=(const Vector& v) {
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

Vector& Vector::operator-=(const Vector& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

Vector& Vector::operator*=(float f) {
	x *= f;
	y *= f;
	z *= f;

	return *this;
}

Vector& Vector::operator/=(float f) {
	x /= f;
	y /= f;
	z /= f;

	return *this;
}

Vector Vector::operator-() const {
	return Vector(-x, -y, -z, w);
}

Quaternion::Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

Quaternion::Quaternion(const Quaternion& q) : w(q.w), x(q.x), y(q.y), z(q.z) {}

Quaternion::~Quaternion() {}

Quaternion& Quaternion::operator=(const Quaternion& q) {
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;

	return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& q) {
	w = w * q.w - x * q.x - y * q.y - z * q.z;
	x = x * q.w + w * q.x + y * q.z - z * q.y;
	y = y * q.w + w * q.y + z * q.x - x * q.z;
	z = z * q.w + w * q.z + x * q.y - y * q.x;

	return *this;
}

Quaternion& Quaternion::operator*=(const Vector& v) {
	w = -x * v.x - y * v.y - z * v.z;
	x = w * v.x + y * v.z - z * v.y;
	y = w * v.y + z * v.x - x * v.z;
	z = w * v.z + x * v.y - y * v.x;

	return *this;
}

Quaternion Quaternion::operator-() {
	return Quaternion(w, -x, -y, -z);
}

Matrix4x4::Matrix4x4() :
	r1c1(0.0f), r1c2(0.0f), r1c3(0.0f), r1c4(0.0f),
	r2c1(0.0f), r2c2(0.0f), r2c3(0.0f), r2c4(0.0f),
	r3c1(0.0f), r3c2(0.0f), r3c3(0.0f), r3c4(0.0f),
	r4c1(0.0f), r4c2(0.0f), r4c3(0.0f), r4c4(0.0f)
{}

Matrix4x4::Matrix4x4(float a11, float a12, float a13, float a14, float a21, float a22, float a23, float a24, float a31, float a32, float a33, float a34, float a41, float a42, float a43, float a44) :
	r1c1(a11), r1c2(a12), r1c3(a13), r1c4(a14),
	r2c1(a21), r2c2(a22), r2c3(a23), r2c4(a24),
	r3c1(a31), r3c2(a32), r3c3(a33), r3c4(a34),
	r4c1(a41), r4c2(a42), r4c3(a43), r4c4(a44)
{}

Matrix4x4::Matrix4x4(const Vector & v1, const Vector & v2, const Vector & v3, const Vector & v4) :
	r1c1(v1.x), r1c2(v2.x), r1c3(v3.x), r1c4(v4.x),
	r2c1(v1.y), r2c2(v2.y), r2c3(v3.y), r2c4(v4.y),
	r3c1(v1.z), r3c2(v2.z), r3c3(v3.z), r3c4(v4.z),
	r4c1(v1.w), r4c2(v2.w), r4c3(v3.w), r4c4(v4.w)
{}

Matrix4x4::Matrix4x4(const Matrix4x4 & m) :
	r1c1(m.r1c1), r1c2(m.r1c2), r1c3(m.r1c3), r1c4(m.r1c4),
	r2c1(m.r2c1), r2c2(m.r2c2), r2c3(m.r2c3), r2c4(m.r2c4),
	r3c1(m.r3c1), r3c2(m.r3c2), r3c3(m.r3c3), r3c4(m.r3c4),
	r4c1(m.r4c1), r4c2(m.r4c2), r4c3(m.r4c3), r4c4(m.r4c4)
{}

Matrix4x4::~Matrix4x4() {}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& m) {
	r1c1 = m.r1c1; r1c2 = m.r1c2; r1c3 = m.r1c3; r1c4 = m.r1c4;
	r2c1 = m.r2c1; r2c2 = m.r2c2; r2c3 = m.r2c3; r2c4 = m.r2c4;
	r3c1 = m.r3c1; r3c2 = m.r3c2; r3c3 = m.r3c3; r3c4 = m.r3c4;
	r4c1 = m.r4c1; r4c2 = m.r4c2; r4c3 = m.r4c3; r4c4 = m.r4c4;

	return *this;
}

Matrix4x4& Matrix4x4::operator+=(const Matrix4x4 m) {
	r1c1 += m.r1c1; r1c2 += m.r1c2; r1c3 += m.r1c3; r1c4 += m.r1c4;
	r2c1 += m.r2c1; r2c2 += m.r2c2; r2c3 += m.r2c3; r2c4 += m.r2c4;
	r3c1 += m.r3c1; r3c2 += m.r3c2; r3c3 += m.r3c3; r3c4 += m.r3c4;
	r4c1 += m.r4c1; r4c2 += m.r4c2; r4c3 += m.r4c3; r4c4 += m.r4c4;

	return *this;
}

Matrix4x4& Matrix4x4::operator-=(const Matrix4x4 m) {
	r1c1 -= m.r1c1; r1c2 -= m.r1c2; r1c3 -= m.r1c3; r1c4 -= m.r1c4;
	r2c1 -= m.r2c1; r2c2 -= m.r2c2; r2c3 -= m.r2c3; r2c4 -= m.r2c4;
	r3c1 -= m.r3c1; r3c2 -= m.r3c2; r3c3 -= m.r3c3; r3c4 -= m.r3c4;
	r4c1 -= m.r4c1; r4c2 -= m.r4c2; r4c3 -= m.r4c3; r4c4 -= m.r4c4;

	return *this;
}

Matrix4x4& Matrix4x4::operator*=(float f) {
	r1c1 *= f; r1c2 *= f; r1c3 *= f; r1c4 *= f;
	r2c1 *= f; r2c2 *= f; r2c3 *= f; r2c4 *= f;
	r3c1 *= f; r3c2 *= f; r3c3 *= f; r3c4 *= f;
	r4c1 *= f; r4c2 *= f; r4c3 *= f; r4c4 *= f;

	return *this;
}

Matrix4x4& Matrix4x4::operator/=(float f) {
	r1c1 /= f; r1c2 /= f; r1c3 /= f; r1c4 /= f;
	r2c1 /= f; r2c2 /= f; r2c3 /= f; r2c4 /= f;
	r3c1 /= f; r3c2 /= f; r3c3 /= f; r3c4 /= f;
	r4c1 /= f; r4c2 /= f; r4c3 /= f; r4c4 /= f;

	return *this;
}

Matrix4x4 Matrix4x4::operator-() {
	return Matrix4x4(
		-r1c1, -r1c2, -r1c3, -r1c4,
		-r2c1, -r2c2, -r2c3, -r2c4,
		-r3c1, -r3c2, -r3c3, -r3c4,
		-r4c1, -r4c2, -r4c3, -r4c4
	);
}

Colour::Colour() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}

Colour::Colour(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

Colour::Colour(const Colour& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}

Colour::~Colour() {}

Colour& Colour::operator=(const Colour& c) {
	r = c.r;
	g = c.g;
	b = c.b;
	a = c.a;

	return *this;
}

Colour& Colour::operator+=(const Colour& c) {
	r += c.r;
	g += c.g;
	b += c.b;
	a += c.a;

	return *this;
}

Colour& Colour::operator-=(const Colour& c) {
	r -= c.r;
	g -= c.g;
	b -= c.b;
	a -= c.a;

	return *this;
}

Colour& Colour::operator*=(float f) {
	r *= f;
	g *= f;
	b *= f;
	a *= f;

	return *this;
}

Colour& Colour::operator/=(float f) {
	r /= f;
	g /= f;
	b /= f;
	a /= f;

	return *this;
}

Colour Colour::operator-() const {
	return Colour(-r, -g, -b, -a);
}

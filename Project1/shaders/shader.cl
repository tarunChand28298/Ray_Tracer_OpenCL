//=============================================================================
//=============================================================================
//Math Specific:
//Floats:
bool absolute(float n){ if(n > 0)return n; else return -n;}
bool FloatEqual(float a, float b) { return absolute((float)(a - b)) < 0.0001f; }
float FloatSquare(float n) { return n * n; }

//Vector:
typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vector;

Vector MakeVector(float x, float y, float z, float w){
  Vector v;

  v.x = x;
  v.y = y;
  v.z = z;
  v.w = w;

  return v;}
Vector VectorPoint(float x, float y, float z){
  Vector v;

  v.x = x;
  v.y = y;
  v.z = z;
  v.w = 1.0f;

  return v;}
Vector VectorDirection(float x, float y, float z){
  Vector v;

  v.x = x;
  v.y = y;
  v.z = z;
  v.w = 0.0f;

  return v;}

Vector VectorAdd(Vector v1, Vector v2){return MakeVector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);}
Vector VectorSub(Vector v1, Vector v2){return MakeVector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);}
Vector VectorMul(Vector v, float f){return MakeVector(v.x * f, v.y * f, v.z * f, v.w);}
Vector VectorDiv(Vector v, float f){return MakeVector(v.x / f, v.y / f, v.z / f, v.w);}
bool VectorEqual(Vector v1, Vector v2){return (FloatEqual(v1.x, v2.z) && FloatEqual(v1.y, v2.y) && FloatEqual(v1.z, v2.z) && FloatEqual(v1.w, v2.w));}

float VectorLengthSquared(Vector v) {return FloatSquare(v.x) + FloatSquare(v.y) + FloatSquare(v.z); }
float VectorLength(Vector v) { return sqrt(VectorLengthSquared(v)); }
Vector VectorNormalize(Vector v){
  float length = VectorLength(v);
  return MakeVector(v.x / length, v.y / length, v.z / length, v.w);}

float VectorDot(Vector v1, Vector v2){return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;}
Vector VectorCross(Vector v1, Vector v2){return VectorDirection(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);}
Vector VectorHadamard(Vector v1, Vector v2){return MakeVector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);}

//Quaternion:
typedef struct {
  float w;
	float x;
	float y;
	float z;
} Quaternion;

Quaternion MakeQuaternion(float w, float x, float y, float z){
  Quaternion q;

  q.w = w;
  q.x = x;
  q.y = y;
  q.z = z;

  return q;}

Quaternion QuaternionMulQuat (Quaternion q1, Quaternion q2){
    float _w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	  float _x = q1.x * q2.w + q1.w * q2.x + q1.y * q2.z - q1.z * q2.y;
	  float _y = q1.y * q2.w + q1.w * q2.y + q1.z * q2.x - q1.x * q2.z;
	  float _z = q1.z * q2.w + q1.w * q2.z + q1.x * q2.y - q1.y * q2.x;
	  return MakeQuaternion(_w, _x, _y, _z);}
Quaternion QuaternionMulVec (Quaternion q, Vector v){
    float _w = -q.x * v.x - q.y * v.y - q.z * v.z;
  	float _x = q.w * v.x + q.y * v.z - q.z * v.y;
  	float _y = q.w * v.y + q.z * v.x - q.x * v.z;
  	float _z = q.w * v.z + q.x * v.y - q.y * v.x;

  	return MakeQuaternion(_w, _x, _y, _z);}
bool QuaternionEqual (Quaternion q1, Quaternion q2){return (FloatEqual(q1.w, q2.w) && FloatEqual(q1.x, q2.x) && FloatEqual(q1.y, q2.y) && FloatEqual(q1.z, q2.z));}

float QuaternionLengthSquared(Quaternion q){return FloatSquare(q.x) + FloatSquare(q.y) + FloatSquare(q.z) + FloatSquare(q.w);}
float QuaternionLength(Quaternion q){return sqrt(QuaternionLengthSquared(q));}
Quaternion QuaternionNormalize(Quaternion q){
  float length = QuaternionLength(q);
	return MakeQuaternion(q.w / length, q.x / length, q.y / length, q.z / length);}

//Matrix (Column Major):
typedef struct {
  float r1c1; float r1c2; float r1c3; float r1c4;
  float r2c1; float r2c2; float r2c3; float r2c4;
  float r3c1; float r3c2; float r3c3; float r3c4;
  float r4c1; float r4c2; float r4c3; float r4c4;
} Matrix4x4;

Matrix4x4 MakeMatrixF(float a11, float a12, float a13, float a14, float a21, float a22, float a23, float a24, float a31, float a32, float a33, float a34, float a41, float a42, float a43, float a44){
  Matrix4x4 m;

  m.r1c1 = a11; m.r1c2 = a12; m.r1c3 = a13; m.r1c4 = a14;
  m.r2c1 = a21; m.r2c2 = a22; m.r2c3 = a23; m.r2c4 = a24;
  m.r3c1 = a31; m.r3c2 = a32; m.r3c3 = a33; m.r3c4 = a34;
  m.r4c1 = a41; m.r4c2 = a42; m.r4c3 = a43; m.r4c4 = a44;

  return m;}
Matrix4x4 MakeMatrixV(Vector v1, Vector v2, Vector v3, Vector v4) {
  Matrix4x4 m;

  m.r1c1 = v1.x; m.r1c2 = v2.x; m.r1c3 = v3.x; m.r1c4 = v4.x;
  m.r2c1 = v1.y; m.r2c2 = v2.y; m.r2c3 = v3.y; m.r2c4 = v4.y;
  m.r3c1 = v1.z; m.r3c2 = v2.z; m.r3c3 = v3.z; m.r3c4 = v4.z;
  m.r4c1 = v1.w; m.r4c2 = v2.w; m.r4c3 = v3.w; m.r4c4 = v4.w;

  return m;}

Matrix4x4 ZeroMatrix(){
  return MakeMatrixF(
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f);}
Matrix4x4 IdentityMatrix(){
  return MakeMatrixF(
  		1.0f, 0.0f, 0.0f, 0.0f,
  		0.0f, 1.0f, 0.0f, 0.0f,
  		0.0f, 0.0f, 1.0f, 0.0f,
  		0.0f, 0.0f, 0.0f, 1.0f
  	);}
Matrix4x4 TranslationMatrix(Vector v){
  return MakeMatrixF(
		1.0f, 0.0f, 0.0f, v.x,
		0.0f, 1.0f, 0.0f, v.y,
		0.0f, 0.0f, 1.0f, v.z,
		0.0f, 0.0f, 0.0f, 1.0f
	);}
Matrix4x4 ScalingMatrix(Vector v){
  return MakeMatrixF(
  		v.x, 0.0f, 0.0f, 0.0f,
  		0.0f, v.y, 0.0f, 0.0f,
  		0.0f, 0.0f, v.z, 0.0f,
  		0.0f, 0.0f, 0.0f, 1.0f
  	);}
Matrix4x4 RotationMatrix(Quaternion q){
  return MakeMatrixF(
  		1 - 2 * (q.y * q.y + q.z * q.z), 2 * (q.x * q.y - q.z * q.w), 2 * (q.x * q.z + q.y * q.w), 0,
  		2 * (q.x * q.y + q.z * q.w), 1 - 2 * (q.x * q.x + q.z * q.z), 2 * (q.y * q.z - q.x * q.w), 0,
  		2 * (q.x * q.z - q.y * q.w), 2 * (q.x * q.z + q.x * q.w), 1 - 2 * (q.x * q.x + q.y * q.y), 0,
  		0, 0, 0, 1
  	);}
Matrix4x4 PerspectiveProjectionMatrix(float fovDegree, float aspectRatio, float zFar, float zNear){
  float fovRadian = fovDegree * 0.01745329f;

  	return MakeMatrixF(
  		aspectRatio / tan(fovRadian / 2.0f), 0.0f, 0.0f, 0.0f,
  		0.0f, 1.0f / (tan(fovRadian / 2.0f)), 0.0f, 0.0f,
  		0.0f, 0.0f, zFar / (zFar - zNear), 1.0f,
  		0.0f, 0.0f, -zFar * zNear / (zFar - zNear), 0.0f
  	);}

Matrix4x4 MatrixAdd(Matrix4x4 m1, Matrix4x4 m2){
  return MakeMatrixF(
		m1.r1c1 + m2.r1c1, m1.r1c2 + m2.r1c2, m1.r1c3 + m2.r1c3, m1.r1c4 + m2.r1c4,
		m1.r2c1 + m2.r2c1, m1.r2c2 + m2.r2c2, m1.r2c3 + m2.r2c3, m1.r2c4 + m2.r2c4,
		m1.r3c1 + m2.r3c1, m1.r3c2 + m2.r3c2, m1.r3c3 + m2.r3c3, m1.r3c4 + m2.r3c4,
		m1.r4c1 + m2.r4c1, m1.r4c2 + m2.r4c2, m1.r4c3 + m2.r4c3, m1.r4c4 + m2.r4c4
	);}
Matrix4x4 MatrixSub(Matrix4x4 m1, Matrix4x4 m2){
  return MakeMatrixF(
  		m1.r1c1 - m2.r1c1, m1.r1c2 - m2.r1c2, m1.r1c3 - m2.r1c3, m1.r1c4 - m2.r1c4,
  		m1.r2c1 - m2.r2c1, m1.r2c2 - m2.r2c2, m1.r2c3 - m2.r2c3, m1.r2c4 - m2.r2c4,
  		m1.r3c1 - m2.r3c1, m1.r3c2 - m2.r3c2, m1.r3c3 - m2.r3c3, m1.r3c4 - m2.r3c4,
  		m1.r4c1 - m2.r4c1, m1.r4c2 - m2.r4c2, m1.r4c3 - m2.r4c3, m1.r4c4 - m2.r4c4
  	);}
Vector MatrixMulV(Matrix4x4 m, Vector v){
  return MakeVector(
  		m.r1c1 * v.x + m.r1c2 * v.y + m.r1c3 * v.z + m.r1c4 * v.w,
  		m.r2c1 * v.x + m.r2c2 * v.y + m.r2c3 * v.z + m.r2c4 * v.w,
  		m.r3c1 * v.x + m.r3c2 * v.y + m.r3c3 * v.z + m.r3c4 * v.w,
  		m.r4c1 * v.x + m.r4c2 * v.y + m.r4c3 * v.z + m.r4c4 * v.w
  	);}
Matrix4x4 MatrixMulM(Matrix4x4 m1, Matrix4x4 m2){
  Vector v1 = MakeVector(m2.r1c1, m2.r2c1, m2.r3c1, m2.r4c1);
  Vector v2 = MakeVector(m2.r1c2, m2.r2c2, m2.r3c2, m2.r4c2);
  Vector v3 = MakeVector(m2.r1c3, m2.r2c3, m2.r3c3, m2.r4c3);
  Vector v4 = MakeVector(m2.r1c4, m2.r2c4, m2.r3c4, m2.r4c4);

  	return MakeMatrixV(MatrixMulV(m1, v1), MatrixMulV(m1, v2), MatrixMulV(m1, v3), MatrixMulV(m1, v4));}
Matrix4x4 MatrixMulF(Matrix4x4 m, float f){
  return MakeMatrixF(
  		m.r1c1 * f, m.r1c2 * f, m.r1c3 * f, m.r1c4 * f,
  		m.r2c1 * f, m.r2c2 * f, m.r2c3 * f, m.r2c4 * f,
  		m.r3c1 * f, m.r3c2 * f, m.r3c3 * f, m.r3c4 * f,
  		m.r4c1 * f, m.r4c2 * f, m.r4c3 * f, m.r4c4 * f
  	);}
Matrix4x4 MatrixDivF(Matrix4x4 m, float f){
  return MakeMatrixF(
  		m.r1c1 / f, m.r1c2 / f, m.r1c3 / f, m.r1c4 / f,
  		m.r2c1 / f, m.r2c2 / f, m.r2c3 / f, m.r2c4 / f,
  		m.r3c1 / f, m.r3c2 / f, m.r3c3 / f, m.r3c4 / f,
  		m.r4c1 / f, m.r4c2 / f, m.r4c3 / f, m.r4c4 / f
  	);}
bool MatrixEqual(Matrix4x4 m1, Matrix4x4 m2){
  return (
  		FloatEqual(m1.r1c1, m2.r1c1) && FloatEqual(m1.r1c2, m2.r1c2) && FloatEqual(m1.r1c3, m2.r1c3) && FloatEqual(m1.r1c4, m2.r1c4) &&
  		FloatEqual(m1.r2c1, m2.r2c1) && FloatEqual(m1.r2c2, m2.r2c2) && FloatEqual(m1.r2c3, m2.r2c3) && FloatEqual(m1.r2c4, m2.r2c4) &&
  		FloatEqual(m1.r3c1, m2.r3c1) && FloatEqual(m1.r3c2, m2.r3c2) && FloatEqual(m1.r3c3, m2.r3c3) && FloatEqual(m1.r3c4, m2.r3c4) &&
  		FloatEqual(m1.r4c1, m2.r4c1) && FloatEqual(m1.r4c2, m2.r4c2) && FloatEqual(m1.r4c3, m2.r4c3) && FloatEqual(m1.r4c4, m2.r4c4)
  		);}

float Determinant3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i){
  return (a * e * i) + (b * f * g) + (c * d * h) - (c * e * g) - (a * f * h) - (b * d * i);}
float MatrixDeterminant(Matrix4x4 m){
  return
    m.r1c1 * Determinant3x3(m.r2c2, m.r2c3, m.r2c4, m.r3c2, m.r3c3, m.r3c4, m.r4c2, m.r4c3, m.r4c4)
		- m.r1c2 * Determinant3x3(m.r2c1, m.r2c3, m.r2c4, m.r3c1, m.r3c3, m.r3c4, m.r4c1, m.r4c3, m.r4c4)
		+ m.r1c3 * Determinant3x3(m.r2c1, m.r2c2, m.r2c4, m.r3c1, m.r3c2, m.r3c4, m.r4c1, m.r4c2, m.r4c4)
		- m.r1c4 * Determinant3x3(m.r2c1, m.r2c2, m.r2c3, m.r3c1, m.r3c2, m.r3c3, m.r4c1, m.r4c2, m.r4c3)
		;}

Matrix4x4 MatrixTranspose(Matrix4x4 m){
  return MakeMatrixF(
  		m.r1c1, m.r2c1, m.r3c1, m.r4c1,
  		m.r1c2, m.r2c2, m.r3c2, m.r4c2,
  		m.r1c3, m.r2c3, m.r3c3, m.r4c3,
  		m.r1c4, m.r2c4, m.r3c4, m.r4c4
  	);}
Matrix4x4 MatrixInverse(Matrix4x4 m){

  float determinant = MatrixDeterminant(m);

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

	Matrix4x4 adj = MakeMatrixF(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44);

  if (determinant != 0) { return MatrixDivF(adj, determinant); }
	else { return ZeroMatrix(); }
}

//Colour:
typedef struct {
	float r;
	float g;
	float b;
	float a;
} Colour;

Colour MakeColour(float r, float g, float b, float a) {
  Colour c;

  c.r = r;
  c.g = g;
  c.b = b;
  c.a = a;

  return c;}

  Colour ColourAdd(Colour c1, Colour c2){
    return MakeColour(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a);}
  Colour ColourSub(Colour c1, Colour c2){
    return MakeColour(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b, c1.a - c2.a);}
  Colour ColourMulCol(Colour c1, Colour c2){
    return MakeColour(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b, c1.a * c2.a);}
  Colour ColourMulF(Colour c, float f){
    return MakeColour(c.r * f, c.g * f, c.b * f, c.a * f);}
  Colour ColourDivF(Colour c, float f){
    return MakeColour(c.r / f, c.g / f, c.b / f, c.a / f);}
  bool ColourEqual(Colour c1, Colour c2){
    return (FloatEqual(c1.r, c2.r) && FloatEqual(c1.g, c2.g) && FloatEqual(c1.b, c2.b) && FloatEqual(c1.a, c2.a));}

int ColourToInt(Colour c) {
	int colour = 0;

	unsigned char p = (unsigned char)(c.a * 255.0f);
	unsigned char r = (unsigned char)(c.r * 255.0f);
	unsigned char g = (unsigned char)(c.g * 255.0f);
	unsigned char b = (unsigned char)(c.b * 255.0f);

	colour = p;
	colour <<= 8;
	colour |= r;
	colour <<= 8;
	colour |= g;
	colour <<= 8;
	colour |= b;

	return colour;}

//=============================================================================
//=============================================================================

//Ray Tracer Specific:

//Input from CPU:
//Mesh:
typedef struct
{
	int transformIndex;
	int startTriangleIndex;
	int endTriangleIndex;
} Mesh;

typedef struct
{
	int vertex0;
	int vertex1;
	int vertex2;

	Colour albedo;
	Colour specular;
} Index;

//GPU only structs:
//Triangle:
typedef struct
{
	Vector v0;
	Vector v1;
	Vector v2;

	Colour albedo;
	Colour specular;
} Triangle;

typedef struct
{
	Vector origin;
	Vector direction;
} Ray;

//GPU functions:
Ray MakeRay(Vector origin, Vector direction)
{
	Ray r;

	r.origin = origin;
	r.direction = direction;

	return r;
}

Ray CreateCameraRay(float u, float v, Matrix4x4 cameraTransform, Matrix4x4 cameraInverseProjection)
{
	Vector origin = MatrixMulV(cameraTransform, VectorPoint(0.0f, 0.0f, 0.0f));

	Vector directionRaw = MatrixMulV(cameraInverseProjection, VectorPoint(u, v, 0.0f));
	directionRaw = MatrixMulV(cameraTransform, directionRaw);
	Vector direction = VectorNormalize(directionRaw);

	return MakeRay(origin, direction);
}

bool IntersectTriangle(Ray ray, Triangle tri, float* t, float* u, float* v, float* w)
{
	Vector edge1 = VectorSub(tri.v1, tri.v0);
	Vector edge2 = VectorSub(tri.v2, tri.v0);

	Vector pVec = VectorCross(ray.direction, edge2);
	float det = VectorDot(edge1, pVec);

	//backface culling:
	if (det <= 0) return false;

	float inv_det = 1.0f / det;
	Vector tVec = VectorSub(ray.origin, tri.v0);

	*u = VectorDot(tVec, pVec) * inv_det;
	if (*u < 0.0f || *u > 1.0f) return false;

	Vector qVec = VectorCross(tVec, edge1);
	*v = VectorDot(ray.direction, qVec) * inv_det;
	if (*v < 0.0f || *u + *v > 1.0f) return false;

	*t = VectorDot(edge2, qVec) * inv_det;
	*w = 1.0f - *u - *v;
	return true;
}

//=============================================================================
//Debug print matrix:
//printf("Mesh transform");
//printf("%f  %f  %f  %f\n", meshTransform.r1c1, meshTransform.r1c2, meshTransform.r1c3, meshTransform.r1c4);
//printf("%f  %f  %f  %f\n", meshTransform.r2c1, meshTransform.r2c2, meshTransform.r2c3, meshTransform.r2c4);
//printf("%f  %f  %f  %f\n", meshTransform.r3c1, meshTransform.r3c2, meshTransform.r3c3, meshTransform.r3c4);
//printf("%f  %f  %f  %f\n", meshTransform.r4c1, meshTransform.r4c2, meshTransform.r4c3, meshTransform.r4c4);
//=============================================================================


kernel void GPUMain(
		int nMeshes,
		global Mesh* meshArray,
		global Matrix4x4* xformArray,
		global Index* indexArray,
		global Vector* vertexArray,
		int width,
		int height,
		Matrix4x4 camXform,
		Matrix4x4 InvCamProjMat,
		global int* result
	)
{
    int id = get_global_id(0);

    int x = id % width;
    int y = id / width;

		float u = (((float)x / (float)width ) - 0.5f) * 2.0f;
		float v = (((float)y / (float)height) - 0.5f) * 2.0f;

		Colour pixelColour;

		//==========================================================================

		Ray cameraRay = CreateCameraRay(u, v, camXform, InvCamProjMat);
		float currentT, nearestT = 1000000.0f;
		bool intersection = false;
		for(int i=0; i<nMeshes; i++)
		{
			Mesh currentMesh = meshArray[i];
			Matrix4x4 meshTransform = xformArray[currentMesh.transformIndex];
			for(int j=currentMesh.startTriangleIndex; j<currentMesh.endTriangleIndex; j++)
			{
				Index currentTri = indexArray[j];

				Triangle tri;
				tri.v0 = MatrixMulV(meshTransform, vertexArray[currentTri.vertex0]);
				tri.v1 = MatrixMulV(meshTransform, vertexArray[currentTri.vertex1]);
				tri.v2 = MatrixMulV(meshTransform, vertexArray[currentTri.vertex2]);
				tri.albedo = currentTri.albedo;
				tri.specular = currentTri.specular;

				float outU, outV, outW;
				intersection |= IntersectTriangle(cameraRay, tri, &currentT, &outU, &outV, &outW);
			}

			if(intersection)
			{
					//Hit shader:
					pixelColour = MakeColour(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else
			{
					//Miss shader:
					float vNorm = (v + 1.0f) * 0.5f;
					Colour blue = MakeColour(0.33f, 0.68, 0.9f, 1.0f);
					Colour white = MakeColour(1.0f, 1.0f, 1.0f, 1.0f);

					Colour lerpColour = MakeColour( (1.0f - vNorm) * white.r + vNorm * blue.r, (1.0f - vNorm) * white.g + vNorm * blue.g, (1.0f - vNorm) * white.b + vNorm * blue.b, (1.0f - vNorm) * white.a + vNorm * blue.a);

					pixelColour = lerpColour;
			}
		}
		//==========================================================================

    result[id] = ColourToInt(pixelColour);
}

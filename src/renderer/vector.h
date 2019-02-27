#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

#define DEGREES_TO_RADIANS(degrees) (degrees * (M_PI / 180))
#define RADIANS_TO_DEGREES(radians) (radians * (180 / M_PI))

// # Vectors
// ## Vector operations
// # new
// # access (get nth element)
// # add
// # subtract
// # dot
// # cross
// # scalar
// # magnitude
// # normalize

// Vector
typedef struct Vector2 {
  double x;
  double y;
} Vector2;

Vector2 vec2(double x, double y);
double * access2(Vector2 *v, int row);
Vector2 add2(Vector2 a, Vector2 b);
Vector2 subtract2(Vector2 a, Vector2 b);
double dot2(Vector2 a, Vector2 b);
Vector2 scalar2(Vector2 v, double s);
double magnitude2(Vector2 v);
Vector2 normalize2(Vector2 v);

typedef struct Vector3 {
  double x;
  double y;
  double z;
} Vector3;

Vector3 vec3(double x, double y, double z);
double * access3(Vector3 *v, int row);
Vector3 add3(Vector3 a, Vector3 b);
Vector3 subtract3(Vector3 a, Vector3 b);
double dot3(Vector3 a, Vector3 b);
Vector3 cross(Vector3 a, Vector3 b);
Vector3 scalar3(Vector3 v, double s);
double magnitude3(Vector3 v);
Vector3 normalize3(Vector3 v);

typedef struct Vector4 {
  double x;
  double y;
  double z;
  double w;
} Vector4;

double * access4(Vector4 *v, int row);

Vector4 vec4(double x, double y, double z, double w);
Vector4 add4(Vector4 a, Vector4 b);
Vector4 subtract4(Vector4 a, Vector4 b);
double dot4(Vector4 a, Vector4 b);
Vector4 scalar4(Vector4 v, double s);
double magnitude4(Vector4 v);
Vector4 normalize4(Vector4 v);

// Matrix
typedef struct Matrix4x4 {
  double a11, a12, a13, a14,
         a21, a22, a23, a24,
         a31, a32, a33, a34,
         a41, a42, a43, a44;
} Matrix4x4;

#define MATMUL(a, b) multiplyMatrix4x4(a, b)

double * accessMatrix4x4(Matrix4x4 *m, int row, int column);
Matrix4x4 multiplyMatrix4x4(Matrix4x4 a, Matrix4x4 b);
Matrix4x4 identityMatrix4x4();
Matrix4x4 translationMatrix(Vector3 translation);
Matrix4x4 scalingMatrix(Vector3 scale);
Matrix4x4 rotationXMatrix(double angle);
Matrix4x4 rotationYMatrix(double angle);
Matrix4x4 rotationZMatrix(double angle);
Vector4 matrix4x4timesVector4(Matrix4x4 a, Vector4 b);
Matrix4x4 perspectiveProjectionMatrix(double nearPlane, double farPlane, double fovy, double aspect);
Matrix4x4 orthographicProjectionMatrix(double nearPlane, double farPlane, double left, double right, double bottom, double top);
Matrix4x4 lookAt(Vector3 eye, Vector3 center, Vector3 up);

typedef struct Matrix4x4F {
  float a11, a12, a13, a14,
        a21, a22, a23, a24,
        a31, a32, a33, a34,
        a41, a42, a43, a44;
} Matrix4x4F;
Matrix4x4F matrix4x4toMatrix4x4F(Matrix4x4 m);

#endif

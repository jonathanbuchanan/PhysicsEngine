#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

#define DEGREES_TO_RADIANS(degrees) (degrees * (M_PI / 180))
#define RADIANS_TO_DEGREES(radians) (radians * (180 / M_PI))

// Vector
typedef struct Vector2 {
  double x;
  double y;
} Vector2;

Vector2 addVector2(Vector2 a, Vector2 b);
Vector2 subtractVector2(Vector2 a, Vector2 b);
double dotProduct2(Vector2 a, Vector2 b);
double magnitudeVector2(Vector2 v);

typedef struct Vector3 {
  double x;
  double y;
  double z;
} Vector3;

double * accessVector3(Vector3 *v, int row);

Vector3 addVector3(Vector3 a, Vector3 b);
Vector3 subtractVector3(Vector3 a, Vector3 b);
double dotProduct(Vector3 a, Vector3 b);
Vector3 crossProduct(Vector3 a, Vector3 b);
double magnitudeVector3(Vector3 v);
Vector3 vec3(double x, double y, double z);

typedef struct Vector4 {
  double x;
  double y;
  double z;
  double w;
} Vector4;

double * accessVector4(Vector4 *v, int row);

Vector4 addVector4(Vector4 a, Vector4 b);
Vector4 subtractVector4(Vector4 a, Vector4 b);
double dotProduct4(Vector4 a, Vector4 b);

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

typedef struct Matrix4x4F {
  float a11, a12, a13, a14,
        a21, a22, a23, a24,
        a31, a32, a33, a34,
        a41, a42, a43, a44;
} Matrix4x4F;
Matrix4x4F matrix4x4toMatrix4x4F(Matrix4x4 m);

#endif

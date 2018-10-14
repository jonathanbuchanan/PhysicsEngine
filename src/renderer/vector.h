#ifndef VECTOR_H
#define VECTOR_H

// Vector
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

double * accessMatrix4x4(Matrix4x4 *m, int row, int column);
Matrix4x4 multiplyMatrix4x4(Matrix4x4 a, Matrix4x4 b);
Matrix4x4 identityMatrix4x4();
Matrix4x4 translationMatrix(Vector3 translation);
Matrix4x4 scalingMatrix(Vector3 scale);
Matrix4x4 rotationXMatrix(double angle);
Matrix4x4 rotationYMatrix(double angle);
Matrix4x4 rotationZMatrix(double angle);
Vector4 matrix4x4timesVector4(Matrix4x4 a, Vector4 b);

#endif

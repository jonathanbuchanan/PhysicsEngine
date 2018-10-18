#include "vector.h"

#include <stdlib.h>
#include <math.h>

double * accessVector3(Vector3 *v, int row) {
  if (row == 0) { return &v->x; }
  else if (row == 1) { return &v->y; }
  else if (row == 2) { return &v->x; }
  else { return NULL; }
}

Vector3 addVector3(Vector3 a, Vector3 b) {
  return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 subtractVector3(Vector3 a, Vector3 b) {
  return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

double dotProduct(Vector3 a, Vector3 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vector3 crossProduct(Vector3 a, Vector3 b) {
  return (Vector3){(a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)};
}

double magnitudeVector3(Vector3 v) {
  return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

Vector3 vec3(double x, double y, double z) {
  return (Vector3){x, y, z};
}



double * accessVector4(Vector4 *v, int row) {
  if (row == 0) { return &v->x; }
  else if (row == 1) { return &v->y; }
  else if (row == 2) { return &v->z; }
  else if (row == 3) { return &v->w; }
  else { return NULL; }
}

Vector4 addVector4(Vector4 a, Vector4 b) {
  return (Vector4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

Vector4 subtractVector4(Vector4 a, Vector4 b) {
  return (Vector4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

double dotProduct4(Vector4 a, Vector4 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

double magnitudeVector4(Vector4 v) {
  return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}



double * accessMatrix4x4(Matrix4x4 *m, int row, int column) {
  if (row == 0 && column == 0) { return &m->a11; }
  else if (row == 0 && column == 1) { return &m->a12; }
  else if (row == 0 && column == 2) { return &m->a13; }
  else if (row == 0 && column == 3) { return &m->a14; }
  else if (row == 1 && column == 0) { return &m->a21; }
  else if (row == 1 && column == 1) { return &m->a22; }
  else if (row == 1 && column == 2) { return &m->a23; }
  else if (row == 1 && column == 3) { return &m->a24; }
  else if (row == 2 && column == 0) { return &m->a31; }
  else if (row == 2 && column == 1) { return &m->a32; }
  else if (row == 2 && column == 2) { return &m->a33; }
  else if (row == 2 && column == 3) { return &m->a34; }
  else if (row == 3 && column == 0) { return &m->a41; }
  else if (row == 3 && column == 1) { return &m->a42; }
  else if (row == 3 && column == 2) { return &m->a43; }
  else if (row == 3 && column == 3) { return &m->a44; }
  else {
    // Error
    return NULL;
  } 
}

Matrix4x4 multiplyMatrix4x4(Matrix4x4 a, Matrix4x4 b) {
  Matrix4x4 result = {0};
  for (int col = 0; col < 4; ++col) {
    for (int row = 0; row < 4; ++row) {
      double total = 0;
      for (int i = 0; i < 4; ++i) {
        // Go across the row of a and down the column of b
        double aValue = *accessMatrix4x4(&a, row, i);
        double bValue = *accessMatrix4x4(&b, i, col);
        total += aValue * bValue;
      }
      double *output = accessMatrix4x4(&result, row, col);
      *output = total;
    }
  }
  return result;
}

Matrix4x4 identityMatrix4x4() {
  return (Matrix4x4){1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1};
}

Matrix4x4 translationMatrix(Vector3 translation) {
  return (Matrix4x4){1, 0, 0, translation.x,
                     0, 1, 0, translation.y,
                     0, 0, 1, translation.z,
                     0, 0, 0, 1};
}

Matrix4x4 scalingMatrix(Vector3 scale) {
  return (Matrix4x4){scale.x, 0, 0, 0,
                     0, scale.y, 0, 0,
                     0, 0, scale.z, 0,
                     0, 0, 0, 1};
}

Matrix4x4 rotationXMatrix(double angle) {
  return (Matrix4x4){1, 0, 0, 0,
                     0, cos(-angle), -sin(-angle), 0,
                     0, sin(-angle), cos(-angle), 0,
                     0, 0, 0, 1};
}

Matrix4x4 rotationYMatrix(double angle) {
  return (Matrix4x4){cos(-angle), 0, sin(-angle), 0,
                     0, 1, 0, 0,
                     -sin(-angle), 0, cos(-angle), 0,
                     0, 0, 0, 1};
}

Matrix4x4 rotationZMatrix(double angle) {
  return (Matrix4x4){cos(-angle), -sin(-angle), 0, 0,
                     sin(-angle), cos(-angle), 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1};
}

Vector4 matrix4x4timesVector4(Matrix4x4 a, Vector4 b) {
  Vector4 result = {0};
  for (int row = 0; row < 4; ++row) {
    double value = 0;
    for (int i = 0; i < 4; ++i) {
      double aValue = *accessMatrix4x4(&a, row, i);
      double bValue = *accessVector4(&b, i);
      value += aValue * bValue;
    }
    *accessVector4(&result, row) = value;
  }
  return result;
}

double tan(double x) {
  return sin(x) / cos(x);
}

double cotan(double x) {
  return 1 / tan(x);
}

Matrix4x4 perspectiveProjectionMatrix(double zNear, double zFar, double fovy, double aspect) {
  Matrix4x4 result = {0};
  double f = cotan(fovy / 2);
  result.a11 = f / aspect;
  result.a22 = f;
  result.a33 = (zFar + zNear) / (zNear - zFar);
  result.a34 = (2 * zFar * zNear) / (zNear - zFar);
  result.a43 = -1;
  return result;
}

Matrix4x4F matrix4x4toMatrix4x4F(Matrix4x4 m) {
  Matrix4x4F result;
  float *outArray = &result.a11;
  double *inArray = &m.a11;
  for (int i = 0; i < 16; ++i) {
    outArray[i] = (float)inArray[i];
  }
  return result;
}

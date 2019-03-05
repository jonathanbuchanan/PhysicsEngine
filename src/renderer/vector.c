#include "vector.h"

#include <stdlib.h>
#include <math.h>

// ## Vector2
Vector2 vec2(double x, double y) {
  return (Vector2){x, y};
}

double * access2(Vector2 *v, int row) {
  if (row == 0) { return &v->x; }
  else if (row == 1) { return &v->y; }
  else { return NULL; }
}

Vector2 add2(Vector2 a, Vector2 b) {
  return (Vector2){a.x + b.x, a.y + b.y};
}

Vector2 subtract2(Vector2 a, Vector2 b) {
  return (Vector2){a.x - b.x, a.y - b.y};
}

double dot2(Vector2 a, Vector2 b) {
  return (a.x * b.x) + (a.y * b.y);
}

Vector2 scalar2(Vector2 v, double s) {
  return (Vector2){v.x * s, v.y * s};
}

double magnitude2(Vector2 v) {
  return sqrt((v.x * v.x) + (v.y * v.y));
}

Vector2 normalize2(Vector2 v) {
  return scalar2(v, 1 / magnitude2(v));
}

// ## Vector3
Vector3 vec3(double x, double y, double z) {
  return (Vector3){x, y, z};
}

double * access3(Vector3 *v, int row) {
  if (row == 0) { return &v->x; }
  else if (row == 1) { return &v->y; }
  else if (row == 2) { return &v->z; }
  else { return NULL; }
}

Vector3 add3(Vector3 a, Vector3 b) {
  return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 subtract3(Vector3 a, Vector3 b) {
  return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

double dot3(Vector3 a, Vector3 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vector3 cross(Vector3 a, Vector3 b) {
  return (Vector3){(a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)};
}

Vector3 scalar3(Vector3 v, double s) {
  return (Vector3){v.x * s, v.y * s, v.z * s};
}

double magnitude3(Vector3 v) {
  return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

Vector3 normalize3(Vector3 v) {
  return scalar3(v, 1 / magnitude3(v));
}

// ## Vector4
Vector4 vec4(double x, double y, double z, double w) {
  return (Vector4){x, y, z, w};
}

double * access4(Vector4 *v, int row) {
  if (row == 0) { return &v->x; }
  else if (row == 1) { return &v->y; }
  else if (row == 2) { return &v->z; }
  else if (row == 3) { return &v->w; }
  else { return NULL; }
}

Vector4 add4(Vector4 a, Vector4 b) {
  return (Vector4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

Vector4 subtract4(Vector4 a, Vector4 b) {
  return (Vector4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

double dot4(Vector4 a, Vector4 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

Vector4 scalar4(Vector4 v, double s) {
  return (Vector4){v.x * s, v.y * s, v.z * s, v.w * s};
}

double magnitude4(Vector4 v) {
  return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

Vector4 normalize4(Vector4 v) {
  return scalar4(v, 1 / magnitude4(v));
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
      double bValue = *access4(&b, i);
      value += aValue * bValue;
    }
    *access4(&result, row) = value;
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

Matrix4x4 orthographicProjectionMatrix(double zNear, double zFar, double left, double right, double bottom, double top) {
  Matrix4x4 result = {0};
  result.a11 = 2 / (right - left);
  result.a14 = -1 * ((right + left) / (right - left));
  result.a22 = 2 / (top - bottom);
  result.a24 = -1 * ((top + bottom) / (top - bottom));
  result.a33 = -2 / (zFar - zNear);
  result.a34 = -1 * ((zFar + zNear) / (zFar - zNear));
  result.a44 = 1;
  return result;
}

Matrix4x4 lookAt(Vector3 eye, Vector3 center, Vector3 up) {
  Vector3 f = normalize3(subtract3(center, eye));
  Vector3 u = normalize3(up);
  Vector3 s = normalize3(cross(f, u));
  u = cross(s, f);

  Matrix4x4 result = {0};

  result.a11 = s.x;
  result.a12 = s.y;
  result.a13 = s.z;

  result.a21 = u.x;
  result.a22 = u.y;
  result.a23 = u.z;

  result.a31 = -f.x;
  result.a32 = -f.y;
  result.a33 = -f.z;

  result.a44 = 1;

  Matrix4x4 trans = translationMatrix(vec3(-eye.x, -eye.y, -eye.z));

  return multiplyMatrix4x4(result, trans);
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

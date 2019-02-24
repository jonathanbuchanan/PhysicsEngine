#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

typedef struct Camera {
  Vector3 position;
  Vector3 target;
  Vector3 up;
} Camera;

Vector3 cameraGetPosition(Camera *camera);
Vector3 cameraGetTarget(Camera *camera);
Vector3 cameraGetUp(Camera *camera);

void cameraSetPosition(Camera *camera, Vector3 position);
void cameraSetTarget(Camera *camera, Vector3 target);
void cameraSetUp(Camera *camera, Vector3 up);

Matrix4x4 getViewMatrix(Camera *camera);

#endif

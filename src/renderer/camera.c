#include "camera.h"

Vector3 cameraGetPosition(Camera *camera) {
  return camera->position;
}

Vector3 cameraGetTarget(Camera *camera) {
  return camera->target;
}

Vector3 cameraGetUp(Camera *camera) {
  return camera->up;
}

void cameraSetPosition(Camera *camera, Vector3 position) {
  camera->position = position;
}

void cameraSetTarget(Camera *camera, Vector3 target) {
  camera->target = target;
}

void cameraSetUp(Camera *camera, Vector3 up) {
  camera->up = up;
}

Matrix4x4 getViewMatrix(Camera *camera) {
  return lookAt(camera->position, camera->target, camera->up);
}

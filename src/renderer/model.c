#include "model.h"

#include "vector.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>

int loadModel(Model *model) {
  glGenVertexArrays(1, &model->vao);

  glGenBuffers(1, &model->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
  glBindVertexArray(model->vao);

  glBufferData(GL_ARRAY_BUFFER, model->vertices_n * sizeof(float), model->vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);

  return 0;
}

int drawModel(Model *model) {
  glBindVertexArray(model->vao);
  glDrawArrays(GL_TRIANGLES, 0, model->vertices_n);

  glBindVertexArray(0);
}

Matrix4x4 modelMatrix(Model *model) {
  Matrix4x4 translation = translationMatrix(model->position);
  Matrix4x4 rotX = rotationXMatrix(model->eulerRotation.x);
  Matrix4x4 rotY = rotationYMatrix(model->eulerRotation.y);
  Matrix4x4 rotZ = rotationZMatrix(model->eulerRotation.z);

  return MATMUL(MATMUL(MATMUL(translation, rotX), rotY), rotZ);
}



Vector3 sphericalToCartesian(float radius, float inclination, float azimuth) {
  return (Vector3){radius * sin(inclination) * cos(azimuth), radius * cos(inclination), radius * sin(inclination) * sin(azimuth)};
}

#include <stdio.h>
Model generateUVSphere(float radius, int latDivisions, int longDivisions) {
  Model model;
  model.vertices_n = 18 * latDivisions * longDivisions; // 6 * 3 * quads
  model.vertices = malloc(sizeof(float) * model.vertices_n);

  float deltaThetaLat = (2 * M_PI) / latDivisions;
  float deltaThetaLong = M_PI / longDivisions;
  int index = 0;
  for (int lat = 0; lat < latDivisions; ++lat) {
    float thetaLatMin = lat * deltaThetaLat;
    float thetaLatMax = (lat + 1) * deltaThetaLat;
    for (int long_ = 0; long_ < longDivisions; ++long_) {
      float thetaLongMin = (long_ * deltaThetaLong);
      float thetaLongMax = ((long_ + 1) * deltaThetaLong);

      // Four corners
      Vector3 bl = sphericalToCartesian(radius, thetaLongMin, thetaLatMin);
      Vector3 br = sphericalToCartesian(radius, thetaLongMin, thetaLatMax);
      Vector3 tl = sphericalToCartesian(radius, thetaLongMax, thetaLatMin);
      Vector3 tr = sphericalToCartesian(radius, thetaLongMax, thetaLatMax);

      // Two triangles
      float triangles[] = {
        bl.x, bl.y, bl.z,
        tl.x, tl.y, tl.z,
        tr.x, tr.y, tr.z,

        tr.x, tr.y, tr.z,
        br.x, br.y, br.z,
        bl.x, bl.y, bl.z
      };
      memcpy(&model.vertices[index], triangles, 18 * sizeof(float));
      index += 18;
    }
  }

  return model;
}

Model generateIcoSphere(float radius, int subdivisions) {
  Model model;
  return model;
}

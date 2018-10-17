#include "model.h"

#include "vector.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>

int loadModel(Model *model) {
  glGenVertexArrays(1, &model->vao);
  glBindVertexArray(model->vao);

  glGenBuffers(1, &model->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, model->vbo);

  glGenBuffers(1, &model->ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ebo);

  glBufferData(GL_ARRAY_BUFFER, model->vertices_n * sizeof(float), model->vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indices_n * sizeof(unsigned int), model->indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);

  return 0;
}

int drawModel(Model *model) {
  glBindVertexArray(model->vao);
  glDrawElements(GL_TRIANGLES, model->indices_n, GL_UNSIGNED_INT, 0);
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
  int longVertices = longDivisions + 1;

  Model model;

  model.vertices_n = 3 * latDivisions * longVertices;
  model.vertices = malloc(sizeof(float) * model.vertices_n);

  model.indices_n = 6 * latDivisions * longDivisions;
  model.indices = malloc(sizeof(unsigned int) * model.indices_n);

  float deltaThetaLat = (2 * M_PI) / latDivisions;
  float deltaThetaLong = M_PI / longDivisions;

  // Vertices
  for (int lat = 0; lat < latDivisions; ++lat) {
    float thetaLat = lat * deltaThetaLat;
    for (int long_ = 0; long_ < longVertices; ++long_) {
      float thetaLong = long_ * deltaThetaLong;

      Vector3 vertex = sphericalToCartesian(radius, thetaLong, thetaLat);

      float coordinates[] = {
        vertex.x, vertex.y, vertex.z
      };

      memcpy(&model.vertices[((lat * longVertices) + long_) * 3], coordinates, 3 * sizeof(float));
    }
  }

  // Indices
  int index = 0;

  for (int lat = 0; lat < latDivisions; ++lat) {
    int latMin = lat;
    int latMax = (lat + 1) % latDivisions;
    for (int long_ = 0; long_ < longDivisions; ++long_) {
      int longMin = long_;
      int longMax = long_ + 1;

      // Four corners
      unsigned int bl = ((latMin * longVertices) + longMin);
      unsigned int br = ((latMax * longVertices) + longMin);
      unsigned int tl = ((latMin * longVertices) + longMax);
      unsigned int tr = ((latMax * longVertices) + longMax);

      // Two triangles
      unsigned int triangles[] = {
        bl, tl, tr,
        tr, br, bl
      };
      memcpy(&model.indices[index], triangles, 6 * sizeof(unsigned int));
      index += 6;
    }
  }

  return model;
}

Model generateIcoSphere(float radius, int subdivisions) {
  Model model;
  return model;
}

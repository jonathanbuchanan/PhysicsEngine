#include "model.h"

#include "vector.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>

int loadModel(Model *model) {
  glGenVertexArrays(1, &model->mesh.vao);
  glBindVertexArray(model->mesh.vao);

  glGenBuffers(1, &model->mesh.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, model->mesh.vbo);

  glGenBuffers(1, &model->mesh.ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->mesh.ebo);

  glBufferData(GL_ARRAY_BUFFER, model->vertices_n * sizeof(float), model->vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indices_n * sizeof(unsigned int), model->indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);

  return 0;
}

int drawModel(Model *model) {
  glBindVertexArray(model->mesh.vao);
  glDrawElements(GL_TRIANGLES, model->indices_n, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  return 0;
}

int freeModel(Model *model) {
  glDeleteBuffers(1, &model->mesh.vbo);
  glDeleteBuffers(1, &model->mesh.ebo);

  free(model->vertices);
  free(model->indices);

  glDeleteVertexArrays(1, &model->mesh.vao);

  return 0;
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

Vector3 midpoint(Vector3 a, Vector3 b) {
  return (Vector3){(a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2};
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

  float phi = (1 + sqrt(5)) / 2;

  model.vertices_n = 3 * 12;
  model.vertices = malloc(sizeof(float) * 3 * (12 + (20 * (int)(pow(4, subdivisions)))));
  float vertices[] = {
    -1, phi, 0,
    1, phi, 0,
    -1, -phi, 0,
    1, -phi, 0,

    0, -1, phi,
    0, 1, phi,
    0, -1, -phi,
    0, 1, -phi,

    phi, 0, -1,
    phi, 0, 1,
    -phi, 0, -1,
    -phi, 0, 1
  };
  memcpy(model.vertices, vertices, 3 * 12 * sizeof(float));

  int index = 0;
  for (int i = 0; i < 12; ++i) {
    Vector3 vertex = vec3(model.vertices[index], model.vertices[index + 1], model.vertices[index + 2]);
    double magnitude = magnitudeVector3(vertex);
    vertex = vec3(vertex.x / magnitude, vertex.y / magnitude, vertex.z / magnitude);
    model.vertices[index] = vertex.x;
    model.vertices[index + 1] = vertex.y;
    model.vertices[index + 2] = vertex.z;
    index += 3;
  }

  model.indices_n = 3 * 20;
  model.indices = malloc(sizeof(unsigned int) * 3 * 20 * (int)(pow(4, subdivisions)));
  unsigned int indices[] = {
    0, 11, 5,
    0, 5, 1,
    0, 1, 7,
    0, 7, 10,
    0, 10, 11,

    1, 5, 9,
    5, 11, 4,
    11, 10, 2,
    10, 7, 6,
    7, 1, 8,

    3, 9, 4,
    3, 4, 2,
    3, 2, 6,
    3, 6, 8,
    3, 8, 9,

    4, 9, 5,
    2, 4, 11,
    6, 2, 10,
    8, 6, 7,
    9, 8, 1
  };
  memcpy(model.indices, indices, 3 * 20 * sizeof(unsigned int));

  int vertices_index = 12;
  // Subdivide and form the triangles
  for (int i = 0; i < subdivisions; ++i) {
    int indices_index = 0;
    unsigned int *subdivision_indices = malloc(sizeof(unsigned int) * 3 * 20 * (int)(pow(4, i + 1)));

    // Iterate through the triangles
    for (int t = 0; t < model.indices_n / 3; ++t) {
      // Find the midpoint of each edge
      unsigned int a_index = model.indices[t * 3];
      Vector3 a = vec3(model.vertices[a_index * 3], model.vertices[(a_index * 3) + 1], model.vertices[(a_index * 3) + 2]);

      unsigned int b_index = model.indices[(t * 3) + 1];
      Vector3 b = vec3(model.vertices[b_index * 3], model.vertices[(b_index * 3) + 1], model.vertices[(b_index * 3) + 2]);

      unsigned int c_index = model.indices[(t * 3) + 2];
      Vector3 c = vec3(model.vertices[c_index * 3], model.vertices[(c_index * 3) + 1], model.vertices[(c_index * 3) + 2]);

      unsigned int ab_index = vertices_index;
      Vector3 ab = midpoint(a, b);

      unsigned int ac_index = vertices_index + 1;
      Vector3 ac = midpoint(a, c);

      unsigned int bc_index = vertices_index + 2;
      Vector3 bc = midpoint(b, c);

      // Add the 3 new vertices
      float new_vertices[] = {
        ab.x, ab.y, ab.z,
        ac.x, ac.y, ac.z,
        bc.x, bc.y, bc.z
      };
      memcpy(&model.vertices[vertices_index * 3], new_vertices, 3 * 3 * sizeof(float));
      vertices_index += 3;

      // Add the new indices (4 triangles)
      unsigned int new_indices[] = {
        a_index, ab_index, ac_index,
        ab_index, b_index, bc_index,
        ac_index, bc_index, c_index,
        ab_index, ac_index, bc_index
      };
      memcpy(&subdivision_indices[indices_index], new_indices, 3 * 4 * sizeof(unsigned int));
      indices_index += 12;
    }
    model.indices_n = indices_index;
    model.vertices_n = vertices_index * 3;

    memcpy(model.indices, subdivision_indices, 3 * 20 * (int)(pow(4, i + 1)) * sizeof(unsigned int));

    // Make all vertices lie on the sphere
    index = 0;
    for (int i = 0; i < model.vertices_n / 3; ++i) {
      Vector3 vertex = vec3(model.vertices[index], model.vertices[index + 1], model.vertices[index + 2]);
      double magnitude = magnitudeVector3(vertex);
      vertex = vec3(vertex.x / magnitude, vertex.y / magnitude, vertex.z / magnitude);
      model.vertices[index] = vertex.x;
      model.vertices[index + 1] = vertex.y;
      model.vertices[index + 2] = vertex.z;
      index += 3;
    }
  }

  return model;
}


Shape generateQuad() {
  Shape q;

  // x, y, u, v
  const float quad_vertices[] = {
    0.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 0.0,
    1.0, 0.0, 1.0, 1.0
  };

  const unsigned int quad_indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  q.vertices = malloc(sizeof(quad_vertices));
  q.vertices_n = 16;
  memcpy(q.vertices, quad_vertices, sizeof(float) * q.vertices_n);

  q.indices = malloc(sizeof(quad_indices));
  q.indices_n = 6;
  memcpy(q.indices, quad_indices, sizeof(unsigned int) * q.indices_n);

  return q;
}

int loadShape(Shape *s) {
  glGenVertexArrays(1, &s->mesh.vao);
  glBindVertexArray(s->mesh.vao);

  glGenBuffers(1, &s->mesh.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, s->mesh.vbo);

  glGenBuffers(1, &s->mesh.ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s->mesh.ebo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * s->vertices_n, s->vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * s->indices_n, s->indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  return 0;
}

int freeShape(Shape *s) {
  glDeleteBuffers(1, &s->mesh.vbo);
  glDeleteBuffers(1, &s->mesh.ebo);
  glDeleteVertexArrays(1, &s->mesh.vao);

  return 0;
}

int drawShape(Shape *s) {
  glBindVertexArray(s->mesh.vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
 

  return 0;
}

Matrix4x4 shapeModelMatrix(Shape *s) {
  Matrix4x4 scale = scalingMatrix(vec3(s->size.x, s->size.y, 0.0));
  Matrix4x4 translation = translationMatrix(vec3(s->position.x, s->position.y, 0.0));

  return MATMUL(translation, scale);
}

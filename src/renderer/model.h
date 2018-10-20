#ifndef MODEL_H
#define MODEL_H

#include "vector.h"

// A 3D model
typedef struct Model {
  float *vertices;
  int vertices_n;

  unsigned int *indices;
  unsigned int indices_n;

  unsigned int vbo;
  unsigned int vao;
  unsigned int ebo;

  Vector3 position;
  Vector3 eulerRotation;
} Model;

// Loads the model data into OpenGL buffers
int loadModel(Model *model);

// Frees the model data
int freeModel(Model *model);

// Renders the model
int drawModel(Model *model);

// Generates the model matrix from the transformations stored in the model
Matrix4x4 modelMatrix(Model *model);



// Generates a sphere along latitude and longitude
Model generateUVSphere(float radius, int latDivisions, int longDivisions);

// Generates a sphere by subdividing an icosahedron and projecting each point onto the sphere
Model generateIcoSphere(float radius, int subdivisions);


typedef struct Quad {
  unsigned int vbo;
  unsigned int vao;
  unsigned int ebo;

  Vector2 size;
  Vector2 position;
} Quad;

// Creates a quad and loads it into memory
Quad generateQuad();

// Frees the quad buffers
int freeQuad(Quad *q);

// Draws the quad
int drawQuad2D(Quad *q);

// Generates the model matrix for the quad
Matrix4x4 quadModelMatrix(Quad *q);

#endif

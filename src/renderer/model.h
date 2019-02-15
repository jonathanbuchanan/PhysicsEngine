#ifndef MODEL_H
#define MODEL_H

#include "vector.h"

// An object containing a VAO, VBO, and EBO
typedef struct Mesh {
  unsigned int vbo;
  unsigned int vao;
  unsigned int ebo;
} Mesh;

// A 3D model
typedef struct Model {
  float *vertices;
  int vertices_n;

  unsigned int *indices;
  int indices_n;

  Mesh mesh;

  Vector3 position;
  Vector3 eulerRotation;
  Vector3 scale;
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

// Generates a cube (size = side_length / 2)
Model generateCube(float size);


// A 2D shape
typedef struct Shape {
  float *vertices;
  int vertices_n;

  unsigned int *indices;
  int indices_n;

  Mesh mesh;

  Vector2 size;
  Vector2 position;
} Shape;

// Creates a quad
Shape generateQuad();

// Loads the shape into buffers
int loadShape(Shape *s);

// Frees the quad buffers
int freeShape(Shape *s);

// Draws the quad
int drawShape(Shape *s);

// Generates the model matrix for the quad
Matrix4x4 shapeModelMatrix(Shape *s);

#endif

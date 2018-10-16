#ifndef MODEL_H
#define MODEL_H

typedef struct Model {
  float *vertices;
  int vertices_n;
} Model;

// Generates a sphere along latitude and longitude
Model generateUVSphere(float radius, int latDivisions, int longDivisions);

// Generates a sphere by subdividing an icosahedron and projecting each point onto the sphere
Model generateIcoSphere(float radius, int subdivisions);

#endif

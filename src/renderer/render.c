#include "render.h"
#include "vector.h"
#include "model.h"

#include <stdlib.h>
#include <stdio.h>

float vertices[] = {
  -0.5, -0.5, 0.0,
  -0.5, 0.5, 0.0,
  0.5, -0.5, 0.0,
};

float cube[] = {
  -1.0, -1.0, 1.0,
  -1.0, 1.0, 1.0,
  1.0, -1.0, 1.0,

  1.0, -1.0, 1.0,
  1.0, 1.0, 1.0,
  -1.0, 1.0, 1.0,


  -1.0, 1.0, 1.0,
  1.0, 1.0, 1.0,
  1.0, 1.0, -1.0,

  1.0, 1.0, -1.0,
  -1.0, 1.0, -1.0,
  -1.0, 1.0, 1.0,


  -1.0, -1.0, 1.0,
  1.0, -1.0, 1.0,
  1.0, -1.0, -1.0,

  1.0, -1.0, -1.0,
  -1.0, -1.0, -1.0,
  -1.0, -1.0, 1.0,


  -1.0, -1.0, -1.0,
  -1.0, 1.0, -1.0,
  1.0, -1.0, -1.0,

  1.0, -1.0, -1.0,
  1.0, 1.0, -1.0,
  -1.0, 1.0, -1.0,


  -1.0, -1.0, 1.0,
  -1.0, 1.0, 1.0,
  -1.0, 1.0, -1.0,

  -1.0, 1.0, -1.0,
  -1.0, -1.0, -1.0,
  -1.0, -1.0, 1.0,


  1.0, -1.0, 1.0,
  1.0, 1.0, 1.0,
  1.0, 1.0, -1.0,

  1.0, 1.0, -1.0,
  1.0, -1.0, -1.0,
  1.0, -1.0, 1.0
};

static const char* vertex_shader_text =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(pos, 1.0);\n"
"    color = pos;\n"
"}\n";

static const char* fragment_shader_text =
"#version 330 core\n"
"in vec3 color;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(color, 1.0);\n"
"}\n";



Model sphere;

RenderInfo * createRenderer(GLFWwindow *window) {
  glfwMakeContextCurrent(window);

  RenderInfo *renderer = malloc(sizeof(RenderInfo));

  glEnable(GL_DEPTH_TEST);

  GLuint vao;
  glGenVertexArrays(1, &vao);

  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  glCompileShader(vertex_shader);
  int success;
  char infoLog[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
    printf("Vertex Shader Error: %s\n", infoLog);
  } else {
    printf("Vertex Shader Compiled\n");
  }

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
    printf("Fragment Shader Error: %s\n", infoLog);
  } else {
    printf("Fragment Shader Compiled\n");
  }

  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  sphere = generateUVSphere(1.0, 32, 16);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);
  glBufferData(GL_ARRAY_BUFFER, sphere.vertices_n * sizeof(float), sphere.vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);

  renderer->shaderProgram = program;
  renderer->vbo = vbo;
  renderer->vao = vao;

  return renderer;
}

double step = 0.0;
void render(GLFWwindow *window, RenderInfo *renderer) {
  glfwMakeContextCurrent(window);

  // Set the viewport
  int height, width;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  // Clear
  clear(window);

  // Transform
  Matrix4x4 scale = scalingMatrix(vec3(0.2, 0.2, 0.2));
  Matrix4x4 rot1 = rotationYMatrix(step * 0.5);
  Matrix4x4 rot2 = rotationZMatrix(step * 2);
  step += 0.01;
  Matrix4x4F model = matrix4x4toMatrix4x4F(multiplyMatrix4x4(multiplyMatrix4x4(scale, rot1), rot2));
  unsigned int modelL = glGetUniformLocation(renderer->shaderProgram, "model");
  glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

  Matrix4x4F view = matrix4x4toMatrix4x4F(translationMatrix(vec3(0.0, 0.0, -2.0)));
  unsigned int viewL = glGetUniformLocation(renderer->shaderProgram, "view");
  glUniformMatrix4fv(viewL, 1, GL_TRUE, (GLfloat *)&view.a11);

  Matrix4x4F projection = matrix4x4toMatrix4x4F(perspectiveProjectionMatrix(0.1, 100.0, DEGREES_TO_RADIANS(45.0), (double)(640.0 / 480.0)));
  unsigned int projectionL = glGetUniformLocation(renderer->shaderProgram, "projection");
  glUniformMatrix4fv(projectionL, 1, GL_TRUE, (GLfloat *)&projection.a11);

  // Draw
  glUseProgram(renderer->shaderProgram);
  glBindVertexArray(renderer->vao);
  glDrawArrays(GL_TRIANGLES, 0, sphere.vertices_n); 

  // Swap the buffers
  swapBuffers(window);
  glfwPollEvents();
}

void clear(GLFWwindow *window) {
  glfwMakeContextCurrent(window);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void swapBuffers(GLFWwindow *window) {
  glfwSwapBuffers(window);
}

void setClearColor(GLFWwindow *window, float red, float green, float blue, float alpha) {
  glfwMakeContextCurrent(window);
  glClearColor(red, green, blue, alpha);
}


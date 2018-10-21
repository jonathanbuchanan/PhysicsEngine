#include "render.h"
#include "vector.h"
#include "model.h"

#include <stdlib.h>
#include <stdio.h>

static const char *vertex_shader_3D =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec3 color;\n"
"void main() {\n"
"    gl_Position = projection * view * model * vec4(pos, 1.0);\n"
"    color = pos;\n"
"}\n";

static const char *fragment_shader_3D =
"#version 330 core\n"
"in vec3 color;\n"
"out vec4 FragColor;\n"
"void main() {\n"
"    FragColor = vec4((color / 2) + vec3(0.5, 0.5, 0.5), 1.0);\n"
"}\n";



static const char *vertex_shader_2D =
"#version 330 core\n"
"layout (location = 0) in vec2 pos;\n"
"uniform mat4 model;\n"
"void main() {\n"
"    gl_Position = model * vec4(pos, 0.0, 1.0);\n"
"}\n";

static const char *fragment_shader_2D =
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main() {\n"
"    FragColor = color;\n"
"}\n";



ShaderProgram compileShader(const char *vertex_shader_source, const char *fragment_shader_source) {
  GLuint vertex_shader, fragment_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);

  glCompileShader(vertex_shader);
  glCompileShader(fragment_shader);

  int success;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    printf("Vertex shader error\n");
    return -1;
  }
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    printf("Fragment shader error\n");
    return -1;
  }

  ShaderProgram program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  return program;
}

Control button;
RenderInfo * createRenderer(GLFWwindow *window) {
  glfwMakeContextCurrent(window);

  RenderInfo *renderer = malloc(sizeof(RenderInfo));

  renderer->window = window;

  glEnable(GL_DEPTH_TEST);

  GLuint vao;
  glGenVertexArrays(1, &vao);

  ShaderProgram shader3D = compileShader(vertex_shader_3D, fragment_shader_3D);
  if (shader3D == -1) {
    printf("Error compiling 3D shader\n");
  } else {
    renderer->shader3D = shader3D;
  }

  ShaderProgram shader2D = compileShader(vertex_shader_2D, fragment_shader_2D);
  if (shader2D == -1) {
    printf("Error compiling 2D shader\n");
  } else {
    renderer->shader2D = shader2D;
  }

  renderer->model = generateIcoSphere(1.0, 3);
  loadModel(&renderer->model);

  renderer->quad2D = generateQuad();
  loadShape(&renderer->quad2D);

  renderer->menu = createMenu();
  button = createButton(vec2(100.0, 100.0), vec2(0.0, 0.0));
  addControlToMenu(&renderer->menu, &button);

  return renderer;
}

void freeRenderer(RenderInfo *renderer) {
  freeModel(&renderer->model);
}

double step = 0.0;
void render(RenderInfo *renderer) {
  GLFWwindow *window = renderer->window;

  glfwMakeContextCurrent(window);

  // Set the viewport
  int height, width;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  // Clear
  clear(window);

  // Draw
  glUseProgram(renderer->shader3D);

  renderer->model.position = vec3(0.0, 2.0 * sin(step), -3.0);
  renderer->model.eulerRotation = vec3(step, 0.5 * step, 2.0 * step);
  step += 0.01;
  Matrix4x4F model = matrix4x4toMatrix4x4F(modelMatrix(&renderer->model));
  unsigned int modelL = glGetUniformLocation(renderer->shader3D, "model");
  glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

  Matrix4x4F view = matrix4x4toMatrix4x4F(translationMatrix(vec3(0.0, 0.0, -2.0)));
  unsigned int viewL = glGetUniformLocation(renderer->shader3D, "view");
  glUniformMatrix4fv(viewL, 1, GL_TRUE, (GLfloat *)&view.a11);

  Matrix4x4F projection = matrix4x4toMatrix4x4F(perspectiveProjectionMatrix(0.1, 100.0, DEGREES_TO_RADIANS(45.0), (double)(640.0 / 480.0)));
  unsigned int projectionL = glGetUniformLocation(renderer->shader3D, "projection");
  glUniformMatrix4fv(projectionL, 1, GL_TRUE, (GLfloat *)&projection.a11);

  drawModel(&renderer->model);



  ((Button *)button.control)->color = vec4(fabs(sin(step * 0.4)), fabs(cos(step * 0.2)), fabs(sin(step * 0.55)), 1.0);

  glUseProgram(renderer->shader2D);

  drawMenu(&renderer->menu, renderer);

  // Swap the buffers
  swapBuffers(window);
  glfwPollEvents();
}

void renderQuad(RenderInfo *renderer, Vector2 size, Vector2 position, Vector4 color) {
  glUseProgram(renderer->shader2D);

  renderer->quad2D.size = size;
  renderer->quad2D.position = position;

  Matrix4x4F model = matrix4x4toMatrix4x4F(shapeModelMatrix(&renderer->quad2D));
  unsigned int modelL = glGetUniformLocation(renderer->shader2D, "model");
  glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

  unsigned int colorL = glGetUniformLocation(renderer->shader2D, "color");
  glUniform4f(colorL, color.x, color.y, color.z, color.w);

  drawShape(&renderer->quad2D);
}

Vector2 getWindowSize(const RenderInfo *renderer) {
  int width, height;
  glfwGetWindowSize(renderer->window, &width, &height);
  return (Vector2){(double)width, (double)height};
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


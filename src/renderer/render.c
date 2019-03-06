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
"void main() {\n"
"    gl_Position = projection * view * model * vec4(pos, 1.0);\n"
"}\n";

static const char *fragment_shader_3D =
"#version 330 core\n"
"uniform vec3 color;\n"
"out vec4 FragColor;\n"
"void main() {\n"
"    FragColor = vec4(color, 1.0);\n"
"}\n";



static const char *vertex_shader_2D =
"#version 330 core\n"
"layout (location = 0) in vec2 pos;\n"
"uniform mat4 model;\n"
"uniform mat4 projection;\n"
"uniform float zPosition;\n"
"void main() {\n"
"    gl_Position = projection * model * vec4(pos, 0.0, 1.0);\n"
"    gl_Position.z = -zPosition;\n"
"}\n";

static const char *fragment_shader_2D =
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main() {\n"
"    FragColor = color;\n"
"}\n";



static const char *vertex_shader_2D_textured =
"#version 330 core\n"
"layout (location = 0) in vec2 pos;\n"
"layout (location = 1) in vec2 textureCoordinates;\n"
"uniform mat4 model;\n"
"uniform mat4 projection;\n"
"uniform float zPosition;\n"
"out vec2 texCoords;\n"
"void main() {\n"
"    gl_Position = projection * model * vec4(pos, 0.0, 1.0);\n"
"    gl_Position.z = -zPosition;\n"
"    texCoords = textureCoordinates;\n"
"}\n";

static const char *fragment_shader_2D_textured =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 texCoords;\n"
"uniform sampler2D text;\n"
"uniform vec4 color;\n"
"void main() {\n"
"    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);\n"
"    FragColor = color * sampled;\n"
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



void checkKeys(RenderInfo *renderer) {
  for (int i = 0; i < renderer->input.callbacks_n; ++i) {
    int key = renderer->input.chars[i];
    int action = renderer->input.actions[i];
    int previousState = renderer->input.keystates[key];
    int state = glfwGetKey(renderer->window, key);
    if (previousState == 0 && state == 1 && action == Press) renderer->input.callbacks[i](renderer, key);
    if (previousState == 1 && state == 0 && action == Release) renderer->input.callbacks[i](renderer, key);
    if (previousState == 1 && state == 1 && action == Repeat) renderer->input.callbacks[i](renderer, key);
  }
  for (int i = LOWEST_KEY; i < HIGHEST_KEY; ++i) {
    renderer->input.keystates[i] = glfwGetKey(renderer->window, i);
  }
}

void windowResizeCallback(GLFWwindow *window, int width, int height) {
  // Resize menus
  RenderInfo *renderer = (RenderInfo *)glfwGetWindowUserPointer(window);

  renderer->resizeCallback(renderer, width, height);
}

Control button;
Control label;
RenderInfo * createRenderer(GLFWwindow *window) {
  glfwMakeContextCurrent(window);

  glfwSetWindowSizeCallback(window, windowResizeCallback);

  RenderInfo *renderer = malloc(sizeof(RenderInfo));

  renderer->input.chars = NULL;
  renderer->input.actions = NULL;
  renderer->input.callbacks = NULL;
  renderer->input.callbacks_n = 0;

  glfwSetWindowUserPointer(window, renderer);

  renderer->window = window;

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

  ShaderProgram shader2DTextured = compileShader(vertex_shader_2D_textured, fragment_shader_2D_textured);
  if (shader2DTextured == -1) {
    printf("Error compiling 2D-Textured shader\n");
  } else {
    renderer->shader2DTextured = shader2DTextured;
  }

  renderer->camera.position = vec3(0.0, 0.0, -10.0);
  renderer->camera.target = vec3(0.0, 0.0, 0.0);
  renderer->camera.up = vec3(0.0, 1.0, 0.0);

  renderer->sphere = generateIcoSphere(1.0, 2);
  loadModel(&renderer->sphere);

  renderer->cube = generateCube(1.0);
  loadModel(&renderer->cube);

  renderer->quad2D = generateQuad();
  loadShape(&renderer->quad2D);

  renderer->textRenderer = initTextRenderer();

  return renderer;
}

Camera * getCamera(RenderInfo *renderer) {
  return &renderer->camera;
}

void freeRenderer(RenderInfo *renderer) {
  freeModel(&renderer->sphere);
  freeShape(&renderer->quad2D);

  destroyTextRenderer(&renderer->textRenderer);
}

void beginRender(RenderInfo *renderer) {
  GLFWwindow *window = renderer->window;

  glfwMakeContextCurrent(window);

  checkKeys(renderer);

  // Set the viewport
  int height, width;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  // Clear
  clear(window);
}

void endRender(RenderInfo *renderer) {
  GLFWwindow *window = renderer->window;

  swapBuffers(window);
  glfwPollEvents();
}

void renderSphere(RenderInfo *renderer, float radius, Vector3 color, Vector3 position) {
  // Draw
  glUseProgram(renderer->shader3D);

  int height, width;
  glfwGetFramebufferSize(renderer->window, &width, &height);
  glViewport(0, 0, width, height);

  renderer->sphere.position = position;
  renderer->sphere.scale = vec3(radius, radius, radius);

  Matrix4x4F model = matrix4x4toMatrix4x4F(modelMatrix(&renderer->sphere));
  unsigned int modelL = glGetUniformLocation(renderer->shader3D, "model");
  glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

  Matrix4x4F view = matrix4x4toMatrix4x4F(getViewMatrix(&renderer->camera));
  unsigned int viewL = glGetUniformLocation(renderer->shader3D, "view");
  glUniformMatrix4fv(viewL, 1, GL_TRUE, (GLfloat *)&view.a11);

  Matrix4x4F projection = matrix4x4toMatrix4x4F(perspectiveProjectionMatrix(0.1, 100.0, DEGREES_TO_RADIANS(45.0), (double)(width) / (double)(height)));
  unsigned int projectionL = glGetUniformLocation(renderer->shader3D, "projection");
  glUniformMatrix4fv(projectionL, 1, GL_TRUE, (GLfloat *)&projection.a11);

  unsigned int colorL = glGetUniformLocation(renderer->shader3D, "color");
  glUniform3f(colorL, color.x, color.y, color.z);

  drawModel(&renderer->sphere);
}

void renderQuad(RenderInfo *renderer, Vector2 size, Vector2 position, Vector4 color, double z) {
  glUseProgram(renderer->shader2D);

  renderer->quad2D.size = size;
  renderer->quad2D.position = position;

  Vector2 windowSize = getWindowSize(renderer);

  Matrix4x4F model = matrix4x4toMatrix4x4F(shapeModelMatrix(&renderer->quad2D));
  unsigned int modelL = glGetUniformLocation(renderer->shader2D, "model");
  glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

  Matrix4x4F projection = matrix4x4toMatrix4x4F(orthographicProjectionMatrix(-1.0, 1.0, 0.0, windowSize.x, 0.0, windowSize.y));
  unsigned int projectionL = glGetUniformLocation(renderer->shader2D, "projection");
  glUniformMatrix4fv(projectionL, 1, GL_TRUE, (GLfloat *)&projection.a11);

  unsigned int zPositionL = glGetUniformLocation(renderer->shader2D, "zPosition");
  glUniform1f(zPositionL, z);

  unsigned int colorL = glGetUniformLocation(renderer->shader2D, "color");
  glUniform4f(colorL, color.x, color.y, color.z, color.w);

  drawShape(&renderer->quad2D);
}

void renderMenu(RenderInfo *renderer, Menu *menu) {
  drawMenu(menu, renderer);
}

void renderOrientation(RenderInfo *renderer) {
  // Data
  char *labels[] = {"X", "Y", "Z"};
  Vector3 axes[] = {vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0)};
  Vector3 colors[] = {vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0)};

  Vector2 windowSize = getWindowSize(renderer);

  // Draw
  for (int i = 0; i < 3; ++i) {
    char *label = labels[i];
    Vector3 axis = axes[i];
    Vector3 color = colors[i];

    glUseProgram(renderer->shader3D);

    int height, width;
    glfwGetFramebufferSize(renderer->window, &width, &height);
    glViewport(0, 0, width, height);

    float aspectRatio = height / width;

    renderer->cube.position = vec3(0.0, 0.0, 0.0);
    renderer->cube.eulerRotation = vec3(0.0, 0.0, 0.0);
    if (i == 0) {
      renderer->cube.scale = vec3(0.5, 0.01, 0.01);
      renderer->cube.position = vec3(0.5, 0.0, 0.0);
    } else if (i == 1) {
      renderer->cube.scale = vec3(0.01, 0.5, 0.01);
      renderer->cube.position = vec3(0.0, 0.5, 0.0);
    } else if (i == 2) {
      renderer->cube.scale = vec3(0.01, 0.01, 0.5);
      renderer->cube.position = vec3(0.0, 0.0, 0.5);
    }

    Matrix4x4F model = matrix4x4toMatrix4x4F(modelMatrix(&renderer->cube));
    unsigned int modelL = glGetUniformLocation(renderer->shader3D, "model");
    glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

    Vector3 orientation = subtract3(renderer->camera.target, renderer->camera.position);
    Matrix4x4 camera = lookAt(orientation, vec3(0.0, 0.0, 0.0), renderer->camera.up);
    Matrix4x4F view = matrix4x4toMatrix4x4F(camera);
    unsigned int viewL = glGetUniformLocation(renderer->shader3D, "view");
    glUniformMatrix4fv(viewL, 1, GL_TRUE, (GLfloat *)&view.a11);

    Matrix4x4F projection = matrix4x4toMatrix4x4F(multiplyMatrix4x4(multiplyMatrix4x4(orthographicProjectionMatrix(-3.0, 3.0, -1.0, 1.0, -1.0, 1.0), scalingMatrix(vec3(0.1/* * aspectRatio*/, 0.1, 0.0))), translationMatrix(vec3(9.0, 9.0, 0.0))));
    unsigned int projectionL = glGetUniformLocation(renderer->shader3D, "projection");
    glUniformMatrix4fv(projectionL, 1, GL_TRUE, (GLfloat *)&projection.a11);

    unsigned int colorL = glGetUniformLocation(renderer->shader3D, "color");
    glUniform3f(colorL, color.x, color.y, color.z);

    drawModel(&renderer->cube);
  }
}

void renderGrid(RenderInfo *renderer) {
  // Data
  char *labels[] = {"X", "Y", "Z"};
  Vector3 axes[] = {vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0)};
  Vector3 colors[] = {vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0)};

  Vector2 windowSize = getWindowSize(renderer);

  // Draw Major Axes
  for (int i = 0; i < 3; ++i) {
    char *label = labels[i];
    Vector3 axis = axes[i];
    Vector3 color = colors[i];

    renderer->cube.position = vec3(0.0, 0.0, 0.0);
    renderer->cube.eulerRotation = vec3(0.0, 0.0, 0.0);
    if (i == 0) {
      renderer->cube.scale = vec3(10.0, 0.01, 0.01);
    } else if (i == 1) {
      renderer->cube.scale = vec3(0.01, 10.0, 0.01);
    } else if (i == 2) {
      renderer->cube.scale = vec3(0.01, 0.01, 10.0);
    }

    // Draw
    glUseProgram(renderer->shader3D);

    int height, width;
    glfwGetFramebufferSize(renderer->window, &width, &height);
    glViewport(0, 0, width, height);

    Matrix4x4F model = matrix4x4toMatrix4x4F(modelMatrix(&renderer->cube));
    unsigned int modelL = glGetUniformLocation(renderer->shader3D, "model");
    glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

    Matrix4x4F view = matrix4x4toMatrix4x4F(getViewMatrix(&renderer->camera));
    unsigned int viewL = glGetUniformLocation(renderer->shader3D, "view");
    glUniformMatrix4fv(viewL, 1, GL_TRUE, (GLfloat *)&view.a11);

    Matrix4x4F projection = matrix4x4toMatrix4x4F(perspectiveProjectionMatrix(0.1, 100.0, DEGREES_TO_RADIANS(45.0), (double)(width) / (double)(height)));
    unsigned int projectionL = glGetUniformLocation(renderer->shader3D, "projection");
    glUniformMatrix4fv(projectionL, 1, GL_TRUE, (GLfloat *)&projection.a11);

    unsigned int colorL = glGetUniformLocation(renderer->shader3D, "color");
    glUniform3f(colorL, color.x, color.y, color.z);

    drawModel(&renderer->cube);
  }

  // Draw XZ-Plane grid
  float tickInterval = 1.0f;
  int ticks = 9;

  // X
  for (int i = -ticks; i <= ticks; ++i) {
    if (i == 0)
      continue;

    renderer->cube.position = vec3(0.0, 0.0, i * tickInterval);
    renderer->cube.eulerRotation = vec3(0.0, 0.0, 0.0);
    renderer->cube.scale = vec3(10.0, 0.009, 0.009);

    Vector4 color = vec4(0.8, 0.8, 0.8, 1.0);

    // Draw
    glUseProgram(renderer->shader3D);

    int height, width;
    glfwGetFramebufferSize(renderer->window, &width, &height);
    glViewport(0, 0, width, height);

    Matrix4x4F model = matrix4x4toMatrix4x4F(modelMatrix(&renderer->cube));
    unsigned int modelL = glGetUniformLocation(renderer->shader3D, "model");
    glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

    Matrix4x4F view = matrix4x4toMatrix4x4F(getViewMatrix(&renderer->camera));
    unsigned int viewL = glGetUniformLocation(renderer->shader3D, "view");
    glUniformMatrix4fv(viewL, 1, GL_TRUE, (GLfloat *)&view.a11);

    Matrix4x4F projection = matrix4x4toMatrix4x4F(perspectiveProjectionMatrix(0.1, 100.0, DEGREES_TO_RADIANS(45.0), (double)(width) / (double)(height)));
    unsigned int projectionL = glGetUniformLocation(renderer->shader3D, "projection");
    glUniformMatrix4fv(projectionL, 1, GL_TRUE, (GLfloat *)&projection.a11);

    unsigned int colorL = glGetUniformLocation(renderer->shader3D, "color");
    glUniform3f(colorL, color.x, color.y, color.z);

    drawModel(&renderer->cube);
  }

  // Y
  for (int i = -ticks; i <= ticks; ++i) {
    if (i == 0)
      continue;

    renderer->cube.position = vec3(i * tickInterval, 0.0, 0.0);
    renderer->cube.eulerRotation = vec3(0.0, 0.0, 0.0);
    renderer->cube.scale = vec3(0.009, 0.009, 10.0);

    Vector4 color = vec4(0.8, 0.8, 0.8, 1.0);

    // Draw
    glUseProgram(renderer->shader3D);

    int height, width;
    glfwGetFramebufferSize(renderer->window, &width, &height);
    glViewport(0, 0, width, height);

    Matrix4x4F model = matrix4x4toMatrix4x4F(modelMatrix(&renderer->cube));
    unsigned int modelL = glGetUniformLocation(renderer->shader3D, "model");
    glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

    Matrix4x4F view = matrix4x4toMatrix4x4F(getViewMatrix(&renderer->camera));
    unsigned int viewL = glGetUniformLocation(renderer->shader3D, "view");
    glUniformMatrix4fv(viewL, 1, GL_TRUE, (GLfloat *)&view.a11);

    Matrix4x4F projection = matrix4x4toMatrix4x4F(perspectiveProjectionMatrix(0.1, 100.0, DEGREES_TO_RADIANS(45.0), (double)(width) / (double)(height)));
    unsigned int projectionL = glGetUniformLocation(renderer->shader3D, "projection");
    glUniformMatrix4fv(projectionL, 1, GL_TRUE, (GLfloat *)&projection.a11);

    unsigned int colorL = glGetUniformLocation(renderer->shader3D, "color");
    glUniform3f(colorL, color.x, color.y, color.z);

    drawModel(&renderer->cube);
  }
}

Vector2 getWindowSize(const RenderInfo *renderer) {
  int width, height;
  glfwGetWindowSize(renderer->window, &width, &height);
  return (Vector2){(double)width, (double)height};
}

Vector2 getCursorPosition(const RenderInfo *renderer) {
  Vector2 size = getWindowSize(renderer);

  double x, y;
  glfwGetCursorPos(renderer->window, &x, &y);
  return vec2(x, size.y - y);
}

int isLeftMouseButtonPressed(const RenderInfo *renderer) {
  int state = glfwGetMouseButton(renderer->window, GLFW_MOUSE_BUTTON_LEFT);
  if (state == GLFW_PRESS)
    return 1;
  else
    return 0;
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

void addKeyCallback(RenderInfo *renderer, Key key, KeyAction action, KeyCallbackFunction callback) {
  renderer->input.callbacks_n += 1;

  renderer->input.chars = realloc(renderer->input.chars, renderer->input.callbacks_n * sizeof(Key));
  renderer->input.actions = realloc(renderer->input.actions, renderer->input.callbacks_n * sizeof(KeyAction));
  renderer->input.callbacks = realloc(renderer->input.callbacks, renderer->input.callbacks_n * sizeof(KeyCallbackFunction));

  renderer->input.chars[renderer->input.callbacks_n - 1] = key;
  renderer->input.actions[renderer->input.callbacks_n - 1] = action;
  renderer->input.callbacks[renderer->input.callbacks_n - 1] = callback;
}

void setResizeCallback(RenderInfo *renderer, WindowResizeCallback callback) {
  renderer->resizeCallback = callback;
}

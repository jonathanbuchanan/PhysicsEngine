#include "render.h"

#include <stdlib.h>

float vertices[] = {
  -0.5, -0.5,
  -0.5, 0.5,
  0.5, -0.5
};

static const char* vertex_shader_text =
"#version 330 core\n"
"layout (location = 0) in vec2 pos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(pos, 0.0, 1.0);\n"
"}\n";

static const char* fragment_shader_text =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}\n";

RenderInfo * createRenderer(GLFWwindow *window) {
  glfwMakeContextCurrent(window);

  RenderInfo *renderer = malloc(sizeof(RenderInfo));

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

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);

  renderer->shaderProgram = program;
  renderer->vbo = vbo;
  renderer->vao = vao;

  return renderer;
}

void render(GLFWwindow *window, RenderInfo *renderer) {
  glfwMakeContextCurrent(window);

  // Set the viewport
  int height, width;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  // Clear
  clear(window);

  // Draw
  glUseProgram(renderer->shaderProgram);
  glBindVertexArray(renderer->vao);
  glDrawArrays(GL_TRIANGLES, 0, 3); 

  // Swap the buffers
  swapBuffers(window);
  glfwPollEvents();
}

void clear(GLFWwindow *window) {
  glfwMakeContextCurrent(window);
  glClear(GL_COLOR_BUFFER_BIT);
}

void swapBuffers(GLFWwindow *window) {
  glfwSwapBuffers(window);
}

void setClearColor(GLFWwindow *window, float red, float green, float blue, float alpha) {
  glfwMakeContextCurrent(window);
  glClearColor(red, green, blue, alpha);
}


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "renderer.h"
#include "shader.h"
#include "callback.h"
#include "camera.h"

struct ScreenMode {
  GLFWmonitor* monitor;
  GLFWvidmode* mode;
};

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
float deltaTime{};
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;   


GLFWwindow* setWindowBorderless() {
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
 
  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
  int x, y;
  glfwGetMonitorPos(monitor, &x, &y);

  GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
  if(!window) {
    glfwTerminate();
    return window;
  }
  glfwSetWindowPos(window, x, y);
  glfwMakeContextCurrent(window);

  return window;
}

Camera camera;


int main() {

  std::cout << "Initialize GLFW and GLAD\n";
  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

  GLFWwindow *window = setWindowBorderless();
  if(!window) return -1; /** already terminated by function setWindowBorderless() */


  /** Setting input */
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);


  stbi_set_flip_vertically_on_load(true);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD\n";
    return -1;
  }


  Shader modelShader("resources/shaders/model.vs", "resources/shaders/model.fs");
  std::cout << "loaded";

  ModelData detectie {Model("resources/models/detectie.obj"), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 1.4f, 3.0f), glm::vec3(0.0f), 0.0f};
  ModelData lamp {Model("resources/models/lamp.obj"), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.2f, 1.2f, 1.2f), glm::vec3(0.0f), 0.0f};
  ModelData checkerboard {Model("resources/models/groundpane.obj"), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f), 0.0f};
  ModelData human {Model("resources/models/human.obj"), glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f), 0.0f};


  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  float lastTime = glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    float currentTime = static_cast<float>(glfwGetTime());
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    processInput(window);
    glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glm::mat4 projection = glm::perspective(camera.Zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = camera.GetViewMatrix();
    
    renderModel(detectie, projection, view, modelShader);
    renderModel(lamp, projection, view, modelShader);
    renderModel(checkerboard, projection, view, modelShader);
    renderModel(human, projection, view, modelShader);


    glfwSwapBuffers(window);
    glfwPollEvents();


  }




  glfwTerminate();
  return 0;
}
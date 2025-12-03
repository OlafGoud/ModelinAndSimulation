#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "renderer.h"

struct ScreenMode {
  GLFWmonitor* monitor;
  GLFWvidmode* mode;
};

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
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


  stbi_set_flip_vertically_on_load(true);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD\n";
    return -1;
  }






  glfwTerminate();
  return 0;
}
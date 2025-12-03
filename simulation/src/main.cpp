#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer.h"
#include "model.h"
#include "shader.h"

struct ScreenMode {
  GLFWmonitor* monitor;
  GLFWvidmode* mode;
};

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;


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


  Shader modelShader("resources\\shaders\\model.vs", "resources\\shaders\\model.fs");
  std::cout << "loaded";
  Model axe("resources\\models\\hatchet.obj");

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  float lastTime = glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    float currentTime = static_cast<float>(glfwGetTime());
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    modelShader.use();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelShader.setMat4("projection", projection);
    modelShader.setMat4("view", view);


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelShader.setMat4("model", model);
    axe.Draw(modelShader);



    glfwSwapBuffers(window);
    glfwPollEvents();


  }




  glfwTerminate();
  return 0;
}
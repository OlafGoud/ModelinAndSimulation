#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"
extern Camera camera;
extern float deltaTime;
extern bool firstMouse;
extern float lastX;
extern float lastY;

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

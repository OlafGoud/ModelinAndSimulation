#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "model.h"
#include "shader.h"


struct ModelData {
  Model model;
  glm::vec3 pos;
  glm::vec3 scale;
  glm::vec3 rot;
  float angle;
};



void renderModel(ModelData &data, glm::mat4 projection, glm::mat4 view, Shader &shader);
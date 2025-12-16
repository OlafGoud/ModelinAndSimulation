#include "renderer.h"

void renderModel(ModelData &data, glm::mat4 projection, glm::mat4 view, Shader &shader) {

  shader.use();

  shader.setMat4("projection", projection);
  shader.setMat4("view", view);


  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, data.pos); // translate it down so it's at the center of the scene
  model = glm::scale(model, data.scale);	// it's a bit too big for our scene, so scale it down
  //model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  shader.setMat4("model", model);


  data.model.Draw(shader);



}
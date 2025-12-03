#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb/stb_image.h>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <unordered_map>
#include <string>

struct Mesh {
  
  std::vector<float> vertex;
  std::vector<uint32_t> indices;

  unsigned int VAO{}, VBO{}, EBO{};

};

struct Model {
  std::vector<Mesh> meshes;
};


Model loadModel(const char* path);

void processNode(aiNode *node, const aiScene *scene, std::vector<Mesh>* meshes);
unsigned int loadTexture(char const* path);
Mesh processMesh(aiMesh *mesh, const aiScene *scene);
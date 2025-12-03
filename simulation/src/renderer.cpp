#include "renderer.h"


std::unordered_map<std::string, unsigned int> texture;


/** 
 * Function to load a texture.
 * @param path char* to the place of the file.
 * @returns a index for the texture.
 * @note function from https://learnopengl.com */
unsigned int loadTexture(char const* path) {
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
        format = GL_RED;
    else if (nrComponents == 3)
        format = GL_RGB;
    else if (nrComponents == 4)
        format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    GLenum internalFormat = (nrComponents == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
  }
  stbi_image_free(data);

  return textureID;
}


/**
 * Function to load a model
 * @param path char array with the path to the file
 * @return a model.
 */
Model loadModel(const char* path) {
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
  // check for errors
  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) { 
    std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << "\n";
    return;
  }
  // retrieve the directory path of the filepath
  Model model;
  processNode(scene->mRootNode, scene, &model.meshes);

  return model;
}

void processNode(aiNode *node, const aiScene *scene, std::vector<Mesh>* meshes) {
  
  for(unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    meshes->push_back(processMesh(mesh, scene));
  }

  for(unsigned int i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene, meshes);
  }
}

Mesh processMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<float> vertices;
  std::vector<uint32_t> indices;

  for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
    vertices.push_back(mesh->mVertices[i].x);
    vertices.push_back(mesh->mVertices[i].y);
    vertices.push_back(mesh->mVertices[i].z);

    if(mesh->HasNormals()) {
      vertices.push_back(mesh->mNormals[i].x);
      vertices.push_back(mesh->mNormals[i].y);
      vertices.push_back(mesh->mNormals[i].z);
    }

    if(mesh->mTextureCoords[0]) {
      
    }
  }

}
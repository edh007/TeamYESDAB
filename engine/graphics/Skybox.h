#pragma once
#include "glew.h"
#include <vector>
#include <stb_image.h>
#include <iostream>

class Skybox
{
public:
    Skybox(std::vector<std::string> faces, float _size);
    ~Skybox();
    void Draw();
    unsigned int loadCubemap(std::vector<std::string> faces);

    void SetID(unsigned int _id) { id = _id; }
    unsigned int GetID() { return id; }
private:
    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int id;
};

//
// Created by Martin Hertel on 10.02.2024.
//

#ifndef MINECRAFTCLONE_SHADER_H
#define MINECRAFTCLONE_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glm/fwd.hpp>


class Shader {

public:
    // program ID
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    void deleteShader();

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setVector3f(const std::string &name,
                     const float value1,
                     const float value2,
                     const float value3) const;

    void setVector4f(const std::string &name,
                     const float value1,
                     const float value2,
                     const float value3,
                     const float value4) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;
};


#endif //MINECRAFTCLONE_SHADER_H

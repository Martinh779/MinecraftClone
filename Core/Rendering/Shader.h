/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef MINECRAFTCLONE_SHADER_H
#define MINECRAFTCLONE_SHADER_H

#include <string>
#include <sstream>
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
                     float value1,
                     float value2,
                     float value3) const;

    void setVector4f(const std::string &name,
                     float value1,
                     float value2,
                     float value3,
                     float value4) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    static Shader* shader;
};


#endif //MINECRAFTCLONE_SHADER_H

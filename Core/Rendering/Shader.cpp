//
// Created by Martin Hertel on 10.02.2024.
//

#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "../Utils/Logger.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        LOG(LOG_ERROR, "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ");
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Vertex
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        LOG(LOG_ERROR, "ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s", infoLog);
    }

    // Fragment
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        LOG(LOG_ERROR, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s", infoLog);
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        LOG(LOG_ERROR, "ERROR::SHADER::PROGRAM::LINKING_FAILED: %s", infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


void Shader::use() {
    glUseProgram(ID);
}


void Shader::deleteShader() {
    glDeleteProgram(ID);
}


void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}


void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}


void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}


void Shader::setVector3f(const std::string &name, const float value1, const float value2, const float value3) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}


void Shader::setVector4f(const std::string &name, const float value1, const float value2, const float value3, const float value4) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}


void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
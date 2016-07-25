//
// Created by Evgenii Loikov
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>

#include "ShaderManager.h"
#include "logging.h"

bool printLog(GLuint obj);

bool loadContent(const char *path, std::string &result);

bool ShaderManager::init() {
    std::string vertShader, fragShader;
    VERIFY(loadContent("shaders/shader.vert", vertShader), "Unable to load vertex shader", return false);
    VERIFY(loadContent("shaders/shader.frag", fragShader), "Unable to load fragment shader", return false);
    const char * vertChars = vertShader.c_str();
    const char * fragChars = fragShader.c_str();

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertChars, NULL);
    glCompileShader(vertex_shader);
    printLog(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragChars, NULL);
    glCompileShader(fragment_shader);
    printLog(fragment_shader);

    shaderId = glCreateProgram();
    VERIFY(shaderId != 0, "Unable to create shader", return false)
    glAttachShader(shaderId, vertex_shader);
    glAttachShader(shaderId, fragment_shader);
    glLinkProgram(shaderId);

    bool success = printLog(shaderId);

    return success;
}

unsigned int ShaderManager::attribParam(const std::string &name) {
    auto result = attribParamsCache.find(name);
    if (result != attribParamsCache.end()) {
        return result->second;
    }

    GLuint id = (GLuint) glGetAttribLocation(shaderId, name.c_str());
    attribParamsCache[name] = id;
    return id;
}

int ShaderManager::uniformParam(const std::string &name) {
    auto result = uniformParamsCache.find(name);
    if (result != uniformParamsCache.end()) {
        return result->second;
    }

    GLint id = glGetUniformLocation(shaderId, name.c_str());
    uniformParamsCache[name] = id;
    return id;
}

bool printLog(GLuint obj) {
    int infologLength = 0;
    int maxLength = 1024;

    if (glIsShader(obj))
        glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &maxLength);
    else
        glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &maxLength);

    char infoLog[128 * 1024];

    if (glIsShader(obj))
        glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
    else
        glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);

    if (infologLength > 0) {
        LOG("%s\n", infoLog);
        return false;
    }

    return true;
}

#include <unistd.h>
bool loadContent(const char *path, std::string &result) {
    std::ifstream stream(path);
    if (!stream.is_open()) {
        return false;
    }

    result = "";
    std::string line = "";
    while (std::getline(stream, line)) {
        result += line + "\n";
    }

    return true;
}


//
// Created by Evgenii Loikov
//

#include <GL/glew.h>
#include <string>
#include <fstream>

#include "ShaderManager.h"
#include "logging.h"

bool printLog(GLuint obj);

bool loadContent(const std::string path, std::string &result);

bool ShaderManager::init() {
    VERIFY(initShader("shader", shaderId), "Unable to load main shader", return false);
    VERIFY(initShader("defShader", deferredShaderId), "Unable to load deferred shader", return false);

    return true;
}

bool ShaderManager::initShader(const std::string fileName, unsigned int &shaderId) {
    std::string vertShader, fragShader;
    VERIFY(loadContent("shaders/" + fileName + ".vert", vertShader), "Unable to load vertex shader", return false);
    VERIFY(loadContent("shaders/" + fileName + ".frag", fragShader), "Unable to load fragment shader", return false);
    const char *vertChars = vertShader.c_str();
    const char *fragChars = fragShader.c_str();

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

    VERIFY(glGetError() == GL_NO_ERROR, "Error while loading shaders", return false);

    bool success = printLog(shaderId) && printLog(vertex_shader) && printLog(fragment_shader);

    return success;
}

unsigned int ShaderManager::attribParam(const std::string &name) {
    auto result = attribParamsCache.find(name);
    if (result != attribParamsCache.end()) {
        return result->second;
    }

    const int intLocation = glGetAttribLocation(shaderId, name.c_str());
    if (intLocation == -1) {
        LOG("Can't find shader attribute with name: %s", name.c_str())
        return (unsigned int) -1;
    }
    GLuint id = (GLuint) intLocation;
    attribParamsCache[name] = id;
    return id;
}

int ShaderManager::uniformParam(const std::string &name) {
    auto result = uniformParamsCache.find(name);
    if (result != uniformParamsCache.end()) {
        return result->second;
    }

    GLint id = glGetUniformLocation(shaderId, name.c_str());
    if (id == -1) {
        LOG("Can't find shader uniform param with name: %s", name.c_str())
        return -1;
    }
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

bool loadContent(const std::string path, std::string &result) {
    std::ifstream stream(path);
    if (!stream.is_open()) {
        return false;
    }

    result = "";
    std::string line = "";
    while (std::getline(stream, line)) {
        result += line + "\n";
    }
    LOG("Loading shader [%s]: \n%s", path.c_str(), result.c_str());

    return true;
}


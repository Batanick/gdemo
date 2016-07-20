//
// Created by eloy on 7/19/16.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "logging.h"
#include "Renderer.h"
#include "sceneBuilding.h"
#include "../lib/glfw-3.2/deps/linmath.h"

static const char *vertex_shader_text =
        "uniform mat4 MVP;\n"
                "attribute vec3 vCol;\n"
                "attribute vec3 vPos;\n"
                "varying vec3 color;\n"
                "void main()\n"
                "{\n"
                "    gl_Position = vec4(vPos, 1.0);\n"
                "    color = vCol;\n"
                "}\n";
static const char *fragment_shader_text =
        "varying vec3 color;\n"
                "void main()\n"
                "{\n"
                "    gl_FragColor = vec4(color, 1.0);\n"
                "}\n";


void printLog(GLuint obj);

bool Renderer::init() {
    VERIFY(glewInit() == GLEW_OK, "Unable to initialize glew", return false);
    VERIFY(initShaders(), "Unable to initialize shaders", return false;)

    scene = buildScene();
    loadScene();

    return true;
}

bool Renderer::initShaders() {
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    printLog(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    printLog(fragment_shader);

    shaderId = glCreateProgram();
    VERIFY(shaderId != 0, "Unable to create shader", return false)
    glAttachShader(shaderId, vertex_shader);
    glAttachShader(shaderId, fragment_shader);
    glLinkProgram(shaderId);
    printLog(shaderId);

    return true;
}

void Renderer::loadScene() {
    for (auto model : scene->getModels()) {
        GLuint bufferId;

        const std::vector<Model::VertexData> &vertices = model->getVertices();
        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Model::VertexData), &vertices[0], GL_STATIC_DRAW);

        Mesh mesh;
        mesh.vertexBuffer = bufferId;
        meshes.push_back(mesh);
    }
}

void Renderer::doRender(const float &ratio, const float timeDelta) {
    glUseProgram(shaderId);

    const int mvpLoc = shaderParam("MVP", true);
    const int colLoc = shaderParam("vCol", false);
    const int posLoc = shaderParam("vPos", false);

    glm::mat4 model;
    glm::mat4 projection;
    glm::mat4 view;

    glm::mat4 mvp = projection * view * projection;

    for (Mesh &mesh : meshes) {
        glEnableVertexAttribArray(posLoc);
        glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *) 0);
        glEnableVertexAttribArray(colLoc);
        glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *) (sizeof(float) * 3));

        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, (const GLfloat *) &mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

}

void Renderer::draw(const std::shared_ptr<Model> &model) {

}

int Renderer::shaderParam(const std::string &name, bool uniform) {
    auto result = shaderParamsCache.find(name);
    if (result != shaderParamsCache.end()) {
        return result->second;
    }

    const GLint location = uniform ? glGetUniformLocation(shaderId, name.c_str())
                                   : glGetAttribLocation(shaderId, name.c_str());
    shaderParamsCache[name] = location;
    return location;
}

void printLog(GLuint obj) {
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

    if (infologLength > 0) LOG("%s\n", infoLog);
}



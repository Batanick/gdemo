//
// Created by eloy on 7/19/16.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"

#include "logging.h"
#include "sceneBuilding.h"

static const char *vertex_shader_text =
        "uniform mat4 MVP;\n"
                "attribute vec3 vCol;\n"
                "attribute vec3 vPos;\n"
                "varying vec3 color;\n"
                "void main()\n"
                "{\n"
                "    gl_Position = MVP * vec4(vPos, 1.0);\n"
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

    const int mvpLoc = uniformParam("MVP");
    const unsigned int colLoc = attribParam("vCol");
    const unsigned int posLoc = attribParam("vPos");

    const glm::vec3 &cameraPos = camera->getPosition();
    const glm::vec3 &cameraDir = camera->getDirection();
    const glm::vec3 &cameraUp = camera->getUp();

    const glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraDir, cameraUp);
    const glm::mat4 projection = glm::perspective<float>(45.0f, ratio, 0.01f, 5000.0f);

    for (Mesh &mesh : meshes) {
        const glm::mat4 model;
        const glm::mat4 mvp = projection * view * model;

        glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexBuffer);

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

unsigned int Renderer::attribParam(const std::string &name) {
    auto result = attribParamsCache.find(name);
    if (result != attribParamsCache.end()) {
        return result->second;
    }

    GLuint id = (GLuint) glGetAttribLocation(shaderId, name.c_str());
    attribParamsCache[name] = id;
    return id;
}

int Renderer::uniformParam(const std::string &name) {
    auto result = uniformParamsCache.find(name);
    if (result != uniformParamsCache.end()) {
        return result->second;
    }

    GLint id = glGetUniformLocation(shaderId, name.c_str());
    uniformParamsCache[name] = id;
    return id;
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



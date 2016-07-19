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
                "attribute vec2 vPos;\n"
                "varying vec3 color;\n"
                "void main()\n"
                "{\n"
                "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
                "    color = vCol;\n"
                "}\n";
static const char *fragment_shader_text =
        "varying vec3 color;\n"
                "void main()\n"
                "{\n"
                "    gl_FragColor = vec4(color, 1.0);\n"
                "}\n";


bool Renderer::init() {
    VERIFY(glewInit() == GLEW_OK, "Unable to initialize glew", return false);
    VERIFY(initShaders(), "Unable to initialize shaders", return false;)

    scene = buildScene();
    loadScene();

    return true;
}

bool Renderer::initShaders() {
    GLuint vertex_shader, fragment_shader;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    shaderId = glCreateProgram();
    VERIFY(shaderId != 0, "Unable to create shader", return false)
    glAttachShader(shaderId, vertex_shader);
    glAttachShader(shaderId, fragment_shader);
    glLinkProgram(shaderId);

    return true;
}


void Renderer::loadScene() {
    for (auto model : scene->getModels()) {
        GLuint bufferId;
        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        const std::vector<Model::VertexData> &vertices = model->getVertices();
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Model::VertexData), &vertices, GL_STATIC_DRAW);

        Mesh mesh;
        mesh.vertexBuffer = bufferId;
        meshes.push_back(mesh);
    }
}

void Renderer::doRender(const float &ratio) {
    glUseProgram(shaderId);

    const unsigned int mvpLoc = shaderParam("MVP");
    const unsigned int colLoc = shaderParam("vCol");
    const unsigned int posLoc = shaderParam("vPos");

    glm::mat4 model;
    glm::mat4 projection;
    glm::mat4 view;

    glm::mat4 mvp =
    mat4x4 m, p, mvp;
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float) glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    for (Mesh &mesh : meshes) {
        glEnableVertexAttribArray(posLoc);
        glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *) 0);
        glEnableVertexAttribArray(colLoc);
        glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *) (sizeof(float) * 3));

        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, (const GLfloat*) mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

}

void Renderer::draw(const std::shared_ptr<Model> &model) {

}

unsigned int Renderer::shaderParam(const std::string &name) {
    auto result = shaderParamsCache.find(name);
    if (result != shaderParamsCache.end()) {
        return result->second;
    }

    const int location = glGetUniformLocation(shaderId, name.c_str());
    shaderParamsCache[name] = location;
    return location;
}






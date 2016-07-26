//
// Created by eloy on 7/19/16.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"

#include "logging.h"
#include "sceneBuilding.h"

bool Renderer::init() {
    VERIFY(glewInit() == GLEW_OK, "Unable to initialize glew", return false);
    VERIFY(shaderManager->init(), "Unable to initialize shaders", return false;)

    scene = buildScene();
    loadScene();

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

void Renderer::doRender(const float &ratio, const float &) {
    glUseProgram(shaderManager->getShaderId());

    const int mvpLoc = shaderManager->uniformParam("MVP");
    const unsigned int colLoc = shaderManager->attribParam("vCol");
    const unsigned int posLoc = shaderManager->attribParam("vPos");

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

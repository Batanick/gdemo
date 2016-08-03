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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    return true;
}

void Renderer::loadScene() {
    for (auto model : scene->getModels()) {
        GLuint vertexBuffer, indexBuffer;

        auto &vertices = model->getVertices();
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Model::VertexData), &vertices[0], GL_STATIC_DRAW);

        auto &indices = model->getIndices();
        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

        Mesh mesh(vertexBuffer, indexBuffer, (unsigned int) indices.size());
        meshes.push_back(mesh);
    }
}

void Renderer::doRender(const float &ratio, const float &) {
    glUseProgram(shaderManager->getShaderId());

    const int mvpLoc = shaderManager->uniformParam("MVP");
    const int viewLoc = shaderManager->uniformParam("view");
//    const int projectionLoc = shaderManager->uniformParam("projection");
    const int lightDirViewLoc = shaderManager->uniformParam("lightDirView");

    const unsigned int colLoc = shaderManager->attribParam("vColor");
    const unsigned int posLoc = shaderManager->attribParam("vPos");
    const unsigned int normLoc = shaderManager->attribParam("vNorm");

    const glm::vec3 &cameraPos = camera->getPosition();
    const glm::vec3 &cameraDir = camera->getDirection();
    const glm::vec3 &cameraUp = camera->getUp();

    const glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraDir, cameraUp);
    const glm::mat4 projection = glm::perspective<float>(45.0f, ratio, 0.01f, 5000.0f);

    const glm::vec4 lightDirView = view * glm::vec4(lightDir.x, lightDir.y, lightDir.z, 0.0f);
    const glm::vec3 lightDirViewNorm = glm::normalize(glm::vec3(lightDirView));

    for (Mesh &mesh : meshes) {
        const glm::mat4 model = mesh.getTransform();
        const glm::mat4 mvp = projection * view * model;

        glBindBuffer(GL_ARRAY_BUFFER, mesh.getVertexBuffer());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndexBuffer());

        glEnableVertexAttribArray(posLoc);
        glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void *) 0);
        glEnableVertexAttribArray(colLoc);
        glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void *) (sizeof(float) * 3));
        glEnableVertexAttribArray(normLoc);
        glVertexAttribPointer(normLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void *) (sizeof(float) * 6));

        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, (const GLfloat *) &mvp);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat *) &view);
//        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (const GLfloat *) &projection);
        glUniform3fv(lightDirViewLoc, 1, (const GLfloat *) &lightDirViewNorm);

        glDrawElements(GL_TRIANGLES, mesh.getElementsSize(), GL_UNSIGNED_SHORT, 0);
    }
}

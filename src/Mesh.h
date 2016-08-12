//
// Created by Evgenii Loikov
//

#ifndef GDEMO_MESH_H
#define GDEMO_MESH_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <memory>

#include "MoveController.h"

class Mesh {
public:
    Mesh(const unsigned int vertexBuffer, const unsigned int elementsSize, const glm::mat4 &model,
         const float shininess) :
            vertexBuffer(vertexBuffer),
            elementsSize(elementsSize),
            model(model),
            shininess(shininess) { }

    unsigned int getVertexBuffer() const {
        return vertexBuffer;
    }

    unsigned int getElementsSize() const {
        return elementsSize;
    }

    float getShininess() const {
        return shininess;
    }

    glm::mat4 updateTransform(const float &delta) {
        for (auto &controller : moveControllers) {
            this->model = controller->move(model, delta);
        }

        return model;
    }

    void setMoveControllers(const std::vector<std::shared_ptr<MoveController>> &moveControllers) {
        Mesh::moveControllers = moveControllers;
    }

private :
    const unsigned int vertexBuffer;
    const unsigned int elementsSize;
    glm::mat4 model;
    const float shininess;

    std::vector<std::shared_ptr<MoveController>> moveControllers;


};


#endif //GDEMO_MESH_H

//
// Created by Evgenii Loikov
//

#ifndef GDEMO_MODEL_H
#define GDEMO_MODEL_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "MoveController.h"

class Model {
public:
    struct VertexData {
        glm::vec3 position;
        glm::vec3 diffuse;
        glm::vec3 normal;

        VertexData(const glm::vec3 &position, const glm::vec3 &diffuse, const glm::vec3 &normal) :
                position(position),
                diffuse(diffuse),
                normal(normal) { }
    };

    void add(const glm::vec3 &pos, const glm::vec3 &diffuse, const glm::vec3 &normal) {
        vertices.push_back(VertexData(pos, diffuse, glm::normalize(normal)));
    }

    void add(const glm::vec3 &pos, const glm::vec3 &diffuse) {
        vertices.push_back(VertexData(pos, diffuse, glm::normalize(pos)));
    }

    const std::vector<VertexData> &getVertices() const {
        return vertices;
    }

    const std::vector<std::shared_ptr<MoveController>> &getMoveControllers() const {
        return moveControllers;
    }

    void withRotation(const glm::vec3 &axis, const float &speed) {
        moveControllers.push_back(rotationController(axis, speed));
    }

private:
    std::vector<VertexData> vertices;

    std::vector<std::shared_ptr<MoveController>> moveControllers;
};


#endif //GDEMO_MODEL_H

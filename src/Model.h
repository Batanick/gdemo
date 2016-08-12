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

    const glm::mat4 &getInitialModel() const {
        return initialModel;
    }

    float getShininess() const {
        return shininess;
    }

    Model& shine(float shininess) {
        Model::shininess = shininess;
        return *this;
    }

    Model& withRotation(const glm::vec3 &axis, const float &speed) {
        moveControllers.push_back(rotationController(axis, speed));
        return *this;
    }

    Model& withRotationAround(const glm::vec3 &axis, const float &speed) {
        moveControllers.push_back(rotationAroundController(axis, speed));
        return *this;
    }

    Model& move(const glm::vec3 &translate) {
        initialModel = glm::translate(translate) * initialModel;
        return *this;
    }

private:
    std::vector<VertexData> vertices;

    std::vector<std::shared_ptr<MoveController>> moveControllers;

    glm::mat4 initialModel;
    float shininess = 0.0f;
};

#endif //GDEMO_MODEL_H

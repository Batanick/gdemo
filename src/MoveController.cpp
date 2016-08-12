//
// Created by Evgenii Loikov
//

#include "MoveController.h"

class RotationController : public MoveController {
    const float speed;
    const glm::vec3 axis;

public:
    RotationController(const glm::vec3 &axis, const float speed) :
            speed(speed),
            axis(axis) { }

private:
    virtual glm::mat4 move(const glm::mat4 &model, const float &timeDelta) override {
        return model * glm::rotate(speed * timeDelta, axis);
    }
};

class RotationAroundController : public MoveController {
    const float speed;
    const glm::vec3 axis;

public:
    RotationAroundController(const float speed, const glm::vec3 &axis)
            : speed(speed), axis(axis) { }

private:
    virtual glm::mat4 move(const glm::mat4 &model, const float &timeDelta) override {
        return glm::rotate(speed * timeDelta, axis) * model;
    }
};

std::shared_ptr<MoveController> rotationController(const glm::vec3 &axis, const float speed) {
    return std::shared_ptr<MoveController>(new RotationController(axis, speed));
}

std::shared_ptr<MoveController> rotationAroundController(const glm::vec3 &axis, const float speed) {
    return std::shared_ptr<MoveController>(new RotationAroundController(speed, axis));
}

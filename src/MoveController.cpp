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

std::shared_ptr<MoveController> rotationController(const glm::vec3 &axis, const float speed) {
    return std::shared_ptr<MoveController>(new RotationController(axis, speed));
}

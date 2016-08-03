//
// Created by Evgenii Loikov
//

#ifndef GDEMO_MOVECONTROLLER_H
#define GDEMO_MOVECONTROLLER_H

#include <glm/glm.hpp>
#include <memory>
#include <glm/gtx/transform.hpp>

class MoveController {
public:
    virtual glm::mat4 move(const glm::mat4 &model, const float &timeDelta) = 0;
};

std::shared_ptr<MoveController> rotationController(const glm::vec3 &axis, const float speed);

#endif //GDEMO_MOVECONTROLLER_H

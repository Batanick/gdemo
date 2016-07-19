//
// Created by Evgenii Loikov
//

#ifndef GDEMO_SCENEBUILDING_H
#define GDEMO_SCENEBUILDING_H

#include <memory>

#include "sceneBuilding.h"
#include "Scene.h"

glm::vec3 pos(const float &x, const float &y, const float &z) {
    return glm::vec3(x, y, z);
}

glm::vec3 clr(const float &r, const float &g, const float &b) {
    return glm::vec3(r, g, b);
}

std::shared_ptr<Model> testTriangle() {
    auto model = std::make_shared<Model>();

    model->add(pos(-0.6f, -0.4f, 0.0f), clr(1.f, 0.f, 0.f));
    model->add(pos(0.6f, -0.4f, 0.0f), clr(0.f, 1.f, 0.f));
    model->add(pos(0.f, 0.6f, 0.0f), clr(0.f, 0.f, 1.f));

    return model;
}

std::unique_ptr<Scene> buildScene() {
    auto scene = std::unique_ptr<Scene>(new Scene());

    scene->add(testTriangle());

    return scene;
}

#endif //GDEMO_SCENEBUILDING_H

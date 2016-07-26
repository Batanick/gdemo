//
// Created by Evgenii Loikov
//

#ifndef GDEMO_SCENEBUILDING_H
#define GDEMO_SCENEBUILDING_H

#include <memory>

#include "sceneBuilding.h"
#include "Scene.h"

glm::vec3 GREEN(0.0f, 1.0f, 0.0f);
glm::vec3 RED(1.0f, 0.0f, 0.0f);
glm::vec3 BLUE(0.0f, 0.0f, 1.0f);

glm::vec3 pos(const float &x, const float &y, const float &z) {
    return glm::vec3(x, y, z);
}

glm::vec3 clr(const float &r, const float &g, const float &b) {
    return glm::vec3(r, g, b);
}

std::shared_ptr<Model> testTriangle() {
    auto model = std::make_shared<Model>();

    model->add(pos(0.6f, -0.4f, 0.0f), clr(0.f, 1.f, 0.f));
    model->add(pos(-0.6f, -0.4f, 0.0f), clr(1.f, 0.f, 0.f));
    model->add(pos(0.f, 0.6f, 0.0f), clr(0.f, 0.f, 1.f));

    model->poly(0, 1, 2);

    return model;
}

std::shared_ptr<Model> cube(const float &size, const glm::vec3 &clr) {
    auto model = std::make_shared<Model>();
    const float hSize = size / 2;


    model->add(pos(-hSize, -hSize, hSize), clr);
    model->add(pos(hSize, -hSize, hSize), clr);
    model->add(pos(hSize, hSize, hSize), clr);
    model->add(pos(-hSize, hSize, hSize), clr);

    model->add(pos(-hSize, -hSize, -hSize), clr);
    model->add(pos(hSize, -hSize, -hSize), clr);
    model->add(pos(hSize, hSize, -hSize), clr);
    model->add(pos(-hSize, hSize, -hSize), clr);

    // front
    model->poly(0, 1, 2);
    model->poly(2, 3, 0);
    // top
    model->poly(1, 5, 6);
    model->poly(6, 2, 1);
    // back
    model->poly(7, 6, 5);
    model->poly(5, 4, 7);
    // bottom
    model->poly(4, 0, 3);
    model->poly(3, 7, 4);
    // left
    model->poly(4, 5, 1);
    model->poly(1, 0, 4);
    // right
    model->poly(3, 2, 6);
    model->poly(6, 7, 3);

    return model;
}

std::unique_ptr<Scene> buildScene() {
    auto scene = std::unique_ptr<Scene>(new Scene());

    scene->add(testTriangle());
    scene->add(cube(0.3f, GREEN));

    return scene;
}

#endif //GDEMO_SCENEBUILDING_H

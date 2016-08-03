//
// Created by Evgenii Loikov
//

#ifndef GDEMO_SCENEBUILDING_H
#define GDEMO_SCENEBUILDING_H

#include <memory>

#include "constants.h"
#include "Scene.h"


glm::vec3 GREEN(0.0f, 1.0f, 0.0f);
glm::vec3 RED(1.0f, 0.0f, 0.0f);
glm::vec3 BLUE(0.0f, 0.0f, 1.0f);
glm::vec3 GREY(0.5f, 0.5f, 0.5f);

glm::vec3 pos(const float &x, const float &y, const float &z) {
    return glm::vec3(x, y, z);
}

glm::vec3 clr(const float &r, const float &g, const float &b) {
    return glm::vec3(r, g, b);
}

glm::vec3 normal(const float &x, const float &y, const float &z) {
    return glm::normalize(glm::vec3(x, y, z));
}

std::shared_ptr<Model> testTriangle() {
    auto model = std::make_shared<Model>();

    model->add(pos(0.6f, -0.4f, 0.0f), clr(0.f, 1.f, 0.f), glm::vec3());
    model->add(pos(-0.6f, -0.4f, 0.0f), clr(1.f, 0.f, 0.f), glm::vec3());
    model->add(pos(0.f, 0.6f, 0.0f), clr(0.f, 0.f, 1.f), glm::vec3());

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

std::shared_ptr<Model> box(const float &size, const glm::vec3 &clr) {
    auto model = std::make_shared<Model>();
    const float hSize = size / 2;

    model->add(pos(-hSize, -hSize, hSize), clr, normal(hSize, hSize, -hSize));
    model->add(pos(hSize, -hSize, hSize), clr, normal(-hSize, hSize, -hSize));
    model->add(pos(hSize, hSize, hSize), clr, normal(-hSize, -hSize, -hSize));
    model->add(pos(-hSize, hSize, hSize), clr, normal(hSize, -hSize, -hSize));

    model->add(pos(-hSize, -hSize, -hSize), clr, normal(hSize, hSize, hSize));
    model->add(pos(hSize, -hSize, -hSize), clr, normal(-hSize, hSize, hSize));
    model->add(pos(hSize, hSize, -hSize), clr, normal(-hSize, -hSize, hSize));
    model->add(pos(-hSize, hSize, -hSize), clr, normal(hSize, -hSize, hSize));

    // front
    model->poly(1, 0, 2);
    model->poly(3, 2, 0);
    // top
    model->poly(5, 1, 6);
    model->poly(2, 6, 1);
    // back
    model->poly(6, 7, 5);
    model->poly(4, 5, 7);
    // bottom
    model->poly(0, 4, 3);
    model->poly(7, 3, 4);
    // left
    model->poly(5, 4, 1);
    model->poly(0, 1, 4);
    // right
    model->poly(2, 3, 6);
    model->poly(7, 6, 3);

    return model;
}


std::unique_ptr<Scene> buildScene() {
    auto scene = std::unique_ptr<Scene>(new Scene());

    scene->add(box(ROOM_SIZE, GREY));
    scene->add(cube(0.3f, GREEN))->withRotation(glm::vec3(1.0f, 0.0f, 1.0f), 0.5f);

    return scene;
}

#endif //GDEMO_SCENEBUILDING_H

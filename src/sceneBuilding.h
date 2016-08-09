//
// Created by Evgenii Loikov
//

#ifndef GDEMO_SCENEBUILDING_H
#define GDEMO_SCENEBUILDING_H

#include <memory>

#include "constants.h"
#include "Scene.h"

glm::vec3 UP(0.0f, 1.0f, 0.0f);
glm::vec3 DOWN(0.0f, -1.0f, 0.0f);
glm::vec3 LEFT(-1.0f, 0.0f, 0.0f);
glm::vec3 RIGHT(1.0f, 0.0f, 0.0f);
glm::vec3 FWD(0.0f, 0.0f, 1.0f);
glm::vec3 BKWD(0.0f, 0.0f, -1.0f);


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

void addSquare(const std::shared_ptr<Model> model, glm::vec3 normal, const glm::vec3 &clr, const float &hSize) {
    auto rotation = glm::rotation(UP, normal);

    model->add(rotation * pos(-hSize, hSize, -hSize), clr, normal);
    model->add(rotation * pos(-hSize, hSize, hSize), clr, normal);
    model->add(rotation * pos(hSize, hSize, -hSize), clr, normal);

    model->add(rotation * pos(hSize, hSize, hSize), clr, normal);
    model->add(rotation * pos(hSize, hSize, -hSize), clr, normal);
    model->add(rotation * pos(-hSize, hSize, hSize), clr, normal);
}

void addSquareInv(const std::shared_ptr<Model> model, glm::vec3 normal, const glm::vec3 &clr, const float &hSize) {
    auto rotation = glm::rotation(UP, normal);
    normal = -normal;

    model->add(rotation * pos(-hSize, hSize, hSize), clr, normal);
    model->add(rotation * pos(-hSize, hSize, -hSize), clr, normal);
    model->add(rotation * pos(hSize, hSize, -hSize), clr, normal);

    model->add(rotation * pos(hSize, hSize, -hSize), clr, normal);
    model->add(rotation * pos(hSize, hSize, hSize), clr, normal);
    model->add(rotation * pos(-hSize, hSize, hSize), clr, normal);
}

std::shared_ptr<Model> testTriangle() {
    auto model = std::make_shared<Model>();

    model->add(pos(0.6f, -0.4f, 0.0f), clr(0.f, 1.f, 0.f), glm::vec3());
    model->add(pos(-0.6f, -0.4f, 0.0f), clr(1.f, 0.f, 0.f), glm::vec3());
    model->add(pos(0.f, 0.6f, 0.0f), clr(0.f, 0.f, 1.f), glm::vec3());

    return model;
}

std::shared_ptr<Model> cube(const float &size, const glm::vec3 &clr) {
    auto model = std::make_shared<Model>();
    const float hSize = size / 2;

    addSquare(model, UP, clr, hSize);
    addSquare(model, DOWN, clr, hSize);
    addSquare(model, LEFT, clr, hSize);
    addSquare(model, RIGHT, clr, hSize);
    addSquare(model, FWD, clr, hSize);
    addSquare(model, BKWD, clr, hSize);
    return model;
}

std::shared_ptr<Model> box(const float &size, const glm::vec3 &clr) {
    auto model = std::make_shared<Model>();
    const float hSize = size / 2;

    addSquareInv(model, UP, clr, hSize);
    addSquareInv(model, DOWN, clr, hSize);
    addSquareInv(model, LEFT, clr, hSize);
    addSquareInv(model, RIGHT, clr, hSize);
    addSquareInv(model, FWD, clr, hSize);
    addSquareInv(model, BKWD, clr, hSize);

    return model;
}


std::unique_ptr<Scene> buildScene() {
    auto scene = std::unique_ptr<Scene>(new Scene());

    scene->add(box(ROOM_SIZE, GREY));
    scene->add(cube(0.3f, GREEN))->withRotation(glm::vec3(1.0f, 0.0f, 1.0f), 0.5f);

    return scene;
}

#endif //GDEMO_SCENEBUILDING_H

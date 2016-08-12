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
glm::vec3 BWD(0.0f, 0.0f, -1.0f);


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

void subdivide(const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 p3, const int &depth,
               std::vector<glm::vec3> &result) {
    if (depth == 0) {
        result.push_back(p1);
        result.push_back(p2);
        result.push_back(p3);
        return;
    }

    const glm::vec3 p12 = glm::normalize(p1 + p2);
    const glm::vec3 p23 = glm::normalize(p2 + p3);
    const glm::vec3 p31 = glm::normalize(p3 + p1);

    subdivide(p1, p12, p31, depth - 1, result);
    subdivide(p2, p23, p12, depth - 1, result);
    subdivide(p3, p31, p23, depth - 1, result);
    subdivide(p12, p23, p31, depth - 1, result);
}

std::shared_ptr<Model> sphere(const float &rad, const glm::vec3 &clr, const int resolution) {
    auto model = std::make_shared<Model>();
    std::vector<glm::vec3> vertices;

    const glm::vec3 lf = glm::normalize(LEFT + FWD);
    const glm::vec3 rf = glm::normalize(RIGHT + FWD);
    const glm::vec3 lb = glm::normalize(LEFT + BWD);
    const glm::vec3 rb = glm::normalize(RIGHT + BWD);

    subdivide(UP, lf, rf, resolution, vertices);
    subdivide(UP, rb, lb, resolution, vertices);
    subdivide(UP, lb, lf, resolution, vertices);
    subdivide(UP, rf, rb, resolution, vertices);

    subdivide(lf, DOWN, rf, resolution, vertices);
    subdivide(rb, DOWN, lb, resolution, vertices);
    subdivide(lb, DOWN, lf, resolution, vertices);
    subdivide(rf, DOWN, rb, resolution, vertices);

    for (auto &vertex : vertices) {
        model->add(vertex * rad, clr, glm::normalize(vertex));
    }

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
    addSquare(model, BWD, clr, hSize);
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
    addSquareInv(model, BWD, clr, hSize);

    return model;
}


std::unique_ptr<Scene> buildScene() {
    auto scene = std::unique_ptr<Scene>(new Scene());

    scene->add(box(ROOM_SIZE, GREY));

    scene->add(cube(0.3f, GREEN))->
            shine(2.0f).
            withRotation(glm::vec3(1.0f, 0.0f, 1.0f), 0.5f).getShininess();

    scene->add(sphere(0.2f, BLUE, 6))->
            shine(16.0f).
            move(LEFT * 1.0f).
            withRotationAround(UP, 0.3f);

    scene->add(sphere(0.2f, BLUE, 6))->
            shine(16.0f).
            move(RIGHT * 1.0f).
            withRotationAround(UP, 0.3f);

    scene->add(sphere(0.2f, RED, 6))->
            shine(16.0f).
            move(FWD * 1.0f).
            withRotationAround(UP, 0.3f);

    scene->add(sphere(0.2f, RED, 6))->
            shine(16.0f).
            move(BWD * 1.0f).
            withRotationAround(UP, 0.3f);

    return scene;
}

#endif //GDEMO_SCENEBUILDING_H

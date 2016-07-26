//
// Created by Evgenii Loikov
//

#ifndef GDEMO_SCENE_H
#define GDEMO_SCENE_H


#include <vector>
#include <memory>
#include "Model.h"

class Scene {
public :
    void add(const std::shared_ptr<const Model> &model) {
        models.push_back(model);
    }

    const std::vector<std::shared_ptr<const Model>> &getModels() const {
        return models;
    }

private:
    std::vector<std::shared_ptr<const Model>> models;
};


#endif //GDEMO_SCENE_H

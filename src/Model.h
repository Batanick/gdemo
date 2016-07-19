//
// Created by Evgenii Loikov
//

#ifndef GDEMO_MODEL_H
#define GDEMO_MODEL_H

#include <vector>
#include <glm/glm.hpp>

class Model {
public:
    struct VertexData {
        glm::vec3 position;
        glm::vec3 diffuse;

        VertexData(const glm::vec3 &position, const glm::vec3 &diffuse) : position(position), diffuse(diffuse) { }
    };

    void add(const glm::vec3 &pos, const glm::vec3 &diffuse) {
        vertices.push_back(VertexData(pos, diffuse));
    }

    const std::vector<VertexData> &getVertices() const {
        return vertices;
    }

private:
    std::vector<VertexData> vertices;
};


#endif //GDEMO_MODEL_H

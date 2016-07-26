//
// Created by Evgenii Loikov
//

#ifndef GDEMO_MODEL_H
#define GDEMO_MODEL_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

class Model {
public:
    struct VertexData {
        glm::vec3 position;
        glm::vec3 diffuse;
        glm::vec3 normal;

        VertexData(const glm::vec3 &position, const glm::vec3 &diffuse, const glm::vec3 &normal) :
                position(position),
                diffuse(diffuse),
                normal(normal) { }
    };

    void add(const glm::vec3 &pos, const glm::vec3 &diffuse, const glm::vec3 &normal) {
        vertices.push_back(VertexData(pos, diffuse, normal));
    }

    void poly(const unsigned short &p1, const unsigned short &p2, const unsigned short &p3) {
        indices.push_back(p1);
        indices.push_back(p2);
        indices.push_back(p3);
    }

    const std::vector<VertexData> &getVertices() const {
        return vertices;
    }

    const std::vector<unsigned short> &getIndices() const {
        return indices;
    }

private:
    std::vector<VertexData> vertices;
    std::vector<unsigned short> indices;
};


#endif //GDEMO_MODEL_H

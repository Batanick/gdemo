#ifndef GDEMO_RENDERER_H
#define GDEMO_RENDERER_H

#include <memory>
#include <map>
#include "Scene.h"

class Renderer {
public:
    bool init();

    bool initShaders();

    void doRender(const float &ratio);

private :
    struct Mesh {
        unsigned int vertexBuffer = 0;
    };

    std::unique_ptr<Scene> scene;

    void loadScene();

    void draw(const std::shared_ptr<Model> &model);

    unsigned int shaderParam(const std::string &name);

    unsigned int shaderId = 0;
    std::map<std::string, unsigned int> shaderParamsCache;
    std::vector<Mesh> meshes;
};


#endif //GDEMO_RENDERER_H

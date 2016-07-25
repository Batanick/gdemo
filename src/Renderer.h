#ifndef GDEMO_RENDERER_H
#define GDEMO_RENDERER_H

#include <memory>
#include <map>

#include "Scene.h"
#include "Camera.h"

class Renderer {
public:
    bool init();

    bool initShaders();

    void doRender(const float &ratio, const float timeDelta);

    const std::unique_ptr<Camera> &getCamera() const {
        return camera;
    }

private :
    struct Mesh {
        unsigned int vertexBuffer = 0;
    };

    std::unique_ptr<Scene> scene;
    std::unique_ptr<Camera> camera {new Camera()};

    void loadScene();

    void draw(const std::shared_ptr<Model> &model);

    unsigned int attribParam(const std::string &name);

    int uniformParam(const std::string &name);

    unsigned int shaderId = 0;
    std::map<std::string, unsigned int> attribParamsCache;
    std::map<std::string, int> uniformParamsCache;
    std::vector<Mesh> meshes;
};


#endif //GDEMO_RENDERER_H

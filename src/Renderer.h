#ifndef GDEMO_RENDERER_H
#define GDEMO_RENDERER_H

#include <memory>
#include <map>

#include "Scene.h"
#include "Camera.h"
#include "ShaderManager.h"

class Renderer {
public:
    bool init();

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
    std::unique_ptr<ShaderManager> shaderManager {new ShaderManager()};

    void loadScene();

    std::vector<Mesh> meshes;
};


#endif //GDEMO_RENDERER_H

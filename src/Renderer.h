#ifndef GDEMO_RENDERER_H
#define GDEMO_RENDERER_H

#include <memory>
#include <map>

#include "Scene.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Mesh.h"

class Renderer {
public:
    bool init();

    void doRender(const float &ratio, const float &timeDelta);

    const std::unique_ptr<Camera> &getCamera() const {
        return camera;
    }

private :
    std::unique_ptr<Scene> scene;
    std::unique_ptr<Camera> camera{new Camera()};
    std::unique_ptr<ShaderManager> shaderManager{new ShaderManager()};

    void loadScene();

    std::vector<Mesh> meshes;
    glm::vec3 lightDir{0.0f, -1.0f, 0.0f};
};


#endif //GDEMO_RENDERER_H

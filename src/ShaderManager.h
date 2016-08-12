//
// Created by Evgenii Loikov
//

#ifndef GDEMO_SHADERMANAGER_H
#define GDEMO_SHADERMANAGER_H

#include <map>

class ShaderManager {

public:
    bool init();

    unsigned int attribParam(const std::string &name);

    int uniformParam(const std::string &name);

    unsigned int getShaderId() const {
        return shaderId;
    }

    unsigned int getDeferredShaderId() const {
        return deferredShaderId;
    }

private:
    unsigned int shaderId = 0;
    unsigned int deferredShaderId = 0;
    std::map<std::string, unsigned int> attribParamsCache;
    std::map<std::string, int> uniformParamsCache;

    bool initShader(const std::string fileName, unsigned int &shaderId);
};


#endif //GDEMO_SHADERMANAGER_H

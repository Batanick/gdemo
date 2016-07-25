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

private:
    unsigned int shaderId = 0;
    std::map<std::string, unsigned int> attribParamsCache;
    std::map<std::string, int> uniformParamsCache;
};


#endif //GDEMO_SHADERMANAGER_H

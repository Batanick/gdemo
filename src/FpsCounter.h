//
// Created by Evgenii Loikov
//

#ifndef GDEMO_FPSCOUNTER_H
#define GDEMO_FPSCOUNTER_H


class FpsCounter {

public:
    double onFrame();

    double getFps() const;

private:
    double lastTickTime = 0.0;

    double currentFps = 0.0;
    int fpsCounter = 0;

    double timeCounter = 0.0;
};


#endif //GDEMO_FPSCOUNTER_H

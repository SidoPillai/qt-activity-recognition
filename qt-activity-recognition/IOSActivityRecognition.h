#ifndef IOSACTIVITYRECOGNITION_H
#define IOSACTIVITYRECOGNITION_H

#include "AbstractActivityRecognition.h"

class IOSActivityRecognition : public AbstractActivityRecognition
{
public:
    IOSActivityRecognition();

public:
    void start() override;
    void stop() override;
};

#endif // IOSACTIVITYRECOGNITION_H

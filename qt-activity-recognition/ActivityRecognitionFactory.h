#ifndef ACTIVITYRECOGNITIONFACTORY_H
#define ACTIVITYRECOGNITIONFACTORY_H

#include "AbstractActivityRecognition.h"

class ActivityRecognitionFactory
{
public:
    static AbstractActivityRecognition* getInstance();
};

#endif // ACTIVITYRECOGNITIONFACTORY_H

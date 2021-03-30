#include "ActivityRecognitionFactory.h"

#if defined Q_OS_ANDROID
    #include "AndroidActivityRecognition.h"
#elif defined Q_OS_IOS
    #include "IOSActivityRecognition.h"
#else
    #include "AbstractActivityRecognition.h"
#endif

//------------------------------------------------------------------------------

AbstractActivityRecognition* ActivityRecognitionFactory::getInstance()
{
#if defined Q_OS_ANDROID
    return new AndroidActivityRecognition();
#elif defined Q_OS_IOS
    return new IOSActivityRecognition();
#else
    return new AbstractActivityRecognition();
#endif
}

//------------------------------------------------------------------------------

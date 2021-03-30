#ifndef ANDROIDACTIVITYRECOGNITION_H
#define ANDROIDACTIVITYRECOGNITION_H

#include "AbstractActivityRecognition.h"

#include <QtAndroidExtras>

class AndroidActivityRecognition : public AbstractActivityRecognition
{
public:
    AndroidActivityRecognition();

private slots:
    void onRecognizerStateChanged(int state);

public:
    void start() override;
    void stop() override;

private:
    static void updateDetectedActivities(JNIEnv *env, jobject thiz, jstring detectedActivities);
    static void updateStateChanged(JNIEnv *env, jobject thiz, jint state);

private:
    static AndroidActivityRecognition*          g_Instance;
    const QAndroidJniObject                     m_JavaInstance;
};

#endif // ANDROIDACTIVITYRECOGNITION_H

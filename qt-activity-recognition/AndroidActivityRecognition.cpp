#include "AndroidActivityRecognition.h"

//------------------------------------------------------------------------------

AndroidActivityRecognition* AndroidActivityRecognition::g_Instance = nullptr;

//------------------------------------------------------------------------------

AndroidActivityRecognition::AndroidActivityRecognition() :
    m_JavaInstance("com/sensors/activities/ActivityRecognizer",
                   "(Landroid/app/Activity;)V",
                   QtAndroid::androidActivity().object<jobject>())
{
    g_Instance = this;

    if (!m_JavaInstance.isValid())
    {
        return;
    }

    m_JavaInstance.callMethod<void>("init",
                                    "(Landroid/content/Context;J)V",
                                    QtAndroid::androidActivity().object(),
                                    reinterpret_cast<jlong>(g_Instance));

    const JNINativeMethod methods [] =
    {
        {
            "updateDetectedActivities",
            "()V",
            reinterpret_cast<void *>(&AndroidActivityRecognition::updateDetectedActivities)

        },
        {
            "updateStateChanged",
            "(I)V",
            reinterpret_cast<void *>(&AndroidActivityRecognition::updateStateChanged)
        }
    };

    QAndroidJniEnvironment JniEnv;
    jclass ObjectClass;
    ObjectClass = JniEnv->GetObjectClass(m_JavaInstance.object<jobject>());
    JniEnv->RegisterNatives(ObjectClass, methods, sizeof(methods)/sizeof(JNINativeMethod));
    JniEnv->DeleteLocalRef(ObjectClass);
}

//------------------------------------------------------------------------------

void AndroidActivityRecognition::start()
{
    if (!m_JavaInstance.isValid())
    {
        return;
    }
    m_JavaInstance.callMethod<void>("start" , "()V");
}

//------------------------------------------------------------------------------

void AndroidActivityRecognition::stop()
{
    if (!m_JavaInstance.isValid())
    {
        return;
    }
    m_JavaInstance.callMethod<void>("stop" , "()V");
}

//------------------------------------------------------------------------------

void AndroidActivityRecognition::updateDetectedActivities(JNIEnv *env, jobject thiz, jstring detectedActivities)
{
    Q_UNUSED(thiz)

    QString qstr(env->GetStringUTFChars(detectedActivities, 0));
    g_Instance->setActivities(qstr);
}

//------------------------------------------------------------------------------

void AndroidActivityRecognition::updateStateChanged(JNIEnv *env, jobject thiz, jint state)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    emit g_Instance->onRecognizerStateChanged(state);
}

//------------------------------------------------------------------------------

void AndroidActivityRecognition::onRecognizerStateChanged(int state)
{
    setState(state);
}

//------------------------------------------------------------------------------

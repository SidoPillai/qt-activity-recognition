#include "ActivityRecognition.h"
#include "ActivityRecognitionFactory.h"

//------------------------------------------------------------------------------

ActivityRecognition::ActivityRecognition(QObject* parent) : QObject(parent)
{
    m_ActivityRecognition = ActivityRecognitionFactory::getInstance();
    connect(m_ActivityRecognition, &AbstractActivityRecognition::error,
            this, &ActivityRecognition::error);
    connect(m_ActivityRecognition, &AbstractActivityRecognition::activityDetected,
            this, &ActivityRecognition::onDetectedChanged);
    connect(m_ActivityRecognition, &AbstractActivityRecognition::stateChanged,
            this, &ActivityRecognition::stateChanged);
}

//------------------------------------------------------------------------------

void ActivityRecognition::start()
{
    m_ActivityRecognition->start();
}

//------------------------------------------------------------------------------

void ActivityRecognition::stop()
{
    m_ActivityRecognition->stop();
}

//------------------------------------------------------------------------------

ActivityRecognition::ActivityRecognitionState ActivityRecognition::state() const
{
    return static_cast<ActivityRecognition::ActivityRecognitionState>(m_ActivityRecognition->status());
}

//------------------------------------------------------------------------------

void ActivityRecognition::onDetectedChanged()
{
    emit activityDetected(m_ActivityRecognition->activities());
}

//------------------------------------------------------------------------------

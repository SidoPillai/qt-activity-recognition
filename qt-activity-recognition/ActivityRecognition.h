#ifndef ACTIVITYRECOGNITION_H
#define ACTIVITYRECOGNITION_H

#include <QObject>

#include "AbstractActivityRecognition.h"

class ActivityRecognition : public QObject
{
    Q_OBJECT


    Q_PROPERTY(ActivityRecognitionState state READ state NOTIFY stateChanged)

public:
    enum ActivityRecognitionState
    {
        ActivityRecognitionStateUnknown = -1,
        ActivityRecognitionStateStarted,
        ActivityRecognitionStateStopped
    };
    Q_ENUM(ActivityRecognitionState)

public:
    explicit ActivityRecognition(QObject* parent=nullptr);

public:
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

signals:
    void activityDetected(QVariant activity);
    void error(QString errorMessage);
    void stateChanged();

private slots:
    void onDetectedChanged();

public:
    ActivityRecognitionState state() const;

private:
    AbstractActivityRecognition*         m_ActivityRecognition;
};

#endif // ACTIVITYRECOGNITION_H

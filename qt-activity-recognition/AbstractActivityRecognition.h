#ifndef ABSTRACTACTIVITYRECOGNITION_H
#define ABSTRACTACTIVITYRECOGNITION_H

#include <QObject>
#include <QVariant>

class AbstractActivityRecognition : public QObject
{
    Q_OBJECT

public:
    AbstractActivityRecognition()
    {
        m_Status = -1;
        m_DetectedActivities = QVariant();
    }

signals:
    void activityDetected();
    void error(QString errorMessage);
    void stateChanged();

public:
    virtual void start() {}
    virtual void stop() {}
    void setState(int state) { m_Status = state; emit stateChanged(); }
    int status() { return m_Status; }
    QVariant activities() { return m_DetectedActivities; }
    void setActivities(QVariant activities) { m_DetectedActivities = activities; emit activityDetected(); }

private:
    int             m_Status;
    QVariant        m_DetectedActivities;
};

#endif // ABSTRACTACTIVITYRECOGNITION_H

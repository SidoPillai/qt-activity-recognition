import QtQuick 2.12
import QtQuick.Window 2.12

import ActivityRecognition 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    ActivityRecognition {
        id: activityRecognition

        onActivityDetected: {
            console.log(activityDetected)
        }
    }
}

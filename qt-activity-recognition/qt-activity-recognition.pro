QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    AbstractActivityRecognition.h \
    ActivityRecognition.h \
    ActivityRecognitionFactory.h

SOURCES += \
        ActivityRecognition.cpp \
        ActivityRecognitionFactory.cpp \
        main.cpp

android {
QT += androidextras
HEADERS += AndroidActivityRecognition.h
SOURCES += AndroidActivityRecognition.cpp
}

ios {
LIBS += -framework CoreMotion
LIBS += -framework AVFoundation
HEADERS += IOSActivityRecognition.h
OBJECTIVE_SOURCES += IOSActivityRecognition.mm
}

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_ABIS = armeabi-v7a

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/src/com/sensors/activities/ActivityRecognizer.java \
    android/src/com/sensors/activities/DetectedActivityIntentService.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android


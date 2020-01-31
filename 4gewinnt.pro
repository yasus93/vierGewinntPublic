QT += core gui quick qml
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

RC_FILE = windows/myicon.rc

#only run on windows
win32:{
    LIBS += -lopengl32
}

linux-g++:{
   LIBS += -lGL -lGLU
}


android{
   DEFINES += GLES
   RESOURCEDIR = /assets
}
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TRANSLATIONS += translations/testmmp2018p1_de.ts

lupdate_only {
    SOURCES = qml/*.qml
}

HEADERS += \
        src/glpoint.h \
    src/glcolorrgba.h \
    src/gldefines.h \
    src/glesrenderer.h \
    src/glitem.h \
    src/shaderdebugger.h \
    src/myglitem.h \
        src/glbody.h \
    src/gldisc.h \
    src/gldisc.h \
    src/board.h


SOURCES += \
        src/main.cpp \
    src/glcolorrgba.cpp \
    src/glesrenderer.cpp \
    src/glitem.cpp \
    src/glpoint.cpp \
    src/shaderdebugger.cpp \
    src/myglitem.cpp \
        src/glbody.cpp \
    src/gldisc.cpp \
    src/board.cpp


RESOURCES += qml.qrc \
    translations.qrc \
    shaders.qrc \
    textures.qrc \
    obj.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/res/values/apptheme.xml \
    android/res/drawable/splash.xml \
    windows/icons8_number_4_96_jnD_icon.ico \
    windows/myicon.rc \
    android/res/drawable/icons8_number_4_96.jpg \
    android/res/drawable/splashimage.jpg

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

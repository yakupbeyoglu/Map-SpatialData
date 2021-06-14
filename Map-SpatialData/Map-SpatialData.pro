QT += quick \
    widgets
QT += sql
QT += core

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        application.cpp \
        applicationwidget.cpp \
        builder.cpp \
        customwidget.cpp \
        footer.cpp \
        main.cpp \
        model.cpp \
        sidewidget.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Configs.h \
    Types.h \
    application.h \
    applicationwidget.h \
    builder.h \
    customwidget.h \
    footer.h \
    model.h \
    sidewidget.h

DISTFILES += \
    Assets/lefke-image.jpg

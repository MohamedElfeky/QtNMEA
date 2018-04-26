#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T16:28:52
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtNMEA
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        ReceiverWindow.cpp \
    gpsdata_adapter.cpp \
    utils.cpp \
    private/udp_client.cpp \
    private/udp_dummy.cpp \
    udp_interface.cpp \
    private/udp_server.cpp \
    private/udp_base.cpp \
    configuration.cpp

HEADERS += \
        ReceiverWindow.h \
    gpsdata_adapter.h \
    strings.h \
    utils.h \
    types.h \
    private/udp_client.h \
    private/udp_dummy.h \
    udp_interface.h \
    private/udp_server.h \
    private/udp_base.h \
    configuration.h

FORMS += \
        ReceiverWindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libnmea-cpp/x64/Release/ -llibnmea-cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libnmea-cpp/x64/Debug/ -llibnmea-cpp

INCLUDEPATH += $$PWD/libnmea-cpp/libnmea-cpp/Public
DEPENDPATH += $$PWD/libnmea-cpp/libnmea-cpp/Public

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libnmea-cpp/x64/Release/liblibnmea-cpp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libnmea-cpp/x64/Debug/liblibnmea-cpp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libnmea-cpp/x64/Release/libnmea-cpp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libnmea-cpp/x64/Debug/libnmea-cpp.lib

TEMPLATE = app

QT += qml quick widgets core

SOURCES += src/main.cpp \
    src/timetrackingdatastore.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += \
	inc

HEADERS += \
	inc/timetrackingdatastore.h

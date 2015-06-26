#-------------------------------------------------
#
# Project created by QtCreator 2015-06-25T17:43:40
#
#-------------------------------------------------
include(../chess_shared.pro)

QT       += qml quick

TARGET = ui_qml
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = lib

DEFINES += UI_QML_LIB_IMPORT

HEADERS += \
    UiStartup.h \
    ui_qml_api.h

SOURCES += \
    UiStartup.cpp

RESOURCES += \
    ui_qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

QT += quick multimedia
TARGET = Orphean
DESTDIR = ../bin/x64-Debug/Orphean
CONFIG += debug console
DEFINES += $(Qt_DEFINES_) debug ORPHEAN_DEBUG
INCLUDEPATH += src
LIBS += -L"."
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += .
include(Orphean.pri)

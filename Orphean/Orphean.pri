HEADERS += ./src/Devices/AudioDevice.h \
    $$PWD/src/OrpheanAdapter.hpp \
    ./src/Effectors/Effector.hpp \
    ./src/Effectors/eRNNoise.hpp \
    ./src/EffectThread.h \
    ./src/OrpheanAssert.hpp \
    ./src/pch.h \
    ./src/PCMBuffer.h \
    ./src/Orphean.h \
    ./src/Devices/AInput.h \
    ./src/Devices/AOutput.h \
    ./src/Devices.h \
    ./src/Effectors.h
SOURCES += ./src/Devices/AudioDevice.cpp \
    ./src/EffectThread.cpp \
    ./src/main.cpp \
    ./src/pch.cpp \
    ./src/Orphean.cpp \
    ./src/Devices/AInput.cpp \
    ./src/Devices/AOutput.cpp
RESOURCES += qml.qrc

TARGET = dso
DESTDIR = ../release
SOURCES = main.cpp \
    DeviceManager.cpp \
    DeviceSelectDialog.cpp \
    DSOWindow.cpp \
    DSO.cpp \
    DSOScreen.cpp
HEADERS += DeviceManager.h \
    api/TransportPlugin.h \
    DeviceSelectDialog.h \
    DSOWindow.h \
    DSO.h \
    api/DSOTransport.h \
    DSOScreen.h
INCLUDEPATH += api
FORMS += DeviceSelectDialog.ui \
    DSOWindow.ui

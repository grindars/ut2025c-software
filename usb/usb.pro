TARGET = transport_usb
CONFIG += plugin
DESTDIR = ../release/plugins
TEMPLATE = lib
HEADERS += USBTransportPlugin.h \
    USBTransport.h
SOURCES += USBTransportPlugin.cpp \
    device_table.cpp \
    USBTransport.cpp
INCLUDEPATH += ../dso/api
CONFIG += link_pkgconfig
PKGCONFIG += libusb-1.0
QT -= gui

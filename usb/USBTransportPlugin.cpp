#include <QStringList>
#include <QtDebug>

#include <errno.h>
#include <libusb.h>

#include "USBTransportPlugin.h"
#include "USBTransport.h"

USBTransportPlugin::USBTransportPlugin(QObject *parent) : QObject(parent) {
    int ret = libusb_init(&m_context);

    if(ret != 0) {
        QString error = translate_libusb(ret);
        qFatal("libusb_init: %s\n", qPrintable(error));
    }
}

USBTransportPlugin::~USBTransportPlugin() {
    libusb_exit(m_context);
}

QStringList USBTransportPlugin::enumerate() {
    QStringList devices;

    libusb_device **list;

    int count = libusb_get_device_list(m_context, &list);

    if(count < 0)
        return devices;

    for(int i = 0; i < count; i++) {
        struct libusb_device_descriptor descr;

        libusb_get_device_descriptor(list[i], &descr);

        if(!is_dso(descr.idVendor, descr.idProduct))
            continue;

        QString device_id = QString("usb:%1.%2 VID %3 PID %4").arg(libusb_get_bus_number(list[i])).arg(libusb_get_device_address(list[i]))
                            .arg(descr.idVendor, 4, 16, QChar('0')).arg(descr.idProduct, 4, 16, QChar('0'));
        devices.append(device_id);

    }

    libusb_free_device_list(list, 1);

    return devices;
}

bool USBTransportPlugin::open(QString device, DSOTransport **transport, QString *error) {
    if(!device.startsWith("usb:"))
        return false;

    int semicolon = device.indexOf(':') + 1;
    int space = device.indexOf(' ');

    QStringList parts = device.mid(semicolon, space - semicolon).split('.');

    int nbus = parts[0].toInt(), ndevice = parts[1].toInt();

    libusb_device **list;

    int count = libusb_get_device_list(m_context, &list);

    if(count < 0)
        return false;

    for(int i = 0; i < count; i++) {
        if(libusb_get_bus_number(list[i]) == nbus && libusb_get_device_address(list[i]) == ndevice) {
            *transport = USBTransport::create(m_context, list[i], error);

            return true;
        }
    }

    libusb_free_device_list(list, 1);

    return false;
}

QString USBTransportPlugin::translate_libusb(int code) {
    switch(code) {
    case LIBUSB_SUCCESS:
            return tr("Success");

    case LIBUSB_ERROR_IO:
            return tr("Input/output error");


    case LIBUSB_ERROR_INVALID_PARAM:
            return tr("Invalid parameter");

    case LIBUSB_ERROR_ACCESS:
            return tr("Permission denied");

    case LIBUSB_ERROR_NO_DEVICE:
            return tr("Device not present");

    case LIBUSB_ERROR_NOT_FOUND:
            return tr("Not found");

    case LIBUSB_ERROR_BUSY:
            return tr("Busy");

    case LIBUSB_ERROR_TIMEOUT:
            return tr("Timeout");

    case LIBUSB_ERROR_OVERFLOW:
            return tr("Overflow");

    case LIBUSB_ERROR_PIPE:
            return tr("Broken pipe");

    case LIBUSB_ERROR_INTERRUPTED:
            return tr("Interrupted system call");

    case LIBUSB_ERROR_NO_MEM:
            return tr("Out of memory");

    case LIBUSB_ERROR_NOT_SUPPORTED:
            return tr("Not supported");

    case LIBUSB_ERROR_OTHER:
    default:
            return tr("Other error");
    }
}

bool USBTransportPlugin::is_dso(quint16 vendor, quint16 product) {
    for(int i = 0; m_devices[i].vid != 0; i++) {
        if(m_devices[i].vid == vendor && m_devices[i].pid == product)
            return true;
    }

    return false;
}

Q_EXPORT_PLUGIN2(transport_usb, USBTransportPlugin)

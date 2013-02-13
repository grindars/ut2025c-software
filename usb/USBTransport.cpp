#include <libusb.h>
#include "USBTransportPlugin.h"
#include "USBTransport.h"

USBTransport::USBTransport(libusb_device_handle *handle, QObject *parent) : QObject(parent), m_device(handle) {

}

USBTransport::~USBTransport() {
    libusb_release_interface(m_device, 0);
    libusb_close(m_device);
}

USBTransport *USBTransport::create(libusb_context *ctx, libusb_device *device, QString *error) {
    Q_UNUSED(ctx);

    libusb_device_handle *handle;

    int ret = libusb_open(device, &handle);

    if(ret != 0) {
        *error = USBTransportPlugin::translate_libusb(ret);

        return NULL;
    }

    ret = libusb_set_configuration(handle, 1);

    if(ret != 0) {
        *error = USBTransportPlugin::translate_libusb(ret);

        return NULL;
    }


    ret = libusb_claim_interface(handle, 0);

    if(ret != 0) {
        *error = USBTransportPlugin::translate_libusb(ret);

        libusb_close(handle);

        return NULL;
    }

    ret = libusb_set_interface_alt_setting(handle, 0, 0);

    if(ret != 0) {
        libusb_release_interface(handle, 0);

        *error = USBTransportPlugin::translate_libusb(ret);

        libusb_close(handle);

        return NULL;
    }

    ret =  libusb_reset_device(handle);

    if(ret != 0) {
        libusb_release_interface(handle, 0);

        *error = USBTransportPlugin::translate_libusb(ret);

        libusb_close(handle);

        return NULL;
    }

    return new USBTransport(handle);
}

QString USBTransport::errorString() const {
    return m_errorString;
}

bool USBTransport::req_out(quint16 request) {
    int ret = libusb_control_transfer(m_device, LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_ENDPOINT, RequestOut,
                                      request, 0, NULL, 0, 250);

    if(ret < 0) {
        m_errorString = USBTransportPlugin::translate_libusb(ret);

        return false;
    }

    return true;
}

bool USBTransport::req_in(quint16 request, QByteArray &data) {
    int ret = libusb_control_transfer(m_device, LIBUSB_ENDPOINT_IN | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_ENDPOINT, RequestIn,
                                      request, 0, (unsigned char *) data.data(), data.size(), 250);

    if(ret < 0) {
        m_errorString = USBTransportPlugin::translate_libusb(ret);

        return false;
    }

    data.resize(ret);

    return true;
}

bool USBTransport::data_in(QByteArray &data) {
    int ret = libusb_control_transfer(m_device, LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_ENDPOINT, RequestBulkSize,
                                      0, data.size() / 1024, NULL, 0, 250);

    if(ret < 0)
        goto libusb_error;

    int transferred;

    ret = libusb_bulk_transfer(m_device, LIBUSB_ENDPOINT_IN | 0x02, (unsigned char *) data.data(), data.size(), &transferred, 250);

    if(ret < 0)
        goto libusb_error;

    data.resize(transferred);

    return true;

libusb_error:
    m_errorString = USBTransportPlugin::translate_libusb(ret);

    return false;
}


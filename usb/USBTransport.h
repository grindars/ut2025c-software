#ifndef USBTRANSPORT_H
#define USBTRANSPORT_H

#include <QObject>
#include <DSOTransport.h>

struct libusb_context;
struct libusb_device;
struct libusb_device_handle;

class USBTransport : public QObject, public DSOTransport {
    Q_OBJECT

    enum {
        RequestBulkSize = 0xB0,
        RequestOut      = 0xB1,
        RequestIn       = 0xB2
    };

protected:
    explicit USBTransport(libusb_device_handle *handle, QObject *parent = 0);

public:
    static USBTransport *create(libusb_context *ctx, libusb_device *device, QString *error);
    virtual ~USBTransport();

    virtual bool req_out(quint16 request);
    virtual bool req_in(quint16 request, QByteArray &data);
    virtual bool data_in(QByteArray &data);

    virtual QString errorString() const;

private:
    libusb_device_handle *m_device;
    QString m_errorString;
};

#endif // USBTRANSPORT_H

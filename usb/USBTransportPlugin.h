#ifndef USBTRANSPORTPLUGIN_H
#define USBTRANSPORTPLUGIN_H

#include <QObject>
#include <TransportPlugin.h>

struct libusb_context;

class USBTransportPlugin : public QObject, public TransportPlugin {
    Q_OBJECT
    Q_INTERFACES(TransportPlugin)

public:
    explicit USBTransportPlugin(QObject *parent = 0);
    virtual ~USBTransportPlugin();

    virtual QStringList enumerate();
    virtual bool open(QString device, DSOTransport **transport, QString *error);

    static QString translate_libusb(int ret);

private:
    bool is_dso(quint16 vendor, quint16 product);

    libusb_context *m_context;

    typedef struct {
        quint16 vid;
        quint16 pid;
    } device_ids_t;

    static const device_ids_t m_devices[];
};

#endif // USBTRANSPORTPLUGIN_H

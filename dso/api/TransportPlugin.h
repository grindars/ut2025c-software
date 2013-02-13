#ifndef TRANSPORTPLUGIN_H
#define TRANSPORTPLUGIN_H

#include <QtPlugin>

class DSOTransport;

class TransportPlugin {
public:
    virtual QStringList enumerate() = 0;
    virtual bool open(QString device, DSOTransport **transport, QString *error) = 0;
};

Q_DECLARE_INTERFACE(TransportPlugin, "org.grindars.dso.TransportPlugin/1.0")

#endif // TRANSPORTPLUGIN_H

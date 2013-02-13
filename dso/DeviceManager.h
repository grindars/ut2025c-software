#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QStringList>

class DSO;
class TransportPlugin;
class DeviceManager : public QObject {
    Q_OBJECT

public:
    explicit DeviceManager(QObject *parent = 0);

    QStringList enumerate();
    DSO *open(QString device);

    QString errorString() const;

private:
    void loadPlugins();

    QList<TransportPlugin *> m_transports;

    QString m_errorString;
};

#endif // DEVICEMANAGER_H

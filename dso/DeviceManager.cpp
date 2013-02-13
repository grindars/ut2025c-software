#include <QCoreApplication>
#include <QDir>
#include <QtDebug>
#include <QLibrary>
#include <QPluginLoader>

#include "TransportPlugin.h"
#include "DeviceManager.h"
#include "DSOTransport.h"
#include "DSO.h"

DeviceManager::DeviceManager(QObject *parent) : QObject(parent) {
    loadPlugins();
}

void DeviceManager::loadPlugins() {
    foreach(QFileInfo info, QDir(QCoreApplication::applicationDirPath() + "/plugins").entryInfoList(QDir::Files)) {
        QString plugin = info.absoluteFilePath();

        if(!QLibrary::isLibrary(plugin))
            continue;

        QPluginLoader *loader = new QPluginLoader(plugin, this);

        if(!loader->load()) {
            qCritical() << "Load of" << plugin << "failed:" << loader->errorString();

            delete loader;

            continue;
        }

        TransportPlugin *transport = qobject_cast<TransportPlugin *>(loader->instance());

        if(transport == 0) {
            qCritical() << plugin << "is not a TransportPlugin";

            loader->unload();

            delete loader;

            continue;
        }

        m_transports.append(transport);
    }
}

QStringList DeviceManager::enumerate() {
    QStringList devices;

    for(QList<TransportPlugin *>::Iterator it = m_transports.begin(); it != m_transports.end(); it++) {
        devices += (*it)->enumerate();
    }

    return devices;
}

DSO *DeviceManager::open(QString device) {
    for(QList<TransportPlugin *>::Iterator it = m_transports.begin(); it != m_transports.end(); it++) {
        QString error;
        DSOTransport *ret;

        if((*it)->open(device, &ret, &error)) {
            if(ret == NULL) {
                m_errorString = error;

                return NULL;
            } else {
                return new DSO(ret);
            }
        }
    }

    m_errorString = tr("DSO '%1'' not found").arg(device);

    return NULL;
}

QString DeviceManager::errorString() const {
    return m_errorString;
}

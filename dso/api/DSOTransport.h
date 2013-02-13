#ifndef DSOTRANSPORT_H
#define DSOTRANSPORT_H

#include <QObject>

class DSOTransport {
public:
    virtual bool req_out(quint16 request) = 0;
    virtual bool req_in(quint16 request, QByteArray &data) = 0;
    virtual bool data_in(QByteArray &data) = 0;

    virtual QString errorString() const = 0;
};

#endif // DSOTRANSPORT_H

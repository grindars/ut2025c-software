#ifndef DSO_H
#define DSO_H

#include <QObject>

class DSOTransport;

class DSO : public QObject {
    Q_OBJECT

    enum {
        RequestProbe    = 0x00,
        RequestPrepare  = 0x2C,
        RequestPrepare2 = 0xCC,
        RequestFinish   = 0xDC,

        RequestSetSource = 0xE0,
        
        RequestPrepare3	= 0xF0,

        DataWaveform1   = 0x00,
        DataWaveform2   = 0x01,
        DataScreen      = 0x02
    };

public:
    explicit DSO(DSOTransport *transport, QObject *parent = 0);
    virtual ~DSO();

    QString errorString() const;

    bool probe(QByteArray &magic);

    bool captureScreen(QByteArray &data);

private:
    bool readData(quint8 id, QByteArray &data);

    DSOTransport *m_transport;
    QString m_errorString;
};

#endif // DSO_H

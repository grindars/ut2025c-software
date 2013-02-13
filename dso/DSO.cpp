#include "DSO.h"
#include "DSOTransport.h"

DSO::DSO(DSOTransport *transport, QObject *parent) : QObject(parent), m_transport(transport) {

}

DSO::~DSO() {
    delete m_transport;
}

bool DSO::probe(QByteArray &magic) {
    if(!m_transport->req_out(RequestPrepare))
        goto transport_error;

    magic.resize(8);

    if(!m_transport->req_in(RequestProbe, magic))
        goto transport_error;

    return true;

transport_error:
    m_errorString = m_transport->errorString();

    return false;
}

bool DSO::captureScreen(QByteArray &data) {
    if(!m_transport->req_out(RequestPrepare3))
        goto transport_error;

    for(int i = 0; i < 10; i++)
    	if(!m_transport->req_out(RequestPrepare))
            goto transport_error;

    for(int i = 0; i < 10; i++)
	if(!m_transport->req_out(RequestPrepare2))
            goto transport_error;

    data.resize(38912);

    if(!readData(DataScreen, data))
        goto transport_error;

    if(!m_transport->req_out(RequestFinish))
        goto transport_error;

    return true;

transport_error:
    m_errorString = m_transport->errorString();

    return false;
}

bool DSO::readData(quint8 id, QByteArray &data) {
    if(!m_transport->req_out(RequestSetSource | id))
        return false;

    return m_transport->data_in(data);
}

QString DSO::errorString() const {
    return m_errorString;
}

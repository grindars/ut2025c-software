#include <QtDebug>
#include <QPainter>

#include "DSO.h"
#include "DSOScreen.h"

DSOScreen::DSOScreen(DSO *dso, QWidget *parent) : QFrame(parent), m_screen(QImage(QSize(320, 240), QImage::Format_Indexed8)), m_dso(dso) {
    m_screen.setColorCount(16);

    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    QSize size(320, 240);
    size.setWidth(size.width() + frameWidth() * 2);
    size.setHeight(size.height() + frameWidth() * 2);

    setMinimumSize(size);
    setMaximumSize(size);

    qDebug() << contentsRect();

    QByteArray screen;
    screen.resize(320 * 240 / 2);

    if(dso->captureScreen(screen) == false) {
        qCritical() << dso->errorString();
    } else {
        unsigned char *bytes = m_screen.bits();
        unsigned char *nibbles = (unsigned char *) screen.data(), nibble;

        for(int i = 0; i < 320 * 240; i++) {
            if(i % 2) {
                nibble >>= 4;
            } else {
                nibble = *nibbles++;
            }

            *bytes++ = nibble & 0x0F;
        }
    }
}

void DSOScreen::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);

    QPainter painter;
    painter.begin(this);

    painter.drawImage(contentsRect(), m_screen, QRect(0, 0, 320, 240));

    painter.end();
}


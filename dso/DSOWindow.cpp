#include "DSOWindow.h"
#include "DSOScreen.h"
#include "DSO.h"

#include "ui_DSOWindow.h"

DSOWindow::DSOWindow(DSO *dso, QWidget *parent) : QMainWindow(parent), ui(new Ui::DSOWindow), m_dso(dso) {
    ui->setupUi(this);

    QByteArray magic(8, 0);

    if(dso->probe(magic) == false) {
        qFatal("Probe failed: %s", qPrintable(dso->errorString()));
    }

    qDebug("Magic: %s", magic.toHex().data());

    DSOScreen *screen = new DSOScreen(dso, this);

    setCentralWidget(screen);
}

DSOWindow::~DSOWindow() {
    delete ui;
}

void DSOWindow::changeEvent(QEvent *event) {
    QMainWindow::changeEvent(event);

    if(event->type() == QEvent::LocaleChange)
        ui->retranslateUi(this);
}

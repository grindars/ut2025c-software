#include <QTimer>

#include "DeviceSelectDialog.h"
#include "DeviceManager.h"

#include "ui_DeviceSelectDialog.h"

DeviceSelectDialog::DeviceSelectDialog(DeviceManager *devmgr, QWidget *parent) : QDialog(parent), ui(new Ui::DeviceSelectDialog) {
    ui->setupUi(this);

    ui->select->addItems(devmgr->enumerate());

    if(ui->select->count() == 1) {
        ui->select->setCurrentRow(0);

        QTimer::singleShot(0, this, SLOT(accept()));
    }
}

DeviceSelectDialog::~DeviceSelectDialog() {
    delete ui;
}

QString DeviceSelectDialog::selectedDevice() const {
    if(ui->select->currentItem() == NULL)
        return QString::null;
    else
        return ui->select->currentItem()->text();
}

void DeviceSelectDialog::changeEvent(QEvent *event) {
    QDialog::changeEvent(event);

    if(event->type() == QEvent::LocaleChange) {
        ui->retranslateUi(this);
    }
}

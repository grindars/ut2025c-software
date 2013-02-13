#include <QApplication>
#include <QtDebug>
#include <QMessageBox>

#include "DSO.h"
#include "DeviceManager.h"
#include "DeviceSelectDialog.h"
#include "DSOWindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    DeviceManager *devmgr = new DeviceManager;

    DeviceSelectDialog *select = new DeviceSelectDialog(devmgr);

    if(select->exec() == QDialog::Rejected) {
        delete select;

        return 0;
    }

    QString device = select->selectedDevice();

    qDebug() << "Opening" << device;

    DSO *dso = devmgr->open(device);

    if(dso == NULL) {
        QMessageBox::critical(0, app.translate("main", "Open DSO"), app.translate("main", "Unable to open DSO %1: %2").arg(device).arg(devmgr->errorString()));

        return 1;
    }

    DSOWindow *window = new DSOWindow(dso);

    window->show();

    return app.exec();
}

#ifndef __DEVICE_SELECT_DIALOG__H__
#define __DEVICE_SELECT_DIALOG__H__

#include <QDialog>

namespace Ui {
    class DeviceSelectDialog;
}

class DeviceManager;
class DSO;

class DeviceSelectDialog: public QDialog {
    Q_OBJECT

public:
    DeviceSelectDialog(DeviceManager *devmgr, QWidget *parent = 0);
    virtual ~DeviceSelectDialog();

    QString selectedDevice() const;

protected:
    virtual void changeEvent(QEvent *event);

private:
    Ui::DeviceSelectDialog *ui;
};

#endif

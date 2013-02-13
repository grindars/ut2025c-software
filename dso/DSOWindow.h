#ifndef __DSO_WINDOW__H__
#define __DSO_WINDOW__H__

#include <QMainWindow>

namespace Ui {
    class DSOWindow;
}

class DSO;

class DSOWindow: public QMainWindow {
    Q_OBJECT

public:
    DSOWindow(DSO *dso, QWidget *parent = 0);
    virtual ~DSOWindow();

protected:
    virtual void changeEvent(QEvent *event);

private:
    Ui::DSOWindow *ui;
    DSO *m_dso;
};

#endif

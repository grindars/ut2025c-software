#ifndef DSOSCREEN_H
#define DSOSCREEN_H

#include <QFrame>

class DSO;

class DSOScreen : public QFrame {
    Q_OBJECT

public:
    explicit DSOScreen(DSO *dso, QWidget *parent = 0);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QImage m_screen;
    DSO *m_dso;
};

#endif // DSOSCREEN_H

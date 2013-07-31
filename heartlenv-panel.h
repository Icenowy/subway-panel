#ifndef heartlenv_panel_H
#define heartlenv_panel_H

#include <QtGui/QMainWindow>
#include <QtGui/QDesktopWidget>
#include <QSettings>
#include <QtGui/QBoxLayout>
// A terrible hack... Qt do not allow include <X11/X.h> before <QApplication>
#include <QApplication>
#include <QtGui/QFrame>
#include <X11/X.h>
#include <libheartlenv/xfitman.h>

class heartlenv_panel : public QFrame
{
    Q_OBJECT
public:
    enum position_T{top,bottom,left,right};
public:
    heartlenv_panel(int len, int hei, heartlenv_panel::position_T pos, QString name);
    virtual ~heartlenv_panel();
protected:
    int length,height;
    position_T position;
    QDesktopWidget *desktop;
    void setScreenPos(const QPoint &pt);
    QSettings *settings;
    QLayout *layout;
    Display *display;
};

#endif // heartlenv_panel_H

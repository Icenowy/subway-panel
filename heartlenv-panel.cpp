#include "heartlenv-panel.h"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>

#include <QTypeInfo>

#include <QMessageBox>

#include <QX11Info>
#include <QLayout>
#include <QStackedLayout>

#include "applet-menu.h"

#include <libheartlenv/xfitman.h>


heartlenv_panel::heartlenv_panel(int len, int hei, heartlenv_panel::position_T pos, QString name): QFrame()
{
    desktop = QApplication::desktop();
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Window|Qt::WindowStaysOnTopHint);
    switch(pos)
    {
	case top:
	case bottom:
	if(len == 0)
	{
	    length = desktop->width();
	}
	else length = len;
	this->setMinimumWidth(length);
	this->setMaximumWidth(length);
	height = hei;
	this->setMaximumHeight(height);
	this->setMinimumHeight(height);
	layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
	((QBoxLayout*)layout)->setAlignment(Qt::AlignLeft);
	((QBoxLayout*)layout)->setSpacing(1);
	//layout = new QStackedLayout(this);
	//((QStackedLayout*)layout)->setStackingMode(QStackedLayout::StackAll);
	break;
    }
    switch(pos)
    {
	case top:
	  setScreenPos(QPoint(0,0));
	  break;
	case bottom:
	  setScreenPos(QPoint(0,desktop->height()-height));
	  break;
	case left:
	case right:
	  break;
    }
    settings = new QSettings("Heartlenv","Panel-" + name + "-Applets");
    if(settings->value("initialized","").toString() == "")
    {
	//Initialize new panel
	settings->setValue("initialized","y");
	settings->setValue("appletnum",1);
	settings->setValue("applet1","menu");
	settings->setValue("applet1-height",32);
	settings->setValue("applet1-width",32);
	//settings->setValue("applet1-align","left");
    }
    this->setLayout(layout);
    for(int i = 1;i<=settings->value("appletnum").toInt();i++)
    {
	QString applet_setting_name = QString("applet")+QVariant(i).toString();
	QString name = settings->value(applet_setting_name).toString();
	QWidget *applet;
	if(name == "menu")
	{
	    applet = new applet_menu(this);
	}
	else
	{
	    applet = new QWidget(this);
	}
	int tmp;
	if((tmp = settings->value(applet_setting_name+"-height").toInt()) != 0)
	{
	    applet->setMinimumHeight(tmp);
	    applet->setMaximumHeight(tmp);
	}
	if((tmp = settings->value(applet_setting_name+"-width").toInt()) != 0)
	{
	    applet->setMaximumWidth(tmp);
	    applet->setMinimumWidth(tmp);
	}
	layout->addWidget(applet);
    }
    this->setAttribute(Qt::WA_X11NetWmWindowTypeDock);
    display = this->x11Info().display();
    XfitMan fitman = xfitMan();
    switch(pos)
    {
      case bottom:
	fitman.setStrut(winId(),  0, 0, 0, height,
               /* Left   */   0, 0,
               /* Right  */   0, 0,
               /* Top    */   0, 0,
               /* Bottom */   0, desktop->width()
                         );
	break;
      case top:
	fitman.setStrut(winId(),  0, 0, height, 0,
               /* Left   */   0, 0,
               /* Right  */   0, 0,
               /* Top    */   0, desktop->width(),
               /* Bottom */   0, 0
                         );
    }
}

heartlenv_panel::~heartlenv_panel()
{
}

void heartlenv_panel::setScreenPos(const QPoint &pt)
{
    this->move(pt);
}


#include "heartlenv-panel.moc"

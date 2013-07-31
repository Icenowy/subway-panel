#include <QtGui/QApplication>
#include "heartlenv-panel.h"

#include <QSettings>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QSettings panel_set("Heartlenv","Panel-main");
    if(panel_set.value("initialized","") == "")
    {
      panel_set.setValue("initialized","y");
      panel_set.setValue("length",0);
      panel_set.setValue("weight",48);
      panel_set.setValue("direction","bottom");
    }
    int length = panel_set.value("length").toInt();
    int weight = panel_set.value("weight").toInt();
    heartlenv_panel::position_T direction;
    QString direction_val = panel_set.value("direction").toString();
    if(direction_val == "bottom")
    {
      direction = heartlenv_panel::bottom;
    }
    if(direction_val == "top")
    {
      direction = heartlenv_panel::top;
    }
    if(direction_val == "left")
    {
      direction = heartlenv_panel::left;
    }
    if(direction_val == "right")
    {
      direction = heartlenv_panel::right;
    }
    heartlenv_panel foo(length,weight,direction,"main");
    foo.show();
    return app.exec();
}
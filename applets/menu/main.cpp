/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "applet-menu.h"
#include <libheartlenv/loginserviceagent.h>
#include <QMessageBox>

applet_menu::applet_menu(QWidget* parent): QToolButton(parent), icon("/usr/share/pixmaps/qt4logo.png")
{
    //this->setText(tr(" Menu"));
    this->setIcon(QIcon("/usr/share/pixmaps/qt4logo.png"));
    connect(this,SIGNAL(released()),this,SLOT(showMenu()));
    //connect(this,SIGNAL(
    menu = new QMenu(NULL);
    QAction *tmp;
    tmp = menu->addAction("Suspend");
    connect(tmp,SIGNAL(triggered(bool)),this,SLOT(Suspend(bool)));
    //this->setMenu(menu);
}

void applet_menu::showMenu()
{
    if(parentWidget()->pos().y() != 0)
    {
	menu->move(parentWidget()->pos()-QPoint(0,menu->size().height()));
    }
    else if(parentWidget()->pos().x() != 0)
    {
	menu->move(this->pos()+parentWidget()->pos());
    }
    menu->show();
}

void applet_menu::Suspend(bool unused)
{
    LoginServiceAgent lsa;
    if(!lsa.canWork())
    {
	QMessageBox::warning(this,tr("Login Service Agent Cannot Work"),tr("Login Service Agent Cannot Work. No suitable Provider."));
    }
    if(!lsa.Suspend())
    {
	QMessageBox::warning(this,tr("Cannot Suspend"),tr("I cannot suspend.This is may because of you have not Systemd-logind, or you have no permission."));
    }
}

#include "applet-menu.moc"

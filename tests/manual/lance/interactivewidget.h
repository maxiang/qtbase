/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef INTERACTIVEWIDGET_H
#define INTERACTIVEWIDGET_H

#include "widgets.h"
#include "paintcommands.h"

#include <QtGui>

#include <private/qmath_p.h>

QT_FORWARD_DECLARE_CLASS(QToolBox)

class InteractiveWidget : public QMainWindow
{
    Q_OBJECT
public:
    InteractiveWidget();

public slots:
    void run();
    void load();
    void load(const QString &fname);
    void save();

protected:
    bool eventFilter(QObject *o, QEvent *e);

protected slots:
    void cmdSelected(QListWidgetItem *item);
    void enumSelected(QListWidgetItem *item);

private:
    QToolBox *m_commandsToolBox;
    QToolBox *m_enumsToolBox;
    OnScreenWidget<QWidget> *m_onScreenWidget;
    QTextEdit *ui_textEdit;
    QString m_filename;
};

#endif

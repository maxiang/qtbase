/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QABSTRACTSCROLLAREA_P_H
#define QABSTRACTSCROLLAREA_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "private/qframe_p.h"
#include "qabstractscrollarea.h"

QT_BEGIN_NAMESPACE

#ifndef QT_NO_SCROLLAREA

class QScrollBar;
class QAbstractScrollAreaScrollBarContainer;
class Q_WIDGETS_EXPORT QAbstractScrollAreaPrivate: public QFramePrivate
{
    Q_DECLARE_PUBLIC(QAbstractScrollArea)

public:
    QAbstractScrollAreaPrivate();

    void replaceScrollBar(QScrollBar *scrollBar, Qt::Orientation orientation);

    QAbstractScrollAreaScrollBarContainer *scrollBarContainers[Qt::Vertical + 1];
    QScrollBar *hbar, *vbar;
    Qt::ScrollBarPolicy vbarpolicy, hbarpolicy;

    QWidget *viewport;
    QWidget *cornerWidget;
    QRect cornerPaintingRect;
#ifdef Q_WS_MAC
    QRect reverseCornerPaintingRect;
#endif
    int left, top, right, bottom; // viewport margin

    int xoffset, yoffset;
    QPoint overshoot;

    void init();
    void layoutChildren();
    // ### Fix for 4.4, talk to Bjoern E or Girish.
    virtual void scrollBarPolicyChanged(Qt::Orientation, Qt::ScrollBarPolicy) {}
    bool canStartScrollingAt( const QPoint &startPos );

    void _q_hslide(int);
    void _q_vslide(int);
    void _q_showOrHideScrollBars();

    virtual QPoint contentsOffset() const;

    inline bool viewportEvent(QEvent *event)
    { return q_func()->viewportEvent(event); }
    QScopedPointer<QObject> viewportFilter;

#ifdef Q_WS_WIN
    bool singleFingerPanEnabled;
    void setSingleFingerPanEnabled(bool on = true);
#endif
};

class QAbstractScrollAreaFilter : public QObject
{
    Q_OBJECT
public:
    QAbstractScrollAreaFilter(QAbstractScrollAreaPrivate *p) : d(p)
    { setObjectName(QLatin1String("qt_abstractscrollarea_filter")); }
    bool eventFilter(QObject *o, QEvent *e)
    { return (o == d->viewport ? d->viewportEvent(e) : false); }
private:
    QAbstractScrollAreaPrivate *d;
};

class QBoxLayout;
class QAbstractScrollAreaScrollBarContainer : public QWidget
{
public:
    enum LogicalPosition { LogicalLeft = 1, LogicalRight = 2 };

    QAbstractScrollAreaScrollBarContainer(Qt::Orientation orientation, QWidget *parent);
    void addWidget(QWidget *widget, LogicalPosition position);
    QWidgetList widgets(LogicalPosition position);
    void removeWidget(QWidget *widget);

    QScrollBar *scrollBar;
    QBoxLayout *layout;
private:
    int scrollBarLayoutIndex() const;

    Qt::Orientation orientation;
};

#endif // QT_NO_SCROLLAREA

QT_END_NAMESPACE

#endif // QABSTRACTSCROLLAREA_P_H

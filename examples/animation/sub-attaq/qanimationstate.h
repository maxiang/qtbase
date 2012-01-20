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

#ifndef QANIMATIONSTATE_H
#define QANIMATIONSTATE_H

#ifndef QT_STATEMACHINE_SOLUTION
#  include <QtCore/qstate.h>
#  include <QtCore/qabstractanimation.h>
#else
#  include "qstate.h"
#  include "qabstractanimation.h"
#endif

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

#ifndef QT_NO_ANIMATION

class QAbstractAnimation;

class QAnimationState : public QState
{
    Q_OBJECT
public:
    QAnimationState(QState *parent = 0);
    ~QAnimationState();

    void setAnimation(QAbstractAnimation *animation);
    QAbstractAnimation* animation() const;

signals:
    void animationFinished();

protected:
    void onEntry(QEvent *);
    void onExit(QEvent *);
    bool event(QEvent *e);

private:
    Q_DISABLE_COPY(QAnimationState)
    QAbstractAnimation *m_animation;
};

#endif

QT_END_NAMESPACE

QT_END_HEADER

#endif // QANIMATIONSTATE_H

/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the QtCore module of the Qt Toolkit.
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

//Own
#include "torpedo.h"
#include "pixmapitem.h"
#include "boat.h"
#include "graphicsscene.h"
#include "animationmanager.h"
#include "qanimationstate.h"

#include <QtCore/QPropertyAnimation>
#include <QtCore/QStateMachine>
#include <QtCore/QFinalState>

Torpedo::Torpedo() : PixmapItem(QString::fromLatin1("torpedo"),GraphicsScene::Big),
    currentSpeed(0)
{
    setZValue(2);
}

void Torpedo::launch()
{
    QPropertyAnimation *launchAnimation = new QPropertyAnimation(this, "pos");
    AnimationManager::self()->registerAnimation(launchAnimation);
    launchAnimation->setEndValue(QPointF(x(),qobject_cast<GraphicsScene *>(scene())->sealLevel() - 15));
    launchAnimation->setEasingCurve(QEasingCurve::InQuad);
    launchAnimation->setDuration(y()/currentSpeed*10);
    connect(launchAnimation,SIGNAL(valueChanged(QVariant)),this,SLOT(onAnimationLaunchValueChanged(QVariant)));
    connect(this,SIGNAL(torpedoExploded()), launchAnimation, SLOT(stop()));

    //We setup the state machine of the torpedo
    QStateMachine *machine = new QStateMachine(this);

    //This state is when the launch animation is playing
    QAnimationState *launched = new QAnimationState(machine);
    launched->setAnimation(launchAnimation);

    //End
    QFinalState *final = new QFinalState(machine);

    machine->setInitialState(launched);

    //### Add a nice animation when the torpedo is destroyed
    launched->addTransition(this, SIGNAL(torpedoExploded()),final);

    //If the animation is finished, then we move to the final state
    launched->addTransition(launched, SIGNAL(animationFinished()), final);

    //The machine has finished to be executed, then the boat is dead
    connect(machine,SIGNAL(finished()),this, SIGNAL(torpedoExecutionFinished()));

    machine->start();
}

void Torpedo::setCurrentSpeed(int speed)
{
    if (speed < 0) {
        qWarning("Torpedo::setCurrentSpeed : The speed is invalid");
        return;
    }
    currentSpeed = speed;
}

void Torpedo::onAnimationLaunchValueChanged(const QVariant &)
{
    foreach (QGraphicsItem *item , collidingItems(Qt::IntersectsItemBoundingRect)) {
        if (Boat *b = qgraphicsitem_cast<Boat*>(item))
            b->destroy();
    }
}

void Torpedo::destroy()
{
    emit torpedoExploded();
}

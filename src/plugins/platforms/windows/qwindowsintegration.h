/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the plugins of the Qt Toolkit.
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

#ifndef QWINDOWSINTEGRATION_H
#define QWINDOWSINTEGRATION_H

#include <QtGui/QPlatformIntegration>
#include <QtCore/QScopedPointer>

QT_BEGIN_NAMESPACE

struct QWindowsIntegrationPrivate;

class QWindowsIntegration : public QPlatformIntegration
{
public:
    QWindowsIntegration();
    virtual ~QWindowsIntegration();

    bool hasCapability(QPlatformIntegration::Capability cap) const;

    virtual QPlatformPixmap *createPlatformPixmap(QPlatformPixmap::PixelType type) const;
    QPlatformWindow *createPlatformWindow(QWindow *window) const;
    QPlatformBackingStore *createPlatformBackingStore(QWindow *window) const;
    virtual QPlatformOpenGLContext *createPlatformOpenGLContext(QOpenGLContext *context) const;
    virtual QAbstractEventDispatcher *guiThreadEventDispatcher() const;

    virtual QPlatformClipboard *clipboard() const;
    virtual QPlatformDrag *drag() const;
    virtual QPlatformInputContext *inputContext() const;
    virtual QPlatformAccessibility *accessibility() const;
    virtual QPlatformNativeInterface *nativeInterface() const;
    virtual QPlatformFontDatabase *fontDatabase() const;
    virtual QPlatformTheme *platformTheme() const;
    virtual QVariant styleHint(StyleHint hint) const;

    static QWindowsIntegration *instance();

    inline void emitScreenAdded(QPlatformScreen *s) { screenAdded(s); }

private:
    QScopedPointer<QWindowsIntegrationPrivate> d;
};

QT_END_NAMESPACE

#endif

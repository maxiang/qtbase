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

#ifndef QGLXINTEGRATION_H
#define QGLXINTEGRATION_H

#include "qxcbwindow.h"
#include "qxcbscreen.h"

#include <QtGui/QPlatformOpenGLContext>
#include <QtGui/QSurfaceFormat>

#include <QtCore/QMutex>

#include <GL/glx.h>

QT_BEGIN_NAMESPACE

class QGLXContext : public QPlatformOpenGLContext
{
public:
    QGLXContext(QXcbScreen *xd, const QSurfaceFormat &format, QPlatformOpenGLContext *share);
    ~QGLXContext();

    bool makeCurrent(QPlatformSurface *surface);
    void doneCurrent();
    void swapBuffers(QPlatformSurface *surface);
    void (*getProcAddress(const QByteArray &procName)) ();

    QSurfaceFormat format() const;
    bool isSharing() const;
    bool isValid() const;

    GLXContext glxContext() const { return m_context; }

private:
    QXcbScreen *m_screen;
    GLXContext m_context;
    GLXContext m_shareContext;
    QSurfaceFormat m_format;
};

QT_END_NAMESPACE

#endif

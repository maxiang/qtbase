/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the QtOpenGL module of the Qt Toolkit.
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

#include <QApplication>
#include <private/qapplication_p.h>
#include <QPixmap>
#include <QDebug>

#include <private/qapplication_p.h>
#include <QtGui/QPlatformOpenGLContext>
#include <QtGui/QPlatformWindow>
#include <QtGui/QSurfaceFormat>

#include "qgl.h"
#include "qgl_p.h"

QT_BEGIN_NAMESPACE

/*!
    Returns an OpenGL format for the window format specified by \a format.
*/
QGLFormat QGLFormat::fromSurfaceFormat(const QSurfaceFormat &format)
{
    QGLFormat retFormat;
    if (format.alphaBufferSize() >= 0)
        retFormat.setAlphaBufferSize(format.alphaBufferSize());
    if (format.blueBufferSize() >= 0)
        retFormat.setBlueBufferSize(format.blueBufferSize());
    if (format.greenBufferSize() >= 0)
        retFormat.setGreenBufferSize(format.greenBufferSize());
    if (format.redBufferSize() >= 0)
        retFormat.setRedBufferSize(format.redBufferSize());
    if (format.depthBufferSize() >= 0)
        retFormat.setDepthBufferSize(format.depthBufferSize());
    if (format.samples() > 1) {
        retFormat.setSampleBuffers(format.samples());
        retFormat.setSamples(true);
    }
    if (format.stencilBufferSize() > 0) {
        retFormat.setStencil(true);
        retFormat.setStencilBufferSize(format.stencilBufferSize());
    }
    retFormat.setDoubleBuffer(format.swapBehavior() != QSurfaceFormat::SingleBuffer);
    retFormat.setStereo(format.stereo());
    return retFormat;
}

/*!
    Returns a window format for the OpenGL format specified by \a format.
*/
QSurfaceFormat QGLFormat::toSurfaceFormat(const QGLFormat &format)
{
    QSurfaceFormat retFormat;
    if (format.alpha())
        retFormat.setAlphaBufferSize(format.alphaBufferSize() == -1 ? 1 : format.alphaBufferSize());
    if (format.blueBufferSize() >= 0)
        retFormat.setBlueBufferSize(format.blueBufferSize());
    if (format.greenBufferSize() >= 0)
        retFormat.setGreenBufferSize(format.greenBufferSize());
    if (format.redBufferSize() >= 0)
        retFormat.setRedBufferSize(format.redBufferSize());
    if (format.depth())
        retFormat.setDepthBufferSize(format.depthBufferSize() == -1 ? 1 : format.depthBufferSize());
    retFormat.setSwapBehavior(format.doubleBuffer() ? QSurfaceFormat::DoubleBuffer : QSurfaceFormat::DefaultSwapBehavior);
    if (format.sampleBuffers())
        retFormat.setSamples(format.samples() == -1 ? 4 : format.samples());
    if (format.stencil())
        retFormat.setStencilBufferSize(format.stencilBufferSize() == -1 ? 1 : format.stencilBufferSize());
    retFormat.setStereo(format.stereo());
    return retFormat;
}

void QGLContextPrivate::setupSharing() {
    Q_Q(QGLContext);
    QOpenGLContext *sharedContext = guiGlContext->shareContext();
    if (sharedContext) {
        QGLContext *actualSharedContext = QGLContext::fromOpenGLContext(sharedContext);
        sharing = true;
        QGLContextGroup::addShare(q, actualSharedContext);
    }
}

bool QGLFormat::hasOpenGL()
{
    return QApplicationPrivate::platformIntegration()
            ->hasCapability(QPlatformIntegration::OpenGL);
}

void qDeleteQGLContext(void *handle)
{
    QGLContext *context = static_cast<QGLContext *>(handle);
    delete context;
}

bool QGLContext::chooseContext(const QGLContext* shareContext)
{
    Q_D(QGLContext);
    if(!d->paintDevice || d->paintDevice->devType() != QInternal::Widget) {
        d->valid = false;
    }else {
        QWidget *widget = static_cast<QWidget *>(d->paintDevice);
        QGLFormat glformat = format();
        QSurfaceFormat winFormat = QGLFormat::toSurfaceFormat(glformat);
        if (widget->testAttribute(Qt::WA_TranslucentBackground))
            winFormat.setAlphaBufferSize(qMax(winFormat.alphaBufferSize(), 8));

        if (!widget->windowHandle()->handle()) {
            widget->windowHandle()->setSurfaceType(QWindow::OpenGLSurface);
            widget->windowHandle()->setFormat(winFormat);
            widget->winId();//make window
        }

        if (d->ownContext)
            delete d->guiGlContext;
        d->ownContext = true;
        QOpenGLContext *shareGlContext = shareContext ? shareContext->d_func()->guiGlContext : 0;
        d->guiGlContext = new QOpenGLContext;
        d->guiGlContext->setFormat(winFormat);
        d->guiGlContext->setShareContext(shareGlContext);
        d->valid = d->guiGlContext->create();

        if (d->valid)
            d->guiGlContext->setQGLContextHandle(this,qDeleteQGLContext);

        d->glFormat = QGLFormat::fromSurfaceFormat(d->guiGlContext->format());
        d->setupSharing();
    }


    return d->valid;
}

void QGLContext::reset()
{
    Q_D(QGLContext);
    if (!d->valid)
        return;
    d->cleanup();

    d->crWin = false;
    d->sharing = false;
    d->valid = false;
    d->transpColor = QColor();
    d->initDone = false;
    QGLContextGroup::removeShare(this);
    if (d->guiGlContext) {
        if (d->ownContext)
            delete d->guiGlContext;
        else
            d->guiGlContext->setQGLContextHandle(0,0);
        d->guiGlContext = 0;
    }
    d->ownContext = false;
}

void QGLContext::makeCurrent()
{
    Q_D(QGLContext);
    if (!d->paintDevice || d->paintDevice->devType() != QInternal::Widget)
        return;

    QWidget *widget = static_cast<QWidget *>(d->paintDevice);
    if (!widget->windowHandle())
        return;

    if (d->guiGlContext->makeCurrent(widget->windowHandle())) {
        if (!d->workaroundsCached) {
            d->workaroundsCached = true;
            const char *renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
            if (renderer && strstr(renderer, "Mali")) {
                d->workaround_brokenFBOReadBack = true;
            }
        }
    }
}

void QGLContext::doneCurrent()
{
    Q_D(QGLContext);
    d->guiGlContext->doneCurrent();
}

void QGLContext::swapBuffers() const
{
    Q_D(const QGLContext);
    if (!d->paintDevice || d->paintDevice->devType() != QInternal::Widget)
        return;

    QWidget *widget = static_cast<QWidget *>(d->paintDevice);
    if (!widget->windowHandle())
        return;

    d->guiGlContext->swapBuffers(widget->windowHandle());
}

QFunctionPointer QGLContext::getProcAddress(const QString &procName) const
{
    Q_D(const QGLContext);
    return d->guiGlContext->getProcAddress(procName.toAscii());
}

void QGLWidget::setContext(QGLContext *context,
                            const QGLContext* shareContext,
                            bool deleteOldContext)
{
    Q_D(QGLWidget);
    if (context == 0) {
        qWarning("QGLWidget::setContext: Cannot set null context");
        return;
    }

    if (context->device() == 0) // a context may refere to more than 1 window.
        context->setDevice(this); //but its better to point to 1 of them than none of them.

    QGLContext* oldcx = d->glcx;
    d->glcx = context;

    if (!d->glcx->isValid())
        d->glcx->create(shareContext ? shareContext : oldcx);

    if (deleteOldContext)
        delete oldcx;
}

void QGLWidgetPrivate::init(QGLContext *context, const QGLWidget *shareWidget)
{
    initContext(context, shareWidget);
}

bool QGLFormat::hasOpenGLOverlays()
{
    return false;
}

QColor QGLContext::overlayTransparentColor() const
{
    return QColor(); // Invalid color
}

uint QGLContext::colorIndex(const QColor&) const
{
    return 0;
}

void QGLContext::generateFontDisplayLists(const QFont & fnt, int listBase)
{
    Q_UNUSED(fnt);
    Q_UNUSED(listBase);
}

/*
    QGLTemporaryContext implementation
*/
class QGLTemporaryContextPrivate
{
public:
    QWindow *window;
    QOpenGLContext *context;

    QGLContext *oldContext;
};

QGLTemporaryContext::QGLTemporaryContext(bool, QWidget *)
    : d(new QGLTemporaryContextPrivate)
{
    d->oldContext = const_cast<QGLContext *>(QGLContext::currentContext());

    d->window = new QWindow;
    d->window->setSurfaceType(QWindow::OpenGLSurface);
    d->window->setGeometry(QRect(0, 0, 3, 3));
    d->window->create();

    d->context = new QOpenGLContext;
    d->context->create();
    d->context->makeCurrent(d->window);
}

QGLTemporaryContext::~QGLTemporaryContext()
{
    if (d->oldContext)
        d->oldContext->makeCurrent();

    delete d->context;
    delete d->window;
}


bool QGLWidgetPrivate::renderCxPm(QPixmap*)
{
    return false;
}

/*! \internal
  Free up any allocated colormaps. This fn is only called for
  top-level widgets.
*/
void QGLWidgetPrivate::cleanupColormaps()
{
}

void QGLWidget::setMouseTracking(bool enable)
{
    Q_UNUSED(enable);
}

bool QGLWidget::event(QEvent *e)
{
    return QWidget::event(e);
}

void QGLWidget::resizeEvent(QResizeEvent *e)
{
    Q_D(QGLWidget);

    QWidget::resizeEvent(e);
    if (!isValid())
        return;
    makeCurrent();
    if (!d->glcx->initialized())
        glInit();
    resizeGL(width(), height());
}


const QGLContext* QGLWidget::overlayContext() const
{
    return 0;
}

void QGLWidget::makeOverlayCurrent()
{
}


void QGLWidget::updateOverlayGL()
{
}

const QGLColormap & QGLWidget::colormap() const
{
    Q_D(const QGLWidget);
    return d->cmap;
}

void QGLWidget::setColormap(const QGLColormap & c)
{
    Q_UNUSED(c);
}

QGLContext::QGLContext(QOpenGLContext *context)
    : d_ptr(new QGLContextPrivate(this))
{
    Q_D(QGLContext);
    d->init(0, QGLFormat::fromSurfaceFormat(context->format()));
    d->guiGlContext = context;
    d->guiGlContext->setQGLContextHandle(this,qDeleteQGLContext);
    d->ownContext = false;
    d->valid = context->isValid();
    d->setupSharing();
}

QOpenGLContext *QGLContext::contextHandle() const
{
    Q_D(const QGLContext);
    return d->guiGlContext;
}

/*!
    Returns a OpenGL context for the window context specified by \a windowContext
*/
QGLContext *QGLContext::fromOpenGLContext(QOpenGLContext *context)
{
    if (!context)
        return 0;
    if (context->qGLContextHandle()) {
        return reinterpret_cast<QGLContext *>(context->qGLContextHandle());
    }
    QGLContext *glContext = new QGLContext(context);
    //Dont call create on context. This can cause the platformFormat to be set on the widget, which
    //will cause the platformWindow to be recreated.
    return glContext;
}

QT_END_NAMESPACE

/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include "renderthread.h"

RenderThread::RenderThread(QObject *parent)
    : QThread(parent)
{
    m_abort = false;
}

RenderThread::~RenderThread()
{
    mutex.lock();
    m_abort = true;
    mutex.unlock();

    wait();
}

//![processing the image (start)]
void RenderThread::processImage(const QImage &image)
{
    if (image.isNull())
        return;

    m_image = image;
    m_abort = false;
    start();
}

void RenderThread::run()
{
    int size = qMax(m_image.width()/20, m_image.height()/20);
    for (int s = size; s > 0; --s) {
        for (int c = 0; c < 400; ++c) {
//![processing the image (start)]
            int x1 = qMax(0, (qrand() % m_image.width()) - s/2);
            int x2 = qMin(x1 + s/2 + 1, m_image.width());
            int y1 = qMax(0, (qrand() % m_image.height()) - s/2);
            int y2 = qMin(y1 + s/2 + 1, m_image.height());
            int n = 0;
            int red = 0;
            int green = 0;
            int blue = 0;
            for (int i = y1; i < y2; ++i) {
                for (int j = x1; j < x2; ++j) {
                    QRgb pixel = m_image.pixel(j, i);
                    red += qRed(pixel);
                    green += qGreen(pixel);
                    blue += qBlue(pixel);
                    n += 1;
                }
            }
//![processing the image (finish)]
            Block block(QRect(x1, y1, x2 - x1 + 1, y2 - y1 + 1),
                        QColor(red/n, green/n, blue/n));
            emit sendBlock(block);
            if (m_abort)
                return;
            msleep(10);
        }
    }
}
//![processing the image (finish)]

void RenderThread::stopProcess()
{
    mutex.lock();
    m_abort = true;
    mutex.unlock();
}

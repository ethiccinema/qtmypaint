/*
Copyright (c) 2016, François Téchené
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef MPHANDLER_H
#define MPHANDLER_H

#include <QColor>

#include "mypaint-brush.h"
#include "mypaint-surface.h"

#include "mpbrush.h"
#include "mpsurface.h"

#ifndef QTMYPAINT_SURFACE_WIDTH
#define QTMYPAINT_SURFACE_WIDTH 100
#endif

#ifndef QTMYPAINT_SURFACE_HEIGHT
#define QTMYPAINT_SURFACE_HEIGHT 100
#endif


class MPHandler : public QObject
{
    Q_OBJECT

public:
    ~MPHandler();

    static MPHandler *handler();

    typedef void (*MPOnUpdateFunction) (MPHandler *handler, MPSurface *surface, MPTile *tile);

    void startStroke();
    void strokeTo(float x, float y, float pressure, float xtilt, float ytilt);
    void strokeTo(float x, float y);
    void endStroke();

    float getBrushValue(MyPaintBrushSetting setting);

    void setBrushColor(QColor newColor);
    void setBrushValue(MyPaintBrushSetting setting, float value);

    void requestUpdateTile(MPSurface *surface, MPTile *tile);
    void hasNewTile(MPSurface *surface, MPTile *tile);
    void hasClearedSurface(MPSurface *surface);

    void setSurfaceSize(QSize size);
    QSize surfaceSize();

    void clearSurface();
    QImage renderImage();

    void loadImage(const QImage &image);


public slots:
    void loadBrush(const QByteArray& content);

private:
    MPHandler();
    static bool instanceFlag;
    static MPHandler *currentHandler;

    MPBrush *   m_brush;
    MPSurface * m_surface;

signals:
    void updateTile(MPSurface *surface, MPTile *tile);
    void newTile(MPSurface *surface, MPTile *tile);
    void clearedSurface(MPSurface *surface);

};

#endif // MPHANDLER_H

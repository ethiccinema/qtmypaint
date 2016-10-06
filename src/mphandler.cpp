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
#include "mphandler.h"

#include "mypaint-brush.h"
#include "mypaint-surface.h"

#include "libmypaint.c"

#define HAVE_JSON_C;

#define DEFAULT_BRUSHES_PATH ":brushes"

bool MPHandler::instanceFlag = false;
MPHandler* MPHandler::currentHandler = NULL;

static void
onUpdatedTile(MPSurface *surface, MPTile *tile)
{
    MPHandler* handler = MPHandler::handler();
    handler->requestUpdateTile(surface, tile);
}

static void
onNewTile(MPSurface *surface, MPTile *tile)
{
    MPHandler* handler = MPHandler::handler();
    handler->hasNewTile(surface, tile);
}

static void
onClearedSurface(MPSurface *surface)
{
    MPHandler* handler = MPHandler::handler();
    handler->hasClearedSurface(surface);
}

MPHandler *
MPHandler::handler()
{
    if(! instanceFlag)
    {
        currentHandler = new MPHandler();
        instanceFlag = true;
    }

    return currentHandler;

}

MPHandler::MPHandler()
{
    QSize defaultSize = QSize(  QTMYPAINT_SURFACE_WIDTH,
                                QTMYPAINT_SURFACE_HEIGHT ) ;

    m_brush = new MPBrush();
    m_surface = new MPSurface(defaultSize);

    this->m_surface->setOnUpdateTile(onUpdatedTile);
    this->m_surface->setOnNewTile(onNewTile);
    this->m_surface->setOnClearedSurface(onClearedSurface);
}

MPHandler::~MPHandler()
{
    mypaint_surface_unref((MyPaintSurface *)m_surface);
}

void
MPHandler::requestUpdateTile(MPSurface *surface, MPTile *tile)
{
    emit updateTile(surface, tile);
}

void
MPHandler::hasNewTile(MPSurface *surface, MPTile *tile)
{
    emit newTile(surface, tile);
}

void MPHandler::hasClearedSurface(MPSurface *surface)
{
    emit clearedSurface(surface);
}

void MPHandler::setSurfaceSize(QSize size)
{
    m_surface->setSize(size);
}

QSize MPHandler::surfaceSize()
{
    return m_surface->size();
}

void MPHandler::clearSurface()
{
    m_surface->clear();
}

QImage MPHandler::renderImage()
{
    QImage image = m_surface->renderImage();
    return image;
}

void MPHandler::loadImage(const QImage &image)
{
    m_surface->loadImage(image);
}

void MPHandler::loadBrush(const QByteArray &content)
{
    m_brush->load(content);
}

void
MPHandler::strokeTo(float x, float y, float pressure, float xtilt, float ytilt)
{
    float dtime = 1.0/10;
    mypaint_surface_begin_atomic((MyPaintSurface *)m_surface);
    mypaint_brush_stroke_to(m_brush->brush, (MyPaintSurface *)m_surface, x, y, pressure, xtilt, ytilt, dtime);
    MyPaintRectangle roi;
    mypaint_surface_end_atomic((MyPaintSurface *)m_surface, &roi);
}

void
MPHandler::startStroke()
{
    mypaint_brush_reset (m_brush->brush);
    mypaint_brush_new_stroke(m_brush->brush);
}

void
MPHandler::strokeTo(float x, float y)
{
    float pressure = 1.0;
    float xtilt = 0.0;
    float ytilt = 0.0;
    strokeTo(x, y, pressure, xtilt, ytilt);
}

void
MPHandler::endStroke()
{

}

float MPHandler::getBrushValue(MyPaintBrushSetting setting)
{
    return this->m_brush->getValue(setting);
}

void
MPHandler::setBrushColor(QColor newColor)
{
    this->m_brush->setColor(newColor);
}

void MPHandler::setBrushValue(MyPaintBrushSetting setting, float value)
{
    this->m_brush->setValue(setting, value);
}

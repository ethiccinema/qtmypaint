#include "mphandler.h"

#include "mypaint-brush.h"
#include "mypaint-surface.h"

#include "libmypaint.c"

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
    m_brush = new MPBrush();
    m_surface = new MPSurface(1920, 1080);

    this->m_surface->setOnUpdateTile(onUpdatedTile);
    this->m_surface->setOnNewTile(onNewTile);
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

void
MPHandler::setBrushColor(QColor newColor)
{
    this->m_brush->setColor(newColor);
}

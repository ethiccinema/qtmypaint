/*
    Copyright © 2015 by The QTMyPaint Project

    This file is part of QTMyPaint, a Qt-based interface for MyPaint C++ library.

    QTMyPaint is libre software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QTMyPaint is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QTMyPaint. If not, see <http://www.gnu.org/licenses/>.
*/

#include "mpsurface.h"

static void freeTiledSurface(MyPaintSurface *surface)
{
    MPSurface *self = (MPSurface *)surface;
    mypaint_tiled_surface_destroy(self);

    free(self->tile_buffer);
    free(self->null_tile);
    free(self);
}

static void defaultUpdateFonction(MPSurface *surface, MPTile *tile)
{
    Q_UNUSED(surface);
    Q_UNUSED(tile);
    // Things to do if no update callback has been affected
}

static void onTileRequestStart(MyPaintTiledSurface *tiled_surface, MyPaintTileRequest *request)
{
    MPSurface *self = (MPSurface *)tiled_surface;

    const int tx = request->tx;
    const int ty = request->ty;
    uint16_t *tile_pointer = NULL;

    if (tx >= self->getTilesWidth() || ty >= self->getTilesHeight() || tx < 0 || ty < 0) {
        // Give it a tile which we will ignore writes to
        tile_pointer = self->null_tile;
    } else {
        MPTile* tile = self->getTileFromIdx(QPoint(tx,ty));
        tile_pointer = tile ? tile->Bits(false) : NULL;
    }

    request->buffer = tile_pointer;
}

static void onTileRequestEnd(MyPaintTiledSurface *tiled_surface, MyPaintTileRequest *request)
{
    MPSurface *self = (MPSurface *)tiled_surface;

    const int tx = request->tx;
    const int ty = request->ty;

    MPTile* tile = self->getTileFromIdx(QPoint(tx,ty));
    if (tile) tile->updateCache();

    self->onUpdateTileFunction(self, tile);
}

MPSurface::MPSurface(QSize size)
{
    // Init callbacks
    //
    this->onUpdateTileFunction   = defaultUpdateFonction;
    this->onNewTileFunction      = defaultUpdateFonction;

    // MPSurface vfuncs
    this->parent.destroy = freeTiledSurface;

    resetSurface(size);

    mypaint_tiled_surface_init((MyPaintTiledSurface *)this, onTileRequestStart, onTileRequestEnd);
}

MPSurface::~MPSurface()
{

}

void MPSurface::setOnUpdateTile(MPOnUpdateTileFunction onUpdateFunction)
{
    this->onUpdateTileFunction = onUpdateFunction;
}

void MPSurface::setOnNewTile(MPOnUpdateTileFunction onNewTileFunction)
{
    this->onNewTileFunction = onNewTileFunction;
}

void MPSurface::setOnClearedSurface(MPOnUpdateSurfaceFunction onClearedSurfaceFunction)
{
    this->onClearedSurfaceFunction = onClearedSurfaceFunction;
}

void MPSurface::setSize(QSize size)
{
    free(this->tile_buffer);
    free(this->null_tile);

    resetSurface(size);
}

void MPSurface::clear()
{
    foreach(QGraphicsItem *item, surfaceScene.items())
    {
      MPTile *tile = qgraphicsitem_cast<MPTile *>(item);
      if (tile)
      {
        tile->clear();
      }
    }

    this->onClearedSurfaceFunction(this);
}

void MPSurface::render(QPainter *painter)
{
    surfaceScene.render(painter);
}

int MPSurface::getTilesWidth()
{
    return this->tiles_width;
}

int MPSurface::getTilesHeight()
{
    return this->tiles_height;
}

int MPSurface::getWidth()
{
    return this->width;
}

int MPSurface::getHeight()
{
    return this->height;
}

void MPSurface::resetNullTile()
{
    memset(this->null_tile, 0, this->tile_size);
}

void MPSurface::resetSurface(QSize size)
{
    width = size.width();
    height = size.height();

    assert(width > 0);
    assert(height > 0);

    surfaceScene.setSceneRect(QRect(QPoint(0,0), size));

    const int tile_size_pixels = MYPAINT_TILE_SIZE;

    const int tiles_width = ceil((float)width / tile_size_pixels);
    const int tiles_height = ceil((float)height / tile_size_pixels);

    const size_t tile_size = tile_size_pixels * tile_size_pixels * 4 * sizeof(uint16_t);
    const size_t buffer_size = tiles_width * tiles_height * tile_size;

    assert(tile_size_pixels*tiles_width >= width);
    assert(tile_size_pixels*tiles_height >= height);
    assert(buffer_size >= width*height*4*sizeof(uint16_t));

    uint16_t* buffer = (uint16_t *)malloc(buffer_size);
    if (!buffer)
        fprintf(stderr, "CRITICAL: unable to allocate enough memory: %Zu bytes", buffer_size);

    memset(buffer, 255, buffer_size);

    this->tile_buffer = buffer;
    this->tile_size = tile_size;
    this->null_tile = (uint16_t *)malloc(tile_size);
    this->tiles_width = tiles_width;
    this->tiles_height = tiles_height;

    resetNullTile();
}

MPTile* MPSurface::getTileFromPos(const QPoint& pos)
{
    return getTileFromIdx(getTileIndex(pos));
}

MPTile* MPSurface::getTileFromIdx(const QPoint& idx)
{

    QTransform transform;
    MPTile* selectedTile = (MPTile*)surfaceScene.itemAt(idx, transform);

    if (!selectedTile) {
        selectedTile = new MPTile();
        QPoint tilePos ( getTilePos(idx) );
        selectedTile->setPos(tilePos);

        surfaceScene.addItem(selectedTile);
        this->onNewTileFunction(this, selectedTile);
    }

    return selectedTile;
}

inline bool MPSurface::checkIndex(uint n)
{
    return ((int)n<k_max);
}

inline QPoint MPSurface::getTilePos(const QPoint& idx)
{
    return QPoint(MYPAINT_TILE_SIZE*idx.x(), MYPAINT_TILE_SIZE*idx.y());
}

inline QPoint MPSurface::getTileIndex(const QPoint& pos)
{
    return QPoint(pos.x()/MYPAINT_TILE_SIZE, pos.y()/MYPAINT_TILE_SIZE);
}

inline QPointF MPSurface::getTileFIndex(const QPoint& pos)
{
    return QPointF((qreal)pos.x()/MYPAINT_TILE_SIZE, (qreal)pos.y()/MYPAINT_TILE_SIZE);
}

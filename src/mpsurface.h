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

#ifndef MPSURFACE_H
#define MPSURFACE_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <QGraphicsScene>
#include <QImage>

#include "mypaint-glib-compat.h"
#include "mypaint-tiled-surface.h"
#include "mpbrush.h"
#include "mptile.h"

class MPSurface : public MyPaintTiledSurface
{
public:
    MPSurface(QSize size);
    ~MPSurface();

    uint16_t *tile_buffer; // Stores tiles in a linear chunk of memory (16bpc RGBA)
    uint16_t *null_tile; // Single tile that we hand out and ignore writes to

    int getTilesWidth();
    int getTilesHeight();
    int getWidth();
    int getHeight();

    enum { k_center = 50, k_max = 2*k_center};

    MPTile* getTileFromPos(const QPoint& pos);
    MPTile* getTileFromIdx(const QPoint& idx);
    inline bool checkIndex(uint n);
    inline QPoint getTilePos(const QPoint& idx);
    inline QPoint getTileIndex(const QPoint& pos);
    inline QPointF getTileFIndex(const QPoint& pos);

    typedef void (*MPOnUpdateTileFunction) (MPSurface *surface, MPTile *tile);
    typedef void (*MPOnUpdateSurfaceFunction) (MPSurface *surface);

    void setOnUpdateTile(MPOnUpdateTileFunction onUpdateTileFunction);
    void setOnNewTile(MPOnUpdateTileFunction onNewTileFunction);
    void setOnClearedSurface(MPOnUpdateSurfaceFunction onNewTileFunction);

    MPOnUpdateTileFunction onUpdateTileFunction;
    MPOnUpdateTileFunction onNewTileFunction;
    MPOnUpdateSurfaceFunction onClearedSurfaceFunction;

    void setSize(QSize size);
    QSize size();

    void clear();
    QImage renderImage();

    void loadImage(const QImage &image);

private:
    void resetNullTile();
    void resetSurface(QSize size);
    bool isFullyTransparent(QImage image);
    std::string key;

    int tiles_width; // width in tiles
    int tiles_height; // height in tiles
    int width; // width in pixels
    int height; // height in pixels

    MPBrush*    m_brush;
    QColor      m_color;

protected:
    QHash<QPoint, MPTile*> m_Tiles;
};

inline uint qHash (const QPoint & key)
{
    return qHash (QPair<int,int>(key.x(), key.y()) );
}

#endif // MPSURFACE_H

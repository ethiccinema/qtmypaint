#ifndef MPSURFACE_H
#define MPSURFACE_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "mypaint-glib-compat.h"
#include "mypaint-tiled-surface.h"

#include "mpbrush.h"

#include "mptile.h"


class MPSurface : public MyPaintTiledSurface
{

public:
    MPSurface(int width, int height);
    ~MPSurface();

    uint16_t *tile_buffer; // Stores tiles in a linear chunk of memory (16bpc RGBA)
    uint16_t *null_tile; // Single tile that we hand out and ignore writes to

    int getTilesWidth();
    int getTilesHeight();
    int getWidth();
    int getHeight();

    enum { k_center = 50, k_max = 2*k_center};


    MPTile*         getTileFromPos (const QPoint& pos);
    MPTile*         getTileFromIdx (const QPoint& idx);
    inline bool     checkIndex     (uint n);
    inline QPoint   getTilePos     (const QPoint& idx);
    inline QPoint   getTileIndex   (const QPoint& pos);
    inline QPointF  getTileFIndex  (const QPoint& pos);

    typedef void (*MPOnUpdateFunction) (MPSurface *surface, MPTile *tile);

    void setOnUpdateTile(MPOnUpdateFunction onUpdateTileFunction);
    void setOnNewTile(MPOnUpdateFunction onNewTileFunction);

    MPOnUpdateFunction onUpdateTileFunction;
    MPOnUpdateFunction onNewTileFunction;

private:
    void resetNullTile();

    std::string key;

    int tiles_width; // width in tiles
    int tiles_height; // height in tiles
    int width; // width in pixels
    int height; // height in pixels

    MPBrush*    m_brush;
    QColor      m_color;


protected:
    MPTile* m_tileTable [k_max][k_max];

};


#endif // MPSURFACE_H

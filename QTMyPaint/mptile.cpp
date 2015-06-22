#include "mptile.h"

MPTile::MPTile(QGraphicsItem * parent) : QGraphicsItem(parent), m_cache_img(k_tile_dim, k_tile_dim, QImage::Format_ARGB32_Premultiplied)
{
    setCacheMode(QGraphicsItem::NoCache);
    memset(t_pixels, 0, sizeof(t_pixels)); // Tile is transparent for now
    m_cache_img.fill( QColor(0,0,0,0) ); // image cache is transparent too, and aligned to the pixel table:
    m_cache_valid = true;
}

MPTile::~MPTile()
{

}

QImage
MPTile::image () {
    return m_cache_img;
}

QRectF
MPTile::boundingRect () const {
    return m_cache_img.rect();
}

bool
MPTile::contains (const QPointF & point) const
{
    // opaque if alpha > 16
    return qAlpha(m_cache_img.pixel(point.toPoint())) > 0x10;
}


QPainterPath
MPTile::shape() const
{
    QPainterPath path;
    path.addRect(m_cache_img.rect());
    return path;
}

void
MPTile::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  if (!m_cache_valid) updateCache(); // We need to transfer the uint16_t table to the QImage cache
  painter->drawImage( QPoint(), m_cache_img, m_cache_img.rect());
}




uint16_t*
MPTile::Bits (bool readOnly)
{
    // Correct C++ way of doing things is using "const" but MyPaint API is not compatible here
    m_cache_valid = readOnly ? m_cache_valid : false;
    return (uint16_t*)t_pixels;
}



// debug function (simply replace previous value of pixel in t_pixels)
//
void
MPTile::drawPoint ( uint x, uint y, uint16_t r, uint16_t g, uint16_t b, uint16_t a )
{
    m_cache_valid = false;
    t_pixels[y][x][k_red  ] = r;
    t_pixels[y][x][k_green] = g;
    t_pixels[y][x][k_blue ] = b;
    t_pixels[y][x][k_alpha] = a;
}

// Time to transfer the pixels from the uint16 to 32 bits cache before repaint...
//
void
MPTile::updateCache()
{
    QRgb* dst = (QRgb*)m_cache_img.bits();
    for (int y = 0 ; y < k_tile_dim ; y++)
    {
      for (int x = 0 ; x < k_tile_dim ; x++)
      {
        uint16_t alpha = t_pixels[y][x][k_alpha];
        *dst = alpha ? qRgba(
          CONV_16_8(t_pixels[y][x][k_red  ]),
          CONV_16_8(t_pixels[y][x][k_green]),
          CONV_16_8(t_pixels[y][x][k_blue ]),
          CONV_16_8(                  alpha)) :
          0; // aplha is 0 => all is zero (little optimization)
        dst++; // next image pixel...
      }
    }
    m_cache_valid = true;
}

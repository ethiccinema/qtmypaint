#include "mpbrush.h"

MPBrush::MPBrush()
{
    // Init Brush
    initBrush();

    // Set Default color to black
    setColor(QColor(0, 0, 0));
}

MPBrush::~MPBrush()
{
    mypaint_brush_unref(brush);
}

QColor
MPBrush::getColor()
{
    return m_color;
}

void
MPBrush::setColor(QColor newColor)
{
    m_color = newColor;

    float h = m_color.hue()/360.0;
    float s = m_color.saturation()/255.0;
    float v = m_color.value()/255.0;

    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_H, h);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_S, s);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_V, v);

}

void
MPBrush::initBrush()
{
    brush = mypaint_brush_new();
    mypaint_brush_from_defaults(brush);

    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_H, 0);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_S, 0);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_V, 0);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_SNAP_TO_PIXEL, 0.0);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_ANTI_ALIASING, 1.0);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_RADIUS_LOGARITHMIC, 0.3);
//    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_STROKE_DURATION_LOGARITHMIC, 4.0);
//    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_SPEED2_SLOWNESS, 0.8);
//    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_SPEED2_GAMMA, 10);
//    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_SPEED1_SLOWNESS, 0.04);
//    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_SPEED1_GAMMA, 10);
//    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_SMUDGE_LENGTH, 0.5);
//    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_SLOW_TRACKING_PER_DAB, 1.5);
//    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_SLOW_TRACKING, 1.03);
//    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_OFFSET_BY_RANDOM, 0.5);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_DIRECTION_FILTER, 10.0);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_DABS_PER_ACTUAL_RADIUS, 4.0);
}

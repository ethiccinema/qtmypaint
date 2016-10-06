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

void MPBrush::initBrush()
{
    brush = mypaint_brush_new();
    mypaint_brush_from_defaults(brush);

    setValue(MYPAINT_BRUSH_SETTING_COLOR_H, 0);
    setValue(MYPAINT_BRUSH_SETTING_COLOR_S, 0);
    setValue(MYPAINT_BRUSH_SETTING_COLOR_V, 0);
    setValue(MYPAINT_BRUSH_SETTING_SNAP_TO_PIXEL, 0.0);
    setValue(MYPAINT_BRUSH_SETTING_ANTI_ALIASING, 1.0);
    setValue(MYPAINT_BRUSH_SETTING_RADIUS_LOGARITHMIC, 0.3);
//    setValue(MYPAINT_BRUSH_SETTING_STROKE_DURATION_LOGARITHMIC, 4.0);
//    setValue(MYPAINT_BRUSH_SETTING_SPEED2_SLOWNESS, 0.8);
//    setValue(MYPAINT_BRUSH_SETTING_SPEED2_GAMMA, 10);
//    setValue(MYPAINT_BRUSH_SETTING_SPEED1_SLOWNESS, 0.04);
//    setValue(MYPAINT_BRUSH_SETTING_SPEED1_GAMMA, 10);
//    setValue(MYPAINT_BRUSH_SETTING_SMUDGE_LENGTH, 0.5);
//    setValue(MYPAINT_BRUSH_SETTING_SLOW_TRACKING_PER_DAB, 1.5);
//    setValue(MYPAINT_BRUSH_SETTING_SLOW_TRACKING, 1.03);
//    setValue(MYPAINT_BRUSH_SETTING_OFFSET_BY_RANDOM, 0.5);
    setValue(MYPAINT_BRUSH_SETTING_DIRECTION_FILTER, 10.0);
    setValue(MYPAINT_BRUSH_SETTING_DABS_PER_ACTUAL_RADIUS, 4.0);
}

void MPBrush::load(const QByteArray& content)
{
    mypaint_brush_from_defaults(brush);

    if (!mypaint_brush_from_string(brush, content.constData()))
    {
        // Not able to load the selected brush. Let's execute some backup code...
        qDebug("Trouble when reading the selected brush !");
    }
    setColor(m_color);
}

QColor MPBrush::getColor()
{
    return m_color;
}

void MPBrush::setColor(QColor newColor)
{
    m_color = newColor;

    float h = m_color.hue()/360.0;
    float s = m_color.saturation()/255.0;
    float v = m_color.value()/255.0;

    // Opacity is not handled here as it is defined by the brush settings.
    // If you wish to force opacity, use MPHandler::setBrushValue()
    //
//    float opacity = m_color.alpha()/255.0;
//    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_OPAQUE, opacity);

    setValue(MYPAINT_BRUSH_SETTING_COLOR_H, h);
    setValue(MYPAINT_BRUSH_SETTING_COLOR_S, s);
    setValue(MYPAINT_BRUSH_SETTING_COLOR_V, v);
}

float MPBrush::getValue(MyPaintBrushSetting setting)
{
    return mypaint_brush_get_base_value(brush, setting);
}

void MPBrush::setValue(MyPaintBrushSetting setting, float value)
{
    mypaint_brush_set_base_value(brush, setting, value);
}



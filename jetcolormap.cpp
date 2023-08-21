#include "jetcolormap.h"

JetColorMap::JetColorMap()
    : ColorMap()
{
}

JetColorMap::JetColorMap(double a, double b)
    : ColorMap(a, b)
{
}

JetColorMap::~JetColorMap(){}

QColor JetColorMap::getColor(double value) const
{
    QColor color(255, 255, 255);
    double interval;

    if(value > _max){
        value = _max;
    }
    else if(value < _min){
        value = _min;
    }
    interval = _max -_min;

    if (value < (_min + 0.25 * interval)) {
        color.setRedF(0);
        color.setGreenF(4 * (value - _min) / interval);
    } else if (value < (_min + 0.5 * interval)) {
        color.setRedF(0);
        color.setBlueF(1 + 4 * (_min + 0.25 * interval - value) / interval);
    } else if (value < (_min + 0.75 * interval)) {
        color.setRedF(4 * (value - _min - 0.5 * interval) / interval);
        color.setBlueF(0);
    } else {
        color.setGreenF(1 + 4 * (_min + 0.75 * interval - value) / interval);
        color.setBlueF(0);
    }

    return color;
}

#ifndef COLORMAP_H
#define COLORMAP_H

#include "qcolor.h"
class ColorMap
{
public:
    ColorMap();
    ColorMap(double a, double b);
    virtual ~ColorMap() = 0;
    virtual QColor getColor(double value) const = 0;

protected:
    double _min;
    double _max;
};

#endif // COLORMAP_H

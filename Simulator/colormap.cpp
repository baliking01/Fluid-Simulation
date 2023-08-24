#include "colormap.h"
ColorMap::ColorMap()
    : _min{0.0}
    , _max{1.0}
{
}

ColorMap::ColorMap(double a, double b)
    : _min{a}
    , _max{b}
{
}

ColorMap::~ColorMap(){}

QColor ColorMap::getColor(double value) const
{

}

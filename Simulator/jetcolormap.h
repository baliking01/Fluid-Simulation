#ifndef JET_H
#define JET_H

#include "colormap.h"

class JetColorMap : public ColorMap
{
public:
    JetColorMap();
    JetColorMap(double a, double b);
    virtual ~JetColorMap();
    virtual QColor getColor(double value) const override;
};

#endif // JET_H

#pragma once

#include "Typedefs.h"

namespace SmartMet
{

double linearInterpolation(double wantedPosition, double position1, double position2, double value1, double value2);
double linearInterpolation(double x,double y,double x1,double y1,double x2,double y2,double val_q11,double val_q21,double val_q22,double val_q12);
double logarithmicInterpolation(double wantedPosition, double position1, double position2, double value1, double value2);


}


#include "InterpolationFunctions.h"
#include "Exception.h"
#include "../grid/Typedefs.h"


namespace SmartMet
{


double linearInterpolation(double wantedPosition, double position1, double position2, double value1, double value2)
{
  try
  {
    //std::cout << "Linear interpolation : " << wantedPosition << " " << position1 << " " << position2 << " " << value1 << " " << value2 << "\n";
    if (position1 != position2  &&  value1 != ParamValueMissing  &&  value2 != ParamValueMissing)
    {
      double positionDiff = position2 - position1;
      double valueDiff = value2 - value1;

      double valueStep = valueDiff / positionDiff;
      double distance = wantedPosition - position1;

      double value = value1 + distance * valueStep;
      // std::cout << "RESULT : " << value << "\n";
      return value;
    }

    if (value1 != ParamValueMissing)
      return value1;

    if (value2 != ParamValueMissing)
      return value2;

    return ParamValueMissing;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





double linearInterpolation(double x,double y,double x1,double y1,double x2,double y2,double val_q11,double val_q21,double val_q22,double val_q12)
{
  try
  {
    // https://en.wikipedia.org/wiki/Bilinear_interpolation

    double dist_x1 = x-x1;
    double dist_x2 = x2-x;
    double dist_y1 = y-y1;
    double dist_y2 = y2-y;

    // If the given point is on the border then we can do simple
    // linear interpolation.

    if (dist_x1 == 0)
    {
      // Linear interpolation x1,y1 - x1,y2
      if (val_q11 != ParamValueMissing  &&  val_q12 != ParamValueMissing)
        return (dist_y1*val_q11 + dist_y2*val_q12);

      return ParamValueMissing;
    }

    if (dist_x2 == 0)
    {
      // Linear interpolation x2,y1 - x2,y2
      if (val_q21 != ParamValueMissing  &&  val_q22 != ParamValueMissing)
        return (dist_y1*val_q21 + dist_y2*val_q22);

      return ParamValueMissing;
    }

    if (dist_y1 == 0)
    {
      // Linear interpolation x1,y1 - x2,y1
      if (val_q11 != ParamValueMissing  &&  val_q21 != ParamValueMissing)
        return (dist_x1*val_q11 + dist_x2*val_q21);

      return ParamValueMissing;
    }

    if (dist_y2 == 0)
    {
      // Linear interpolation x1,y2 - x2,y2
      if (val_q12 != ParamValueMissing  &&  val_q22 != ParamValueMissing)
        return (dist_x1*val_q12 + dist_x2*val_q22);

      return ParamValueMissing;
    }

    // Bilinear interpolation

    if (val_q11 != ParamValueMissing && val_q21 != ParamValueMissing  &&
        val_q12 != ParamValueMissing &&  val_q22 != ParamValueMissing)
    {
      // All corners have a value.

      double fy1 = dist_x2*val_q11 + dist_x1*val_q21;
      double fy2 = dist_x2*val_q12 + dist_x1*val_q22;
      double f = dist_y2*fy1 + dist_y1*fy2;
      return f;
    }

    // Three corners have a value (triangular interpolation).

    if (val_q11 == ParamValueMissing && val_q21 != ParamValueMissing  &&
        val_q12 != ParamValueMissing &&  val_q22 != ParamValueMissing)
    {
      double wsum = (dist_x2 * dist_y1 + dist_x1 * dist_y1 + dist_x1 * dist_y2);
      return ((dist_x1 * dist_y2 * val_q21 + dist_x2 * dist_y1 * val_q12 +
          dist_x1 * dist_y1 * val_q22) / wsum);
    }

    if (val_q11 != ParamValueMissing && val_q21 == ParamValueMissing  &&
        val_q12 != ParamValueMissing &&  val_q22 != ParamValueMissing)
    {
      double wsum = (dist_x2 * dist_y2 + dist_x2 * dist_y1 + dist_x1 * dist_y1);
      return ((dist_x2 * dist_y2 * val_q11 + dist_x2 * dist_y1 * val_q12 +
          dist_x1 * dist_y1 * val_q22) / wsum);
    }

    if (val_q11 != ParamValueMissing && val_q21 != ParamValueMissing  &&
        val_q12 == ParamValueMissing &&  val_q22 != ParamValueMissing)
    {
      double wsum = (dist_x1 * dist_y1 + dist_x2 * dist_y2 + dist_x1 * dist_y2);
      return ((dist_x2 * dist_y2 * val_q11 + dist_x1 * dist_y2 * val_q21 +
        dist_x1 * dist_y1 * val_q22) / wsum);
    }

    if (val_q11 != ParamValueMissing && val_q21 != ParamValueMissing  &&
        val_q12 != ParamValueMissing &&  val_q22 == ParamValueMissing)
    {
      double wsum = (dist_x2 * dist_y1 + dist_x2 * dist_y2 + dist_x1 * dist_y2);
      return ((dist_x2 * dist_y2 * val_q11 + dist_x1 * dist_y2 * val_q21 +
        dist_x2 * dist_y2 * val_q12) / wsum);
    }

    return ParamValueMissing;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





double logarithmicInterpolation(double wantedPosition, double position1, double position2, double value1, double value2)
{
  try
  {
    if (position1 != position2  &&  value1 != ParamValueMissing  &&  value2 != ParamValueMissing)
    {
      double w = (::log(wantedPosition) - ::log(position1)) / (::log(position2) - ::log(position1));
      double value = (1 - w) * value1 + w * value2;
      return value;
    }

    if (value1 != ParamValueMissing)
      return value1;

    if (value2 != ParamValueMissing)
      return value2;

    return ParamValueMissing;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}



}

#include "InterpolationFunctions.h"
#include "Exception.h"
#include "GeneralFunctions.h"


namespace SmartMet
{

typedef long long longlong;

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

    uint missingFlags = 0;
    uint missingCount = 0;
    if (val_q11 == ParamValueMissing)
    {
      missingFlags = 1;
      missingCount++;
    }

    if (val_q21 == ParamValueMissing)
    {
      missingFlags |= 2;
      missingCount++;
    }

    if (val_q12 == ParamValueMissing)
    {
      missingFlags |= 4;
      missingCount++;
    }

    if (val_q22 == ParamValueMissing)
    {
      missingFlags |= 8;
      missingCount++;
    }

    if (missingCount == 4)
      return ParamValueMissing;


    double dist_x1 = x-x1;
    double dist_x2 = x2-x;
    double dist_y1 = y-y1;
    double dist_y2 = y2-y;


    // Bilinear interpolation

    if (missingCount == 0)
    {
      // All corners have a value.

      double fy1 = dist_x2*val_q11 + dist_x1*val_q21;
      double fy2 = dist_x2*val_q12 + dist_x1*val_q22;
      return (dist_y2*fy1 + dist_y1*fy2);
    }

    if (missingCount == 1)
    {
      // Three corners have a value (triangular interpolation).

      if (missingFlags == 1)
      {
        double wsum = (dist_x2 * dist_y1 + dist_x1 * dist_y1 + dist_x1 * dist_y2);
        return ((dist_x1 * dist_y2 * val_q21 + dist_x2 * dist_y1 * val_q12 +
            dist_x1 * dist_y1 * val_q22) / wsum);
      }

      if (missingFlags == 2)
      {
        double wsum = (dist_x2 * dist_y2 + dist_x2 * dist_y1 + dist_x1 * dist_y1);
        return ((dist_x2 * dist_y2 * val_q11 + dist_x2 * dist_y1 * val_q12 +
            dist_x1 * dist_y1 * val_q22) / wsum);
      }

      if (missingFlags == 4)
      {
        double wsum = (dist_x1 * dist_y1 + dist_x2 * dist_y2 + dist_x1 * dist_y2);
        return ((dist_x2 * dist_y2 * val_q11 + dist_x1 * dist_y2 * val_q21 +
          dist_x1 * dist_y1 * val_q22) / wsum);
      }

      if (missingFlags == 8)
      {
        double wsum = (dist_x2 * dist_y1 + dist_x2 * dist_y2 + dist_x1 * dist_y2);
        return ((dist_x2 * dist_y2 * val_q11 + dist_x1 * dist_y2 * val_q21 +
          dist_x2 * dist_y2 * val_q12) / wsum);
      }
    }

    if (missingCount == 2)
    {
      // If the given point is on the border then we can do simple
      // linear interpolation.

      if (dist_x1 == 0)
      {
        // Linear interpolation x1,y1 - x1,y2
        if (missingFlags == 10)
          return (dist_y1*val_q11 + dist_y2*val_q12);

        return ParamValueMissing;
      }

      if (dist_x2 == 0)
      {
        // Linear interpolation x2,y1 - x2,y2
        if (missingFlags == 5)
          return (dist_y1*val_q21 + dist_y2*val_q22);

        return ParamValueMissing;
      }

      if (dist_y1 == 0)
      {
        // Linear interpolation x1,y1 - x2,y1
        if (missingFlags == 12)
          return (dist_x1*val_q11 + dist_x2*val_q21);

        return ParamValueMissing;
      }

      if (dist_y2 == 0)
      {
        // Linear interpolation x1,y2 - x2,y2
        if (missingFlags == 3)
          return (dist_x1*val_q12 + dist_x2*val_q22);

        return ParamValueMissing;
      }
    }

    return ParamValueMissing;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





longlong linearInterpolation(longlong x,longlong y,longlong x1,longlong y1,longlong x2,longlong y2,longlong val_q11,longlong val_q21,longlong val_q22,longlong val_q12)
{
  try
  {
    longlong XParamValueMissing = 0x7FFFFFFFFFFFFFFF;
    // https://en.wikipedia.org/wiki/Bilinear_interpolation

    longlong dist_x1 = x-x1;
    longlong dist_x2 = x2-x;
    longlong dist_y1 = y-y1;
    longlong dist_y2 = y2-y;


    // Bilinear interpolation

    if (val_q11 != XParamValueMissing && val_q21 != XParamValueMissing  &&
        val_q12 != XParamValueMissing &&  val_q22 != XParamValueMissing)
    {
      // All corners have a value.

      longlong fy1 = dist_x2*val_q11 + dist_x1*val_q21;
      longlong fy2 = dist_x2*val_q12 + dist_x1*val_q22;
      return (dist_y2*fy1 + dist_y1*fy2);
    }


    // If the given point is on the border then we can do simple
    // linear interpolation.

    if (dist_x1 == 0)
    {
      // Linear interpolation x1,y1 - x1,y2
      if (val_q11 != XParamValueMissing  &&  val_q12 != XParamValueMissing)
        return (dist_y1*val_q11 + dist_y2*val_q12);

      return XParamValueMissing;
    }

    if (dist_x2 == 0)
    {
      // Linear interpolation x2,y1 - x2,y2
      if (val_q21 != XParamValueMissing  &&  val_q22 != XParamValueMissing)
        return (dist_y1*val_q21 + dist_y2*val_q22);

      return XParamValueMissing;
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


    // Three corners have a value (triangular interpolation).

    if (val_q11 == ParamValueMissing && val_q21 != ParamValueMissing  &&
        val_q12 != ParamValueMissing &&  val_q22 != ParamValueMissing)
    {
      longlong wsum = (dist_x2 * dist_y1 + dist_x1 * dist_y1 + dist_x1 * dist_y2);
      return ((dist_x1 * dist_y2 * val_q21 + dist_x2 * dist_y1 * val_q12 +
          dist_x1 * dist_y1 * val_q22) / wsum);
    }

    if (val_q11 != ParamValueMissing && val_q21 == ParamValueMissing  &&
        val_q12 != ParamValueMissing &&  val_q22 != ParamValueMissing)
    {
      longlong wsum = (dist_x2 * dist_y2 + dist_x2 * dist_y1 + dist_x1 * dist_y1);
      return ((dist_x2 * dist_y2 * val_q11 + dist_x2 * dist_y1 * val_q12 +
          dist_x1 * dist_y1 * val_q22) / wsum);
    }

    if (val_q11 != ParamValueMissing && val_q21 != ParamValueMissing  &&
        val_q12 == ParamValueMissing &&  val_q22 != ParamValueMissing)
    {
      longlong wsum = (dist_x1 * dist_y1 + dist_x2 * dist_y2 + dist_x1 * dist_y2);
      return ((dist_x2 * dist_y2 * val_q11 + dist_x1 * dist_y2 * val_q21 +
        dist_x1 * dist_y1 * val_q22) / wsum);
    }

    if (val_q11 != ParamValueMissing && val_q21 != ParamValueMissing  &&
        val_q12 != ParamValueMissing &&  val_q22 == ParamValueMissing)
    {
      longlong wsum = (dist_x2 * dist_y1 + dist_x2 * dist_y2 + dist_x1 * dist_y2);
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




double linearInterpolation2(double x,double y,double x1,double y1,double x2,double y2,double val_q11,double val_q21,double val_q22,double val_q12)
{
  if (val_q11 == ParamValueMissing && val_q21 == ParamValueMissing  &&
      val_q12 == ParamValueMissing &&  val_q22 == ParamValueMissing)
    return ParamValueMissing;

  longlong ax = (longlong)(x*1000000);
  longlong ay = (longlong)(y*1000000);
  longlong ax1 = (longlong)(x1*1000000);
  longlong ay1 = (longlong)(y1*1000000);
  longlong ax2 = (longlong)(x2*1000000);
  longlong ay2 = (longlong)(y2*1000000);
  longlong aval_q11 = (longlong)(val_q11*1000000);
  longlong aval_q21 = (longlong)(val_q21*1000000);
  longlong aval_q22 = (longlong)(val_q22*1000000);
  longlong aval_q12 = (longlong)(val_q12*1000000);

  longlong res = linearInterpolation(ax,ay,ax1,ay1,ax2,ay2,aval_q11,aval_q21,aval_q22,aval_q12);

  if (res != 0x7FFFFFFFFFFFFFFF)
    return (double)res / 1000000;
  else
    return ParamValueMissing;
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





T::ParamValue levelInterpolation(T::ParamValue value1,T::ParamValue value2,int level1,int level2,int newLevel,short levelInterpolationMethod)
{
  try
  {
    if (level1 == newLevel)
      return value1;

    if (level2 == newLevel)
      return value2;

    int diff1 = newLevel - level1;
    int diff2 = level2 - newLevel;
    double levelDiff = C_DOUBLE(level2 - level1);

    switch (levelInterpolationMethod)
    {
      case T::LevelInterpolationMethod::None:
        return value1;

      case T::LevelInterpolationMethod::Nearest:
        if (diff1 < diff2)
          return value1;
        else
          return value2;
        break;

      case T::LevelInterpolationMethod::Min:
        if (value1 < value2)
          return value1;
        else
          return value2;
        break;

        case T::LevelInterpolationMethod::Max:
          if (value1 > value2)
            return value1;
          else
            return value2;
          break;

      case T::LevelInterpolationMethod::Logarithmic:
        return logarithmicInterpolation(newLevel, level1, level2, value1, value2);

      default:
      case T::LevelInterpolationMethod::Linear:
        if (value1 != ParamValueMissing && value2 != ParamValueMissing)
        {
          T::ParamValue valueDiff = value2 - value1;
          T::ParamValue valueStep = valueDiff / levelDiff;
          return (value1 + (diff1 * valueStep));
        }
        else
        {
          return ParamValueMissing;
        }
        break;
    }
    return ParamValueMissing;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", nullptr);
  }
}





void levelInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,int level1,int level2,int newLevel,short levelInterpolationMethod,T::ParamValue_vec& values)
{
  try
  {
    if (level1 == newLevel)
    {
      values = values1;
      return;
    }

    if (level2 == newLevel)
    {
      values = values2;
      return;
    }

    int diff1 = newLevel - level1;
    int diff2 = level2 - newLevel;
    double levelDiff = C_DOUBLE(level2 - level1);

    uint len1 = values1.size();
    uint len2 = values2.size();

    if (len1 == len2)
    {
      switch (levelInterpolationMethod)
      {
        case T::LevelInterpolationMethod::None:
          values = values1;
          break;

        case T::LevelInterpolationMethod::Nearest:
          if (diff1 < diff2)
            values = values1;
          else
            values = values2;
          break;

        case T::LevelInterpolationMethod::Min:
          values.reserve(len1);
          for (uint t = 0; t < len1; t++)
          {
            T::ParamValue val1 = values1[t];
            T::ParamValue val2 = values2[t];

            if (val1 < val2)
              values.push_back(val1);
            else
              values.push_back(val2);
          }
          break;

        case T::LevelInterpolationMethod::Max:
          values.reserve(len1);
          for (uint t = 0; t < len1; t++)
          {
            T::ParamValue val1 = values1[t];
            T::ParamValue val2 = values2[t];

            if (val1 > val2)
              values.push_back(val1);
            else
              values.push_back(val2);
          }
          break;

        case T::LevelInterpolationMethod::Logarithmic:
          values.reserve(len1);
          for (uint t = 0; t < len1; t++)
          {
            T::ParamValue val1 = values1[t];
            T::ParamValue val2 = values2[t];

            T::ParamValue val = logarithmicInterpolation(newLevel, level1, level2, val1, val2);
            values.push_back(val);
          }
          break;

        default:
        case T::LevelInterpolationMethod::Linear:
          values.reserve(len1);
          for (uint t = 0; t < len1; t++)
          {
            T::ParamValue val1 = values1[t];
            T::ParamValue val2 = values2[t];
             T::ParamValue val = ParamValueMissing;
            if (val1 != ParamValueMissing && val2 != ParamValueMissing)
            {
              T::ParamValue valueDiff = val2 - val1;
              T::ParamValue valueStep = valueDiff / levelDiff;
              val = val1 + (diff1 * valueStep);
            }
            values.push_back(val);
          }
          break;
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", nullptr);
  }
}





void levelInterpolation(T::GridValueList& values1,T::GridValueList& values2,int level1,int level2,int newLevel,short levelInterpolationMethod,T::GridValueList& valueList)
{
  try
  {
    if (level1 == newLevel)
    {
      valueList = values1;
      return;
    }

    if (level2 == newLevel)
    {
      valueList = values2;
      return;
    }

    int diff1 = newLevel - level1;
    int diff2 = level2 - newLevel;
    double levelDiff = C_DOUBLE(level2 - level1);

    uint len1 = values1.getLength();
    uint len2 = values2.getLength();

    if (len1 == len2)
    {
      switch (levelInterpolationMethod)
      {
        case T::LevelInterpolationMethod::None:
          valueList = values1;
          break;

        case T::LevelInterpolationMethod::Nearest:
          if (diff1 < diff2)
            valueList = values1;
          else
            valueList = values2;
          break;

        case T::LevelInterpolationMethod::Min:
          for (uint t = 0; t < len1; t++)
          {
            T::GridValue val1;
            T::GridValue val2;
            T::GridValue rec;

            values1.getGridValueByIndex(t,val1);
            values2.getGridValueByIndex(t,val2);

            rec.mX = val1.mX;
            rec.mY = val1.mY;

            if (val1.mValue < val2.mValue)
              rec.mValue = val1.mValue;
            else
              rec.mValue = val2.mValue;

            valueList.addGridValue(rec);
          }
          break;

        case T::LevelInterpolationMethod::Max:
          for (uint t = 0; t < len1; t++)
          {
            T::GridValue val1;
            T::GridValue val2;
            T::GridValue rec;

            values1.getGridValueByIndex(t,val1);
            values2.getGridValueByIndex(t,val2);

            rec.mX = val1.mX;
            rec.mY = val1.mY;

            if (val1.mValue > val2.mValue)
              rec.mValue = val1.mValue;
            else
              rec.mValue = val2.mValue;

            valueList.addGridValue(rec);
          }
          break;

        case T::LevelInterpolationMethod::Logarithmic:
          for (uint t = 0; t < len1; t++)
          {
            T::GridValue val1;
            T::GridValue val2;
            T::GridValue rec;

            values1.getGridValueByIndex(t,val1);
            values2.getGridValueByIndex(t,val2);

            rec.mX = val1.mX;
            rec.mY = val1.mY;
            rec.mValue = logarithmicInterpolation(newLevel, level1, level2, val1.mValue, val2.mValue);

            valueList.addGridValue(rec);
          }
          break;

        default:
        case T::LevelInterpolationMethod::Linear:
          for (uint t = 0; t < len1; t++)
          {
            T::GridValue val1;
            T::GridValue val2;
            T::GridValue rec;

            values1.getGridValueByIndex(t,val1);
            values2.getGridValueByIndex(t,val2);

            rec.mX = val1.mX;
            rec.mY = val1.mY;

            if (val1.mValue != ParamValueMissing && val2.mValue != ParamValueMissing)
            {
              T::ParamValue valueDiff = val2.mValue - val1.mValue;
              T::ParamValue valueStep = valueDiff / levelDiff;
              rec.mValue = val1.mValue + (diff1 * valueStep);
            }
            else
            {
              rec.mValue = ParamValueMissing;
            }
            valueList.addGridValue(rec);
          }
          break;
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", nullptr);
  }
}





T::ParamValue timeInterpolation(T::ParamValue value1,T::ParamValue& value2,std::string time1,std::string time2,std::string newTime,short timeInterpolationMethod)
{
  try
  {
    time_t tt = utcTimeToTimeT(newTime);
    time_t t1 = utcTimeToTimeT(time1);
    time_t t2 = utcTimeToTimeT(time2);

    return timeInterpolation(value1,value2,t1,t2,tt,timeInterpolationMethod);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", nullptr);
  }
}





T::ParamValue timeInterpolation(T::ParamValue value1,T::ParamValue& value2,time_t t1,time_t t2,time_t newTime,short timeInterpolationMethod)
{
  try
  {
    if (t1 == newTime)
      return value1;

    if (t2 == newTime)
      return value2;

    double timeDiff = C_DOUBLE(t2 - t1);
    double diff1 = C_DOUBLE(newTime - t1);
    double diff2 = C_DOUBLE(t2 - newTime);

    switch (timeInterpolationMethod)
    {
      case T::TimeInterpolationMethod::Undefined:
      case T::TimeInterpolationMethod::None:
        return value1;

      case T::TimeInterpolationMethod::Linear:
        if (value1 != ParamValueMissing  &&  value2 != ParamValueMissing)
        {
          T::ParamValue vd = (value2 - value1)/timeDiff;
          return (value1 + diff1 * vd);
        }
        else
        {
          return ParamValueMissing;
        }

      case T::TimeInterpolationMethod::Nearest:
        if (diff1 <= diff2)
          return value1;
        else
          return value2;

      case T::TimeInterpolationMethod::Min:
        if (value1 != ParamValueMissing  &&  value2 != ParamValueMissing)
        {
          if (value1 <= value2)
            return value1;
          else
            return value2;
        }
        else
        {
          return ParamValueMissing;
        }

      case T::TimeInterpolationMethod::Max:
        if (value1 != ParamValueMissing  &&  value2 != ParamValueMissing)
        {
          if (value1 >= value2)
            return value1;
          else
            return value2;
        }
        else
        {
          return ParamValueMissing;
        }

      default:
        throw SmartMet::Spine::Exception(BCP,"Unsupported or unknown intepolation method!");
    }

    return ParamValueMissing;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void timeInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,std::string time1,std::string time2,std::string newTime,short timeInterpolationMethod,T::ParamValue_vec& newValues)
{
  try
  {
    time_t tt = utcTimeToTimeT(newTime);
    time_t t1 = utcTimeToTimeT(time1);
    time_t t2 = utcTimeToTimeT(time2);

    timeInterpolation(values1,values2,t1,t2,tt,timeInterpolationMethod,newValues);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void timeInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,time_t t1,time_t t2,time_t newTime,short timeInterpolationMethod,T::ParamValue_vec& newValues)
{
  try
  {
    if (values1.size() != values2.size())
      throw SmartMet::Spine::Exception(BCP,"Value vectors are not the same size!");

    if (t1 == newTime)
    {
      newValues = values1;
      return;
    }

    if (t2 == newTime)
    {
      newValues = values2;
      return;
    }


    double timeDiff = C_DOUBLE(t2 - t1);
    double diff1 = C_DOUBLE(newTime - t1);
    double diff2 = C_DOUBLE(t2 - newTime);

    uint sz = values1.size();
    newValues.reserve(sz);

    switch (timeInterpolationMethod)
    {
      case T::TimeInterpolationMethod::Undefined:
      case T::TimeInterpolationMethod::None:
        newValues = values1;
        return;


      case T::TimeInterpolationMethod::Linear:
        for (uint t=0; t<sz; t++)
        {
          T::ParamValue v1 = values1[t];
          T::ParamValue v2 = values2[t];

          if (v1 != ParamValueMissing  &&  v2 != ParamValueMissing)
          {
            T::ParamValue vd = (v2 - v1)/timeDiff;
            T::ParamValue newValue = v1 + diff1 * vd;
            newValues.push_back(newValue);
          }
          else
          {
            newValues.push_back(ParamValueMissing);
          }
        }
        return;


      case T::TimeInterpolationMethod::Nearest:
        if (diff1 <= diff2)
          newValues = values1;
        else
          newValues = values2;
        return;


      case T::TimeInterpolationMethod::Min:
        for (uint t=0; t<sz; t++)
        {
          T::ParamValue v1 = values1[t];
          T::ParamValue v2 = values2[t];

          if (v1 != ParamValueMissing  &&  v2 != ParamValueMissing)
          {
            if (v1 <= v2)
              newValues.push_back(v1);
            else
              newValues.push_back(v2);
          }
          else
          {
            newValues.push_back(ParamValueMissing);
          }
        }
        return;


      case T::TimeInterpolationMethod::Max:
        for (uint t=0; t<sz; t++)
        {
          T::ParamValue v1 = values1[t];
          T::ParamValue v2 = values2[t];

          if (v1 != ParamValueMissing  &&  v2 != ParamValueMissing)
          {
            if (v1 >= v2)
              newValues.push_back(v1);
            else
              newValues.push_back(v2);
          }
          else
          {
            newValues.push_back(ParamValueMissing);
          }
        }
        return;

      default:
        throw SmartMet::Spine::Exception(BCP,"Unsupported or unknown intepolation method!");
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void timeInterpolation(T::GridValueList& values1,T::GridValueList& values2,std::string time1,std::string time2,std::string newTime,short timeInterpolationMethod,T::GridValueList& valueList)
{
  try
  {
    time_t tt = utcTimeToTimeT(newTime);
    time_t t1 = utcTimeToTimeT(time1);
    time_t t2 = utcTimeToTimeT(time2);

    timeInterpolation(values1,values2,t1,t2,tt,timeInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void timeInterpolation(T::GridValueList& values1,T::GridValueList& values2,time_t t1,time_t t2,time_t newTime,short timeInterpolationMethod,T::GridValueList& valueList)
{
  try
  {
    if (values1.getLength() != values2.getLength())
      throw SmartMet::Spine::Exception(BCP,"Value lists are not the same size!");

    if (t1 == newTime)
    {
      valueList = values1;
      return;
    }

    if (t2 == newTime)
    {
      valueList = values2;
      return;
    }

    time_t diff1 = newTime - t1;
    time_t diff2 = t2 - t1;

    uint len1 = values1.getLength();
    uint len2 = values2.getLength();

    if (len1 == len2)
    {
      switch (timeInterpolationMethod)
      {
        case T::TimeInterpolationMethod::None:
          valueList = values1;
          break;

        case T::TimeInterpolationMethod::Nearest:
          if (diff1 < diff2)
            valueList = values1;
          else
            valueList = values2;
          break;

        case T::TimeInterpolationMethod::Min:
          for (uint t = 0; t < len1; t++)
          {
            T::GridValue val1;
            T::GridValue val2;
            T::GridValue rec;

            values1.getGridValueByIndex(t,val1);
            values2.getGridValueByIndex(t,val2);

            rec.mX = val1.mX;
            rec.mY = val1.mY;

            if (val1.mValue < val2.mValue)
              rec.mValue = val1.mValue;
            else
              rec.mValue = val2.mValue;

            valueList.addGridValue(rec);
          }
          break;

        case T::TimeInterpolationMethod::Max:
          for (uint t = 0; t < len1; t++)
          {
            T::GridValue val1;
            T::GridValue val2;
            T::GridValue rec;

            values1.getGridValueByIndex(t,val1);
            values2.getGridValueByIndex(t,val2);

            rec.mX = val1.mX;
            rec.mY = val1.mY;

            if (val1.mValue > val2.mValue)
              rec.mValue = val1.mValue;
            else
              rec.mValue = val2.mValue;

            valueList.addGridValue(rec);
          }
          break;

        default:
        case T::TimeInterpolationMethod::Linear:
          for (uint t = 0; t < len1; t++)
          {
            T::GridValue val1;
            T::GridValue val2;
            T::GridValue rec;

            values1.getGridValueByIndex(t,val1);
            values2.getGridValueByIndex(t,val2);

            rec.mX = val1.mX;
            rec.mY = val1.mY;

            if (val1.mValue != ParamValueMissing && val2.mValue != ParamValueMissing)
            {
              T::ParamValue valueDiff = val2.mValue - val1.mValue;
              T::ParamValue valueStep = valueDiff / diff2;
              rec.mValue = val1.mValue + (diff1 * valueStep);
            }
            else
            {
              rec.mValue = ParamValueMissing;
            }
            valueList.addGridValue(rec);
          }
          break;
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", nullptr);
  }
}

}

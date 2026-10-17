#include "InterpolationFunctions.h"
#include "TransferInterpolation.h"
#include "GeneralFunctions.h"
#include <macgyver/Exception.h>

#include <algorithm>


namespace SmartMet
{


/*! \brief Linearly interpolates a value between two positions. */

double linearInterpolation(double wantedPosition, double position1, double position2, double value1, double value2)
{
  try
  {
    if (position1 != position2  &&  value1 != ParamValueMissing  &&  value2 != ParamValueMissing)
    {
      double positionDiff = position2 - position1;
      double valueDiff = value2 - value1;

      double valueStep = valueDiff / positionDiff;
      double distance = wantedPosition - position1;

      double value = value1 + distance * valueStep;
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





namespace
{

/*! \brief Triangular interpolation when exactly one of the four corner values is missing. */

double triangularInterpolation(uint missingFlags,double dist_x1,double dist_x2,double dist_y1,double dist_y2,double val_q11,double val_q21,double val_q22,double val_q12)
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
      dist_x2 * dist_y1 * val_q12) / wsum);
  }

  return ParamValueMissing;
}





/*! \brief Linear interpolation along the border when exactly two of the four corner values are missing. */

double borderInterpolation(uint missingFlags,double dist,double dist_x1,double dist_x2,double dist_y1,double dist_y2,double val_q11,double val_q21,double val_q22,double val_q12)
{
  // If the given point is on the border then we can do simple
  // linear interpolation.

  //printf("DIST %.20f,%.20f,%.20f,%.20f  %u\n",dist_x1,dist_y1,dist_x2,dist_y2,missingFlags);
  if (dist_x1 < dist)
  {
    // Linear interpolation x1,y1 - x1,y2
    if (missingFlags == 10)
      return (dist_y1*val_q11 + dist_y2*val_q12);

    return ParamValueMissing;
  }

  if (dist_x2 < dist)
  {
    // Linear interpolation x2,y1 - x2,y2
    if (missingFlags == 5)
      return (dist_y1*val_q21 + dist_y2*val_q22);

    return ParamValueMissing;
  }

  if (dist_y1 < dist)
  {
    // Linear interpolation x1,y1 - x2,y1
    if (missingFlags == 12)
      return (dist_x1*val_q11 + dist_x2*val_q21);

    return ParamValueMissing;
  }

  if (dist_y2 < dist)
  {
    // Linear interpolation x1,y2 - x2,y2
    if (missingFlags == 3)
      return (dist_x1*val_q12 + dist_x2*val_q22);

    return ParamValueMissing;
  }

  return ParamValueMissing;
}

}  // namespace





/*! \brief Performs bilinear interpolation on a quadrilateral, handling missing corner values. */

double linearInterpolation(double x,double y,double x1,double y1,double x2,double y2,double val_q11,double val_q21,double val_q22,double val_q12)
{
  try
  {
    // https://en.wikipedia.org/wiki/Bilinear_interpolation

    double dist = 0.001;
    double dist_x1 = x-x1;
    double dist_x2 = x2-x;
    double dist_y1 = y-y1;
    double dist_y2 = y2-y;

    if (dist_x1 < dist && dist_y1 < dist)
      return val_q11;

    if (dist_x2 < dist && dist_y1 < dist)
      return val_q21;

    if (dist_x1 < dist && dist_y2 < dist)
      return val_q12;

    if (dist_x2 < dist && dist_y2 < dist)
      return val_q22;

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

    // Bilinear interpolation

    if (missingCount == 0)
    {
      // All corners have a value.

      double fy1 = dist_x2*val_q11 + dist_x1*val_q21;
      double fy2 = dist_x2*val_q12 + dist_x1*val_q22;
      return (dist_y2*fy1 + dist_y1*fy2);
    }

    if (missingCount == 1)
      return triangularInterpolation(missingFlags,dist_x1,dist_x2,dist_y1,dist_y2,val_q11,val_q21,val_q22,val_q12);

    if (missingCount == 2)
      return borderInterpolation(missingFlags,dist,dist_x1,dist_x2,dist_y1,dist_y2,val_q11,val_q21,val_q22,val_q12);

    return ParamValueMissing;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}









/*! \brief Logarithmically interpolates a value between two positions. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Interpolates a single parameter value between two vertical levels using the given method. */

T::ParamValue levelInterpolation(T::ParamValue value1,T::ParamValue value2,double level1,double level2,double newLevel,short levelInterpolationMethod)
{
  try
  {
    if (levelInterpolationMethod == T::LevelInterpolationMethod::Logarithmic)
    {
      double tmpLev = newLevel / 100.0;
      if ((int)tmpLev >= (int)level1 && (int)tmpLev <= (int)level2)
        newLevel = tmpLev;
    }

    if (level1 == newLevel)
      return value1;

    if (level2 == newLevel)
      return value2;

    double diff1 = newLevel - level1;
    double diff2 = level2 - newLevel;
    double levelDiff = level2 - level1;

    switch (levelInterpolationMethod)
    {
      case T::LevelInterpolationMethod::None:
        return value1;

      case T::LevelInterpolationMethod::Nearest:
        if (diff1 < diff2)
          return value1;
        else
          return value2;

      case T::LevelInterpolationMethod::Min:
        if (value1 < value2)
          return value1;
        else
          return value2;

      case T::LevelInterpolationMethod::Max:
        if (value1 > value2)
          return value1;
        else
          return value2;

      case T::LevelInterpolationMethod::Previous:
        return value1;

      case T::LevelInterpolationMethod::Next:
        return value2;

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
    }
    return ParamValueMissing;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





namespace
{

/*! \brief Appends func(values1[t],values2[t]) for the first len elements to the output vector. */

template <class Func>
void combineValues(const T::ParamValue_vec& values1,const T::ParamValue_vec& values2,uint len,T::ParamValue_vec& values,Func func)
{
  values.reserve(len);
  for (uint t = 0; t < len; t++)
    values.emplace_back(func(values1[t],values2[t]));
}





/*! \brief Appends grid values with the coordinates of values1 and the value func(value1,value2). */

template <class Func>
void combineGridValues(const T::GridValueList& values1,const T::GridValueList& values2,uint len,T::GridValueList& valueList,Func func)
{
  for (uint t = 0; t < len; t++)
  {
    T::GridValue val1;
    T::GridValue val2;
    T::GridValue rec;

    values1.getGridValueByIndex(t,val1);
    values2.getGridValueByIndex(t,val2);

    rec.mX = val1.mX;
    rec.mY = val1.mY;
    rec.mValue = func(val1.mValue,val2.mValue);

    valueList.addGridValue(rec);
  }
}





/*! \brief Like combineValues, but appends ParamValueMissing when either value is missing. */

template <class Func>
void combinePresentValues(const T::ParamValue_vec& values1,const T::ParamValue_vec& values2,uint len,T::ParamValue_vec& values,Func func)
{
  combineValues(values1,values2,len,values,[&func](T::ParamValue v1,T::ParamValue v2) {
    if (v1 != ParamValueMissing  &&  v2 != ParamValueMissing)
      return T::ParamValue(func(v1,v2));
    return T::ParamValue(ParamValueMissing);
  });
}

}  // namespace





/*! \brief Interpolates two value vectors between vertical levels using the given method. */

void levelInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,double level1,double level2,double newLevel,short levelInterpolationMethod,T::ParamValue_vec& values)
{
  try
  {
    if (levelInterpolationMethod == T::LevelInterpolationMethod::Logarithmic)
    {
      double tmpLev = newLevel / 100.0;
      if ((int)tmpLev >= (int)level1 && (int)tmpLev <= (int)level2)
        newLevel = tmpLev;
    }

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

    double diff1 = newLevel - level1;
    double diff2 = level2 - newLevel;
    double levelDiff = level2 - level1;

    uint len1 = values1.size();
    uint len2 = values2.size();

    if (len1 != len2)
      return;

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
        combineValues(values1,values2,len1,values,[](T::ParamValue val1,T::ParamValue val2) {
          if (val1 < val2)
            return val1;
          return val2;
        });
        break;

      case T::LevelInterpolationMethod::Max:
        combineValues(values1,values2,len1,values,[](T::ParamValue val1,T::ParamValue val2) {
          if (val1 > val2)
            return val1;
          return val2;
        });
        break;

      case T::LevelInterpolationMethod::Logarithmic:
        combineValues(values1,values2,len1,values,[&](T::ParamValue val1,T::ParamValue val2) {
          T::ParamValue val = logarithmicInterpolation(newLevel, level1, level2, val1, val2);
          return val;
        });
        break;

      case T::LevelInterpolationMethod::Previous:
        values = values1;
        break;

      case T::LevelInterpolationMethod::Next:
        values = values2;
        break;

      default:
      case T::LevelInterpolationMethod::Linear:
        combineValues(values1,values2,len1,values,[&](T::ParamValue val1,T::ParamValue val2) {
          T::ParamValue val = ParamValueMissing;
          if (val1 != ParamValueMissing && val2 != ParamValueMissing)
          {
            T::ParamValue valueDiff = val2 - val1;
            T::ParamValue valueStep = valueDiff / levelDiff;
            val = val1 + (diff1 * valueStep);
          }
          return val;
        });
        break;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





/*! \brief Interpolates two grid value lists between vertical levels using the given method. */

void levelInterpolation(const T::GridValueList& values1,const T::GridValueList& values2,double level1,double level2,double newLevel,short levelInterpolationMethod,T::GridValueList& valueList)
{
  try
  {
    if (levelInterpolationMethod == T::LevelInterpolationMethod::Logarithmic)
    {
      double tmpLev = newLevel / 100.0;
      if ((int)tmpLev >= (int)level1 && (int)tmpLev <= (int)level2)
        newLevel = tmpLev;
    }

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

    double diff1 = newLevel - level1;
    double diff2 = level2 - newLevel;
    double levelDiff = level2 - level1;

    uint len1 = values1.getLength();
    uint len2 = values2.getLength();

    if (len1 != len2)
      return;

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
        combineGridValues(values1,values2,len1,valueList,[](T::ParamValue val1,T::ParamValue val2) {
          if (val1 < val2)
            return val1;
          return val2;
        });
        break;

      case T::LevelInterpolationMethod::Max:
        combineGridValues(values1,values2,len1,valueList,[](T::ParamValue val1,T::ParamValue val2) {
          if (val1 > val2)
            return val1;
          return val2;
        });
        break;

      case T::LevelInterpolationMethod::Logarithmic:
        combineGridValues(values1,values2,len1,valueList,[&](T::ParamValue val1,T::ParamValue val2) {
          return T::ParamValue(logarithmicInterpolation(newLevel, level1, level2, val1, val2));
        });
        break;

      case T::LevelInterpolationMethod::Previous:
        valueList = values1;
        break;

      case T::LevelInterpolationMethod::Next:
        valueList = values2;
        break;

      default:
      case T::LevelInterpolationMethod::Linear:
        combineGridValues(values1,values2,len1,valueList,[&](T::ParamValue val1,T::ParamValue val2) {
          if (val1 != ParamValueMissing && val2 != ParamValueMissing)
          {
            T::ParamValue valueDiff = val2 - val1;
            T::ParamValue valueStep = valueDiff / levelDiff;
            return T::ParamValue(val1 + (diff1 * valueStep));
          }
          return T::ParamValue(ParamValueMissing);
        });
        break;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





/*! \brief Interpolates a parameter value between two timestamps given as strings. */

T::ParamValue timeInterpolation(T::ParamValue value1,const T::ParamValue& value2,const std::string& time1,const std::string& time2,const std::string& newTime,short timeInterpolationMethod)
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
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





/*! \brief Interpolates a parameter value between two epoch timestamps using the given method. */

T::ParamValue timeInterpolation(T::ParamValue value1,const T::ParamValue& value2,time_t t1,time_t t2,time_t newTime,short timeInterpolationMethod)
{
  try
  {
    if (t1 == newTime)
      return value1;

    if (t2 == newTime)
      return value2;

    auto timeDiff = C_DOUBLE(t2 - t1);
    auto diff1 = C_DOUBLE(newTime - t1);
    auto diff2 = C_DOUBLE(t2 - newTime);

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
          return value2;
        }
        else
        {
          return ParamValueMissing;
        }

      case T::TimeInterpolationMethod::Previous:
        return value1;

      case T::TimeInterpolationMethod::Next:
        return value2;

      default:
        throw Fmi::Exception(BCP,"Unsupported or unknown intepolation method!");
    }

    return ParamValueMissing;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Interpolates two value vectors between two timestamps given as strings. */

void timeInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,int width,int height,const std::string& time1,const std::string& time2,const std::string& newTime,short timeInterpolationMethod,T::ParamValue_vec& newValues)
{
  try
  {
    time_t tt = utcTimeToTimeT(newTime);
    time_t t1 = utcTimeToTimeT(time1);
    time_t t2 = utcTimeToTimeT(time2);

    timeInterpolation(values1,values2,width,height,t1,t2,tt,timeInterpolationMethod,newValues);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Interpolates two value vectors between two epoch timestamps using the given method. */

void timeInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,int width,int height,time_t t1,time_t t2,time_t newTime,short timeInterpolationMethod,T::ParamValue_vec& newValues)
{
  try
  {
    if (values1.size() != values2.size())
      throw Fmi::Exception(BCP,"Value vectors are not the same size!");

    auto timeDiff = C_DOUBLE(t2 - t1);
    auto diff1 = C_DOUBLE(newTime - t1);
    auto diff2 = C_DOUBLE(t2 - newTime);
    double tp = diff1/timeDiff;

    uint sz = values1.size();
    newValues.reserve(sz);

    switch (timeInterpolationMethod)
    {
      case T::TimeInterpolationMethod::Undefined:
      case T::TimeInterpolationMethod::None:
        newValues = values1;
        return;


      case T::TimeInterpolationMethod::Linear:
        combinePresentValues(values1,values2,sz,newValues,[&](T::ParamValue v1,T::ParamValue v2) {
          T::ParamValue vd = (v2 - v1)/timeDiff;
          T::ParamValue newValue = v1 + diff1 * vd;
          return newValue;
        });
        return;


      case T::TimeInterpolationMethod::Nearest:
        if (diff1 <= diff2)
          newValues = values1;
        else
          newValues = values2;
        return;


      case T::TimeInterpolationMethod::Min:
        combinePresentValues(values1,values2,sz,newValues,[&](T::ParamValue v1,T::ParamValue v2) {
          if (v1 <= v2)
            return v1;
          return v2;
        });
        return;


      case T::TimeInterpolationMethod::Max:
        combinePresentValues(values1,values2,sz,newValues,[&](T::ParamValue v1,T::ParamValue v2) {
          if (v1 >= v2)
            return v1;
          return v2;
        });
        return;

      case T::TimeInterpolationMethod::Previous:
        newValues = values1;
        return;

      case T::TimeInterpolationMethod::Next:
        newValues = values2;
        return;

      case T::TimeInterpolationMethod::Transfer:
        newValues = transferInterpolation(values1,values2,width,height,tp);
        break;

      default:
        throw Fmi::Exception(BCP,"Unsupported or unknown intepolation method!");
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Interpolates two grid value lists between two timestamps given as strings. */

void timeInterpolation(const T::GridValueList& values1,const T::GridValueList& values2,const std::string& time1,const std::string& time2,const std::string& newTime,short timeInterpolationMethod,T::GridValueList& valueList)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Interpolates two grid value lists between two epoch timestamps using the given method. */

void timeInterpolation(const T::GridValueList& values1,const T::GridValueList& values2,time_t t1,time_t t2,time_t newTime,short timeInterpolationMethod,T::GridValueList& valueList)
{
  try
  {
    if (values1.getLength() != values2.getLength())
      throw Fmi::Exception(BCP,"Value lists are not the same size!");

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

    auto diff1 = (double)(newTime - t1);
    auto diff2 = (double)(t2 - t1);

    uint len1 = values1.getLength();
    uint len2 = values2.getLength();

    if (len1 != len2)
      return;

    switch (timeInterpolationMethod)
    {
      case T::TimeInterpolationMethod::None:
        valueList = values1;
        break;

      case T::TimeInterpolationMethod::Nearest:
        // diff2 is the whole interval here: the nearest time is the first one when the new
        // time is in the first half. (Comparing diff1 to diff2 always chose the first time.)
        if (2 * diff1 <= diff2)
          valueList = values1;
        else
          valueList = values2;
        break;

      case T::TimeInterpolationMethod::Min:
        combineGridValues(values1,values2,len1,valueList,[](T::ParamValue val1,T::ParamValue val2) {
          if (val1 < val2)
            return val1;
          return val2;
        });
        break;

      case T::TimeInterpolationMethod::Max:
        combineGridValues(values1,values2,len1,valueList,[](T::ParamValue val1,T::ParamValue val2) {
          if (val1 > val2)
            return val1;
          return val2;
        });
        break;

      case T::TimeInterpolationMethod::Previous:
        valueList = values1;
        break;

      case T::TimeInterpolationMethod::Next:
        valueList = values2;
        break;

      default:
      case T::TimeInterpolationMethod::Linear:
        combineGridValues(values1,values2,len1,valueList,[&](T::ParamValue val1,T::ParamValue val2) {
          if (val1 != ParamValueMissing && val2 != ParamValueMissing)
          {
            double valueDiff = val2 - val1;
            double valueStep = valueDiff / diff2;
            return T::ParamValue(val1 + (diff1 * valueStep));
          }
          return T::ParamValue(ParamValueMissing);
        });
        break;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}




/*! \brief Computes the lapse-rate correction for the height difference between true and model terrain. */

namespace
{
double lapseratefix(double lapseRate,double trueHeight,double modelHeight,bool waterFlag)
{
  try
  {
    // Limit inversion in Norwegian fjords
    double sea_lapse_rate_limit = -3.0;

    if (waterFlag)
    {
      lapseRate = std::min(lapseRate, sea_lapse_rate_limit);
    }

    double diff = trueHeight - modelHeight;

    if (lapseRate > 0)
    {
      if (diff < -300)
        diff = -300;
      else
      if (diff > 150)
        diff = 150;
    }
    else
    {
      if (diff < -1500)
        diff = -1500;
      else
      if (diff > 2000)
        diff = 2000;
    }

    // lapse rate unit is km, hence we divide by 1000 to get change per meters
    return lapseRate / 1000 * diff;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}
}  // namespace





/*! \brief Performs landscape-aware interpolation using height, lapse rate and land-sea-mask corrections. */

double landscapeInterpolation(
    double height,
    int coverType,
    double x,
    double y,
    double val_bl,
    double val_br,
    double val_tr,
    double val_tl,
    double height_bl,
    double height_br,
    double height_tr,
    double height_tl,
    double lapserate_bl,
    double lapserate_br,
    double lapserate_tr,
    double lapserate_tl,
    double land_bl,
    double land_br,
    double land_tr,
    double land_tl)
{
  try
  {
/*
    printf("landscapeInterpolation(%f,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
        height,coverType,x,y,
        val_bl,val_br,val_tr,val_tl,
        height_bl,height_br,height_tr,height_tl,
        lapserate_bl,lapserate_br,lapserate_tr,lapserate_tl,
        land_bl,land_br,land_tr,land_tl);
*/
    bool waterFlag = false;
    if (coverType == 240)
      waterFlag = true;

    if (height == ParamValueMissing || coverType <= 0)
      return  linearInterpolation(x,y,0,0,1,1,val_bl,val_br,val_tr,val_tl);


    if (val_bl == ParamValueMissing || val_br == ParamValueMissing || val_tl == ParamValueMissing || val_tr == ParamValueMissing)
      return  linearInterpolation(x,y,0,0,1,1,val_bl,val_br,val_tr,val_tl);


    // Do height corrections if possible

    if (height_bl != ParamValueMissing && height_br != ParamValueMissing && height_tl != ParamValueMissing && height_tr != ParamValueMissing)
    {
      double default_lapserate = -6.5;   // degrees per kilometer

      if (lapserate_bl == ParamValueMissing)
        lapserate_bl = default_lapserate;

      if (lapserate_br == ParamValueMissing)
        lapserate_br = default_lapserate;

      if (lapserate_tl == ParamValueMissing)
        lapserate_tl = default_lapserate;

      if (lapserate_tr == ParamValueMissing)
        lapserate_tr = default_lapserate;

      // Convert the values to the desired height

      val_bl = val_bl + lapseratefix(lapserate_bl, height, height_bl, waterFlag);
      val_br = val_br + lapseratefix(lapserate_br, height, height_br, waterFlag);
      val_tl = val_tl + lapseratefix(lapserate_tl, height, height_tl, waterFlag);
      val_tr = val_tr + lapseratefix(lapserate_tr, height, height_tr, waterFlag);
    }


    double wbl = (1 - x) * (1 - y);
    double wbr = x * (1 - y);
    double wtl = (1 - x) * y;
    double wtr = x * y;


    // Modify the coefficients based on the land sea mask

    if (land_bl != ParamValueMissing && land_br != ParamValueMissing && land_tl != ParamValueMissing && land_tr != ParamValueMissing)
    {
      // Minimum weight for any value selected by Mikko Rauhala
      double wlimit = 0.3;

      //  Handle land areas
      if (!waterFlag)
      {
        // Scale percentage from 0...1 to wlimit...1
        wbl = wbl * (land_bl + wlimit) / (1 + wlimit);
        wbr = wbr * (land_br + wlimit) / (1 + wlimit);
        wtl = wtl * (land_tl + wlimit) / (1 + wlimit);
        wtr = wtr * (land_tr + wlimit) / (1 + wlimit);
      }
      else
      {
        // Scale percentage from 0...1 to 1...wlimit
        wbl = wbl * (1 - land_bl + wlimit) / (1 + wlimit);
        wbr = wbr * (1 - land_br + wlimit) / (1 + wlimit);
        wtl = wtl * (1 - land_tl + wlimit) / (1 + wlimit);
        wtr = wtr * (1 - land_tr + wlimit) / (1 + wlimit);
      }
    }

    //Perform combined interpolation

    double value = (wbl * val_bl + wbr * val_br + wtl * val_tl + wtr * val_tr) / (wbl + wbr + wtl + wtr);

    return value;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}




}

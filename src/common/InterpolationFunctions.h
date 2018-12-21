#pragma once

#include "Typedefs.h"
#include "../grid/Typedefs.h"
#include "../grid/GridValueList.h"

namespace SmartMet
{

double linearInterpolation(double wantedPosition, double position1, double position2, double value1, double value2);
double linearInterpolation(double x,double y,double x1,double y1,double x2,double y2,double val_q11,double val_q21,double val_q22,double val_q12);
double logarithmicInterpolation(double wantedPosition, double position1, double position2, double value1, double value2);


T::ParamValue levelInterpolation(T::ParamValue value1,T::ParamValue value2,int level1,int level2,int newLevel,short levelInterpolationMethod);
void levelInterpolation(T::GridValueList& values1,T::GridValueList& values2,int level1,int level2,int newLevel,short levelInterpolationMethod,T::GridValueList& valueList);

T::ParamValue timeInterpolation(T::ParamValue value1,T::ParamValue& value2,std::string time1,std::string time2,std::string newTime,short timeInterpolationMethod);
void timeInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,std::string time1,std::string time2,std::string newTime,short timeInterpolationMethod,T::ParamValue_vec& newValues);
void timeInterpolation(T::GridValueList& values1,T::GridValueList& values2,std::string timeStr1,std::string timeStr2,std::string newTime,short timeInterpolationMethod,T::GridValueList& valueList);

}


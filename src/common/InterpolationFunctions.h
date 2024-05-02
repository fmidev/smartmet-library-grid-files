#pragma once

#include "Typedefs.h"
#include "../grid/Typedefs.h"
#include "../grid/GridValueList.h"

namespace SmartMet
{

double linearInterpolation(double wantedPosition, double position1, double position2, double value1, double value2);
double linearInterpolation(double x,double y,double x1,double y1,double x2,double y2,double val_q11,double val_q21,double val_q22,double val_q12);
double logarithmicInterpolation(double wantedPosition, double position1, double position2, double value1, double value2);


T::ParamValue levelInterpolation(T::ParamValue value1,T::ParamValue value2,double level1,double level2,double newLevel,short levelInterpolationMethod);
void levelInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,double level1,double level2,double newLevel,short levelInterpolationMethod,T::ParamValue_vec& values);
void levelInterpolation(T::GridValueList& values1,T::GridValueList& values2,double level1,double level2,double newLevel,short levelInterpolationMethod,T::GridValueList& valueList);

T::ParamValue timeInterpolation(T::ParamValue value1,T::ParamValue& value2,time_t t1,time_t t2,time_t newTime,short timeInterpolationMethod);
T::ParamValue timeInterpolation(T::ParamValue value1,T::ParamValue& value2,std::string time1,std::string time2,std::string newTime,short timeInterpolationMethod);

void timeInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,time_t t1,time_t t2,time_t newTime,short timeInterpolationMethod,T::ParamValue_vec& newValues);
void timeInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,std::string time1,std::string time2,std::string newTime,short timeInterpolationMethod,T::ParamValue_vec& newValues);

void timeInterpolation(T::GridValueList& values1,T::GridValueList& values2,time_t t1,time_t t2,time_t newTime,short timeInterpolationMethod,T::GridValueList& valueList);
void timeInterpolation(T::GridValueList& values1,T::GridValueList& values2,std::string time1,std::string time2,std::string newTime,short timeInterpolationMethod,T::GridValueList& valueList);


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
    double land_tl);

}


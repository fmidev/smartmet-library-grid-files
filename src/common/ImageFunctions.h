#pragma once

#include "Exception.h"
#include "Point.h"
#include "Coordinate.h"


namespace SmartMet
{

// The function writes an image data to the JPEG file.

void jpeg_save(
    const char *filename,
    unsigned long *image,
    int image_height,
    int image_width,
    int quality);


// The function converts RGB color component (Red,Green,Blue) to a single RGB value.
// An individual color should have a value that is the range 0..255.

uint rgb(uint red, uint green, uint blue);


// The function converts HSV (Hue, Saturatio, Value) color to a RGB color. Each
// HSV component should have value that is in the range 0..255.

uint hsv_to_rgb(unsigned char hue, unsigned char saturation, unsigned char value);


void getPointsInsideCircle(int gridWidth,int gridHeight,double origoX,double origoY,double radius,std::vector<T::Point>& gridPoints);
void getPointsInsidePolygon(int gridWidth,int gridHeight,std::vector<T::Coordinate>& polygonPoints,std::vector<T::Point>& gridPoints);

}


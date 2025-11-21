#include "Topography.h"
#include "../common/ImageFunctions.h"
#include <macgyver/Exception.h>


namespace SmartMet
{
namespace Map
{

Topography topography;


inline unsigned char argb_to_gray(uint argb)
{
  uint r = (argb & 0xFF0000) >> 16;
  uint g = (argb & 0x00FF00) >> 8;
  uint b = (argb & 0x0000FF);

  return (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
}





Topography::Topography()
{
  try
  {
    mInitialized = false;

    mLandShading = nullptr;
    mLandShading_width = 0;
    mLandShading_height = 0;
    mLandShading_initialized = false;
    mLandShading_size = 0;
    mLandShading_dx = 0;
    mLandShading_dy = 0;

    mSeaShading = nullptr;
    mSeaShading_width = 0;
    mSeaShading_height = 0;
    mSeaShading_initialized = false;
    mSeaShading_size = 0;
    mSeaShading_dx = 0;
    mSeaShading_dy = 0;

    mLandSeaMask_width = 0;
    mLandSeaMask_height = 0;
    mLandSeaMask_initialized = false;
    mLandSeaMask_size = 0;
    mLandSeaMask_dx = 0;
    mLandSeaMask_dy = 0;


  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




Topography::~Topography()
{
  try
  {
    if (mLandShading)
      delete [] mLandShading;

    if (mSeaShading)
      delete [] mSeaShading;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}




void Topography::init(const char* configFile,bool initLandSeaMask,bool initLandShading,bool initSeaShading)
{
  try
  {
    if (mInitialized)
      return;

    mConfigurationFile.readFile(configFile);

    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.map.land-sea-mask-file",mLandSeaMask_file);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.map.land-shading-file",mLandShading_file);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.map.sea-shading-file",mSeaShading_file);

    if (initLandSeaMask)
      loadLandSeaMask();

    if (initLandShading)
      loadLandShading();

    if (initSeaShading)
      loadSeaShading();

    mInitialized = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void Topography::isLand(const T::Coordinate_vec& coordinates,std::vector<bool>& land)
{
  try
  {
    uint sz = coordinates.size();
    land.reserve(sz);
    for (uint t=0; t<sz; t++)
    {
      land.emplace_back(isLand(coordinates[t].x(),coordinates[t].y()));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void Topography::getLand(const T::Coordinate_vec& coordinates,std::vector<float>& land)
{
  try
  {
    uint sz = coordinates.size();
    land.reserve(sz);
    for (uint t=0; t<sz; t++)
    {
      if (isLand(coordinates[t].x(),coordinates[t].y()))
        land.emplace_back(1.0);
      else
        land.emplace_back(0.0);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Topography::getShading(const T::Coordinate_vec& coordinates,std::vector<float>& shadings)
{
  try
  {
    uint sz = coordinates.size();
    shadings.reserve(sz);
    for (uint t=0; t<sz; t++)
    {
      shadings.emplace_back(getShading(coordinates[t].x(),coordinates[t].y()));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Topography::getLandShading(const T::Coordinate_vec& coordinates,std::vector<float>& shadings)
{
  try
  {
    uint sz = coordinates.size();
    shadings.reserve(sz);
    for (uint t=0; t<sz; t++)
    {
      if (isLand(coordinates[t].x(),coordinates[t].y()))
        shadings.emplace_back(getLandShading(coordinates[t].x(),coordinates[t].y()));
      else
        shadings.emplace_back(ParamValueMissing);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void Topography::getSeaShading(const T::Coordinate_vec& coordinates,std::vector<float>& shadings)
{
  try
  {
    uint sz = coordinates.size();
    shadings.reserve(sz);
    for (uint t=0; t<sz; t++)
    {
      if (isLand(coordinates[t].x(),coordinates[t].y()))
        shadings.emplace_back(ParamValueMissing);
      else
        shadings.emplace_back(getSeaShading(coordinates[t].x(),coordinates[t].y()));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Topography::loadLandSeaMask()
{
  try
  {
    if (mLandSeaMask_initialized)
      return;

    AutoWriteLock writeLock(&mModificationLock);
    if (mLandSeaMask_initialized)
      return;

    FILE *file = fopen(mLandSeaMask_file.c_str(),"r");
    if (file)
    {
      uint length = 0;
      if (fread(&mLandSeaMask_width,4,1,file) > 0  && fread(&mLandSeaMask_height,4,1,file) > 0 && fread(&length,4,1,file) > 0)
      {
        if ((mLandSeaMask_width * mLandSeaMask_height) == length)
        {
          fseek(file,8,SEEK_SET);
          mLandSeaMask.readFromFile(file);
        }
        else
        {
          Fmi::Exception exception(BCP, "Land-sea mask file has wrong format!");
          exception.addParameter("land-sea-mask-file",mLandSeaMask_file);
          exception.printError();

          mLandSeaMask_width = 0;
          mLandSeaMask_height = 0;
        }
      }

      fclose(file);
    }

    mLandSeaMask_size = mLandSeaMask_width * mLandSeaMask_height;
    mLandSeaMask_dx = mLandSeaMask_width/360.0;
    mLandSeaMask_dy = mLandSeaMask_height/180.0;

    mLandSeaMask_initialized = true;
  }
  catch (...)
  {
    mLandSeaMask_initialized = true;
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void Topography::loadLandShading()
{
  try
  {
    if (mLandShading_initialized)
      return;

    if (mLandShading_file.empty())
    {
      mLandShading_initialized = true;
      return;
    }

    AutoWriteLock writeLock(&mModificationLock);
    if (mLandShading_initialized)
      return;

    CImage image;
    png_load(mLandShading_file.c_str(),image);

    mLandShading_width = image.width;
    mLandShading_height = image.height;
    mLandShading_size = mLandShading_width * mLandShading_height;
    mLandShading_dx = (double)mLandShading_width/360.0;
    mLandShading_dy = (double)mLandShading_height/180.0;

    if (mLandShading_size > 0)
    {
      mLandShading = new float[mLandShading_size];

#if 0
      uint div = 5;
      uint dd = div*div;
      uint nw = image.width / div;
      uint nh = image.height / div;

      uint ns = nw*nh;
      uint *newimage = new uint[ns];

      uint c = 0;
      for (uint y=0; y<nh; y++)
      {
        uint yy = y * div;
        for (uint x=0; x<nw; x++)
        {
          uint aa = 0,rr = 0, gg = 0, bb = 0;

          uint xx = x * div;

          for (uint yt=0; yt<div; yt++)
          {
            for (uint xt=0; xt<div; xt++)
            {
              uint p = (yy+yt)*image.width + xx + xt;
              uint col = image.pixel[p];

              uint a = (col & 0xFF000000) >> 24;
              uint r = (col & 0x00FF0000) >> 16;
              uint g = (col & 0x0000FF00) >> 8;
              uint b = (col & 0x000000FF);

              aa += a;
              rr += r;
              gg += g;
              bb += b;
            }
          }
          //newimage[c] = ((aa/100) << 24) + ((rr/100) << 16) + ((gg/100) << 8) + (bb/100);
          newimage[c] = 0xFF000000 + (((uint)(rr/dd)) << 16) + (((uint)(gg/dd)) << 8) + (uint)(bb/dd);
          c++;
        }
      }

      png_save("/tmp/land-shading_lr.png",newimage,nw,nh,9);
      delete [] newimage;
#endif

      for (uint t=0; t<mLandShading_size; t++)
      {
        uint col = image.pixel[t];
        double pp = (double)argb_to_gray(col);
        if (pp <= 207)
          mLandShading[t] = (float)(-((207.0 - pp)/207.0));
        else
          mLandShading[t] = (float)((pp - 207.0)/48.0);
      }
    }

    mLandShading_initialized = true;
  }
  catch (...)
  {
    mLandShading_initialized = true;
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void Topography::loadSeaShading()
{
  try
  {
    if (mSeaShading_initialized)
      return;

    if (mSeaShading_file.empty())
    {
      mSeaShading_initialized = true;
      return;
    }

    AutoWriteLock writeLock(&mModificationLock);
    if (mSeaShading_initialized)
      return;

    CImage image;
    png_load(mSeaShading_file.c_str(),image);

    mSeaShading_width = image.width;
    mSeaShading_height = image.height;
    mSeaShading_size = mSeaShading_width * mSeaShading_height;
    mSeaShading_dx = (double)mSeaShading_width/360.0;
    mSeaShading_dy = (double)mSeaShading_height/180.0;

    if (mSeaShading_size > 0)
    {
      mSeaShading = new float[mSeaShading_size];

#if 0
      uint div = 5;
      uint dd = div*div;
      uint nw = image.width / div;
      uint nh = image.height / div;

      uint ns = nw*nh;
      uint *newimage = new uint[ns];

      uint c = 0;
      for (uint y=0; y<nh; y++)
      {
        uint yy = y * div;
        for (uint x=0; x<nw; x++)
        {
          uint aa = 0,rr = 0, gg = 0, bb = 0;

          uint xx = x * div;

          for (uint yt=0; yt<div; yt++)
          {
            for (uint xt=0; xt<div; xt++)
            {
              uint p = (yy+yt)*image.width + xx + xt;
              uint col = image.pixel[p];

              uint a = (col & 0xFF000000) >> 24;
              uint r = (col & 0x00FF0000) >> 16;
              uint g = (col & 0x0000FF00) >> 8;
              uint b = (col & 0x000000FF);

              aa += a;
              rr += r;
              gg += g;
              bb += b;
            }
          }
          //newimage[c] = ((aa/100) << 24) + ((rr/100) << 16) + ((gg/100) << 8) + (bb/100);
          newimage[c] = 0xFF000000 + (((uint)(rr/dd)) << 16) + (((uint)(gg/dd)) << 8) + (uint)(bb/dd);
          c++;
        }
      }

      png_save("/tmp/sea-shading_lr.png",newimage,nw,nh,9);
      delete [] newimage;
#endif

      for (uint t=0; t<mSeaShading_size; t++)
      {
        uint col = image.pixel[t];
        double pp = (double)argb_to_gray(col);
        if (pp <= 163)
          mSeaShading[t] = (float)(-((163.0 - pp)/163.0));
        else
          mSeaShading[t] = (float)((pp - 163.0)/92.0);
      }
    }

    mSeaShading_initialized = true;
  }
  catch (...)
  {
    mSeaShading_initialized = true;
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}  // namespace Map
}  // namespace SmartMet

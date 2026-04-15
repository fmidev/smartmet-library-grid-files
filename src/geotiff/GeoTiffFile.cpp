#include "GeoTiffFile.h"
#include "../common/ShowFunction.h"
#include "../grid/GridFile.h"
#include "../grid/PrintOptions.h"
#include "../common/GeneralFunctions.h"
#include "../identification/GridDef.h"

#include <algorithm>
#include <ctime>
#include <list>
#include <string>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace GeoTiff
{

/*! \brief The constructor of the class. */

GeoTiffFile::GeoTiffFile(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    mFilename = filename;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

GeoTiffFile::~GeoTiffFile()
{
}







/* Defined as inline

T::ParamValue GeoTiffFile::getGridValue(uint paramIndex,uint levelIndex,uint timeIndex,uint grid_i,uint grid_j) const
{
  FUNCTION_TRACE
  try
  {
    return ParamValueMissing;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}

*/


void GeoTiffFile::read(MemoryReader& memoryReader,MessageInfoVec& messageInfoList)
{
  try
  {
    ushort byteOrder = memoryReader.read_uint16();
    if (byteOrder == 0x4949)
      memoryReader.setLittleEndian(true);
    else
    if (byteOrder == 0x4D4D)
      throw Fmi::Exception(BCP,"Big-endian geoTiffs not supported!",nullptr);
      //memoryReader.setLittleEndian(false);
    else
      throw Fmi::Exception(BCP,"Not a GeoTiff file!",nullptr);

    ushort i = memoryReader.read_uint16();
    if (i != 0x2A)
      throw Fmi::Exception(BCP,"Not a GeoTiff file!",nullptr);

    uint ifdOffset = memoryReader.read_uint32();
    while (ifdOffset != 0)
    {
      //printf("OFFSET %u\n",ifdOffset);
      memoryReader.setReadPosition(ifdOffset);
      readIFD(memoryReader,messageInfoList);
      ifdOffset = memoryReader.read_uint32();
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





void GeoTiffFile::readIFD(MemoryReader& memoryReader,MessageInfoVec& messageInfoList)
{
  try
  {
    uint numOfGrids = 0;
    uint columns = 0;
    uint totalRows = 0;
    uint rowsPerStrip = 0;
    uint totalSize = 0;
    uint dataOffset = 0;
    uint metaOffset = 0;
    uint geometryId = 0;
    uint metaSize = 0;
    uint sampleFormat = 1;
    uint bitsPerSample = 0;

    ushort numOfDirectoryEntries = memoryReader.read_uint16();
    for (ushort t = 0; t < numOfDirectoryEntries; t++)
    {
      ushort tag = memoryReader.read_uint16();
      ushort type = memoryReader.read_uint16();
      uint count = memoryReader.read_uint32();
      uint value = memoryReader.read_uint32();

      //printf("TAG %u: %u,%u,%u,%u\n",t,tag,type,count,value);

      switch (tag)
      {
        case Tag::ImageWidth:
          columns = value;
          break;

        case Tag::ImageLength:
          totalRows = value;
          break;

        case Tag::SampleFormat:
          sampleFormat = value;
          break;

        case Tag::BitsPerSample:
          bitsPerSample = value;
          break;

        case Tag::RowsPerStrip:
          rowsPerStrip = value;
          break;

        case Tag::StripByteCounts:
          totalSize = value;
          break;

        case Tag::StripOffsets:
          dataOffset = value;
          break;

        case Tag::NumOfGrids:
          numOfGrids = value;
          break;

        case Tag::GeometryId:
          geometryId = value;
          break;

        case Tag::MetaOffset:
          metaOffset = value;
          metaSize = count;
          break;

        case Tag::NewSubfileType:
        case Tag::SubfileType:
        case Tag::Compression:
        case Tag::PhotometricInterpretation:
        case Tag::Threshholding:
        case Tag::CellWidth:
        case Tag::CellLength:
        case Tag::FillOrder:
        case Tag::DocumentName:
        case Tag::ImageDescription:
        case Tag::Make:
        case Tag::Model:
        case Tag::Orientation:
        case Tag::SamplesPerPixel:
        case Tag::MinSampleValue:
        case Tag::MaxSampleValue:
        case Tag::XResolution:
        case Tag::YResolution:
        case Tag::PlanarConfiguration:
        case Tag::PageName:
        case Tag::XPosition:
        case Tag::YPosition:
        case Tag::FreeOffsets:
        case Tag::FreeByteCounts:
        case Tag::GrayResponseUnit:
        case Tag::GrayResponseCurve:
        case Tag::T4Options:
        case Tag::T6Options:
        case Tag::ResolutionUnit:
        case Tag::PageNumber:
        case Tag::TransferFunction:
        case Tag::Software:
        case Tag::DateTime:
        case Tag::Artist:
        case Tag::HostComputer:
        case Tag::Predictor:
        case Tag::WhitePoint:
        case Tag::PrimaryChromaticities:
        case Tag::ColorMap:
        case Tag::HalftoneHints:
        case Tag::TileWidth:
        case Tag::TileLength:
        case Tag::TileOffsets:
        case Tag::TileByteCounts:
        case Tag::InkSet:
        case Tag::InkNames:
        case Tag::NumberOfInks:
        case Tag::DotRange:
        case Tag::TargetPrinter:
        case Tag::ExtraSamples:
        case Tag::SMinSampleValue:
        case Tag::SMaxSampleValue:
        case Tag::TransferRange:
        case Tag::JPEGProc:
        case Tag::JPEGInterchangeFormat:
        case Tag::JPEGInterchangeFormatLngth:
        case Tag::JPEGRestartInterval:
        case Tag::JPEGLosslessPredictors:
        case Tag::JPEGPointTransforms:
        case Tag::JPEGQTables:
        case Tag::JPEGDCTables:
        case Tag::JPEGACTables:
        case Tag::YCbCrCoefficients:
        case Tag::YCbCrSubSampling:
        case Tag::YCbCrPositioning:
        case Tag::ReferenceBlackWhite:
        case Tag::Copyright:
          break;
      }
    }

    if (metaOffset == 0  ||  metaSize == 0)
    {
      Fmi::Exception exception(BCP,"No meta information found!",nullptr);
      throw exception;
    }

    if (rowsPerStrip != totalRows)
    {
      Fmi::Exception exception(BCP,"Number or rows should be same as 'rowsPerStrips'!",nullptr);
      exception.addParameter("totalRows",std::to_string(totalRows));
      exception.addParameter("rowsPerStrip",std::to_string(rowsPerStrip));
      throw exception;
    }


    uint rows = totalRows/numOfGrids;
    uint gridSize = totalSize/numOfGrids;

    /*
    printf("numOfGrids %u\n",numOfGrids);
    printf("sampleFormat %u\n",sampleFormat);
    printf("bitsPerSample %u\n",bitsPerSample);
    printf("columns %u\n",columns);
    printf("totalRows %u\n",totalRows);
    printf("rowsPerStrip %u\n",rowsPerStrip);
    printf("rows %u\n",rows);
    printf("totalSize %u\n",totalSize);
    printf("gridSize %u\n",gridSize);
    printf("dataOffset %u\n",dataOffset);
    printf("geometryId %u\n",geometryId);
    printf("metaOffset %u\n",metaOffset);
    printf("metaSize %u\n",metaSize);
    */


    // Reading meta-information

    Int64 rp = memoryReader.getReadPosition();

    std::vector<std::string> lines;
    char buf[metaSize+1];
    memoryReader.setReadPosition(metaOffset);
    uint c = 0;
    for (uint t=0; t<metaSize; t++)
    {
      char ch = memoryReader.read_int8();
      if (ch == '\n')
      {
        buf[c] = '\0';
        if (c > 0)
          lines.push_back(std::string(buf));

        c = 0;
      }
      else
      {
        buf[c] = ch;
        c++;
      }
    }
    buf[c] = '\0';
    if (c > 0)
      lines.push_back(std::string(buf));

    memoryReader.setReadPosition(rp);

    if (lines.size() < numOfGrids)
    {
      Fmi::Exception exception(BCP,"Meta information does not contain enough lines!",nullptr);
      exception.addParameter("lines",std::to_string(lines.size()));
      throw exception;
    }

    // Creating message information:

    for (uint t=0; t<numOfGrids; t++)
    {
      MessageInfo messageInfo;

      std::vector<std::string> fields;
      splitString(lines[t],';',fields);

      if (fields.size() < 6)
      {
        Fmi::Exception exception(BCP,"Meta information line does not contain enough fields (expected 6 fields)!",nullptr);
        exception.addParameter("lineIndex",std::to_string(t));
        exception.addParameter("line",lines[t]);
        throw exception;
      }

      messageInfo.mDataPtr = (char*)(memoryReader.getStartPtr() + dataOffset + t*gridSize);
      messageInfo.mDataSize = gridSize;
      messageInfo.mDataType = sampleFormat;
      messageInfo.mBitsPerValue = bitsPerSample;
      messageInfo.mForecastTimeT = utcTimeToTimeT(fields[0]);
      messageInfo.mColumns = columns;
      messageInfo.mRows = rows;
      messageInfo.mParameterName = fields[1];
      messageInfo.mLevelId = toUInt32(fields[2]);
      messageInfo.mLevel = toUInt32(fields[3]);
      messageInfo.mForecastType = toInt32(fields[4]);
      messageInfo.mForecastNumber = toInt32(fields[5]);
      messageInfo.mGeometryId = geometryId;

      messageInfoList.push_back(messageInfo);
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GeoTiffFile::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "GeoTiffFile\n";
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




}
}

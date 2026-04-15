#pragma once

#include "../grid/Message.h"
#include "Message.h"


namespace SmartMet
{
namespace GeoTiff
{

class GeoTiffFile
{
  public:

                        GeoTiffFile(const char *filename);
    virtual             ~GeoTiffFile();

    void                read(MemoryReader& memoryReader,MessageInfoVec& messageInfoList);
    void                readIFD(MemoryReader& memoryReader,MessageInfoVec& messageInfoList);
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    //T::ParamValue       getGridValue(uint paramIndex,uint grid_i,uint grid_j) const;

  protected:

    std::string         mFilename;

  public:

    class Tag
    {
      public:
        static const unsigned short NewSubfileType = 254;
        static const unsigned short SubfileType = 255;
        static const unsigned short ImageWidth = 256;
        static const unsigned short ImageLength = 257;
        static const unsigned short BitsPerSample = 258;
        static const unsigned short Compression = 259;
        static const unsigned short PhotometricInterpretation = 262;
        static const unsigned short Threshholding = 263;
        static const unsigned short CellWidth = 264;
        static const unsigned short CellLength = 265;
        static const unsigned short FillOrder = 266;
        static const unsigned short DocumentName = 269;
        static const unsigned short ImageDescription = 270;
        static const unsigned short Make = 271;
        static const unsigned short Model = 272;
        static const unsigned short StripOffsets = 273;
        static const unsigned short Orientation = 274;
        static const unsigned short SamplesPerPixel = 277;
        static const unsigned short RowsPerStrip = 278;
        static const unsigned short StripByteCounts = 279;
        static const unsigned short MinSampleValue = 280;
        static const unsigned short MaxSampleValue = 281;
        static const unsigned short XResolution = 282;
        static const unsigned short YResolution = 283;
        static const unsigned short PlanarConfiguration = 284;
        static const unsigned short PageName = 285;
        static const unsigned short XPosition = 286;
        static const unsigned short YPosition = 287;
        static const unsigned short FreeOffsets = 288;
        static const unsigned short FreeByteCounts = 289;
        static const unsigned short GrayResponseUnit = 290;
        static const unsigned short GrayResponseCurve = 291;
        static const unsigned short T4Options = 292;
        static const unsigned short T6Options = 293;
        static const unsigned short ResolutionUnit = 296;
        static const unsigned short PageNumber = 297;
        static const unsigned short TransferFunction = 301;
        static const unsigned short Software = 305;
        static const unsigned short DateTime = 306;
        static const unsigned short Artist = 315;
        static const unsigned short HostComputer = 316;
        static const unsigned short Predictor = 317;
        static const unsigned short WhitePoint = 318;
        static const unsigned short PrimaryChromaticities = 319;
        static const unsigned short ColorMap = 320;
        static const unsigned short HalftoneHints = 321;
        static const unsigned short TileWidth = 322;
        static const unsigned short TileLength = 323;
        static const unsigned short TileOffsets = 324;
        static const unsigned short TileByteCounts = 325;
        static const unsigned short InkSet = 332;
        static const unsigned short InkNames = 333;
        static const unsigned short NumberOfInks = 334;
        static const unsigned short DotRange = 336;
        static const unsigned short TargetPrinter = 337;
        static const unsigned short ExtraSamples = 338;
        static const unsigned short SampleFormat = 339;
        static const unsigned short SMinSampleValue = 340;
        static const unsigned short SMaxSampleValue = 341;
        static const unsigned short TransferRange = 342;
        static const unsigned short JPEGProc = 512;
        static const unsigned short JPEGInterchangeFormat = 513;
        static const unsigned short JPEGInterchangeFormatLngth = 514;
        static const unsigned short JPEGRestartInterval = 515;
        static const unsigned short JPEGLosslessPredictors = 517;
        static const unsigned short JPEGPointTransforms = 518;
        static const unsigned short JPEGQTables = 519;
        static const unsigned short JPEGDCTables = 520;
        static const unsigned short JPEGACTables = 521;
        static const unsigned short YCbCrCoefficients = 529;
        static const unsigned short YCbCrSubSampling = 530;
        static const unsigned short YCbCrPositioning = 531;
        static const unsigned short ReferenceBlackWhite = 532;
        static const unsigned short Copyright = 33432;

        static const unsigned short NumOfGrids = 65000;
        static const unsigned short GeometryId = 65001;
        static const unsigned short MetaOffset = 65002;
    };
};



typedef GeoTiffFile* GeoTiffFilePtr;


}  // namespace GeoTiff
}  // namespace SmartMet


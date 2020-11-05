#include "SecondOrderPacking.h"
#include "DataSection.h"
#include "Message.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"
#include "../common/BitArrayReader.h"
#include "../common/MemoryReader.h"


namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

SecondOrderPacking::SecondOrderPacking()
{
  try
  {
    mN1 = 0;
    mExtendedFlags = 0;
    mN2 = 0;
    mP1 = 0;
    mP2 = 0;
    mExtraValues = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

SecondOrderPacking::SecondOrderPacking(const SecondOrderPacking& other)
:DataDefinition(other)
{
  try
  {
    mN1 = other.mN1;
    mExtendedFlags = other.mExtendedFlags;
    mN2 = other.mN2;
    mP1 = other.mP1;
    mP2 = other.mP2;
    mExtraValues = other.mExtraValues;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

SecondOrderPacking::~SecondOrderPacking()
{
}





DataDefinition* SecondOrderPacking::createDataDefinition() const
{
  try
  {
    return (DataDefinition*) new SecondOrderPacking(*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





PackingMethod SecondOrderPacking::getPackingMethod() const
{
  try
  {
    return PackingMethod::SECOND_ORDER_PACKING;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void SecondOrderPacking::read(MemoryReader& memoryReader)
{
  try
  {
    memoryReader >> mN1;
    memoryReader >> mExtendedFlags;
    memoryReader >> mN2;
    memoryReader >> mP1;
    memoryReader >> mP2;
    memoryReader >> mExtraValues;

    // The rest of the information is stored to dataSection.mDataPtr, which
    // is delivered to the decodeValues() method when needed.
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void SecondOrderPacking::write(DataWriter& dataWriter)
{
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void SecondOrderPacking::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Dimensions dimensions = message->getGridDimensions();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    std::size_t bitmapSizeInBytes = message->getBitmapDataSizeInBytes();
    std::int16_t binaryScaleFactor = message->getBinaryScaleFactor();
    std::uint16_t decimalScaleFactor = message->getDecimalScaleFactor();
    std::float_t referenceValue = message->getReferenceValue();
    std::uint8_t bitsPerValue = message->getBitsPerValue();
    std::uint8_t flags = message->getFlags();

    if (data == nullptr)
      return;
      //throw Fmi::Exception(BCP,"The 'data' pointer points to nullptr!");

    // The documentation of this packing method is just terrible. The basic idea
    // of this packing method should be close to grib2 complex packing, but still
    // there are some issues that are not clear at all.

    if (flags & AdditionalFlags)
    {
      bool secondOrderOfDifferentWidth = false;
      bool matrixOfValues = false;
      bool secondaryBitmapPresent = false;
      bool generalExtended2ordr = false;
      // bool boustrophedonic = false;
      bool plusOneinOrdersOfSPD = false;
      bool twoOrdersOfSPD = false;

      if (mExtendedFlags & DifferentValueWidths)
          secondOrderOfDifferentWidth = true;

      if (mExtendedFlags & MatrixOfValues)
          matrixOfValues = true;

      if (mExtendedFlags & SecondaryBitmapsPresent)
        secondaryBitmapPresent = true;

      if (mExtendedFlags & GeneralExtendedPacking)
        generalExtended2ordr = true;

      // if (mExtendedFlags & BoustrophedonicOrdering)
      //   boustrophedonic = true;

      if (mExtendedFlags & SpatialDifferencingPlus1)
        plusOneinOrdersOfSPD = true;

      if (mExtendedFlags & SpatialDifferencingPlus2)
        twoOrdersOfSPD = true;


      if (!matrixOfValues)
      {
        if (secondOrderOfDifferentWidth  &&  !secondaryBitmapPresent  && !generalExtended2ordr)
        {
          decodeValues_rowByRow(numOfValues,dimensions,data,dataSize,bitmap,bitmapSizeInBytes,
              binaryScaleFactor,decimalScaleFactor,referenceValue,bitsPerValue,flags,decodedValues);
          return;
        }

        if (!secondOrderOfDifferentWidth  &&  secondaryBitmapPresent  &&  !generalExtended2ordr)
        {
          decodeValues_constantWidth(numOfValues,dimensions,data,dataSize,bitmap,bitmapSizeInBytes,
              binaryScaleFactor,decimalScaleFactor,referenceValue,bitsPerValue,flags,decodedValues);
          return;
        }


        if (secondOrderOfDifferentWidth  &&  secondaryBitmapPresent  &&  !generalExtended2ordr)
        {
          decodeValues_differentWidth(numOfValues,dimensions,data,dataSize,bitmap,bitmapSizeInBytes,
              binaryScaleFactor,decimalScaleFactor,referenceValue,bitsPerValue,flags,decodedValues);
          return;
        }

        if (secondOrderOfDifferentWidth  &&  !secondaryBitmapPresent  &&  generalExtended2ordr  &&  !plusOneinOrdersOfSPD  &&  !twoOrdersOfSPD)
        {
          decodeValues_SPD(numOfValues,dimensions,data,dataSize,bitmap,bitmapSizeInBytes,
              binaryScaleFactor,decimalScaleFactor,referenceValue,bitsPerValue,flags,decodedValues,0);
          return;
        }

        if (secondOrderOfDifferentWidth  &&  !secondaryBitmapPresent  &&   generalExtended2ordr  &&  plusOneinOrdersOfSPD  &&  !twoOrdersOfSPD)
        {
          decodeValues_SPD(numOfValues,dimensions,data,dataSize,bitmap,bitmapSizeInBytes,
              binaryScaleFactor,decimalScaleFactor,referenceValue,bitsPerValue,flags,decodedValues,1);
          return;
        }

        if (secondOrderOfDifferentWidth  &&  !secondaryBitmapPresent  &&   generalExtended2ordr  &&  !plusOneinOrdersOfSPD  &&  twoOrdersOfSPD)
        {
          decodeValues_SPD(numOfValues,dimensions,data,dataSize,bitmap,bitmapSizeInBytes,
              binaryScaleFactor,decimalScaleFactor,referenceValue,bitsPerValue,flags,decodedValues,2);
          return;
        }

        if (secondOrderOfDifferentWidth  &&  !secondaryBitmapPresent  &&   generalExtended2ordr  &&  plusOneinOrdersOfSPD  &&  twoOrdersOfSPD)
        {
          decodeValues_SPD(numOfValues,dimensions,data,dataSize,bitmap,bitmapSizeInBytes,
              binaryScaleFactor,decimalScaleFactor,referenceValue,bitsPerValue,flags,decodedValues,3);
          return;
        }
      }
      else
      {
        throw Fmi::Exception(BCP,"Matrix of values not supported!");
      }
    }
    else
    {
      throw Fmi::Exception(BCP,"Additional flags not in use!");
    }

    throw Fmi::Exception(BCP,"Not supported!");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void SecondOrderPacking::decodeValues_rowByRow(
    std::size_t numOfValues,
    T::Dimensions dimensions,
    T::Data_ptr data,
    std::size_t dataSize,
    T::Data_ptr bitmap,
    std::size_t bitmapSizeInBytes,
    std::int16_t binaryScaleFactor,
    std::uint16_t decimalScaleFactor,
    std::float_t referenceValue,
    std::uint8_t bitsPerValue,
    std::uint8_t flags,
    T::ParamValue_vec& decodedValues) const
{
  try
  {
    throw Fmi::Exception(BCP,"Second order packing (rowByRow) not implemented!");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void SecondOrderPacking::decodeValues_constantWidth(
    std::size_t numOfValues,
    T::Dimensions dimensions,
    T::Data_ptr data,
    std::size_t dataSize,
    T::Data_ptr bitmap,
    std::size_t bitmapSizeInBytes,
    std::int16_t binaryScaleFactor,
    std::uint16_t decimalScaleFactor,
    std::float_t referenceValue,
    std::uint8_t bitsPerValue,
    std::uint8_t flags,
    T::ParamValue_vec& decodedValues) const
{
  try
  {
    throw Fmi::Exception(BCP,"Second order packing (constantWidth) not implemented!");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void SecondOrderPacking::decodeValues_differentWidth(
    std::size_t numOfValues,
    T::Dimensions dimensions,
    T::Data_ptr data,
    std::size_t dataSize,
    T::Data_ptr bitmap,
    std::size_t bitmapSizeInBytes,
    std::int16_t binaryScaleFactor,
    std::uint16_t decimalScaleFactor,
    std::float_t referenceValue,
    std::uint8_t bitsPerValue,
    std::uint8_t flags,
    T::ParamValue_vec& decodedValues) const
{
  try
  {
    throw Fmi::Exception(BCP,"Second order packing (differentWidth) not implemented!");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void SecondOrderPacking::decodeValues_SPD(
    std::size_t numOfValues,
    T::Dimensions dimensions,
    T::Data_ptr data,
    std::size_t dataSize,
    T::Data_ptr bitmap,
    std::size_t bitmapSizeInBytes,
    std::int16_t binaryScaleFactor,
    std::uint16_t decimalScaleFactor,
    std::float_t referenceValue,
    std::uint8_t bitsPerValue,
    std::uint8_t flags,
    T::ParamValue_vec& decodedValues,
    uint orderOfSPD) const
{
  try
  {
    // TODO: Check bitmap bits.
    if (bitmap != nullptr &&  bitmapSizeInBytes > 0)
      throw Fmi::Exception(BCP,"Bitmap not yet supported!");


    decodedValues.clear();
    decodedValues.reserve(numOfValues);

    uint numberOfGroups = mP1  + 65536 * mExtraValues;
    uint N1 = mN1;
    uint N2 = mN2;
    uint widthOfWidths = 0;
    uint widthOfLengths = 0;
    uint NL = 0;
    uint widthOfSPD = 0;
    uint SPD[orderOfSPD+1];
    uint totalWidth = 0;
    uint totalLength = 0;
    uint groupLength[numberOfGroups];
    uint groupValue[numberOfGroups];
    uint valueSize[numberOfGroups];

    double *dataValues = new double[numOfValues];
    std::unique_ptr<double> dataValues_delete(dataValues);

    BitArrayReader bitArrayReader(data,dataSize*8);

    bitArrayReader.readBits(8,widthOfWidths);
    bitArrayReader.readBits(8,widthOfLengths);
    bitArrayReader.readBits(16,NL);
    bitArrayReader.readBits(8,widthOfSPD);

    NL = NL + 65536 * mExtraValues;

    for (uint t=0; t<=orderOfSPD; t++)
    {
      bitArrayReader.readBits(widthOfSPD,SPD[t]);
    }

    double bias = SPD[orderOfSPD];
    uint max = 1 << (widthOfSPD-1);
    if (SPD[orderOfSPD] > max)
      bias = -(C_DOUBLE(SPD[orderOfSPD]) - C_DOUBLE(max));

    try
    {
      uint w = 1+((orderOfSPD+1)*widthOfSPD+7)/8;

      bitArrayReader.setReadPosition((4+w)*8);

      for (uint g=0; g<numberOfGroups; g++)
      {
        bitArrayReader.readBits(widthOfWidths,valueSize[g]);
        totalWidth += valueSize[g];
      }
    }
    catch (...)
    {
      throw Fmi::Exception(BCP,"Reading group value widths failed!",nullptr);
    }


    try
    {
      bitArrayReader.setReadPosition((NL-22)*8);
      for (uint g=0; g<numberOfGroups; g++)
      {
        bitArrayReader.readBits(widthOfLengths,groupLength[g]);
        totalLength += groupLength[g];
      }
    }
    catch (...)
    {
      throw Fmi::Exception(BCP,"Reading group lengths failed!",nullptr);
    }


    if (totalLength > numOfValues)
    {
      throw Fmi::Exception(BCP,"Total length is bigger than number of the values!");
    }

    try
    {
      uint dd = (bitArrayReader.getReadPosition()/8) % 65536;
      N1 = mN1 + ((bitArrayReader.getReadPosition()/8)-dd);

      bitArrayReader.setReadPosition((N1-22)*8);
      for (uint g=0; g<numberOfGroups; g++)
      {
        bitArrayReader.readBits(bitsPerValue,groupValue[g]);
      }
    }
    catch (...)
    {
      throw Fmi::Exception(BCP,"Reading group values failed!",nullptr);
    }

    try
    {
      uint dd = (bitArrayReader.getReadPosition()/8) % 65536;
      N2 = mN2 + ((bitArrayReader.getReadPosition()/8)-dd);

      uint c = orderOfSPD;
      bitArrayReader.setReadPosition((N2-22)*8);

      for (uint g=0; g<numberOfGroups; g++)
      {
        if (valueSize[g] > 0)
        {
          for (uint t=0; t<groupLength[g]; t++)
          {
            uint val = 0;
            bitArrayReader.readBits(valueSize[g],val);
            val += groupValue[g];
            dataValues[c] = val;
            c++;
          }
        }
        else
        {
          for (uint t=0; t<groupLength[g]; t++)
          {
            dataValues[c] = groupValue[g];
            c++;
          }
        }
      }
    }
    catch (...)
    {
      throw Fmi::Exception(BCP,"Reading second order values failed!",nullptr);
    }


    for (uint i=0; i<orderOfSPD; i++)
    {
      dataValues[i] = SPD[i];
    }

    switch (orderOfSPD)
    {
      case 1:
      {
        for (uint n=1; n<numOfValues; n++)
        {
          dataValues[n] = dataValues[n] + bias;
          dataValues[n] = dataValues[n] + dataValues[n-1];
        }
      }
      break;

      case 2:
      {
        for (uint n=2; n<numOfValues; n++)
        {
          dataValues[n] = dataValues[n] + bias;
          dataValues[n] = dataValues[n] + (2 * dataValues[n-1]) - dataValues[n-2];
        }
      }
      break;

      case 3:
      {
        double y = dataValues[2] - dataValues[1];
        double z = y-(dataValues[1]-dataValues[0]);
        double w = dataValues[2];
        for (uint n=3; n<numOfValues; n++)
        {
          z += dataValues[n] + bias;
          y += z;
          w += y;
          dataValues[n] = w;
        }
      }
      break;
    }

    double s = grib_power(binaryScaleFactor,2);
    double d = grib_power(-decimalScaleFactor,10);

    for (uint t=0; t<numOfValues; t++)
    {
      dataValues[t] = (((dataValues[t]*s)+referenceValue)*d);
    }

    if (mExtendedFlags & BoustrophedonicOrdering)
    {
      uint nx = dimensions.nx();
      uint inc = nx;
      uint count = nx;

      while (count < numOfValues)
      {
        uint left = 0;
        uint right = nx-1;
        for (uint i=0; i<nx/2; i++)
        {
          double tmp = dataValues[count+left];
          dataValues[count+left] = dataValues[count+right];
          dataValues[count+right] = tmp;

          right--;
          left++;
        }
        inc = nx*2;
        count += inc;
      }
    }

    for (uint t=0; t<numOfValues; t++)
    {
      decodedValues.push_back(dataValues[t]);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void SecondOrderPacking::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SecondOrderPacking\n";
    stream << space(level) << "- N1            = " << toString(mN1) << " (octet number at which first-order packed data begin)\n";
    stream << space(level) << "- extendedFlags = " << toString(mExtendedFlags) << "\n";

    if (mExtendedFlags & MatrixOfValues)
      stream << space(level) << "  * Matrix of values at each grid point\n";
    else
      stream << space(level) << "  * Single datum at each grid point\n";

    if (mExtendedFlags & SecondaryBitmapsPresent)
      stream << space(level) << "  * Secondary bit map present\n";
    else
      stream << space(level) << "  * No secondary bit map present\n";

    if (mExtendedFlags & DifferentValueWidths)
      stream << space(level) << "  * Second order values have different widths\n";
    else
      stream << space(level) << "  * Second order values have constant width\n";

    if (mExtendedFlags & GeneralExtendedPacking)
      stream << space(level) << "  * General extended second order packing used\n";
    else
      stream << space(level) << "  * No general extended second order packing\n";

    if (mExtendedFlags & BoustrophedonicOrdering)
      stream << space(level) << "  * Boustrophedonic ordering in section 4\n";
    else
      stream << space(level) << "  * Standard field ordering in section 4\n";

    if ((mExtendedFlags & 3) == 0)
      stream << space(level) << "  * No spatial differencing used\n";

    if ((mExtendedFlags & 3) == 1)
      stream << space(level) << "  * 1st order spatial differencing used\n";

    if ((mExtendedFlags & 3) == 2)
      stream << space(level) << "  * 2nd order spatial differencing used\n";

    if ((mExtendedFlags & 3) == 3)
      stream << space(level) << "  * 3rd order spatial differencing used\n";

    stream << space(level) << "- N2            = " << toString(mN2) << " (octet number at which second-order packed data begin)\n";
    stream << space(level) << "- P1            = " << toString(mP1) << " (number of first-order packed values)\n";
    stream << space(level) << "- P2            = " << toString(mP2) << " (number of second-order packed values)\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet

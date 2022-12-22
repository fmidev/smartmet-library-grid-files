#include "ComplexDifferenceGridDataRepresentationImpl.h"
#include "../Message.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/BitArrayReader.h"

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

ComplexDifferenceGridDataRepresentationImpl::ComplexDifferenceGridDataRepresentationImpl()
{
}





/*! \brief The copy constructor of the class. */

ComplexDifferenceGridDataRepresentationImpl::ComplexDifferenceGridDataRepresentationImpl(const ComplexDifferenceGridDataRepresentationImpl& other)
:ComplexDifferenceGridDataRepresentation(other)
{
}





/*! \brief The destructor of the class. */

ComplexDifferenceGridDataRepresentationImpl::~ComplexDifferenceGridDataRepresentationImpl()
{
}





/*! \brief The method creates a duplicate of the current object. */

RepresentationDefinition* ComplexDifferenceGridDataRepresentationImpl::createRepresentationDefinition() const
{
  try
  {
    return (RepresentationDefinition*) new ComplexDifferenceGridDataRepresentationImpl(*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current object.
    The purpose of this method is to get access to the read operation that takes place
    in the parent class (which is automatically generated). This means in practice that
    we first call the read operation in the parent class. After that we can ensure that
    the result of the read operation was correct (i.e. attribute values are valid, etc).
    We can also modify or update some attribute values if needed.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ComplexDifferenceGridDataRepresentationImpl::read(MemoryReader& memoryReader)
{
  try
  {
    ComplexDifferenceGridDataRepresentation::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ComplexDifferenceGridDataRepresentationImpl::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    //std::size_t bitmapSizeInBytes = message->getBitmapDataSizeInBytes();

    //if (data == nullptr)
      //throw Fmi::Exception(BCP,"The 'data' pointer points to nullptr!");

    decodedValues.clear();
    decodedValues.reserve(numOfValues);

    std::size_t numberOfValues = numOfValues;
    T::ParamValue ref = mPacking.getReferenceValue();
    T::ParamValue bscale = int_power(2.0,C_INT(*mPacking.getBinaryScaleFactor()));
    T::ParamValue dscale = int_power(10.0,-C_INT(*mPacking.getDecimalScaleFactor()));
    int groupRefBits = *mPacking.getBitsPerValue();
    int numberOfGroups = *mNumberOfGroupsOfDataValues;
    int groupValueSizeBits = *mNumberOfBitsUsedForTheGroupWidths;
    int groupSizeBits = *mNumberOfBitsForScaledGroupLengths;
    int readPosition = 0;
    int extraDescrBits = *mNumberOfOctetsExtraDescriptors * 8;
    int non = 0;

    if (numberOfGroups == 0 || data == nullptr)
    {
      // The number of groups is zero, so all values are set to 'ref'.

      for (std::size_t i=0; i<numberOfValues; i++)
         decodedValues.emplace_back(ref);

       return;
    }


    // Allocating some memory and making sure that it will be released.

    T::ParamValue *value = new T::ParamValue[numOfValues];
    std::unique_ptr<T::ParamValue[]> value_delete(value);

    int *dataValue = new int[numberOfValues];
    std::unique_ptr<int[]> dataValue_delete(dataValue);

    int *groupReference = new int[numberOfGroups];
    std::unique_ptr<int[]> groupReference_delete(groupReference);

    int *groupValueSize = new int[numberOfGroups];
    std::unique_ptr<int[]> groupValueSize_delete(groupValueSize);

    int  *groupSize = new int[numberOfGroups];
    std::unique_ptr<int[]> groupSize_delete(groupSize);

    int *missingDataValue = new int[numberOfValues];
    std::unique_ptr<int[]> missingDataValue_delete(missingDataValue);
/*

   // ### When a value is missing, should we use our own "ParamValueMissing" or
   // ### "mPrimaryMissingValueSubstitute" and "mSecondaryMissingValueSubstitute"
   // ### values? If the value is "really missing" then we probably should
   // ### use "ParamValueMissing".

    T::ParamValue missingValue1 = 0;
    T::ParamValue missingValue2 = 0;

    if (*mMissingValueManagementUsed == 1)
      missingValue1 = *mPrimaryMissingValueSubstitute;

    if (*mMissingValueManagementUsed == 2)
    {
      missingValue1 = *mPrimaryMissingValueSubstitute;
      missingValue2 = *mSecondaryMissingValueSubstitute;
    }
*/

    BitArrayReader dataReader(data,dataSize*8);

    //  ### Finding out spatial differencing values.

    int ival1 = 0;
    int ival2 = 0;
    int isign = 0;
    int minSpaticalDifference = 0;

    if (extraDescrBits != 0)
    {
      dataReader.readBits(extraDescrBits,ival1);
      readPosition = readPosition + extraDescrBits;

      if (*mOrderOfSpatialDifferencing == 2)
      {
        dataReader.readBits(extraDescrBits,ival2);
        readPosition=readPosition+extraDescrBits;
      }
      dataReader.readBits(1,isign);
      readPosition = readPosition + 1;
      dataReader.readBits(extraDescrBits-1,minSpaticalDifference);
      readPosition = readPosition + extraDescrBits - 1;
      if (isign == 1)
        minSpaticalDifference = -minSpaticalDifference;
    }
    else
    {
      ival1 = 0;
      ival2 = 0;
      minSpaticalDifference = 0;
    }


    // ### Finding out the reference data values used in the groups. These reference
    // ### values are added to the actual values read from the group.

    if (groupRefBits == 0)
    {
      for (int g=0; g<numberOfGroups; g++)
        groupReference[g] = 0;
    }
    else
    {
      dataReader.setReadPosition(readPosition);
      dataReader.readBits(groupRefBits,groupReference,numberOfGroups);

      int itemp = groupRefBits * numberOfGroups;
      readPosition = readPosition + itemp;
      if ((itemp % 8) != 0)
        readPosition = readPosition + (8-(itemp % 8));
    }


    //  ### Finding out the number of bits used for defining values in each group.

    if (groupValueSizeBits == 0)
    {
      for (int g=0; g<numberOfGroups; g++)
        groupValueSize[g] = 0;
    }
    else
    {
      dataReader.setReadPosition(readPosition);
      dataReader.readBits(groupValueSizeBits,groupValueSize,numberOfGroups);

      int itemp = groupValueSizeBits * numberOfGroups;
      readPosition = readPosition + itemp;
      if ((itemp % 8) != 0)
        readPosition = readPosition + (8-(itemp % 8));
    }

    for (int g=0; g<numberOfGroups; g++)
      groupValueSize[g] = groupValueSize[g] + *mReferenceForGroupWidths;



    // ### Finding out the number of actual values in each group.

    if (groupSizeBits == 0)
    {
      for (int g=0; g<numberOfGroups; g++)
        groupSize[g] = 0;
    }
    else
    {
      dataReader.setReadPosition(readPosition);
      dataReader.readBits(groupSizeBits,groupSize,numberOfGroups);
      int itemp = groupSizeBits * numberOfGroups;
      readPosition = readPosition + itemp;
      if ((itemp % 8) != 0)
        readPosition = readPosition + (8-(itemp % 8));
    }

    for (int g=0; g<numberOfGroups; g++)
      groupSize[g] = (groupSize[g] * (*mLengthIncrementForTheGroupLengths)) + *mReferenceForGroupLengths;


    groupSize[numberOfGroups-1] = *mTrueLengthOfLastGroup;



    // ### Unpacking the data values from the groups.

    if (*mMissingValueManagementUsed == 0)
    {
      int n = 0;
      for (int g=0; g<numberOfGroups; g++)
      {
        if (groupValueSize[g] != 0)
        {
          dataReader.setReadPosition(readPosition);
          for (int k=0; k<groupSize[g]; k++)
          {
            dataReader.readBits(groupValueSize[g],dataValue[n]);
            // The group reference value is added to the actual value.

            dataValue[n] = dataValue[n] + groupReference[g];
            n++;
          }
        }
        else
        {
          // The value size in the group is 0 bits, so the value of the each
          // is the same as the value of the group reference.

          int lEnd = n+groupSize[g];
          for (int l=n; l<lEnd; l++)
            dataValue[l] = groupReference[g];

          n = n + groupSize[g];
        }
        readPosition = readPosition + (groupValueSize[g] * groupSize[g]);
      }
    }
    else
    if (*mMissingValueManagementUsed == 1 || *mMissingValueManagementUsed == 2)
    {
      for (std::size_t i=0; i<numberOfValues; i++)
        missingDataValue[i] = 0;

      int n=0;
      for (int g=0; g<numberOfGroups; g++)
      {
        if (groupValueSize[g] != 0)
        {
          // The following values are used for indicating that the actual value is missing.

          int missingValueIndicator1 = C_INT(int_power(2.0,groupValueSize[g])-1);
          int missingValueIndicator2 = missingValueIndicator1-1;

          dataReader.setReadPosition(readPosition);

          for (int k=0; k<groupSize[g]; k++)
          {
            dataReader.readBits(groupValueSize[g],dataValue[n]);

            if (dataValue[n] == missingValueIndicator1)
            {
               missingDataValue[n] = 1;
            }
            else
            if (*mMissingValueManagementUsed == 2 && dataValue[n] == missingValueIndicator2)
            {
               missingDataValue[n] = 2;
            }
            else
            {
               missingDataValue[n] = 0;
               dataValue[non++] = dataValue[n] + groupReference[g];
            }
            n++;
          }
          readPosition = readPosition + (groupValueSize[g] * groupSize[g]);
        }
        else
        {
          // The following values are used for indicating that the actual value is missing.

          int missingValueIndicator1 = C_INT(int_power(2.0,groupRefBits)-1);
          int missingValueIndicator2 = missingValueIndicator1 - 1;

          if (groupReference[g] == missingValueIndicator1)
          {
            int lEnd = n + groupSize[g];
            for (int l=n; l<lEnd; l++)
              missingDataValue[l] = 1;
          }
          else
          if (*mMissingValueManagementUsed == 2 && groupReference[g] == missingValueIndicator2)
          {
            int lEnd = n + groupSize[g];
            for (int l=n; l<lEnd; l++)
              missingDataValue[l] = 2;
          }
          else
          {
            int lEnd = n + groupSize[g];
            for (int l=n; l<lEnd; l++)
              missingDataValue[l] = 0;

            lEnd = non + groupSize[g];
            for (int l=non; l<lEnd; l++)
              dataValue[l] = groupReference[g];

            non += groupSize[g];
          }
          n = n + groupSize[g];
        }
      }
    }


    //  ### Spatial differences: add overall min value, and sum up recursively.

    if (*mOrderOfSpatialDifferencing == 1)
    {
      std::size_t itemp = 0;
      dataValue[0] = ival1;
      if (*mMissingValueManagementUsed == 0)
        itemp = numberOfValues;        // no missing values
      else
        itemp = non;

      for (std::size_t n=1; n<itemp; n++)
      {
        dataValue[n] = dataValue[n] + minSpaticalDifference;
        dataValue[n] = dataValue[n] + dataValue[n-1];
      }
    }
    else
    if (*mOrderOfSpatialDifferencing == 2)
    {
      std::size_t itemp = 0;
      dataValue[0] = ival1;
      dataValue[1] = ival2;
      if (*mMissingValueManagementUsed == 0)
        itemp = numberOfValues;        // no missing values
      else
        itemp = non;

      for (std::size_t n=2; n<itemp; n++)
      {
        dataValue[n] = dataValue[n] + minSpaticalDifference;
        dataValue[n] = dataValue[n] + (2 * dataValue[n-1]) - dataValue[n-2];
      }
    }

    //  ### Scaling values.

    if (*mMissingValueManagementUsed == 0 )
    {
      for (std::size_t i=0; i<numberOfValues; i++)
      {
        value[i] = (((float)dataValue[i] * bscale) + ref) * dscale;
      }
    }
    else
    if (*mMissingValueManagementUsed == 1 || *mMissingValueManagementUsed == 2)
    {
      std::size_t n=0;
      for (std::size_t i=0; i<numberOfValues; i++)
      {
        if (missingDataValue[i] == 0)
          value[i] = (((float)dataValue[n++] * bscale) + ref) * dscale;
        else
        if (missingDataValue[i] == 1)
           value[i] = ParamValueMissing; // missingValue1;
        else
        if (missingDataValue[i] == 2)
          value[i] = ParamValueMissing; // missingValue2;
      }
    }


    // ### Returning values.

    if (bitmap == nullptr)
    {
      // No bitmap defined.

      for (std::size_t n=0; n<numberOfValues; n++)
        decodedValues.emplace_back(value[n]);

      return;
    }
    else
    {
      // Bitmap defined.

      const int bitmask[] = {128, 64, 32, 16, 8, 4, 2, 1};

      std::size_t n = 0;
      for (std::size_t i = 0; i < numberOfValues; i++)
      {
        if ((bitmap[i / 8] & bitmask[i % 8]) == 0)
        {
          decodedValues.emplace_back(ParamValueMissing);
        }
        else
        {
          decodedValues.emplace_back(value[n]);
          n++;
        }
      }
      return;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}

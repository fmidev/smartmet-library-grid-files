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

ComplexDifferenceGridDataRepresentationImpl::ComplexDifferenceGridDataRepresentationImpl() = default;





/*! \brief The copy constructor of the class. */

ComplexDifferenceGridDataRepresentationImpl::ComplexDifferenceGridDataRepresentationImpl(const ComplexDifferenceGridDataRepresentationImpl& other) = default;





/*! \brief The destructor of the class. */

ComplexDifferenceGridDataRepresentationImpl::~ComplexDifferenceGridDataRepresentationImpl() = default;





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





namespace
{

/*! \brief Reads one group descriptor value of each group (or sets them to zero when the
    descriptor width is zero) and returns the byte-aligned read position after them. */

int readGroupDescriptors(BitArrayReader& dataReader,int bits,int *values,int numberOfGroups,int readPosition)
{
  if (bits == 0)
  {
    for (int g=0; g<numberOfGroups; g++)
      values[g] = 0;
    return readPosition;
  }

  dataReader.setReadPosition(readPosition);
  dataReader.readBits(bits,values,numberOfGroups);

  int itemp = bits * numberOfGroups;
  readPosition = readPosition + itemp;
  if ((itemp % 8) != 0)
    readPosition = readPosition + (8-(itemp % 8));
  return readPosition;
}





/*! \brief Validates the (attacker-controllable) group descriptors before unpacking.

    The unpack loops write dataValue[n] / missingDataValue[n] with n running over the
    cumulative sum of the group sizes. Both arrays are only 'numberOfValues' long, so a
    crafted GRIB2 message whose group sizes sum to more than numberOfValues would cause a
    heap buffer overflow. Enforce the GRIB2 invariant that the group lengths sum exactly to
    the declared value count, and that the per-group bit widths are sane. */

void validateGroups(const int *groupSize,const int *groupValueSize,int numberOfGroups,std::size_t numberOfValues)
{
  std::size_t totalGroupValues = 0;
  for (int g=0; g<numberOfGroups; g++)
  {
    if (groupSize[g] < 0)
      throw Fmi::Exception(BCP,"Invalid GRIB2 complex-packing group size (negative)!");

    if (groupValueSize[g] < 0 || groupValueSize[g] > 32)
      throw Fmi::Exception(BCP,"Invalid GRIB2 complex-packing group value width!");

    totalGroupValues += static_cast<std::size_t>(groupSize[g]);
  }

  if (totalGroupValues != numberOfValues)
    throw Fmi::Exception(BCP,"GRIB2 complex-packing group sizes do not sum to the expected value count!");
}





/*! \brief Unpacks the data values of all groups when there are no missing values. */

void unpackGroups(BitArrayReader& dataReader,int readPosition,int numberOfGroups,const int *groupValueSize,const int *groupSize,const int *groupReference,int *dataValue)
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





/*! \brief Unpacks the values of a group with a non-zero value width, marking the missing values.
    The non-missing values are packed to the beginning of dataValue (index c). */

void unpackGroupWithMissing(BitArrayReader& dataReader,int readPosition,int valueSize,int size,int reference,int missingValueManagementUsed,int *dataValue,int *missingDataValue,int& n,int& c)
{
  // The following values are used for indicating that the actual value is missing.

  int missingValueIndicator1 = C_INT(int_power(2.0,valueSize)-1);
  int missingValueIndicator2 = missingValueIndicator1-1;

  dataReader.setReadPosition(readPosition);

  for (int k=0; k<size; k++)
  {
    // codechecker_false_positive [security.ArrayBound] the group sizes have been validated to sum to numberOfValues
    dataReader.readBits(valueSize,dataValue[n]);

    if (dataValue[n] == missingValueIndicator1)
    {
       missingDataValue[n] = 1;
    }
    else if (missingValueManagementUsed == 2 && dataValue[n] == missingValueIndicator2)
    {
       missingDataValue[n] = 2;
    }
    else
    {
       missingDataValue[n] = 0;
       dataValue[c++] = dataValue[n] + reference;
    }
    n++;
  }
}





/*! \brief Sets the values of a group with a zero value width, marking the missing values.
    The non-missing values are packed to the beginning of dataValue (index c). */

void fillGroupWithMissing(int groupRefBits,int size,int reference,int missingValueManagementUsed,int *dataValue,int *missingDataValue,int& n,int& c)
{
  // The following values are used for indicating that the actual value is missing.

  int missingValueIndicator1 = C_INT(int_power(2.0,groupRefBits)-1);
  int missingValueIndicator2 = missingValueIndicator1 - 1;

  if (reference == missingValueIndicator1)
  {
    int lEnd = n + size;
    for (int l=n; l<lEnd; l++)
      // codechecker_false_positive [security.ArrayBound] the group sizes have been validated to sum to numberOfValues
      missingDataValue[l] = 1;
  }
  else if (missingValueManagementUsed == 2 && reference == missingValueIndicator2)
  {
    int lEnd = n + size;
    for (int l=n; l<lEnd; l++)
      // codechecker_false_positive [security.ArrayBound] the group sizes have been validated to sum to numberOfValues
      missingDataValue[l] = 2;
  }
  else
  {
    int lEnd = n + size;
    for (int l=n; l<lEnd; l++)
      // codechecker_false_positive [security.ArrayBound] the group sizes have been validated to sum to numberOfValues
      missingDataValue[l] = 0;

    lEnd = c + size;
    for (int l=c; l<lEnd; l++)
      dataValue[l] = reference;

    c += size;
  }
  n = n + size;
}





/*! \brief Unpacks the data values of all groups when missing value management is used.
    Returns the number of non-missing values, which are packed to the beginning of dataValue. */

int unpackGroupsWithMissing(BitArrayReader& dataReader,int readPosition,int numberOfGroups,const int *groupValueSize,const int *groupSize,const int *groupReference,int groupRefBits,int missingValueManagementUsed,std::size_t numberOfValues,int *dataValue,int *missingDataValue)
{
  for (std::size_t i=0; i<numberOfValues; i++)
    missingDataValue[i] = 0;

  int n=0;
  int c = 0;
  for (int g=0; g<numberOfGroups; g++)
  {
    if (groupValueSize[g] != 0)
    {
      unpackGroupWithMissing(dataReader,readPosition,groupValueSize[g],groupSize[g],groupReference[g],missingValueManagementUsed,dataValue,missingDataValue,n,c);
      readPosition = readPosition + (groupValueSize[g] * groupSize[g]);
    }
    else
    {
      fillGroupWithMissing(groupRefBits,groupSize[g],groupReference[g],missingValueManagementUsed,dataValue,missingDataValue,n,c);
    }
  }
  return c;
}





/*! \brief Scales the unpacked data values into physical values. */

void scaleValues(int missingValueManagementUsed,std::size_t numberOfValues,const int *dataValue,const int *missingDataValue,T::ParamValue bscale,T::ParamValue ref,T::ParamValue dscale,T::ParamValue *value)
{
  if (missingValueManagementUsed == 0 )
  {
    for (std::size_t i=0; i<numberOfValues; i++)
    {
      value[i] = (((float)dataValue[i] * bscale) + ref) * dscale;
    }
  }
  else if (missingValueManagementUsed == 1 || missingValueManagementUsed == 2)
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
}





/*! \brief Returns the values, inserting ParamValueMissing where the bitmap bit is not set. */

void storeValues(const T::ParamValue *value,std::size_t numberOfValues,T::Data_ptr bitmap,std::size_t bitmapSizeInBytes,T::ParamValue_vec& decodedValues)
{
  if (bitmap == nullptr)
  {
    // No bitmap defined.

    for (std::size_t n=0; n<numberOfValues; n++)
      decodedValues.emplace_back(value[n]);

    return;
  }
  // Bitmap defined.

  const int bitmask[] = {128, 64, 32, 16, 8, 4, 2, 1};

  std::size_t n = 0;
  for (std::size_t i = 0; i < numberOfValues; i++)
  {
    // Guard against a bitmap that is shorter than the grid implies (OOB read).
    if ((i / 8) >= bitmapSizeInBytes)
      throw Fmi::Exception(BCP,"GRIB2 bitmap is too short for the declared value count!");

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
}

/*! \brief Reads the spatial differencing descriptors (the first values and the overall minimum)
    and returns the read position after them. */

int readSpatialDifferencingDescriptors(BitArrayReader& dataReader,int extraDescrBits,int orderOfSpatialDifferencing,int readPosition,int& ival1,int& ival2,int& minSpaticalDifference)
{
  int isign = 0;

  if (extraDescrBits != 0)
  {
    dataReader.readBits(extraDescrBits,ival1);
    readPosition = readPosition + extraDescrBits;

    if (orderOfSpatialDifferencing == 2)
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
  return readPosition;
}





/*! \brief Spatial differences: adds the overall min value and sums up recursively. */

void undoSpatialDifferencing(int orderOfSpatialDifferencing,int missingValueManagementUsed,std::size_t numberOfValues,int non,int ival1,int ival2,int minSpaticalDifference,int *dataValue)
{
  if (orderOfSpatialDifferencing == 1)
  {
    std::size_t itemp = 0;
    if (numberOfValues >= 1)
      dataValue[0] = ival1;
    if (missingValueManagementUsed == 0)
      itemp = numberOfValues;        // no missing values
    else
      itemp = non;

    for (std::size_t n=1; n<itemp; n++)
    {
      dataValue[n] = dataValue[n] + minSpaticalDifference;
      dataValue[n] = dataValue[n] + dataValue[n-1];
    }
  }
  else if (orderOfSpatialDifferencing == 2)
  {
    std::size_t itemp = 0;
    if (numberOfValues >= 1)
      dataValue[0] = ival1;
    if (numberOfValues >= 2)
      dataValue[1] = ival2;
    if (missingValueManagementUsed == 0)
      itemp = numberOfValues;        // no missing values
    else
      itemp = non;

    for (std::size_t n=2; n<itemp; n++)
    {
      dataValue[n] = dataValue[n] + minSpaticalDifference;
      dataValue[n] = dataValue[n] + (2 * dataValue[n-1]) - dataValue[n-2];
    }
  }
}

}  // namespace





/*! \brief Decodes the complex-difference packed grid values into a vector of parameter values. */

void ComplexDifferenceGridDataRepresentationImpl::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    std::size_t bitmapSizeInBytes = message->getBitmapDataSizeInBytes();

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

    if (numberOfGroups <= 0 || data == nullptr)
    {
      // The number of groups is zero (or invalid), so all values are set to 'ref'.

      for (std::size_t i=0; i<numberOfValues; i++)
         decodedValues.emplace_back(ref);

       return;
    }


    // Allocating some memory and making sure that it will be released.

    auto *value = new T::ParamValue[numOfValues]();
    std::unique_ptr<T::ParamValue[]> value_delete(value);

    int *dataValue = new int[numberOfValues]();
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
    int minSpaticalDifference = 0;

    readPosition = readSpatialDifferencingDescriptors(dataReader,extraDescrBits,*mOrderOfSpatialDifferencing,readPosition,ival1,ival2,minSpaticalDifference);


    // ### Finding out the reference data values used in the groups. These reference
    // ### values are added to the actual values read from the group.

    readPosition = readGroupDescriptors(dataReader,groupRefBits,groupReference,numberOfGroups,readPosition);


    //  ### Finding out the number of bits used for defining values in each group.

    readPosition = readGroupDescriptors(dataReader,groupValueSizeBits,groupValueSize,numberOfGroups,readPosition);

    for (int g=0; g<numberOfGroups; g++)
      groupValueSize[g] = groupValueSize[g] + *mReferenceForGroupWidths;



    // ### Finding out the number of actual values in each group.

    readPosition = readGroupDescriptors(dataReader,groupSizeBits,groupSize,numberOfGroups,readPosition);

    for (int g=0; g<numberOfGroups; g++)
      groupSize[g] = (groupSize[g] * (*mLengthIncrementForTheGroupLengths)) + *mReferenceForGroupLengths;


    groupSize[numberOfGroups-1] = *mTrueLengthOfLastGroup;


    // ### Validating the (attacker-controllable) group descriptors before unpacking.

    validateGroups(groupSize,groupValueSize,numberOfGroups,numberOfValues);



    // ### Unpacking the data values from the groups.

    if (*mMissingValueManagementUsed == 0)
    {
      unpackGroups(dataReader,readPosition,numberOfGroups,groupValueSize,groupSize,groupReference,dataValue);
    }
    else if (*mMissingValueManagementUsed == 1 || *mMissingValueManagementUsed == 2)
    {
      non = unpackGroupsWithMissing(dataReader,readPosition,numberOfGroups,groupValueSize,groupSize,groupReference,
          groupRefBits,*mMissingValueManagementUsed,numberOfValues,dataValue,missingDataValue);
    }


    //  ### Spatial differences: add overall min value, and sum up recursively.

    undoSpatialDifferencing(*mOrderOfSpatialDifferencing,*mMissingValueManagementUsed,numberOfValues,non,ival1,ival2,minSpaticalDifference,dataValue);

    //  ### Scaling values.

    scaleValues(*mMissingValueManagementUsed,numberOfValues,dataValue,missingDataValue,bscale,ref,dscale,value);


    // ### Returning values.

    storeValues(value,numberOfValues,bitmap,bitmapSizeInBytes,decodedValues);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}

#include "BitArrayReader.h"
#include "Exception.h"


namespace SmartMet
{


/*! \brief The constructor of the class. */

BitArrayReader::BitArrayReader(const unsigned char *data,unsigned long long numberOfBits)
{
  try
  {
    if (data == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'data' parameter points to NULL!");

    mData = data;
    mNumberOfBits = numberOfBits;
    mReadPosition = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

BitArrayReader::~BitArrayReader()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




/*! \brief The method returns the size of the bit array/stream counted in bits. */

unsigned long long BitArrayReader::getNumberOfBits()
{
  try
  {
    return mNumberOfBits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the current read position of the bit array/stream.
    The position is counted in bits from the beginning of the bit array/stream.
*/

unsigned long long BitArrayReader::getReadPosition()
{
  try
  {
    return mReadPosition;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method sets the current read position of the bit array/stream.
    The position is counted in bits from the beginning of the bit array/stream.
*/

void BitArrayReader::setReadPosition(unsigned long long _readPosition)
{
  try
  {
    if (_readPosition >= mNumberOfBits)
    {
      SmartMet::Spine::Exception exception(BCP,"The '_readPosition' parameter is out the range!");
      exception.addParameter("Requested read position",std::to_string(_readPosition));
      exception.addParameter("Number of bits",std::to_string(mNumberOfBits));
      throw exception;
    }

    mReadPosition = _readPosition;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method reads a bit from the bit array/stream and return 'true' if
    the bit is '1' and false if the bit is '0'. The method automatically increases
    the current read position. The method throws an exception if the bit cannot be read.
    This is the case if the current read position has reached the end of the bit array/stream.
*/

bool BitArrayReader::readBit()
{
  try
  {
    if ((mReadPosition + 1) > mNumberOfBits)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot read a bit outside of the memory area !");
      exception.addParameter("Read position",std::to_string(mReadPosition));
      exception.addParameter("Number of bits",std::to_string(mNumberOfBits));
      throw exception;
    }

    unsigned long long byt = mReadPosition / 8;
    unsigned long long bit = 7 - (mReadPosition % 8);

    mReadPosition++;

    if ((1 << bit) & mData[byt])
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method reads a bit from the bit array/stream and return 'true' if
    the bit is '1' and false if the bit is '0'. The method automatically increases
    the current read position. The method does not check if the read position
    has reached the end of the bit array/stream. This means that the caller
    should ensure beforehand that the read is possible. This method is typically
    used when a caller wants to go through the whole bitmap in a loop. In this
    case the caller first checks that the size of the bitmap is big enough and
    a bit can be read in each loop cycle. After, there is not need to check
    the same thing in every read operation, which makes the implementation faster.
*/

bool BitArrayReader::readBitNoCheck()
{
  try
  {
    unsigned long long byt = mReadPosition / 8;
    unsigned long long bit = 7 - (mReadPosition % 8);

    mReadPosition++;

    if ((1 << bit) & mData[byt])
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method reads a number of bits from the bit array/stream and
    returns the result in the 'value' parameter.

        \param numberOfBits   The number of bits to read.
        \param value          The result value of the read bits.
*/

void BitArrayReader::readBits(unsigned int numberOfBits,int& value)
{
  try
  {
    if (numberOfBits > 32)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot read more than 32 bits into 'int'!");
      exception.addParameter("Requested bits",std::to_string(numberOfBits));
      throw exception;
    }

    if ((mReadPosition + numberOfBits) > mNumberOfBits)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot read bits outside of the memory area!");
      exception.addParameter("Read position",std::to_string(mReadPosition));
      exception.addParameter("Number of bits",std::to_string(mNumberOfBits));
      exception.addParameter("Requested bits",std::to_string(numberOfBits));
      throw exception;
    }

    value = 0;
    for (unsigned int i=0; i<numberOfBits; i++)
    {
      value = value << 1;

      if (readBitNoCheck())
        value = value + 1;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method reads a number of bits from the bit array/stream and
    returns the result in the 'value' parameter.

        \param numberOfBits   The number of bits to read.
        \param value          The result value of the read bits.
*/

void BitArrayReader::readBits(unsigned int numberOfBits,unsigned int& value)
{
  try
  {
    if (numberOfBits > 32)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot read more than 32 bits into 'unsigned int'!");
      exception.addParameter("Requested bits",std::to_string(numberOfBits));
      throw exception;
    }

    if ((mReadPosition + numberOfBits) > mNumberOfBits)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot read bits outside of the memory area !");
      exception.addParameter("Read position",std::to_string(mReadPosition));
      exception.addParameter("Number of bits",std::to_string(mNumberOfBits));
      exception.addParameter("Requested bits",std::to_string(numberOfBits));
      throw exception;
    }

    value = 0;
    for (unsigned int i=0; i<numberOfBits; i++)
    {
      value = value << 1;

      if (readBitNoCheck())
        value = value + 1;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method reads a number of bits from the bit array/stream and
    returns the result in the 'value' parameter.

        \param numberOfBits   The number of bits to read.
        \param value          The result value of the read bits.
*/

void BitArrayReader::readBits(unsigned int numberOfBits,unsigned long long& value)
{
  try
  {
    if (numberOfBits > 64)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot read more than 64 bits into 'unsigned long long'!");
      exception.addParameter("Requested bits",std::to_string(numberOfBits));
      throw exception;
    }

    if ((mReadPosition + numberOfBits) > mNumberOfBits)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot read bits outside of the memory area !");
      exception.addParameter("Read position",std::to_string(mReadPosition));
      exception.addParameter("Number of bits",std::to_string(mNumberOfBits));
      exception.addParameter("Requested bits",std::to_string(numberOfBits));
      throw exception;
    }

    value = 0;
    for (unsigned int i=0; i<numberOfBits; i++)
    {
      value = value << 1;

      if (readBitNoCheck())
        value = value + 1;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method reads an array of numbers from the bit array/stream. The length of
    the each number in the array is 'numberOfBits".

        \param numberOfBits   The number of bits per array element.
        \param array          The pointer to the returned array elements.
        \param arraySize      The number of elements in the array.
*/

void BitArrayReader::readBits(unsigned int numberOfBits,int *array,unsigned int arraySize)
{
  try
  {
    for (unsigned int t=0; t<arraySize; t++)
    {
      readBits(numberOfBits,array[t]);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}

#include "BitArrayWriter.h"

namespace SmartMet
{



BitArrayWriter::BitArrayWriter(unsigned char *data,ulonglong numberOfBits)
{
  try
  {
    if (data == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'data' parameter points to nullptr!");

    mData = data;
    mNumberOfBits = numberOfBits;
    mWritePosition = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




BitArrayWriter::~BitArrayWriter()
{
  try
  {
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





ulonglong BitArrayWriter::getNumberOfBits()
{
  try
  {
    return mNumberOfBits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





ulonglong BitArrayWriter::getWritePosition()
{
  try
  {
    return mWritePosition;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






void BitArrayWriter::setWritePosition(ulonglong writePosition)
{
  try
  {
    if (writePosition >= mNumberOfBits)
    {
      SmartMet::Spine::Exception exception(BCP,"The 'writePosition' parameter is out the range!");
      exception.addParameter("Requested write position",std::to_string(writePosition));
      exception.addParameter("Number of bits",std::to_string(mNumberOfBits));
      throw exception;
    }

    mWritePosition = writePosition;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void BitArrayWriter:: writeBit(bool bitOn)
{
  try
  {
    if (mData == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mData' attribute points to nullptr!");

    if ((mWritePosition + 1) > mNumberOfBits)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot write a bit outside of the memory area !");
      exception.addParameter("Write position",std::to_string(mWritePosition));
      exception.addParameter("Number of bits",std::to_string(mNumberOfBits));
      throw exception;
    }

    writeBitNoCheck(bitOn);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void BitArrayWriter::writeBits(unsigned int numberOfBits,ulonglong value)
{
  try
  {
    if (mData == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mData' attribute points to nullptr!");

    if (numberOfBits > 64)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot write more than 64 bits!");
      exception.addParameter("Requested bits",std::to_string(numberOfBits));
      throw exception;
    }

    if ((mWritePosition + numberOfBits) > mNumberOfBits)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot write bits outside of the memory area !");
      exception.addParameter("Write position",std::to_string(mWritePosition));
      exception.addParameter("Number of bits",std::to_string(mNumberOfBits));
      exception.addParameter("Requested bits",std::to_string(numberOfBits));
      throw exception;
    }

    for (unsigned int i=0; i<numberOfBits; i++)
    {
      ulonglong m = 1 << (numberOfBits-i-1);
      if ((value & m) != 0)
        writeBitNoCheck(true);
      else
        writeBitNoCheck(false);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void BitArrayWriter::writeBitNoCheck(bool bitOn)
{
  try
  {
    ulonglong byt = mWritePosition / 8;
    ulonglong bit = 7 - (mWritePosition % 8);

    mWritePosition++;

    unsigned char m = (1 << bit);

    if (bitOn)
      mData[byt] = mData[byt] | m;
    else
      mData[byt] = mData[byt] & ~m;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}



}

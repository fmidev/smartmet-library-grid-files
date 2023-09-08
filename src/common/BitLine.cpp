#include "BitLine.h"
#include "GeneralFunctions.h"
#include <macgyver/Exception.h>

#include <memory.h>

namespace SmartMet
{

BitLine::BitLine()
{
  try
  {
    changes = nullptr;
    changeCount = 0;
    length = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





BitLine::BitLine(uchar *bits,uint numOfBits)
{
  try
  {
    changes = nullptr;
    changeCount = 0;
    length = 0;

    setValue(bits,numOfBits);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





BitLine::BitLine(BitLine& bitLine)
{
  try
  {
    changes = nullptr;
    changeCount = bitLine.changeCount;
    length = bitLine.length;

    if (changeCount > 0  &&  bitLine.changes)
    {
      changes = new uint[changeCount];
      memcpy(changes,bitLine.changes,changeCount*sizeof(uint));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





BitLine::~BitLine()
{
  if (changes)
    delete[] changes;
}





void BitLine::operator=(BitLine& bitLine)
{
  try
  {
    if (changes)
    {
      delete[] changes;
      changes = nullptr;
    }

    changeCount = bitLine.changeCount;
    length = bitLine.length;

    if (changeCount > 0  &&  bitLine.changes)
    {
      changes = new uint[changeCount];
      memcpy(changes,bitLine.changes,changeCount*sizeof(uint));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}







uint BitLine::getLength()
{
  try
  {
    return length;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool BitLine::isAllZeros()
{
  try
  {
    if (changeCount == 0 || changes == nullptr)
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool BitLine::isAllOnes()
{
  try
  {
    if (changes == nullptr)
      return false;

    if (changeCount == 1  &&  changes[0] == 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint BitLine::getChange(uint index)
{
  try
  {
    if (changes == nullptr)
    {
      // WARNING: No changes defined!
      return 0;
    }

    if (index > changeCount)
    {
      // WARNING: The '_index' parameter is out of the range!
      return 0;
    }

    return changes[index];
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






uint BitLine::getChangeCount()
{
  try
  {
    return changeCount;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint BitLine::getChangeCount(uint startPos,uint endPos)
{
  try
  {
    if (changeCount == 0)
      return 0;

    uint idx = getClosestIndex(startPos);
    if (changes[idx] > endPos)
      return 0;

    uint ccnt = 0;
    bool bb = getBit(startPos);

    if (bb)
    {
      ccnt++;
    }

    while (idx < changeCount  &&  changes[idx] <= startPos)
      idx++;

    while (idx < changeCount)
    {
      if (changes[idx] <= endPos)
      {
        idx++;
        ccnt++;
      }
      else
      {
        idx = changeCount;
      }
    }
    return ccnt;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint BitLine::getChanges(uint startPos,uint endPos,uint* changePositions)
{
  try
  {
    changePositions[0] = 0;

    if (changeCount == 0)
      return 0;

    uint idx = getClosestIndex(startPos);
     if (changes[idx] > endPos)
      return 0;

    uint ccnt = 0;
    bool bb = getBit(startPos);

    if (bb)
    {
      changePositions[ccnt] = 0;
      //printf("-- %u\n",_changes[ccnt]);
       ccnt++;
    }

    while (idx < changeCount  &&  changes[idx] <= startPos)
      idx++;

    while (idx < changeCount)
    {
      if (changes[idx] <= endPos)
      {
        changePositions[ccnt] = changes[idx] - startPos;
        idx++;
        ccnt++;
      }
      else
      {
        idx = changeCount;
      }
    }
    return ccnt;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint BitLine::getMaxChange()
{
  try
  {
    uint maxChange = 0;
    uint prevChange = 0;

    for (uint t=0; t<changeCount; t++)
    {
      uint diff = changes[t] - prevChange;
      if (diff > maxChange)
        maxChange = diff;

      prevChange = changes[t];
    }
    return maxChange;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}







void BitLine::setValue(uint numOfBits,uint* changePositions,uint numOfChanges,bool release)
{
  try
  {
    if (changes)
    {
      delete[] changes;
      changes = nullptr;
    }

    changeCount = numOfChanges;
    length = numOfBits;
    if (changeCount > 0)
    {
      if (release)
      {
        changes = changePositions;
      }
      else
      {
        changes = new uint[changeCount];
        memcpy(changes,changePositions,changeCount*sizeof(uint));
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void BitLine::setValue(uchar *bits,uint numOfBits)
{
  try
  {
    if (changes)
    {
      delete[] changes;
      changes = nullptr;
    }


    length = numOfBits;
    changeCount = 0;

    uint *tmp = new uint[length];

    bool b = false;

    for (uint t=0; t<length; t++)
    {
      bool bb = getBit(bits,t);
      if (b != bb)
      {
        tmp[changeCount] = t;
        changeCount++;
        b = bb;
      }
    }

    if (changeCount > 0)
    {
      changes = new uint[changeCount];
      memcpy(changes,tmp,changeCount*sizeof(uint));
    }
    delete [] tmp;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void BitLine::readFromFile(const char *filename)
{
  try
  {
    FILE *file = fopen(filename,"r");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open the file!",nullptr);
      exception.addParameter("filename",filename);
      throw exception;
    }
    readFromFile(file);
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void BitLine::readFromFile(FILE *file)
{
  try
  {
    if (changes)
    {
      delete[] changes;
      changes = nullptr;
      changeCount = 0;
      length = 0;
    }

    auto fileSize = getFileSize(file);
    if (fileSize < 12)
    {
      Fmi::Exception exception(BCP,"The file does not exist or its size is too small!",nullptr);
      exception.addParameter("size",std::to_string(fileSize));
      throw exception;
    }

    if (fread(&length,4,1,file) <= 0)
      return;

    if (fread(&changeCount,4,1,file) <= 0)
      return;

    if (changeCount > 0  && (changeCount*4) < fileSize)
    {
      changes = new uint[changeCount];
      if (fread(changes,4,changeCount,file) <= 0)
      {
        delete[] changes;
        changes = nullptr;
        changeCount = 0;
        length = 0;
        return;
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void BitLine::writeToFile(const char *filename)
{
  try
  {
    FILE *file = fopen(filename,"w");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot create the file!",nullptr);
      exception.addParameter("filename",filename);
      throw exception;
    }

    fwrite(&length,4,1,file);
    fwrite(&changeCount,4,1,file);
    if (changeCount > 0)
      fwrite(changes,4,changeCount,file);

    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void BitLine::writeToFile(FILE *file)
{
  try
  {
    fwrite(&length,4,1,file);
    fwrite(&changeCount,4,1,file);
    if (changeCount > 0)
      fwrite(changes,4,changeCount,file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


} // SmartMet


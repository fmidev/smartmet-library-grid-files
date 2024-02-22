#include "MemoryMapper.h"
#include "AutoWriteLock.h"
#include "AutoReadLock.h"
#include "AutoThreadLock.h"
#include "GeneralFunctions.h"
#include "DataFetcher_filesys.h"
#include "DataFetcher_network.h"
#include "ShowFunction.h"

#include <macgyver/Exception.h>
#include <iostream>
#include <linux/userfaultfd.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <signal.h>
#include <poll.h>
#include <curl/curl.h>
#include <sys/utsname.h>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{


MemoryMapper memoryMapper;



void* fault_handler_thread(void *arg)
{
  MemoryMapper *mapper = (MemoryMapper*)arg;
  mapper->faultHandlerThread();
  pthread_exit(nullptr);
  return nullptr;
}



void* fault_processing_thread(void *arg)
{
  MemoryMapper *mapper = (MemoryMapper*)arg;
  mapper->faultProcessingThread();
  pthread_exit(nullptr);
  return nullptr;
}

std::string permission_string(mode_t mode)
{
  std::string permissions;
  permissions += ((mode & S_IRUSR) ? "r" : "-");
  permissions += ((mode & S_IWUSR) ? "w" : "-");
  permissions += ((mode & S_IXUSR) ? "x" : "-");
  permissions += ((mode & S_IRGRP) ? "r" : "-");
  permissions += ((mode & S_IWGRP) ? "w" : "-");
  permissions += ((mode & S_IXGRP) ? "x" : "-");
  permissions += ((mode & S_IROTH) ? "r" : "-");
  permissions += ((mode & S_IWOTH) ? "w" : "-");
  permissions += ((mode & S_IXOTH) ? "x" : "-");
  return permissions;
}
  

MemoryMapper::MemoryMapper()
{
  FUNCTION_TRACE
  try
  {
    mEnabled = false;
    mMaxProcessingThreads = 30;
    mMaxMessages = 1000;
    mMessage = nullptr;
    mFaultProcessingThread = nullptr;

    mThreadsRunning = 0;
    mStopRequired = false;
    mMessageReadCount.store(0);
    mMessageProcessCount.store(0);
    mUffd = -1;
    mPageSize = 0;
    mPageCache = nullptr;
    mPageCacheIndex = nullptr;
    mPageCacheCounter = 0;
    mPageCacheFreedCounter = 0;
    mPageCacheSize = 400000;
    mPremapEnabled = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed!",nullptr);
  }
}





MemoryMapper::~MemoryMapper()
{
  FUNCTION_TRACE
  mStopRequired = true;

  while (mEnabled  &&  mThreadsRunning)
    time_usleep(0,100);

  if (mMessage)
    delete [] mMessage;

  if (mFaultProcessingThread)
    delete [] mFaultProcessingThread;

  curl_global_cleanup();
}




void MemoryMapper::addMapInfo(MapInfo *mapInfo)
{
  FUNCTION_TRACE
  try
  {

    // std::cout << "MAP " << mapInfo->protocol << ":" << mapInfo->serverType << ":" << mapInfo->server << ":" << mapInfo->filename << "\n";

    //AutoWriteLock lock(&mModificationLock);

    int length = mMemoryMappings.size();
    int idx = getClosestIndex(mapInfo->memoryPtr);

    while (idx < length  &&  mMemoryMappings[idx]->memoryPtr <  mapInfo->memoryPtr)
      idx++;

    if (idx == length)
    {
      mMemoryMappings.push_back(mapInfo);
      return;
    }

    mMemoryMappings.insert(mMemoryMappings.begin() + idx, mapInfo);

/*
    printf("\n\nMAPPINGS\n");
    for (auto it = mMemoryMappings.begin(); it != mMemoryMappings.end(); ++it)
    {
      printf("%lld - %lld : %s\n",(long long)(*it)->memoryPtr,(long long)(*it)->memoryPtr+(*it)->allocatedSize,(*it)->filename.c_str());
    }
    printf("\n");
*/
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




int MemoryMapper::getClosestIndex(char *address)
{
  FUNCTION_TRACE
  try
  {
    int length = mMemoryMappings.size();
    if (length == 0)
      return 0;

    int low = 0;
    int high = C_INT(length) - 1;
    int mid = 0;

    while (low <= high)
    {
      mid = (low + high) / 2;
      int res = ptr_compare(mMemoryMappings[mid]->memoryPtr,address);

      if (res == 0)
      {
        while (mid > 0  &&  ptr_compare(mMemoryMappings[mid-1]->memoryPtr,address) == 0)
          mid--;

        return mid;
      }

      if (res < 0)
        low = mid + 1;
      else
        high = mid - 1;
    }

    if (mid >= 0  &&  mid < length)
    {
      if (ptr_compare(mMemoryMappings[mid]->memoryPtr,address) < 0)
      {
        while (mid < length  &&   ptr_compare(mMemoryMappings[mid]->memoryPtr,address) < 0)
          mid++;

        return mid-1;
      }
      else
      {
        while (mid > 0  &&  ptr_compare(mMemoryMappings[mid]->memoryPtr,address) > 0)
          mid--;

        return mid;
      }
    }
    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




bool MemoryMapper::isEnabled()
{
  return mEnabled;
}




bool MemoryMapper::isPremapEnabled()
{
  if (mEnabled)
    return mPremapEnabled;

  return false;
}




void MemoryMapper::setPremapEnabled(bool enabled)
{
  mPremapEnabled = enabled;
}




void MemoryMapper::addAccessInfo(const char *server,uint authenticationMethod,const char *username,const char *password)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mDataFetchers.begin(); it != mDataFetchers.end(); ++it)
    {
      (it->second)->addAccessInfo(server,authenticationMethod,username,password);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryMapper::setAccessFile(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    mAccessFile = filename;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryMapper::setEnabled(bool enabled)
{
  FUNCTION_TRACE
  try
  {
    if (enabled)
    {
      struct utsname systemInfo;
      if (uname(&systemInfo) != 0)
      {
        std::cout << "### WARNING: MemoryMapper::setEnabled(): Error getting system information\n";
        return;
      }

      if (systemInfo.release[0] < '4' &&  systemInfo.release[1] == '.')
      {
        std::cout << "### WARNING: MemoryMapper::setEnabled(): Cannot enable user fault based memory mapping\n";
        return;
      }
    }


    if (enabled  &&  mUffd < 0)
    {
      curl_global_init(CURL_GLOBAL_ALL);

      // ### Initializing the service

      mMessage = new uffd_msg[mMaxMessages];
      mFaultProcessingThread = new pthread_t[mMaxProcessingThreads];

      DataFetcher_sptr df_filesys(new DataFetcher_filesys);
      DataFetcher_sptr df_network(new DataFetcher_network());

      if (!mAccessFile.empty())
        df_network->setAccessFile(mAccessFile.c_str());

      mDataFetchers.insert(std::pair<uint,DataFetcher_sptr>(DataFetcher::ServerType::Unknown,df_filesys));   // Unknow protocol
      mDataFetchers.insert(std::pair<uint,DataFetcher_sptr>(DataFetcher::ServerType::Filesys,df_filesys));   // Fileys
      mDataFetchers.insert(std::pair<uint,DataFetcher_sptr>(DataFetcher::ServerType::S3,df_network));        // S3
      mDataFetchers.insert(std::pair<uint,DataFetcher_sptr>(DataFetcher::ServerType::THREDDS,df_network));   // THREDDS
      mDataFetchers.insert(std::pair<uint,DataFetcher_sptr>(DataFetcher::ServerType::HTTPD,df_network));     // HTTPD

      mPageSize = sysconf(_SC_PAGE_SIZE);
      mUffd = syscall(__NR_userfaultfd, O_CLOEXEC | O_NONBLOCK);

      if (mUffd == -1)
      {
        printf("### WARNING: Cannot initialize UserFault signal based memory mapping!\n  ** File   : %s (%d)\n  ** Method : %s\n",BCP);
        return;
      }

      struct uffdio_api uffdio_api;
      uffdio_api.api = UFFD_API;
      uffdio_api.features = 0;

      if (ioctl(mUffd, UFFDIO_API, &uffdio_api) == -1)
      {
        printf("### WARNING: Cannot initialize UserFault signal based memory mapping (ioctl-UFFDIO_API)!\n  ** File   : %s (%d)\n  ** Method : %s\n",BCP);
        return;
      }

      mPageCacheIndex = new long long[mPageCacheSize];
      mPageCache = new char*[mPageCacheSize];
      for (uint t=0; t<mPageCacheSize; t++)
      {
        mPageCache[t] = new char[mPageSize];
        mPageCacheIndex[t] = -1;
      }

      mEnabled = enabled;
      startFaultHandler();
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void MemoryMapper::map(MapInfo& info)
{
  FUNCTION_TRACE
  try
  {
    AutoWriteLock lock(&mModificationLock);

    info.mappingTime = time(0);

    if (!mEnabled)
    {
      // We should use the old memory mapper

      struct stat buf;
      if (stat(info.filename.c_str(), &buf) == 0)
      {
        info.fileSize = (std::size_t)buf.st_size;
      }
      else
      {
        Fmi::Exception exception(BCP,"The file does not exist!");
        exception.addParameter("Filename",info.filename);
        throw exception;
      }

      if (info.fileSize == 0)
      {
        Fmi::Exception exception(BCP,"The file size is zero!");
        exception.addParameter("Filename",info.filename);
        throw exception;
      }

      // Sometimes MappedFile fails even though stat has already succeeded
      try
      {
        MappedFileParams params(info.filename);
        params.flags = boost::iostreams::mapped_file::readonly;
        params.length = info.fileSize;
        info.mappedFile.reset(new MappedFile(params));
        //mFileModificationTime = getFileModificationTime(mFileName.c_str());
        info.memoryPtr = const_cast<char*>(info.mappedFile->const_data());
        return;
      }
      catch(...)
      {
        Fmi::Exception exception(BCP, "Boost MappedFile call failed", nullptr);
        exception.addParameter("Permissions", permission_string(buf.st_mode));
        exception.addParameter("Filesize", std::to_string(buf.st_size));
        throw exception;
      }
       
    }

    info.allocatedSize = (((info.fileSize + 100)/ mPageSize) + 1) * mPageSize;
    info.memoryPtr = (char*)mmap(NULL, info.allocatedSize, PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (info.memoryPtr == MAP_FAILED)
    {
      info.memoryPtr = 0;
      Fmi::Exception exception(BCP,"mmap failed");
      exception.addParameter("allocatedSize",std::to_string(info.allocatedSize));
      exception.addParameter("filename",info.filename);
      exception.addParameter("fileSize",std::to_string(info.fileSize));
      exception.addParameter("errno",std::to_string(errno));
      throw exception;
    }

    // printf("Add %ld %s %lld - %lld  %ld\n",info.fileSize,info.filename.c_str(),(long long)info.memoryPtr,(long long)info.memoryPtr+info.allocatedSize,info.allocatedSize);

    addMapInfo(new MapInfo(info));
    //mMemoryMappings.insert(std::pair<char*,MapInfo>(info.memoryPtr,info));

    struct uffdio_register uffdio_register;
    uffdio_register.range.start = (unsigned long)info.memoryPtr;
    uffdio_register.range.len = info.allocatedSize;
    uffdio_register.mode = UFFDIO_REGISTER_MODE_MISSING;

    if (ioctl(mUffd, UFFDIO_REGISTER, &uffdio_register) == -1)
      throw Fmi::Exception(BCP,"ioctl-UFFDIO_REGISTER");

  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryMapper::unmap(MapInfo& info)
{
  FUNCTION_TRACE
  try
  {
    if (!mEnabled)
    {
      if (info.mappedFile)
        info.mappedFile->close();

      return;
    }

    if (info.memoryPtr != nullptr)
    {
      {
        AutoWriteLock lock(&mModificationLock);
        int index = getClosestIndex(info.memoryPtr);
        if (mMemoryMappings[index]->memoryPtr == info.memoryPtr)
        {
          //printf("DELETE MEMORY MAP %s\n",info.filename.c_str());
          delete mMemoryMappings[index];
          mMemoryMappings.erase(mMemoryMappings.begin() + index);
        }
      }

      struct uffdio_register uffdio_register;
      uffdio_register.range.start = (unsigned long)info.memoryPtr;
      uffdio_register.range.len = info.allocatedSize;
      uffdio_register.mode = UFFDIO_REGISTER_MODE_MISSING;

      ioctl(mUffd, UFFDIO_UNREGISTER, &uffdio_register);

      munmap(info.memoryPtr,info.allocatedSize);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




MapInfo* MemoryMapper::getMapInfo(char *address)
{
  FUNCTION_TRACE
  try
  {
    AutoReadLock lock(&mModificationLock);

    int index = getClosestIndex(address);
    MapInfo *info = mMemoryMappings[index];
    if (!info || info->memoryPtr != address)
      return nullptr;

    return info;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryMapper::premap(char *startAddress,char *endAddress)
{
  FUNCTION_TRACE
  try
  {
    if (!mEnabled)
      return;

    {
      AutoWriteLock writeLock(&mPageCacheModificationLock);
      if (mPremapRequests.find(startAddress) == mPremapRequests.end())
        mPremapRequests.insert(std::pair<char*,char*>(startAddress,endAddress));
      else
        return;
    }

    //printf("PREMAP REQUESTED\n");
    AutoReadLock lock(&mModificationLock);

    int index = getClosestIndex(startAddress);
    MapInfo *info = mMemoryMappings[index];
    if (!info || info->memoryPtr > startAddress ||  startAddress > (info->memoryPtr+info->allocatedSize) ||  info->protocol <= 1)
      return;

    long long pageIndex = (long long)startAddress / mPageSize;
    long long endPageIndex = (long long)endAddress / mPageSize;

    long long address = pageIndex * mPageSize;

    long long fp = (long long)address - (long long)info->memoryPtr;

    long long pages = endPageIndex - pageIndex + 1;

    long long dataSize = pages*mPageSize;
    char *data = new char[dataSize];
    uint p = 0;

    int n = getData(*info,fp,dataSize,data);

    AutoWriteLock writeLock(&mPageCacheModificationLock);
    for (uint t=0; t<pages; t++)
    {
      uint idx = mPageCacheCounter % mPageCacheSize;
      //printf("PREMAP %lld : %lld\n",pageIndex,mPageCacheCounter);
      memcpy(mPageCache[idx],data+p,mPageSize);
      mPageCacheIndex[idx] = pageIndex;

      mPageCacheIndexList.insert(std::pair<long long,uint>(pageIndex,idx));
      p = p + mPageSize;
      mPageCacheCounter++;
      pageIndex++;
    }

    if (mPageCacheIndexList.size() > (std::size_t)mPageCacheSize)
    {
      //printf("*** PAGE CACHE CLEAR START %ld\n",mPageCacheIndexList.size());
      mPageCacheIndexList.clear();
      mPremapRequests.clear();
      for (uint t=0; t<mPageCacheSize; t++)
      {
        if (mPageCacheIndex[t] >= 0)
          mPageCacheIndexList.insert(std::pair<long long,uint>(mPageCacheIndex[t],t));
      }
      //printf("*** PAGE CACHE CLEAR END %ld\n",mPageCacheIndexList.size());
    }
    if (data)
      delete [] data;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryMapper::startFaultHandler()
{
  try
  {
    if (!mEnabled)
      throw Fmi::Exception(BCP,"MemoryMapper is disabled!");

    pthread_create(&mFaultHandlerThread, nullptr, fault_handler_thread,this);

    for (uint t=0; t<mMaxProcessingThreads; t++)
      pthread_create(&mFaultProcessingThread[t], nullptr, fault_processing_thread,this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryMapper::stopFaultHandler()
{
  try
  {
    if (!mEnabled)
      return;

    mStopRequired = true;

    while (mThreadsRunning)
      time_usleep(0,100);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




long long MemoryMapper::getFileSize(uint serverType,uint protocol,const char *server,const char *filename)
{
  FUNCTION_TRACE
  try
  {
    if (!mEnabled)
      return 0;

    auto it = mDataFetchers.find(serverType);
    if (it != mDataFetchers.end())
      return it->second->getFileSize(serverType,protocol,server,filename);

    return -1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




int MemoryMapper::getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr)
{
  try
  {
    if (dataSize == mPageSize)
    {
      long long address = (long long)info.memoryPtr + filePosition;
      long long pageIndex = address / mPageSize;

      AutoReadLock readLock(&mPageCacheModificationLock);

      auto it = mPageCacheIndexList.find(pageIndex);
      if (it != mPageCacheIndexList.end())
      {
        uint idx = it->second;
        if (mPageCacheIndex[idx] == it->first)
        {
          memcpy(dataPtr,mPageCache[idx],mPageSize);
          //printf("-- Load from precache %lld %u\n",pageIndex,idx);

          mPageCacheIndex[idx] = -1;
          mPageCacheFreedCounter++;
          return mPageSize;
        }
      }
      else
      {
        //printf("-- Fail to load from precache %lld\n",pageIndex);
      }
    }

    auto it = mDataFetchers.find(info.serverType);
    if (it != mDataFetchers.end())
      return it->second->getData(info.serverType,info.protocol,info.server.c_str(),info.filename.c_str(),filePosition,dataSize,dataPtr);

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryMapper::faultProcessingThread()
{
  try
  {
    if (!mEnabled)
      throw Fmi::Exception(BCP,"MemoryMapper is disabled!");

    uint threadId = mThreadsRunning;
    mThreadsRunning++;
    struct uffdio_copy uffdio_copy;

    /* Create a page that will be copied into the faulting region. */

    char *page = (char*)mmap(NULL, mPageSize, PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (page == MAP_FAILED)
      throw Fmi::Exception(BCP,"Memory map creation failed!");

    /* Loop, handling incoming events on the userfaultfd file descriptor. */

    uint sleepCount = 0;
    while (!mStopRequired)
    {
      try
      {
        int idx = -1;
        long long len = 0;
        {
          AutoThreadLock tlock(&mThreadLock);
          len = mMessageReadCount.load() - mMessageProcessCount.load();
          if (len > 0)
          {
            idx = mMessageProcessCount % mMaxMessages;
            //printf("PROCESS %lld  %lld  %lld\n",(long long)mMessageReadCount,(long long)mMessageProcessCount,len);
            mMessageProcessCount++;
          }
        }

        if (idx >= 0)
        {
          AutoReadLock lock(&mModificationLock);

          auto address = (char*)mMessage[idx].arg.pagefault.address;
          int index = getClosestIndex(address);

          MapInfo *info = mMemoryMappings[index];

          //printf("SEARCH %d  %lld  %lld - %lld\n",index,(long long)address,(long long)info->memoryPtr,(long long)(info->memoryPtr + info->allocatedSize));
          if (mMemoryMappings.size() > (std::size_t)index  &&  info->memoryPtr <= address &&
              (info->memoryPtr + info->allocatedSize) > address)
          {
            //printf("FOUND %lld => %lld (%s)\n",(long long)address,(long long)info->memoryPtr,info->filename.c_str());

            unsigned long long fp = (long long)address - (long long)info->memoryPtr;
            try
            {
              int n = 0;

              if (!info->mappingError)
                n = getData(*info,fp,mPageSize,page);

              if (n == 0)
              {
                //printf("***** ZERO DATA RETURNED\n");
                memset(page,0,mPageSize);
                info->mappingError = true;
              }
              else
                info->mappingError = false;
            }
            catch (...)
            {
              Fmi::Exception exception(BCP,"Cannot fetch memory page!",nullptr);
              exception.printError();
              memset(page,0,mPageSize);
              info->mappingError = true;
            }
          }
          else
          {
            //printf("***** MAPPING NOT FOUND\n");
            memset(page,0,mPageSize);
            info->mappingError = true;
          }

          uffdio_copy.src = (unsigned long)page;
          uffdio_copy.dst = (unsigned long)address & ~(mPageSize - 1);
          uffdio_copy.len = mPageSize;
          uffdio_copy.mode = 0;
          uffdio_copy.copy = 0;

          if (ioctl(mUffd, UFFDIO_COPY, &uffdio_copy) == -1  &&  errno != 17)
          {
            Fmi::Exception exception(BCP,"ioctl-UFFDIO_COPY!");
            exception.addParameter("errno",std::to_string(errno));
            throw exception;
          }

          sleepCount = 0;
        }
        else
        {
          sleepCount++;
          if (sleepCount < 100  &&  mMessageReadCount.load() > 0)
          {
            time_usleep(0,500000);
          }
          else
          {
            if (threadId < 5)
              time_usleep(0,10000000);
            else
              time_usleep(0,50000000);
          }
        }
      }
      catch (...)
      {
        Fmi::Exception exception(BCP,"Operation failed!",nullptr);
        exception.printError();
      }
    }
    mThreadsRunning--;
    //std::cout << "THREADS RUNNING " << mThreadsRunning << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void MemoryMapper::faultHandlerThread()
{
  try
  {
    if (!mEnabled)
      throw Fmi::Exception(BCP,"MemoryMapper is disabled!");

    mThreadsRunning++;

    /* Create a page that will be copied into the faulting region. */

    char *page = (char*)mmap(NULL, mPageSize, PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (page == MAP_FAILED)
      throw Fmi::Exception(BCP,"Memory map creation failed!");

    /* Loop, handling incoming events on the userfaultfd file descriptor. */

    while (!mStopRequired)
    {
      try
      {
        auto len = mMessageReadCount.load() - mMessageProcessCount.load();

        if (len < mMaxMessages)
        {
          auto idx = mMessageReadCount.load() % mMaxMessages;

          struct pollfd pollfd;
          pollfd.fd = mUffd;
          pollfd.events = POLLIN;
          int nready = poll(&pollfd, 1, 1000);
          if (nready == -1)
            throw Fmi::Exception(BCP,"Poll error!");

          if (nready > 0)
          {
            ssize_t nread = read(mUffd, &mMessage[idx], sizeof(uffd_msg));
            if (nread == 0)
              throw Fmi::Exception(BCP,"EOF on userfaultfd!");

            if (nread == -1)
              throw Fmi::Exception(BCP,"Read error!");

            if (mMessage[idx].event != UFFD_EVENT_PAGEFAULT)
              throw Fmi::Exception(BCP,"Unexpected event on userfaultfd!");

            AutoThreadLock tlock(&mThreadLock);

            bool found = false;
            auto address = mMessage[idx].arg.pagefault.address;
            for (auto t = (long long)mMessageProcessCount; t<(long long)mMessageReadCount.load()  &&  !found; t++)
            {
              auto i = t % mMaxMessages;
              if (mMessage[i].arg.pagefault.address == address)
                found = true;
            }
            if (!found)
              mMessageReadCount++;
            //else
            //  printf("-------------- PAGE ALREADY IN THE MAPPING LIST\n");
            //printf("READ %lld  %lld\n",(long long)mMessageReadCount,(long long)mMessageProcessCount);
          }
        }
        else
        {
          time_usleep(0,100);
        }
      }
      catch (...)
      {
        Fmi::Exception exception(BCP,"Operation failed!",nullptr);
        // exception.printError();
      }
    }
    mThreadsRunning--;
    //std::cout << "THREADS RUNNING " << mThreadsRunning << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}  // namespace SmartMet

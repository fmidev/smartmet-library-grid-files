#pragma once

#include "ModificationLock.h"
#include "MapInfo.h"
#include "DataFetcher_network.h"

#include <string>
#include <vector>
#include <linux/userfaultfd.h>


namespace SmartMet
{




class MemoryMapper
{
  public:
              MemoryMapper();
              ~MemoryMapper();

    bool      isEnabled();
    void      setEnabled(bool enabled);

    bool      isPremapEnabled();
    void      setPremapEnabled(bool enabled);

    void      addAccessInfo(const char *server,uint authenticationMethod,const char *username,const char *password);
    void      setAccessFile(const char *filename);

    long long getFileSize(uint serverType,uint protocol,const char *server,const char *filename);
    MapInfo*  getMapInfo(char *address);

    void      premap(char *startAddress,char *endAddress);

    void      map(MapInfo& info);
    void      unmap(MapInfo& info);

    void      startFaultHandler();
    void      stopFaultHandler();

    void      faultHandlerThread();
    void      faultProcessingThread();

  protected:

    void      addMapInfo(MapInfo *mapInfo);
    int       getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);
    int       getClosestIndex(char *address);


  protected:
    long                      mUffd;
    int                       mPageSize;
    std::vector<MapInfo*>     mMemoryMappings;
    ModificationLock          mModificationLock;
    uffd_msg*                 mMessage;
    std::atomic<long long>    mMessageReadCount;
    std::atomic<long long>    mMessageProcessCount;
    std::atomic<uint>         mThreadsRunning;
    pthread_t                 mFaultHandlerThread;
    pthread_t*                mFaultProcessingThread;
    bool                      mStopRequired;
    ThreadLock                mThreadLock;
    DataFetcher_sptr_map      mDataFetchers;
    uint                      mMaxProcessingThreads;
    uint                      mMaxMessages;
    bool                      mEnabled;
    ModificationLock          mPageCacheModificationLock;
    std::map<long long,uint>  mPageCacheIndexList;
    char**                    mPageCache;
    long long*                mPageCacheIndex;
    uint                      mPageCacheCounter;
    long long                 mPageCacheFreedCounter;
    long long                 mPageCacheSize;
    std::map<char*,char*>     mPremapRequests;
    std::string               mAccessFile;
    bool                      mPremapEnabled;
};


extern MemoryMapper memoryMapper;

}  // namespace SmartMet

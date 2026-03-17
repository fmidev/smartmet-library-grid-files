#pragma once

#include "ModificationLock.h"
#include "MapInfo.h"
#include "DataFetcher_network.h"
#include "AttributeNode.h"

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
    void      setMaxProcessingThreads(uint maxThreads);
    void      setMaxMessages(uint maxMessages);
    void      setPageCacheSize(std::size_t pageCacheSize);
    void      setFileHandleLimit(std::size_t fileHandleLimit);


    Int64 getFileSize(uint serverType,uint protocol,const char *server,const char *filename);
    MapInfo_sptr getMapInfo(char *address);

    void      premap(char *startAddress,char *endAddress);

    void      map(MapInfo_sptr info);
    void      unmap(MapInfo_sptr info);

    void      startFaultHandler();
    void      stopFaultHandler();

    void      faultHandlerThread();
    void      faultProcessingThread();

    void      getStateAttributes(std::shared_ptr<T::AttributeNode> parent);

  protected:

    void      addMapInfo(MapInfo_sptr mapInfo);
    int       getData(MapInfo_sptr info,std::size_t filePosition,int dataSize,char *dataPtr);
    int       getClosestIndex(char *address);


  protected:
    long                      mUffd;
    int                       mPageSize;
    std::vector<MapInfo_sptr> mMemoryMappings;
    ModificationLock          mModificationLock;
    uffd_msg*                 mMessage;
    std::atomic<Int64>    mMessageReadCount;
    std::atomic<Int64>    mMessageProcessCount;
    std::atomic<uint>         mThreadsRunning;
    pthread_t                 mFaultHandlerThread;
    pthread_t*                mFaultProcessingThread;
    bool                      mStopRequired;
    ThreadLock                mThreadLock;
    DataFetcher_sptr_map      mDataFetchers;
    uint                      mMaxProcessingThreads;
    uint                      mMaxMessages;
    std::size_t               mFileHandleLimit;
    bool                      mEnabled;
    ModificationLock          mPageCacheModificationLock;
    std::map<Int64,uint>  mPageCacheIndexList;
    char**                    mPageCache;
    Int64*                mPageCacheIndex;
    uint                      mPageCacheCounter;
    Int64                 mPageCacheFreedCounter;
    std::size_t               mPageCacheSize;
    std::map<char*,char*>     mPremapRequests;
    std::string               mAccessFile;
    bool                      mPremapEnabled;
};


extern MemoryMapper memoryMapper;

}  // namespace SmartMet

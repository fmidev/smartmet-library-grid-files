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




// ====================================================================================
/*! \brief Lazy memory mapper for local and remote (HTTP/S3) grid files.
 *
 *  Uses Linux `userfaultfd` to create virtual memory regions that are populated
 *  on demand by a background fault-handler thread.  Pages are fetched from a
 *  `DataFetcher` (filesystem or network) and cached in a fixed-size page cache.
 *  An optional pre-map mode (`setPremapEnabled`) eagerly fetches all pages for
 *  a mapping without waiting for faults.
 *
 *  A global instance `memoryMapper` is defined at the end of this header.
 *  Calling `startFaultHandler()` launches the background thread; call
 *  `stopFaultHandler()` before shutdown. */
// ====================================================================================

class MemoryMapper
{
  public:
              MemoryMapper();
              ~MemoryMapper();

    /*! \brief Return true if the mapper is enabled (userfaultfd active). */
    bool      isEnabled();

    /*! \brief Enable or disable the mapper.
     *  \param[in] enabled  True to activate userfaultfd-based lazy mapping. */
    void      setEnabled(bool enabled);

    /*! \brief Return true if eager pre-mapping is enabled. */
    bool      isPremapEnabled();

    /*! \brief Enable or disable eager pre-mapping (fetch all pages at map time).
     *  \param[in] enabled  True to pre-fetch pages immediately on map(). */
    void      setPremapEnabled(bool enabled);

    /*! \brief Register HTTP/S3 access credentials for a server.
     *  \param[in] server                Hostname or URL prefix.
     *  \param[in] authenticationMethod  Authentication method code.
     *  \param[in] username              Login name (may be empty).
     *  \param[in] password              Password or token (may be empty). */
    void      addAccessInfo(const char *server,uint authenticationMethod,const char *username,const char *password);

    /*! \brief Load server access credentials from a configuration file.
     *  \param[in] filename  Path to the access credentials file. */
    void      setAccessFile(const char *filename);

    /*! \brief Set the maximum number of concurrent page-fetch threads.
     *  \param[in] maxThreads  Thread pool size. */
    void      setMaxProcessingThreads(uint maxThreads);

    /*! \brief Set the maximum number of userfaultfd messages to queue.
     *  \param[in] maxMessages  Queue depth. */
    void      setMaxMessages(uint maxMessages);

    /*! \brief Set the in-memory page cache size (number of pages).
     *  \param[in] pageCacheSize  Number of pages to keep in the cache. */
    void      setPageCacheSize(std::size_t pageCacheSize);

    /*! \brief Limit the number of simultaneously open remote file handles.
     *  \param[in] fileHandleLimit  Maximum concurrent open handles. */
    void      setFileHandleLimit(std::size_t fileHandleLimit);

    /*! \brief Query the size of a remote or local file.
     *  \param[in] serverType  MapInfo::ServerType constant.
     *  \param[in] protocol    MapInfo::Protocol constant.
     *  \param[in] server      Server hostname or URL.
     *  \param[in] filename    File path on the server.
     *  \return File size in bytes, or a negative error code. */
    Int64     getFileSize(uint serverType,uint protocol,const char *server,const char *filename);

    /*! \brief Return the MapInfo descriptor that owns the given mapped address.
     *  \param[in] address  Pointer into a mapped region.
     *  \return Shared pointer to the MapInfo, or nullptr if not found. */
    MapInfo_sptr getMapInfo(char *address);

    /*! \brief Eagerly fetch all pages between \p startAddress and \p endAddress.
     *  \param[in] startAddress  Start of the region to pre-fetch.
     *  \param[in] endAddress    One-past-the-end of the region. */
    void      premap(char *startAddress,char *endAddress);

    /*! \brief Establish a userfaultfd-backed virtual mapping for \p info.
     *  \param[in] info  MapInfo describing the file and its allocation. */
    void      map(MapInfo_sptr info);

    /*! \brief Release the virtual mapping for \p info.
     *  \param[in] info  MapInfo to unmap. */
    void      unmap(MapInfo_sptr info);

    /*! \brief Launch the background fault-handler and processing threads. */
    void      startFaultHandler();

    /*! \brief Signal background threads to stop and wait for them to exit. */
    void      stopFaultHandler();

    /*! \brief Entry point for the userfaultfd reader thread (internal). */
    void      faultHandlerThread();

    /*! \brief Entry point for each page-fetch worker thread (internal). */
    void      faultProcessingThread();

    /*! \brief Populate \p parent with an attribute sub-tree describing internal state.
     *  \param[in,out] parent  Root node to append state attributes to. */
    void      getStateAttributes(std::shared_ptr<T::AttributeNode> parent);

  protected:

    void      addMapInfo(MapInfo_sptr mapInfo);
    int       getData(MapInfo_sptr info,std::size_t filePosition,int dataSize,char *dataPtr);
    int       getClosestIndex(char *address);


  protected:
    long                      mUffd;                    //!< userfaultfd file descriptor
    int                       mPageSize;                //!< OS page size in bytes
    std::vector<MapInfo_sptr> mMemoryMappings;          //!< Active mapping descriptors
    ModificationLock          mModificationLock;        //!< Guards mMemoryMappings
    uffd_msg*                 mMessage;                 //!< Reusable userfaultfd message buffer
    std::atomic<Int64>        mMessageReadCount;        //!< Total fault messages read
    std::atomic<Int64>        mMessageProcessCount;     //!< Total fault messages processed
    std::atomic<uint>         mThreadsRunning;          //!< Number of active processing threads
    pthread_t                 mFaultHandlerThread;      //!< Reader thread handle
    pthread_t*                mFaultProcessingThread;   //!< Pool of processing thread handles
    bool                      mStopRequired;            //!< Set to true to request thread shutdown
    ThreadLock                mThreadLock;              //!< Guards message dispatch
    DataFetcher_sptr_map      mDataFetchers;            //!< Per-server data fetchers
    uint                      mMaxProcessingThreads;    //!< Processing thread pool size
    uint                      mMaxMessages;             //!< Fault message queue depth
    std::size_t               mFileHandleLimit;         //!< Maximum concurrent open remote handles
    bool                      mEnabled;                 //!< True when userfaultfd is active
    ModificationLock          mPageCacheModificationLock; //!< Guards page cache structures
    std::map<Int64,uint>      mPageCacheIndexList;      //!< Maps page IDs to cache slots
    char**                    mPageCache;               //!< Array of cached page data pointers
    Int64*                    mPageCacheIndex;          //!< Page ID for each cache slot
    uint                      mPageCacheCounter;        //!< LRU eviction counter
    Int64                     mPageCacheFreedCounter;   //!< Total pages evicted
    std::size_t               mPageCacheSize;           //!< Number of slots in the page cache
    std::map<char*,char*>     mPremapRequests;          //!< Pending eager pre-map requests
    std::string               mAccessFile;              //!< Path to the access credentials file
    bool                      mPremapEnabled;           //!< True when eager pre-mapping is active
};


extern MemoryMapper memoryMapper;

}  // namespace SmartMet

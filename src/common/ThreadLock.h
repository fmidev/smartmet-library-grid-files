#pragma once

#include <pthread.h>
#include <stdio.h>

namespace SmartMet
{


// ====================================================================================
/*! \brief Thin RAII wrapper around a `pthread_mutex_t` with error-check attributes.
 *
 *  Prints a diagnostic message on re-lock attempts from the same thread rather than
 *  deadlocking silently.  Prefer `AutoThreadLock` for scoped acquisition. */
// ====================================================================================

class ThreadLock
{
  public:

    /*! \brief Initialise the mutex with `PTHREAD_MUTEX_ERRORCHECK` attributes. */
    ThreadLock()
    {
      pthread_mutexattr_init(&attr);
      if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK))
        pthread_mutex_init(&threadLock,nullptr);
      else
        pthread_mutex_init(&threadLock,&attr);
    }


    ~ThreadLock()
    {
      pthread_mutex_destroy(&threadLock);
    }
    /*! \brief A copy gets a mutex of its own: a mutex cannot be copied. */
    ThreadLock(const ThreadLock& /* theOther */) : ThreadLock() {}
    /*! \brief Assignment keeps this object's own mutex. */
    // NOLINTNEXTLINE(cert-oop54-cpp): nothing is copied, so self-assignment is harmless
    ThreadLock& operator=(const ThreadLock& /* theOther */) { return *this; }


    /*! \brief Acquire the mutex, blocking until it is available. */
    void lock()
    {
      if (pthread_mutex_lock(&threadLock))
        printf("ERROR ThreadLock.h: Possible re-locking trial from the same thread!\n");
    }


    /*! \brief Try to acquire the mutex without blocking.
     *  \return True if the mutex was acquired; false if it was already held. */
    bool tryLock()
    {
      return pthread_mutex_trylock(&threadLock) == 0;
    }


    /*! \brief Release the mutex. */
    void unlock()
    {
      pthread_mutex_unlock(&threadLock);
    }

  protected:

    pthread_mutexattr_t attr{};    //!< Mutex attribute (error-check mode)
    pthread_mutex_t threadLock{};  //!< Underlying POSIX mutex
};


}

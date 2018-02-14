/* ***********************************************************************

  > File Name: MutexLock.hpp
  > Author: zzy
  > Mail: 942744575@qq.com 
  > Created Time: Mon 12 Feb 2018 09:54:45 PM CST

 ********************************************************************** */
#ifndef __MutexLock_HPP__
#define __MutexLock_HPP__

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

class MutexLock{
 public:
    MutexLock()
        :holder_(0) {
        pthread_mutex_init(&mutex_, NULL);
    }
    ~MutexLock() {
        pthread_mutex_destroy(&mutex_);
        holder_ = 0;
    }
    void lock() {
        pthread_mutex_lock(&mutex_);
        holder_ = getpid();
    }
    void unlock(){
        pthread_mutex_unlock(&mutex_);
        holder_ = 0;
    }
    bool isLockedByThisThread() const {
        return holder_ == getpid();
    }
    pthread_mutex_t* mutex() {
        return &mutex_;
    }
 private:
    pthread_mutex_t mutex_;
    pid_t holder_;
};

class MutexLockGuard
{
 public:
    MutexLockGuard(MutexLock & mutexlock)
        :mutex_(mutexlock){
        mutex_.lock();
    }
    ~MutexLockGuard(){
        mutex_.unlock();
    }
private:
    MutexLock & mutex_;
};

#endif // __MutexLock_HPP__              

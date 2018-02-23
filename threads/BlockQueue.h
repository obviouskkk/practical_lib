/* ***********************************************************************

  > File Name: BlockQueue.h
  > Author: zzy
  > Mail: 942744575@qq.com 
  > Created Time: Fri 23 Feb 2018 04:06:42 PM CST

 ********************************************************************** */

#ifndef __BLOCKQUEUE_H__
#define __BLOCKQUEUE_H__

#include "MutexLock.hpp"
#include "Condition.h"
#include <deque>


template<class T>
class BlockQueue
{
 public:
     BlockQueue() 
     :mutex_(),
      cond_(mutex_),
      queue_() {
    }
     void put (const T& x) {
         MutexLockGuard lock(mutex_);
         queue_.push_back(x);
         cond_.notify();
     }
     T take () {
         MutexLockGuard lock(mutex_);
         while (queue_.empty())
             cond_.wait();
         assert(!queue_.empty());
         T front(queue_.front());
         queue_.pop_front();
         return front;
     }
     size_t size() const
     {
         MutexLockGuard lock(mutex_);
         return queue_.size();
     } 
 private:
    mutable MutexLock mutex_;
    Condition         cond_;
    std::deque<T>     queue_;
};



#endif  // __BLOCKQUEUE_H__

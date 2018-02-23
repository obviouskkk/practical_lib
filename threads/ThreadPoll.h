/* ***********************************************************************

  > File Name: ThreadPoll.h
  > Author: zzy
  > Mail: 942744575@qq.com 
  > Created Time: Fri 23 Feb 2018 04:23:11 PM CST

 ********************************************************************** */
#ifndef __THREADPOLL_H__
#define __THREADPOLL_H__

#include "BlockQueue.h"
#include <functional>
#include <pthread.h>
#include "MutexLock.hpp"

static void * thread_start(void *obj);
class ThreadPoll 
{
    typedef std::function<void()> Func;
 public:
    ThreadPoll() 
        :taskQueue()
    {
    }
    void workerThread() {
        while (1){
            Func  task = taskQueue.take();
            task();
        }
    }
    void createThreads(int num) {
        for (int i = 0; i < num ; ++i)
        {   
            pthread_t thread_id ;
            pthread_create(&thread_id, NULL, &thread_start, this);
            pthread_join(thread_id, NULL);
        }
    }
 private:
    BlockQueue<Func> taskQueue;
};

static void * thread_start(void *obj) {
    ThreadPoll* data = static_cast<ThreadPoll*>(obj);
    data->workerThread();
    return NULL;
}

#endif  // __THREADPOLL_H__ 



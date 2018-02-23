/* ***********************************************************************

  > File Name: rwlock.cpp
  > Author: zzy
  > Mail: 942744575@qq.com 
  > Created Time: Fri 23 Feb 2018 02:45:24 PM CST

 ********************************************************************** */

#include "MutexLock.hpp"
#include <vector>
#include <memory>
#include <cassert>

class Foo;
typedef std::vector<Foo> Foolist;
typedef std::shared_ptr<Foolist> FoolistPtr;
MutexLock mutex;
FoolistPtr g_foos;

void traverse()
{
    FoolistPtr foos;
    {
        MutexLockGuard lock(mutex);
        foos = g_foos;
        assert(!g_foos.unique());
    }
    for (auto it = foos->begin(), it != foos->end(), it++) {
        it->do_it();
    }
}

void post(const Foo& f)
{
    MutexLockGuard lock(mutex);
    if (!g_foos.unique()) {
        g_foos.reset(new Foolist(*g_foos)); // 拷贝一份
    }
    assert(g_foos.unique());
    g_foos->push_back(f);
}

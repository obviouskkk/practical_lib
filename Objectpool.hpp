/* ***********************************************************************

  > File Name: Objectpool.hpp
  > Author: zzy
  > Mail: 942744575@qq.com 
  > Created Time: Fri 16 Feb 2018 06:53:54 PM CST

 ********************************************************************** */

#include <memory>
#include <string>
#include <map>
#include "Noncopyable.hpp"
#include "MutexLock.hpp"

class Obj
{
 public:
    Obj(const std::string& str){}
};
// version 1
// get(),如果找到key，返回Obj_[key];否则新建一个Obj,存入map
// 问题：Obj对象永远不会释放
class Objectpool_1 : public noncopyable
{
 public:
     std::shared_ptr<Obj> get(const std::string& key);
 private:
     mutable MutexLock  mutex_;
     std::map<std::string, std::shared_ptr<Obj> > Obj_;
};

// version 2
class Objectpool_2 : public noncopyable
{
 public:
     std::shared_ptr<Obj> get(const std::string& key);
 private:
     mutable MutexLock  mutex_;
     std::map<std::string, std::weak_ptr<Obj> > Obj_;
};

std::shared_ptr<Obj> Objectpool_2::get(const std::string &key)
{
    std::shared_ptr<Obj> pObj;
    MutexLockGuard lock(mutex_);
    std::weak_ptr<Obj>& wkObj = Obj_[key]; // 如果不存在，会新建一个
    pObj = wkObj.lock(); // 尝试提升
    if (!pObj) {
        pObj.reset(new Obj(key));
        wkObj = pObj; // 更新了Obj_[key]，wkObj 是个引用
    }
    return pObj;
}














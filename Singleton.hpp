/* ***********************************************************************

  > File Name: Singleton.hpp
  > Author: zzy
  > Mail: 942744575@qq.com 
  > Created Time: Mon 12 Feb 2018 07:51:25 PM CST

 ********************************************************************** */
#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

#include <cassert>
#include <cstdlib>

template  <class type>
class Singleton{
 public:
    virtual ~Singleton() {
        m_singleton = NULL;
    }
    static type & get_Singleton() {
        if (m_singleton == NULL)
            m_singleton = new type();
        return *m_singleton;
    }
    static type * get_Singleton_ptr() {
        if (m_singleton == NULL)
            m_singleton = new type();
        return m_singleton;
    }
 protected:
    Singleton() {
        assert(!m_singleton);
        m_singleton = static_cast<type*>(this);  // this在使用时是指向子类的
    }
    static type * m_singleton;
};
template <class type> type* Singleton<type>::m_singleton = NULL;

#endif  // __SINGLETON_HPP__


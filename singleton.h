/* ***********************************************************************

  > File Name: singleton.h
  > Author: zzy
  > Mail: 942744575@qq.com 
  > Created Time: Fri 23 Feb 2018 02:12:52 PM CST

 ********************************************************************** */

#include <pthread.h>

template <class T>
class Singleton
{
 public:
     static T& instance(){
         pthread_once(&ponce_, &Singleton::init);
     }
 private:
     Singleton();
     ~Singleton();
     Singleton(const Singleton &) = delete;
     Singleton operator=(const Singleton&) = delete;
     static void init() {
         value_ = new T();
     }
 private:
     static pthread_once_t ponce_;
     static T* value_;
};

template<class T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<class T>
T* Singleton<T>::value_ = NULL;

// use Foo & foo = Singleton<Foo>::instance();

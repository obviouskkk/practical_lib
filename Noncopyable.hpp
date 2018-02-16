/* ***********************************************************************

  > File Name: Noncopyable.hpp
  > Author: zzy
  > Mail: 942744575@qq.com 
  > Created Time: Fri 16 Feb 2018 06:54:54 PM CST

 ********************************************************************** */

class noncopyable
{
 public:
    noncopyable() = default;
    ~noncopyable() = default;
 private:
    noncopyable(const noncopyable& noncopy) = delete;
    void operator=(const noncopyable&) = delete;
};


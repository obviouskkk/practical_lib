/* ***********************************************************************

  > File Name: Singleton.cpp
  > Author: zzy
  > Mail: zzy@taomee.com 
  > Created Time: Wed 11 Oct 2017 04:27:10 PM CST

 ********************************************************************** */

#include <iostream>
#include "./Singleton.hpp"


class Testclass : public Singleton<Testclass>
{
	public:
		static void print(){
			std::cout << "hello world" << std::endl;
		}
};


#define sTestclass Testclass::get_Singleton()

int main(int argc, const char* argv[])
{
	sTestclass.print();
    return 0;
}


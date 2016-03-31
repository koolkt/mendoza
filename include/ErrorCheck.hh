#include <cerrno>
#include <cstdio>
#include <iostream>
#include <exception>
#include <SError.hh>
#pragma once

class           ErrorCheck
{
public:
  static void                    check(bool test, const char *msg)
  {
    if(!test)
      {
        std::cerr << msg << std::endl;
        throw SE;
      }
  }
};

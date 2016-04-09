#include <cerrno>
#include <cstdio>
#include <iostream>
#include <exception>
#pragma once

class SError: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Error while creating socket";
  }
} SE;

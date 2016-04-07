#pragma once
#include        <iostream>
#include        <vector>
#include        <string>

class                           Mail
{
  std::vector<std::string>*     dest;
  std::string                   body;
public:
  Mail();
  void                          set_dest(std::vector<std::string>*);
  void                          set_body(const std::string&);
  void                          reset();
  std::vector<std::string>&     get_dest();
  std::string&                  get_body();
  ~Mail();
};

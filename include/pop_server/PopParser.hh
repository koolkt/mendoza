#pragma once
#include        <iostream>
#include        <regex>
#include        <string>
#include        <vector>
#include        <Client.hh>

class           PopClient;
class           PopParser
{
  bool                    capa(const std::string *data);
  bool                    user(const std::string *data);
  bool                    pass(const std::string *data);
  bool                    stat(const std::string *data);
  bool                    quit(const std::string *data);
public:
  enum          State {START, V_USER, V_PASS, SEND_MAIL};

  enum          Action {OK, CAPA, AUTH, USER, PASS, STAT, LIST, RETR, DELE,  QUIT, NOT_IMP};
  PopParser();
  Action  parse(Client *);
  ~PopParser();
};

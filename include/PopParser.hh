#pragma once
#include        <iostream>
#include        <regex>
#include        <string>
#include        <vector>

class           PopClient;
class           PopParser
{
public:
  enum          State {START, HELO, MAIL,
                       RCPT, DATA, RSET,
                       VRFY, NOOP, QUIT, MAIL_PARSED};

  enum          Action {OK, END_DATA, BYE, NOT_IMP, MAIL_NA};
  PopParser();
  Action  parse(PopClient *);
  ~PopParser();
};

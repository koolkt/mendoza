#pragma once
#include        <iostream>

class           Client;
class           Parser
{
public:
  enum          State {START, HELO, MAIL,
                       RCPT, DATA, RSET,
                       VRFY, NOOP, QUIT};
  Parser();
  void  parse(Client *);
  ~Parser();
};

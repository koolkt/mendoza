#pragma once
#include        <iostream>

class           Client;
class           Parser
{
  bool          data(Client *client);
  bool          rcpt_to(Client *client);
  bool          mail_from(Client *client);
  bool          ehlo(Client *client);
  bool          helo(Client *client);
  bool          parse_mail(Client *client);
public:
  enum          State {START, HELO, MAIL,
                       RCPT, DATA, RSET,
                       VRFY, NOOP, QUIT};
  Parser();
  void  parse(Client *);
  ~Parser();
};

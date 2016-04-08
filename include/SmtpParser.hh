#pragma once
#include        <iostream>
#include        <regex>
#include        <string>
#include        <vector>

class           Client;
class           SmtpParser
{
  bool          data(Client *client);
  bool          rcpt_to(Client *client);
  bool          mail_from(Client *client);
  bool          ehlo(Client *client);
  bool          helo(Client *client);
  bool          parse_mail(Client *client);
  std::vector<std::string>*     get_adress(std::string s);
public:
  enum          State {START, HELO, MAIL,
                       RCPT, DATA, RSET,
                       VRFY, NOOP, QUIT, MAIL_PARSED};

  enum          Action {OK, END_DATA, BYE, NOT_IMP, MAIL_NA};

  SmtpParser();
  Action  parse(Client *);
  ~SmtpParser();
};

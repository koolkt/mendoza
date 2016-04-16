#pragma once
#include        <iostream>
#include        <regex>
#include        <string>
#include        <vector>
#include        <Client.hh>

class           SmtpClient;

class           SmtpParser
{
  bool          data(Client *client);
  bool          rcptTo(Client *client);
  bool          mailFrom(Client *client);
  bool          ehlo(Client *client);
  bool          helo(Client *client);
  bool          parseMail(Client *client);
  std::vector<std::string>*     getAdress(std::string s);
public:
  enum          State {START, HELO, MAIL,
                       RCPT, DATA, RSET,
                       VRFY, NOOP, QUIT, MAIL_PARSED};

  enum          Action {OK, END_DATA, BYE, NOT_IMP, MAIL_NA};

  SmtpParser();
  Action  parse(Client *);
  ~SmtpParser();
};

#pragma once
#include        <iostream>
#include        <regex>
#include        <string>
#include        <vector>

class           SmtpClient;
class           SmtpParser
{
  bool          data(SmtpClient *client);
  bool          rcpt_to(SmtpClient *client);
  bool          mail_from(SmtpClient *client);
  bool          ehlo(SmtpClient *client);
  bool          helo(SmtpClient *client);
  bool          parse_mail(SmtpClient *client);
  std::vector<std::string>*     get_adress(std::string s);
public:
  enum          State {START, HELO, MAIL,
                       RCPT, DATA, RSET,
                       VRFY, NOOP, QUIT, MAIL_PARSED};

  enum          Action {OK, END_DATA, BYE, NOT_IMP, MAIL_NA};

  SmtpParser();
  Action  parse(SmtpClient *);
  ~SmtpParser();
};

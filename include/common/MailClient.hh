#pragma once
#include        <Mail.hh>
#include        <string>

class           MailClient
{
  std::string           username;
  Mail                  mail;
  public:
  MailClient();
  Mail&                 getMail();
  std::string const&    getUsername() const;
  void                  setUsername(std::string);
  ~MailClient();
};

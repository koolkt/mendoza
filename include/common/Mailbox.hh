#pragma once
#include        <iostream>
#include        <Mail.hh>
#include        <algorithm>
#include        <set>
#include        <unordered_map>

class           Mailbox
{
  std::unordered_map<std::string, std::string > users;
  std::set<std::string> usernames;
public:
  Mailbox();
  bool         user_exists(Mail &mail);
  bool         auth_user(const std::string user, const std::string pass) const;
  bool         send_mail(Mail &mail);
  ~Mailbox();
};

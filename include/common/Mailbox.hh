#pragma once
#include        <iostream>
#include        <Mail.hh>
#include        <algorithm>
#include        <set>
#include        <unordered_map>
#include        <list>
#include        <functional>

typedef         std::unordered_map<std::string, std::list<std::string>* >* Mbmap;
class           Mailbox
{
  Mbmap        mailboxes;
  std::unordered_map<std::string, std::string > users;
  std::set<std::string> usernames;
public:
  Mailbox();
  std::string& get_mail(const std::string& user);
  std::list<std::string>&          number_new_mails(const std::string& user);
  bool         user_exists(Mail &mail);
  bool         auth_user(const std::string user, const std::string pass) const;
  bool         send_mail(Mail &mail);
  ~Mailbox();
};

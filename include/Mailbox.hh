#pragma once
#include        <iostream>
#include        <Mail.hh>

class           Mailbox
{
public:
  Mailbox();
  bool         user_exists(Mail &mail);

  bool         send_mail(Mail &mail);
  ~Mailbox();
};

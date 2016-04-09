#include        <Mailbox.hh>
#define UNUSED(x) (void)(x)
#include <algorithm>

Mailbox::Mailbox()
{
}

Mailbox::~Mailbox()
{
}

void            print(std::string& str)
{
  std::cout << "Dest: " << str << std::endl;
}

bool            Mailbox::user_exists(Mail &mail)
{
  for_each (mail.get_dest().begin(), mail.get_dest().end(), print);
  return true;
}

bool            Mailbox::send_mail(Mail &mail)
{
  UNUSED(mail);
  return true;
}

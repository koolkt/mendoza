#include        <Mailbox.hh>
#define UNUSED(x) (void)(x)

Mailbox::Mailbox()
{
}

Mailbox::~Mailbox()
{
}

bool            Mailbox::user_exists(Mail &mail)
{
  UNUSED(mail);
  return true;
}

bool            Mailbox::send_mail(Mail &mail)
{
  UNUSED(mail);
  return true;
}

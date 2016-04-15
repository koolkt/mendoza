#include        <MailClient.hh>

MailClient::MailClient()
{
}

Mail&                 MailClient::getMail()
{
  return this->mail;
}

std::string const&    MailClient::getUsername() const
{
  return this->username;
}

void                  MailClient::setUsername(std::string str)
{
  this->username = str;
}

MailClient::~MailClient()
{
}

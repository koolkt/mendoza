#include        <Mailbox.hh>
#define UNUSED(x) (void)(x)

Mailbox::Mailbox()
{
  Mbmap mbxs;
  std::string *user;
  std::string *pass;

  mbxs = new std::unordered_map<std::string, std::list<std::string> >;
  user = new std::string("kool@kool.com");
  pass = new std::string("koolkat");
  this->mailboxes = mbxs;
  this->usernames.insert(*user);
  this->usernames.insert(std::string("leopold@kwame.mendoza.epitech.eu"));
  this->users.insert(std::pair<std::string, std::string >(*user,*pass));
  this->mailboxes->insert(std::pair<std::string, std::list<std::string> >(*user, std::list<std::string>()));
  this->mailboxes->insert(std::pair<std::string, std::list<std::string> >(std::string("leopold@kwame.mendoza.epitech.eu"), std::list<std::string>()));
}

Mailbox::~Mailbox()
{
}

void            print(std::string& str)
{
  std::cout << "Dest: " << str << std::endl;
}

bool            Mailbox::auth_user(const std::string user, const std::string pass) const
{
  if((this->usernames.find(user) !=  this->usernames.end()) &&
     (this->users.at(user).compare(pass) == 0))
    return true;
  else
  return(false);
}

bool            Mailbox::user_exists(Mail &mail)
{
  for_each (mail.get_dest().begin(), mail.get_dest().end(), print);
  // return true;
  return (this->usernames.find(mail.get_dest().at(0)) !=  this->usernames.end());
}

bool            Mailbox::send_mail(Mail &mail)
{
  this->mailboxes->at(mail.get_dest().at(0)).push_back(mail.get_body());
  return true;
}

std::string&            Mailbox::get_mail(const std::string& user)
{
  std::string                   *m;
  std::list<std::string>        *mails;

  m = NULL;
  mails = &this->mailboxes->at(user);
  if(!mails->empty())
    {
      m = &mails->front();
      mails->pop_front();
    }
  return *m;
}

int            Mailbox::number_new_mails(const std::string& user)
{
  return this->mailboxes->at(user).size();
}

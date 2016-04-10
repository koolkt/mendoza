#include        <Mailbox.hh>
#define UNUSED(x) (void)(x)

Mailbox::Mailbox()
{
  std::string *user;
  std::string *pass;

  user = new std::string("kool@kool.com");
  pass = new std::string("koolkat");
  this->usernames.insert(*user);
  this->users.insert(std::pair<std::string, std::string >(*user,*pass));
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
  // UNUSED(user);
  // UNUSED(pass);
  std::cout << "USER PASS:  " << user << pass << std::endl;
  if((this->usernames.find(user) !=  this->usernames.end()) &&
     (this->users.at(user).compare(pass) == 0))
    return true;
  else
  return(false);
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

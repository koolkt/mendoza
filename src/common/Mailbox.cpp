#include        <Mailbox.hh>
#define UNUSED(x) (void)(x)

Mailbox::Mailbox()
{
  std::string *user;
  std::string *pass;
  std::string *user2;
  std::string *pass2;

  user2 = new std::string("leopold@kwame.mendoza.epitech.eu");
  pass2 = new std::string("test");
  user = new std::string("kool@kool.com");
  pass = new std::string("koolkat");
  this->mailboxes = new std::unordered_map<std::string, std::list<std::string>* >;
  this->usernames.insert(*user);
  this->usernames.insert(*user2);
  this->users.insert(std::pair<std::string, std::string >(*user,*pass));
  this->users.insert(std::pair<std::string, std::string >(*user2,*pass2));
  this->mailboxes->insert(std::pair<std::string, std::list<std::string>* >(*user, (new std::list<std::string>())));
  this->mailboxes->insert(std::pair<std::string, std::list<std::string>* >(*user2, (new std::list<std::string>())));
  this->mailboxes->at(std::string("kool@kool.com"))->push_back("hello world");
  this->mailboxes->at(std::string("kool@kool.com"))->push_back("hello world");
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
  this->mailboxes->at(mail.get_dest().at(0))->push_back(mail.get_body());
  return true;
}

std::string&            Mailbox::get_mail(const std::string& user)
{
  std::string                   *m;
  std::list<std::string>        *mails;

  m = NULL;
  mails = this->mailboxes->at(user);
  if(!mails->empty())
    {
      m = &mails->front();
      mails->pop_front();
    }
  return *m;
}

std::list<std::string>&         Mailbox::number_new_mails(const std::string& user)
{
  // std::list<std::string>*       res;

  auto res = new std::list<std::string>(2);
  auto t = this->mailboxes->find(user);
  if (t == this->mailboxes->end()) return *res;
  std::cout << "User Found: " << this->mailboxes->at(user)->size() << " new mails"<<std::endl;
  std::transform(this->mailboxes->at(user)->begin(),
                 this->mailboxes->at(user)->end(),
                 res->begin(),
                 [](const std::string& mail) {
                   std::cout << "size: " << mail.size()<< std::endl;
                   return std::to_string(mail.size());
                 });
  std::cout << "final list size: " << res->size() << std::endl;
  return *res;
}

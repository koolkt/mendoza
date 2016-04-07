#include        <Mail.hh>
#define UNUSED(x) (void)(x)

Mail::Mail()
{
  this->dest = NULL;
}

void            Mail::set_dest(std::vector<std::string>* d)
{
  this->dest = d;
}

void            Mail::set_body(const std::string& str)
{
  this->body = str;
}

void            Mail::reset()
{
  if (this->dest)
    delete this->dest;
  this->dest = NULL;
}

std::vector<std::string>&  Mail::get_dest()
{
  return *this->dest;
}

std::string&               Mail::get_body()
{
  return this->body;
}


Mail::~Mail()
{
}

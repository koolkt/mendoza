#include                <Client.hh>
#define UNUSED(x) (void)(x)

Client::Client()
{
}

void            Client::set_socket(int fd)
{
  this->socket = Socket(fd);
}

int             Client::get_fd() const
{
  return(this->socket.socket_fd);
}

void            Client::send_message(const char *msg)
{
  this->socket.ssend(std::string(msg));
}

void            Client::send_message(std::string& msg)
{
  this->socket.ssend(msg);
}

Mail&          Client::get_mail()
{
  return this->mail;
}

std::string const&  Client::get_data()
{
  this->socket.srecv(this->buffer, 4096);
  return(this->buffer);
}

std::string const&  Client::get_username() const
{
  return(this->username);
}

void  Client::set_username(std::string u)
{
  this->username = u;
}

SmtpParser::State const & Client::get_last_state() const
{
  return(*(new SmtpParser::State));
}

void            Client::set_state(SmtpParser::State new_state)
{
  UNUSED(new_state);
  return;
}

PopParser::State const & Client::getp_last_state() const
{
  return(*(new PopParser::State));
}

void            Client::setp_state(PopParser::State new_state)
{
  UNUSED(new_state);
  return;
}

Client::~Client()
{
}

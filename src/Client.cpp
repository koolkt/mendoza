#include                <Client.hh>

Client::Client()
{
  this->last_state = SmtpParser::START;
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

SmtpParser::State const & Client::get_last_state() const
{
  return(this->last_state);
}

void            Client::set_state(SmtpParser::State new_state)
{
  this->last_state = new_state;
}

Client::~Client()
{
}

#include                <Client.hh>

Client::Client()
{
  this->last_state = Parser::START;
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


std::string const&  Client::get_data()
{
  this->socket.srecv(this->buffer, 4096);
  return(this->buffer);
}

Parser::State const & Client::get_last_state() const
{
  return(this->last_state);
}

void            Client::set_state(Parser::State new_state)
{
  this->last_state = new_state;
}

Client::~Client()
{
}

#include                <Client.hh>

Client::Client()
{
}

void          Client::set_socket(int fd)
{
  this->socket = Socket(fd);
}

int           Client::get_fd() const
{
  return(this->socket.socket_fd);
}

std::string const&  Client::get_data() const
{
  return(this->buffer);
}

void            Client::set_state(Parser::State new_state)
{
  this->last_state = new_state;
}

Client::~Client()
{
}

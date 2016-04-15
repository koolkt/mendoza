#include                <Client.hh>

Client::Client()
{
}

void            Client::setSocket(int fd)
{
  this->socket = Socket(fd);
}

void            Client::setInfo(void* info)
{
  this->info = info;
}

void*            Client::getInfo() const
{
  return this->info;
}

int             Client::getFd() const
{
  return(this->socket.socket_fd);
}

void            Client::send(const char *msg)
{
  this->socket.ssend(std::string(msg));
}

void            Client::send(std::string& msg)
{
  this->socket.ssend(msg);
}

std::string const&  Client::rcv()
{
  this->socket.srecv(this->buffer, 4096);
  return(this->buffer);
}

Client::~Client()
{
}

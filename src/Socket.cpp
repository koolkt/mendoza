#include                <Socket.hh>

Socket::Socket()
{
  try
    {
      create_socket();
    }
  catch(std::exception& e)
    {
      std::cout << "Standard exception: " << e.what() << std::endl;
    }
  return;
}

Socket::Socket(int fd)
{
  this->socket_fd = fd;
}


Socket& Socket::operator=(const Socket &rhs)
{
  if (this == &rhs)
    return *this;
  this->socket_fd = rhs.socket_fd;
  return *this;
}

int                    Socket::create_socket()
{
  struct protoent		*s_p;

  s_p = getprotobyname("TCP");
  if(s_p == NULL)
    {
      return(EXIT_FAILURE);
    }
  this->socket_fd = socket(AF_INET, SOCK_STREAM, s_p->p_proto);
  if(this->socket_fd < 0)
    {
      return(EXIT_FAILURE);
    }
  std::cout << "Socket created" << std::endl;
  return (EXIT_SUCCESS);
}

bool                    Socket::connectToServer(std::string const & host, short const port)
{
  struct sockaddr_in    address;

  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  inet_pton(AF_INET, host.c_str(), &address.sin_addr);
  if(connect(this->socket_fd, (struct sockaddr *)&address, sizeof(address)))
    return (false);
  else
    return (true);
}

int                   Socket::srecv(std::string& buffer, int const blocksize, int fd)
{
  char                  b[blocksize];
  ssize_t               br;

  br = recv(fd, b, blocksize-1,0);
  b[br] = '\0';
  buffer = std::string(b);
  return (br);
}

int                   Socket::srecv(std::string& buffer, int const blocksize)
{
  char                  b[blocksize];
  ssize_t               br;

  br = recv(this->socket_fd, b, blocksize-1,0);
  if (br <= 0)
    return(br);
  b[br] = '\0';
  buffer = std::string(b);
  return (br);
}

int                   Socket::ssend(std::string const & data)
{
  int                   sent;

  sent = send(this->socket_fd, data.c_str(), data.length(),0);
  return (sent);
}

Socket::~Socket()
{
}

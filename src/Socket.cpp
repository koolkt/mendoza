#include                <Socket.hh>

char                    Socket::create_socket()
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

Socket::Socket()
{
  create_socket();
}

Socket::Socket(int fd)
{
  this->socket_fd = fd;
}

bool                  Socket::connectToServer(std::string const & host, short const port)
{
  return (true);
}

int                   Socket::srecv(std::string& buffer, int const blocksize)
{
  char                  b[blocksize];
  ssize_t               br;
  ssize_t               total_br;

  // br = 1;
  // total_br = 0;
  // while (br != 0 && total_br < (blocksize-1))
  //   {
  //     br = recv(this->socket_fd, b+total_br, blocksize-total_br-1,0);
  //     total_br += br;
  //   }
  br = recv(this->socket_fd, b, blocksize-1,0);
  b[br] = '\0';
  buffer = std::string(b);
  std::cout << buffer;
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

#include                <ServerSocket.hh>

ServerSocket::ServerSocket()
{
}

char                    ServerSocket::create_socket()
{
  int                           reuse;
  struct protoent		*s_p;

  reuse = 1;
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
  if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR,
                 (const char*)&reuse, sizeof(int)) < 0)
    {
      return (EXIT_FAILURE);
    }
#ifdef SO_REUSEPORT
  if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEPORT,
                 (const char*)&reuse, sizeof(reuse)) < 0)
    {
      return (EXIT_FAILURE);
    }
#endif
  return (EXIT_SUCCESS);
}

char                    ServerSocket::dbind()
{
  int				result;

  this->size = sizeof(this->s_in);
  memset(&this->s_in, 0, this->size);
  this->s_in.sin_family = AF_INET;
  this->s_in.sin_port = htons(this->port);
  this->s_in.sin_addr.s_addr = htonl(INADDR_ANY);
  result = bind(this->socket_fd, (struct sockaddr *)&this->s_in, this->size);
  if(result < 0)
    {
      close(this->socket_fd);
      return(EXIT_FAILURE);
    }
  std::cout << "Socket bind completed" << std::endl;
  return (EXIT_SUCCESS);
}

char                    ServerSocket::dlisten()
{
  int				result;

  result = listen(this->socket_fd, SOMAXCONN);
  if(result < 0)
    {
      close(this->socket_fd);
      return(EXIT_FAILURE);
    }
  std::cout << "Socket bind listening on port " << this->port << std::endl;
  return (EXIT_SUCCESS);
}

bool ServerSocket::init(short const listenPort)
{
  this->port = listenPort;
  if ((this->create_socket())
      || this->dbind()
      || this->dlisten())
    {
      std::cout << "Socket error" << std::endl;
      return (false);
    }
  return (true);
}

int                 ServerSocket::daccept()
{
  int                   accepted_fd;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  client_sin_len = sizeof(client_sin);
  // accepted_fd = accept(this->socket_fd, (struct sockaddr *)&client_sin,
  //                    &client_sin_len);
  accepted_fd = accept4(this->socket_fd, (struct sockaddr *)&client_sin,
                        &client_sin_len, SOCK_NONBLOCK);
  return accepted_fd;
}

ServerSocket::~ServerSocket()
{
}

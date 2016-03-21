#include                <Serversocket.hh>

Serversocket::Serversocket()
{
}

char                    Serversocket::create_socket()
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

char                    Serversocket::dbind()
{
  int				result;

  this->size = sizeof(this->s_in);
  memset(&this->s_in, 0, this->size);
  this->s_in.sin_family = AF_INET;
  this->s_in.sin_port = htons(this->port);
  this->s_in.sin_addr.s_addr = INADDR_ANY;
  result = bind(this->socket_fd, (struct sockaddr *)&this->s_in, this->size);
  if(result < 0)
    {
      close(this->socket_fd);
      return(EXIT_FAILURE);
    }
  std::cout << "Socket bind completed" << std::endl;
  return (EXIT_SUCCESS);
}

char                    Serversocket::dlisten()
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

bool Serversocket::init(short const listenPort)
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

Socket*                 Serversocket::daccept()
{
  int                   accepted_fd;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  client_sin_len = sizeof(client_sin);
  accepted_fd = accept(this->socket_fd, (struct sockaddr *)&client_sin,
                     &client_sin_len);
  // accepted_fd = accept4(this->socket_fd, (struct sockaddr *)&client_sin,
  //                       &client_sin_len, SOCK_NONBLOCK);
  return new Socket(accepted_fd);
}

Serversocket::~Serversocket()
{
}

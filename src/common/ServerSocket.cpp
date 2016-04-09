#include                <ServerSocket.hh>
#include                <ErrorCheck.hh>

ServerSocket::ServerSocket()
{
}

void                    ServerSocket::create_socket()
{
  int                   reuse;
  struct protoent       *s_p;

  reuse = 1;
  s_p = getprotobyname("TCP");
  ErrorCheck::check(s_p != NULL, "create_socket: getprotobyname");
  this->socket_fd = socket(AF_INET, SOCK_STREAM, s_p->p_proto);
  ErrorCheck::check(this->socket_fd > 0, "create_socket: socket");
  ErrorCheck::check(setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR,
                 (const char*)&reuse, sizeof(int)) >= 0, "create_socket: setsockopt");
#ifdef SO_REUSEPORT
  ErrorCheck::check(setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEPORT,
                 (const char*)&reuse, sizeof(reuse)) >= 0, "create_socket: setsockopt");
#endif
  return;
}

void                    ServerSocket::dbind()
{
  this->size = sizeof(this->s_in);
  memset(&this->s_in, 0, this->size);
  this->s_in.sin_family = AF_INET;
  this->s_in.sin_port = htons(this->port);
  this->s_in.sin_addr.s_addr = htonl(INADDR_ANY);
  ErrorCheck::check(bind(this->socket_fd,
             (struct sockaddr *)&this->s_in,
             this->size) >= 0, "dbind: bind");
  return;
}

void                    ServerSocket::dlisten()
{
  ErrorCheck::check(listen(this->socket_fd, SOMAXCONN) >= 0,"dlisten: listen");
  return;
}

void                    ServerSocket::init(short const listenPort)
{
  try
    {
      this->port = listenPort;
      this->create_socket();
      this->dbind();
      this->dlisten();
    }
  catch (std::exception& e)
    {
      std::perror("Perror");
      std::cerr << e.what() << std::endl;
      exit(1);
    }
  return;
}

int                     ServerSocket::daccept()
{
  int                   accepted_fd;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  client_sin_len = sizeof(client_sin);
  accepted_fd = accept4(this->socket_fd, (struct sockaddr *)&client_sin,
                        &client_sin_len, SOCK_NONBLOCK);
  ErrorCheck::check(accepted_fd > 0, "daccept: accept4");
  return accepted_fd;
}

ServerSocket::~ServerSocket()
{
  if (this->socket_fd > 0)
    close(this->socket_fd);
}

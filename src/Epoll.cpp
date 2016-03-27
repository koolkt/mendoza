#include                <Epoll.hh>
#include                <Socket.hh>

Epoll::Epoll():
  server_socket(NULL)
{
}

Epoll::~Epoll()
{
  if (this->events)
    free(this->events);
}

int                     Epoll::add_fd(int fd)
{
  int                   r;

  this->event.events = EPOLLIN | EPOLLRDHUP;
  this->event.data.fd = fd;
  r = epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, fd, &this->event);
  if (r != 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int                     Epoll::delete_fd(int fd)
{
  int                   r;

  r = epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, fd, &this->event);
  if (r != 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int			Epoll::add_server_socket()
{
  this->event.data.fd = this->server_socket->socket_fd;
  this->event.events = EPOLLIN;
  epoll_ctl (this->epoll_fd, EPOLL_CTL_ADD, this->event.data.fd, &this->event);
  return (EXIT_SUCCESS);
}

int			Epoll::init(Serversocket& _socket)
{
  this->server_socket = &_socket;
  this->epoll_fd = epoll_create1(0);
  if (this->epoll_fd == -1)
    return(EXIT_FAILURE);
  this->events = (epoll_event*)calloc(MAXEVENTS, sizeof(this->event));
  if (this->events == NULL)
    return(EXIT_FAILURE);
  add_server_socket();
  return (EXIT_SUCCESS);
}

int             Epoll::accept_new_client()
{
  int                   socket_fd;
  int                   r;

  this->event.events = EPOLLIN | EPOLLRDHUP;
  socket_fd = this->server_socket->daccept();
  this->event.data.fd = socket_fd;
  r = epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, socket_fd, &this->event);
  return (r);
}

int            Epoll::handle_read(int fd)
{
  if (INCOMMING_CONNECTION)
    {
      this->accept_new_client();
    }
  else
    return(fd);
  return (EXIT_SUCCESS);
}

int            Epoll::handle_error(int fd)
{
  this->delete_fd(fd);
  return(-1);
}

int		Epoll::wait()
{
  int		nevents;

  nevents = epoll_wait (this->epoll_fd, this->events, MAXEVENTS, -1);
  for(int i = 0; i < nevents; ++i)
    {
      if (FD_HAS_ERROR_OR_DISCONNECT)
        return(handle_error(this->events[i].data.fd));
      else if (FD_IS_READY_FOR_READ)
        return(handle_read(this->events[i].data.fd));
      else if (FD_IS_READY_FOR_WRITE)
        this->events[i].data.fd;
      else
        std::cout << "WTF" << std::endl;
    }
  return (EXIT_SUCCESS);
}

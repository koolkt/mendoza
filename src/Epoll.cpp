#include                <Epoll.hh>
#include                <Socket.hh>

Epoll::Epoll():
  server_socket(NULL)
{
  this->new_events = Events(4, std::vector<int>(MAXEVENTS + 1));
}

Epoll::~Epoll()
{
  if (this->events)
    free(this->events);
}

int                     Epoll::add_fd(int const fd)
{
  int                   r;

  this->event.events = EPOLLIN | EPOLLRDHUP;
  this->event.data.fd = fd;
  r = epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, fd, &this->event);
  if (r != 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int                     Epoll::delete_fd(int const fd)
{
  int                   r;

  r = epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, fd, &this->event);
  if (r != 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int			Epoll::add_server_socket()
{
  memset(&this->event,0,sizeof(struct epoll_event));
  this->event.data.fd = this->server_socket->socket_fd;
  this->event.events = EPOLLIN;
  epoll_ctl (this->epoll_fd, EPOLL_CTL_ADD, this->event.data.fd, &this->event);
  return (EXIT_SUCCESS);
}

int			Epoll::init(ServerSocket& _socket)
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

int            Epoll::handle_read(int const fd)
{
  if (INCOMMING_CONNECTION)
    {
      this->accept_new_client();
    }
  else
    {
      this->new_events[Epoll::READ_EVENTS].push_back(fd);
    }
  return (EXIT_SUCCESS);
}

int            Epoll::handle_error(int const fd)
{
  this->delete_fd(fd);
  return(-1);
}

void		Epoll::wait()
{
  int           fd;
  int		nevents;

  this->new_events[Epoll::READ_EVENTS].clear();
  this->new_events[Epoll::WRITE_EVENTS].clear();
  this->new_events[Epoll::ERROR_EVENTS].clear();
  nevents = epoll_wait (this->epoll_fd, this->events, MAXEVENTS, -1);
  for(int i = 0; i < nevents; ++i)
    {
      fd = this->events[i].data.fd;
      if (FD_HAS_ERROR_OR_DISCONNECT)
        this->new_events[Epoll::ERROR_EVENTS].push_back(fd);
      else if (FD_IS_READY_FOR_READ)
        handle_read(fd);
      else if (FD_IS_READY_FOR_WRITE)
        this->new_events[Epoll::WRITE_EVENTS].push_back(fd);
    }
  return;
}

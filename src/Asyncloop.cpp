#include                <AsyncLoop.hh>

AsyncLoop::AsyncLoop(int fd):
  listenfd(fd)
{
}

AsyncLoop::~AsyncLoop()
{
  if (this->events)
    free(this->events);
}

int                     AsyncLoop::read_event(int fd)
{
  int			infd;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  if (fd == this->listen_fd)
    {
      client_sin_len = sizeof(client_sin);
      infd = accept4(this->listen_fd, (struct sockaddr *)&client_sin,
		     &client_sin_len, SOCK_NONBLOCK);
      write(infd, "BIENVENUE\n", 10);
      epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, infd, &this->event);
    }
  this->read_handler->handle(fd);
  std::cout << "Read event" << std::endln;
  return (EXIT_SUCCESS);
}

int                     AsyncLoop::write_event(int fd)
{
  std::cout << "Write event" << std::endln;
  return(0);
}

int			AsyncLoop::error_event(int fd)
{
  std::cout << "Error receved" << std::endln;
  epoll_ctl (this->epoll_fd, EPOLL_CTL_DEL, fd, &this->event);
  return (EXIT_SUCCESS);
}


int			AsyncLoop::add_server_socket()
{
  epoll->event.data.fd = listenfd;
  epoll->event.events = EPOLLIN;
  epoll_ctl (this->epoll_fd, EPOLL_CTL_ADD, this->listen_fd, &this->event);
  return (EXIT_SUCCESS);
}

char			AsyncLoop::init_epoll()
{
  epoll->epoll_fd = epoll_create1(0);
  if (epoll->epoll_fd == -1)
    return(EXIT_FAILURE);
  this->events = calloc(MAXEVENTS, sizeof(epoll->event));
  if (epoll->events == NULL)
    return(EXIT_FAILURE);
  add_server_socket();
  return (EXIT_SUCCESS);
}

char		AsyncLoop::poll_for_client_events(void)
{
  int		nevents;

  while(is_running)
    {
      nevents = epoll_wait (this->epoll->efd, this->epoll->events, MAXEVENTS, -1);
      for(int i = 0; i < nevents; ++i)
	{
	  if (FD_HAS_ERROR_OR_DISCONNECT)
	    this->error_event(this->epoll->events[i].fd);
	  else if (FD_IS_READY_FOR_READ)
	    this->read_event(this->epoll->events[i].fd);
	  else if (FD_IS_READY_FOR_WRITE)
	    this->write_event(this->epoll->events[i].fd);
	}
    }
  return (EXIT_SUCCESS);
}

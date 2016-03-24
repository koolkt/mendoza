#include                <AsyncLoop.hh>
#include                <Socket.hh>
AsyncLoop::AsyncLoop(Serversocket& _socket):
  server_socket(_socket)
{
  this->is_running = 0;
}

AsyncLoop::~AsyncLoop()
{
  if (this->events)
    free(this->events);
}

int                     AsyncLoop::init()
{
  init_epoll();
}

int                     AsyncLoop::run()
{
  poll_for_client_events();
}

int                     AsyncLoop::read_event(int fd)
{
  int                   rcvd;
  int                   r;
  int			infd;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;
  Socket                *in_socket;
  std::string           buffer;

  in_socket = NULL;
  rcvd = 0;
  if (fd == this->server_socket.socket_fd)
    {
      this->event.events = EPOLLIN | EPOLLRDHUP;
      client_sin_len = sizeof(client_sin);
      in_socket = this->server_socket.daccept();
      this->event.data.fd = in_socket->socket_fd;
      r = epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, in_socket->socket_fd, &this->event);
      std::cout << "New client connected " << r << infd << std::endl;
    }
  //this->read_handler->handle(fd);
  else
  {
    rcvd = Socket::srecv(buffer, 1000000, fd); /////////////////// ATENTION!! in_socket only exists the first time the client connects. After that it is collected.
    std::cout << fd << ": "<< buffer << "receved: " << rcvd << std::endl;
  }
  //std::cout << "Read event "<< std::endl;
  return (EXIT_SUCCESS);
}

int                     AsyncLoop::write_event(int fd)
{
  std::cout << "Write event" << std::endl;
  return(0);
}

int			AsyncLoop::error_event(int fd)
{
  int r;
  r = epoll_ctl (this->epoll_fd, EPOLL_CTL_DEL, fd, &this->event);
    std::cout << "Error receved " << r << std::endl;
  return (EXIT_SUCCESS);
}


int			AsyncLoop::add_server_socket()
{
  this->event.data.fd = this->server_socket.socket_fd;
  this->event.events = EPOLLIN;
  epoll_ctl (this->epoll_fd, EPOLL_CTL_ADD, this->event.data.fd, &this->event);
  return (EXIT_SUCCESS);
}

int			AsyncLoop::init_epoll()
{
  this->epoll_fd = epoll_create1(0);
  if (this->epoll_fd == -1)
    return(EXIT_FAILURE);
  this->events = (epoll_event*)calloc(MAXEVENTS, sizeof(this->event));
  if (this->events == NULL)
    return(EXIT_FAILURE);
  add_server_socket();
  this->is_running = 1;
  return (EXIT_SUCCESS);
}

int		AsyncLoop::poll_for_client_events(void)
{
  int		nevents;

  while(this->is_running)
    {
      nevents = epoll_wait (this->epoll_fd, this->events, MAXEVENTS, -1);
      for(int i = 0; i < nevents; ++i)
	{
	  if (FD_HAS_ERROR_OR_DISCONNECT)
	    this->error_event(this->events[i].data.fd);
	  else if (FD_IS_READY_FOR_READ)
	    this->read_event(this->events[i].data.fd);
	  else if (FD_IS_READY_FOR_WRITE)
	    this->write_event(this->events[i].data.fd);
          else
            std::cout << "WTF" << std::endl;
	}
    }
  return (EXIT_SUCCESS);
}

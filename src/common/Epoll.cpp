#include                <Epoll.hh>
#include                <Socket.hh>

Epoll::Epoll():
  server_socket(NULL)
{
  this->new_events = Events(5, std::vector<Client*>(MAXEVENTS + 1));
}

Epoll::~Epoll()
{
  if (this->events)
    free(this->events);
}

int                     Epoll::add_client(Client *client)
{
  int                   r;

  r = epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, client->get_fd(), &this->event);
  if (r != 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int                     Epoll::delete_client(Client *client)
{
  int                   r;

  std::cout << "Deleting client" << std::endl;
  r = epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, client->get_fd(), &this->event);
  delete client;
  if (r != 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

void                    Epoll::init_event_struct(void *data, __uint32_t flags)
{
  memset(&this->event,0,sizeof(struct epoll_event));
  this->event.data.ptr = data;
  this->event.events = flags;
  return;
}

int                     Epoll::listen_new_client(int fd, __uint32_t flags)
{
  Client                *client;

  client = new Client();
  init_event_struct((void*)client, flags);
  client->set_socket(fd);
  add_client(client);
  this->new_events[Epoll::NEW_CONN].push_back(client);
  return (0);
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
  listen_new_client(this->server_socket->socket_fd, EPOLLIN);
  return (EXIT_SUCCESS);
}

int                     Epoll::handle_read(Client *client)
{
  int                   new_client_fd;
  int                   server_s;
  int                   incomming_s;

  incomming_s = client->get_fd();
  server_s = this->server_socket->socket_fd;
  if (server_s == incomming_s)
    {
      new_client_fd = this->server_socket->daccept();
      this->listen_new_client(new_client_fd, EPOLLIN | EPOLLRDHUP);
    }
  else
    {
      this->new_events[Epoll::READ_EVENTS].push_back(client);
    }
  return (EXIT_SUCCESS);
}

int                     Epoll::handle_error(Client *client)
{
  this->delete_client(client);
  return(-1);
}

void                    Epoll::wait()
{
  Client                *client;
  int                   nevents;

  this->new_events[Epoll::READ_EVENTS].clear();
  this->new_events[Epoll::WRITE_EVENTS].clear();
  this->new_events[Epoll::ERROR_EVENTS].clear();
  this->new_events[Epoll::NEW_CONN].clear();
  nevents = epoll_wait (this->epoll_fd, this->events, MAXEVENTS, -1);
  for(int i = 0; i < nevents; ++i)
    {
      client = (Client*)this->events[i].data.ptr;
      if (FD_HAS_ERROR_OR_DISCONNECT)
        this->new_events[Epoll::ERROR_EVENTS].push_back(client);
      else if (FD_IS_READY_FOR_READ)
        handle_read(client);
      else if (FD_IS_READY_FOR_WRITE)
        this->new_events[Epoll::WRITE_EVENTS].push_back(client);
    }
  return;
}

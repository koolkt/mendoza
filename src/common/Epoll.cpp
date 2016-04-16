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

int                     Epoll::addClient(int fd)
{
  int                   r;

  r = epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, fd, &this->event);
  if (r != 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int                     Epoll::deleteClient(Client *client)
{
  int                   r;

  std::cout << "Deleting client" << std::endl;
  r = epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, client->getFd(), NULL);
  if (client)
   delete client;
  if (r != 0)
    perror("Epoll Delete Client");
  return (EXIT_SUCCESS);
}

void                    Epoll::initEventStruct(void *data, __uint32_t flags)
{
  memset(&this->event,0,sizeof(struct epoll_event));
  this->event.data.ptr = data;
  this->event.events = flags;
  return;
}

int                     Epoll::listenNewClient(int fd, __uint32_t flags)
{
  Client                *client;

  std::cout << "New client" << fd << std::endl;
  client = new Client();
  initEventStruct((void*)client, flags);
  client->setSocket(fd);
  addClient(client->getFd());
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
  initEventStruct(NULL, EPOLLIN);
  addClient(this->server_socket->socket_fd);
  return (EXIT_SUCCESS);
}

int                     Epoll::handleRead(Client *client)
{
  int                   new_client_fd;

  if (client == NULL)
    {
      new_client_fd = this->server_socket->daccept();
      this->listenNewClient(new_client_fd, EPOLLIN | EPOLLRDHUP);
    }
  else
    {
      this->new_events[Epoll::READ_EVENTS].push_back(client);
    }
  return (EXIT_SUCCESS);
}

int                     Epoll::handleError(Client *client)
{
  this->deleteClient(client);
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
        handleRead(client);
      else if (FD_IS_READY_FOR_WRITE)
        this->new_events[Epoll::WRITE_EVENTS].push_back(client);
    }
  return;
}

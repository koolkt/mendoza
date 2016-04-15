#pragma                 once
#define                 MAXEVENTS 64
#define                 FD_IS_READY_FOR_READ this->events[i].events & EPOLLIN
#define                 FD_HAS_ERROR_OR_DISCONNECT this->events[i].events & (EPOLLHUP | EPOLLERR | EPOLLRDHUP)
#define                 FD_IS_READY_FOR_WRITE this->events[i].events & EPOLLOUT
#include		<stdbool.h>
#include		<sys/epoll.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<arpa/inet.h>
#include		<signal.h>
#include                <EventHandler.hh>
#include                <iostream>
#include                <cstdlib>
#include                <ServerSocket.hh>
#include                <vector>
#include                <map>
#include                <string>
#include                <Client.hh>

typedef  std::vector<std::vector<Client*> > Events;

class                   Epoll
{
  struct epoll_event	event;
  struct epoll_event	*events;
  int			epoll_fd;
  ServerSocket		*server_socket;
  int                   handleRead(Client *);
  int                   handleError(Client *);
  int                   listenNewClient(int fd, __uint32_t flags);
  void                  initEventStruct(void *data, __uint32_t flags);
  public:
  enum                  EType {WRITE_EVENTS, READ_EVENTS, ERROR_EVENTS, NEW_CONN};
  Epoll();
  Events                new_events;
  int                   deleteClient(Client*);
  int                   addClient(Client*);
  int                   init(ServerSocket& socket);
  void                  wait();
  ~Epoll();
};

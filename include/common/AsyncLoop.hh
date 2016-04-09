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
#include                <Serversocket.hh>

class                   Epoll
{
  struct epoll_event	event;
  struct epoll_event	*events;
  int			epoll_fd;
  Serversocket		server_socket;
  int                   add_server_socket();
  public:
                        Epoll();
  int                   delete_fd(int fd);
  int                   add_fd(int fd);
  int                   init(Serversocket& socket);
  int                   wait();
  ~Epoll();
};

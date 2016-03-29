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
#define                 INCOMMING_CONNECTION fd == this->server_socket->socket_fd

typedef  std::vector<std::vector<int> > Events;

class                   Epoll
{
  struct epoll_event	event;
  struct epoll_event	*events;
  int			epoll_fd;
  ServerSocket		*server_socket;
  int                   handle_read(int const fd);
  int                   handle_error(int const fd);
  int                   accept_new_client();
  int                   add_server_socket();
  public:
  enum                  EType {WRITE_EVENTS, READ_EVENTS, ERROR_EVENTS};
  Epoll();
  Events                new_events;
  int                   delete_fd(int const fd);
  int                   add_fd(int const fd);
  int                   init(ServerSocket& socket);
  void                  wait();
  ~Epoll();
};

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

class                   AsyncLoop
{
  bool                  is_running;
  struct epoll_event	event;
  struct epoll_event	*events;
  int			epoll_fd;
  Serversocket		server_socket;
  EventHandler          *write_handler;
  EventHandler          *read_handler;
  EventHandler          *error_handler;
  int                   read_event(int fd);
  int                   write_event(int fd);
  int                   error_event(int fd);
  int                   poll_for_client_events();
  int                   init_epoll();
  int                   add_server_socket();
  public:
  AsyncLoop(Serversocket& socket);
  int init();
  int run();
  ~AsyncLoop();
};

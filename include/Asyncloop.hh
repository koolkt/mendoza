#pragma                 once
#define                 MAXEVENTS 64
#define                 FD_IS_READY_FOR_READ Sepoll->events[i].events & EPOLLIN
#define                 FD_HAS_ERROR_OR_DISCONNECT Sepoll->events[i].events & (EPOLLHUP | EPOLLERR | EPOLLRDHUP)
#define                 FD_IS_READY_FOR_WRITE Sepoll->events[i].events & EPOLLOUT
#include		<stdbool.h>
#include		<sys/epoll.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<arpa/inet.h>
#include		<signal.h>
#include                <EventHandler.hh>

class                   AsyncLoop
{
  struct epoll_event	event;
  struct epoll_event	*events;
  int			epoll_fd;
  int                   listen_fd;
  EventHandler          *write_handler;
  EventHandler          *read_handler;
  EventHandler          *error_handler;
  public:
  AsyncLoop();
  init();
  run();
  ~AsyncLoop();
}

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
#define                 INCOMMING_CONNECTION fd == this->server_socket->socket_fd

class                   Epoll
{
  struct epoll_event	event;
  struct epoll_event	*events;
  int			epoll_fd;
  ServerSocket		*server_socket;
  int                   handle_read(int fd);
  int                   handle_error(int fd);
  int                   accept_new_client();
  int                   add_server_socket();
  public:
                        Epoll();
  int                   delete_fd(int fd);
  int                   add_fd(int fd);
  int                   init(ServerSocket& socket);
  int                   wait();
  ~Epoll();
};

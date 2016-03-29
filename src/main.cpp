#include <iostream>
#include <ServerSocket.hh>
#include <Epoll.hh>

int             main(int argc, char **argv)
{
  int           port;
  ServerSocket  *Server;
  Epoll         *loop;
  Events           fd;

  if (argc != 2)
    return(0);
  port = atoi(argv[1]);
  Server = new ServerSocket();
  Server->init(port);
  loop = new Epoll();
  loop->init(*Server);
  while (42)
    {
      fd = loop->wait();
    }
  delete Server;
  return (0);
}

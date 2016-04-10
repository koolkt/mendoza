#include <iostream>
#include <ServerSocket.hh>
#include <Epoll.hh>
#include <algorithm>
#include <PopServer.hh>

int             main(int argc, char **argv)
{
  PopServer    *Server;
  int           port;

  if (argc != 2)
    return(0);
  port = atoi(argv[1]);
  Server = new PopServer(port);
  Server->run();
  return (0);
}

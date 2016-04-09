#include <iostream>
#include <ServerSocket.hh>
#include <Epoll.hh>
#include <algorithm>
#include <SmtpServer.hh>

int             main(int argc, char **argv)
{
  SmtpServer    *Server;
  int           port;

  if (argc != 2)
    return(0);
  port = atoi(argv[1]);
  Server = new SmtpServer(port);
  Server->run();
  return (0);
}

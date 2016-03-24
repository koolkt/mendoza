#include <iostream>
#include <Serversocket.hh>
#include <AsyncLoop.hh>

int             main(int argc, char **argv)
{
  int           port;
  int           br;
  std::string   buffer;
  int           s;
  Socket        *Socket;
  Serversocket  *Server;
  AsyncLoop     *loop;

  br = 1;
  if (argc != 2)
    return(0);
  port = atoi(argv[1]);
  Server = new Serversocket();
  Server->init(port);
  loop = new AsyncLoop(*Server);
  loop->init();
  loop->run();
  return (0);
}

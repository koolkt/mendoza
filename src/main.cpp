#include <iostream>
#include <Serversocket.hh>

int             main(int argc, char **argv)
{
  int           port;
  int           br;
  std::string   buffer;
  int           s;
  Socket        *Socket;
  Serversocket  *Server;

  br = 1;
  if (argc != 2)
    return(0);
  port = atoi(argv[1]);
  Server = new Serversocket();
  Server->init(port);
  Socket = Server->daccept();
  while (br > 0)
    {
      br = Socket->srecv(buffer,1024);
      std::cout << "echoing "<< buffer << std::endl;
      Socket->ssend(buffer);
    }
  return (0);
}

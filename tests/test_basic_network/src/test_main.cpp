#include <iostream>
#include <ServerSocket.hh>
#include <Epoll.hh>

int             main(int argc, char **argv)
{
  int           port;
  int           br;
  ServerSocket  *Server;
  Epoll         *loop;
  int           fd;
  char          buff[1024];

  br = 0;
  fd = -1;
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
      if (fd > 0)
        {
          br = read(fd, buff, 1023);
          buff[br] = '\0';
          std::cout << buff << std::endl;
        }
      else if(fd < 0)
        std::cout << "Client disconnect" << std::endl;
    }
  delete Server;
  return (0);
}

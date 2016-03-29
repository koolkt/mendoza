#include <iostream>
#include <ServerSocket.hh>
#include <Epoll.hh>

int             main(int argc, char **argv)
{
  int           port;
  int           br;
  ServerSocket  *Server;
  Epoll         *loop;
  Events        *events;
  char          buff[1024];

  br = 0;
  if (argc != 2)
    return(0);
  port = atoi(argv[1]);
  Server = new ServerSocket();
  Server->init(port);
  loop = new Epoll();
  loop->init(*Server);
  while (42)
    {
      loop->wait();
      events = &loop->new_events;
      for (std::vector<int>::iterator it = events->at(Epoll::READ_EVENTS).begin() ;
           it != events->at(Epoll::READ_EVENTS).end();
           ++it)
        {
          br = read(*it, buff, 1023);
          buff[br] = '\0';
          std::cout << buff << std::endl;
          write(*it, buff, strlen(buff));
        }
       for (std::vector<int>::iterator it = events->at(Epoll::ERROR_EVENTS).begin() ;
            it != events->at(Epoll::ERROR_EVENTS).end();
            ++it)
        {
          loop->delete_fd(*it);
          std::cout << "Client disconnect" << std::endl;
        }
    }
  delete Server;
  return (0);
}

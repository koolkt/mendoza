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
  char          buff[4096];
  int           tbr;

  tbr = 0;
  br = 1;
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
          tbr = 0;
          br = 1;
          while (br > 0 && tbr < 4095)
            {
              br = read(*it, buff+tbr, 4095 - tbr);
              if(br > 0)
                tbr += br;
            }
          buff[tbr] = '\0';
          std::cout << buff << std::endl;
          std::cout << tbr << br << std::endl;
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

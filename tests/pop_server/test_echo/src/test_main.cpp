#include <iostream>
#include <ServerSocket.hh>
#include <Epoll.hh>
#include <algorithm>

void             read_incomming(Client *client)
{
  int           br;
  char          buff[4096];

  br = 1;
  br = read(client->get_fd(), buff, 4095);
  buff[br] = '\0';
  write(client->get_fd(), buff, br);
  std::cout << buff << std::endl;
}

int             main(int argc, char **argv)
{
  int           port;
  ServerSocket  *Server;
  Epoll         *loop;
  Events        *events;

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
      std::for_each(events->at(Epoll::READ_EVENTS).begin(),
                    events->at(Epoll::READ_EVENTS).end(),
                    read_incomming);

      std::for_each(events->at(Epoll::ERROR_EVENTS).begin(),
                    events->at(Epoll::ERROR_EVENTS).end(),
                    std::bind1st(std::mem_fun(&Epoll::delete_client), &loop));
    }
  return (0);
}

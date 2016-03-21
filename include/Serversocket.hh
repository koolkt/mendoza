#pragma                 once
#include                <IServersocket.hh>

class                   Serversocket : public IServersocket
{
  struct sockaddr_in	s_in;
  socklen_t		size;
  int			port;
  int			socket_fd;
  char                  dbind();
  char			dlisten();
  char                  create_socket();
public:
  Serversocket();
  virtual bool          init(short const listenPort);
  virtual Socket*       daccept();
  virtual               ~Serversocket();
};

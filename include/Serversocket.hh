#pragma                 once
#include                <IServersocket.hh>

class                   Serversocket : public IServersocket
{
  struct sockaddr_in	s_in;
  socklen_t		size;
  int			port;
  char                  dbind();
  char			dlisten();
  char                  create_socket();
public:
  Serversocket();
  int			socket_fd;
  virtual bool          init(short const listenPort);
  virtual Socket*       daccept();
  virtual               ~Serversocket();
};

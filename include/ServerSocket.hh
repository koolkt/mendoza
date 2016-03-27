#pragma                 once
#include                <IServersocket.hh>

class                   ServerSocket : public IServerSocket
{
  struct sockaddr_in	s_in;
  socklen_t		size;
  int			port;
  char                  dbind();
  char			dlisten();
  char                  create_socket();
public:
  ServerSocket();
  int			socket_fd;
  virtual bool          init(short const listenPort);
  virtual int           daccept();
  virtual               ~ServerSocket();
};

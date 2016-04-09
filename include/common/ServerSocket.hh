#pragma                 once
#include                <IServersocket.hh>

class                   ServerSocket : public IServerSocket
{
  struct sockaddr_in	s_in;
  socklen_t		size;
  int			port;
  void                  dbind();
  void			dlisten();
  void                  create_socket();
public:
  ServerSocket();
  int			socket_fd;
  virtual void          init(short const listenPort);
  virtual int           daccept();
  virtual               ~ServerSocket();
};

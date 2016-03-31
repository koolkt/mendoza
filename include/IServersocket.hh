#pragma                  once
#include                <cstdlib>
#include                <unistd.h>
#include                <cstring>
#include                <Socket.hh>
#define                 SOCKET_ERROR -1

class                   IServerSocket
{
  virtual void                  dbind() = 0;
  virtual void			dlisten() = 0;
  virtual void                  create_socket() = 0;
public:
  virtual void                  init(short const listenPort) = 0;
  virtual int                   daccept() = 0;
  virtual                       ~IServerSocket() {};
};

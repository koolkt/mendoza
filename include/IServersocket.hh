#pragma                  once
#include                <cstdlib>
#include                <unistd.h>
#include                <cstring>
#include                <Socket.hh>
#define                 SOCKET_ERROR -1

class                   IServerSocket
{
  virtual char                  dbind() = 0;
  virtual char			dlisten() = 0;
  virtual char                  create_socket() = 0;
public:
  virtual bool                  init(short const listenPort) = 0;
  virtual int                   daccept() = 0;
  virtual                       ~IServerSocket() {};
};

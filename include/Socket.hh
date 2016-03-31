#pragma                         once
#include                        <iostream>
#include			<sys/types.h>
#include			<netinet/in.h>
#include			<arpa/inet.h>
#include			<errno.h>
#include			<sys/socket.h>
#include			<netdb.h>
#include                        <cstdlib>
#include                        <unistd.h>
#include                        <cstring>
#include                        <exception>

class Socket
{
  int                  create_socket();
 public:
  int			socket_fd;
  Socket();
  Socket(int fd);
  Socket&               operator=(const Socket &rhs);
  bool                  connectToServer(std::string const & host, short const port);
  static int            srecv(std::string& buffer, int const blocksize, int fd);
  int                   srecv(std::string& buffer, int const blocksize);
  int                   ssend(std::string const & data);
                        ~Socket();
};

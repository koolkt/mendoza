#include			<stdlib.h>
#include			<unistd.h>
#include			<sys/types.h>
#include			<netinet/in.h>
#include			<arpa/inet.h>
#include			<errno.h>
#include			<sys/socket.h>
#include			<netdb.h>
#include                        <string.h>
#define				SOCKET_ERROR -1

typedef struct          s_socket
{
  struct sockaddr_in	s_in;
  socklen_t		size;
  int			port;
  int			socket_fd;

}t_socket;

t_socket this;

static char			init_socket()
{
  struct protoent		*s_p;

  s_p = getprotobyname("TCP");
  if(s_p == NULL)
    {
      return(EXIT_FAILURE);
    }
  this.socket_fd = socket(AF_INET, SOCK_STREAM, s_p->p_proto);
  if(this.socket_fd < 0)
    {
      return(EXIT_FAILURE);
    }
  write(1,"Socket initialized\n", 19);
  return (EXIT_SUCCESS);
}

static char			do_bind()
{
  int				result;

  this.size = sizeof(this.s_in);
  memset(&this.s_in, 0, this.size);
  this.s_in.sin_family = AF_INET;
  this.s_in.sin_port = htons(this.port);
  this.s_in.sin_addr.s_addr = INADDR_ANY;
  result = bind(this.socket_fd, (struct sockaddr *)&this.s_in, this.size);
  if(result < 0)
    {
      close(this.socket_fd);
      return(EXIT_FAILURE);
    }
  write(1, "Socket bind completed\n", 22);
  return (EXIT_SUCCESS);
}

static char			do_listen()
{
  int				result;

  result = listen(this.socket_fd, SOMAXCONN);
  if(result < 0)
    {
      close(this.socket_fd);
      return(EXIT_FAILURE);
    }
    write(1, "Socket bind listening on port 1337\n", 35);
  return (EXIT_SUCCESS);
}

int				start_listen()
{
  this.port = 1337;
  if ((init_socket())
      || do_bind()
      || do_listen())
    {
      write(1,"Socket error",12);
      return (SOCKET_ERROR);
    }
  return (this.socket_fd);
}

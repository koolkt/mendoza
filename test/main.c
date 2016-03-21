#include        <stdlib.h>
#include        <unistd.h>
#include			<sys/types.h>
#include			<netinet/in.h>
#include			<arpa/inet.h>
#include			<errno.h>
#include			<sys/socket.h>
#include			<netdb.h>
#include			<string.h>
#define                         BUFFSIZE 10
int				start_listen();
int     main(void)
{
  char  buffer[BUFFSIZE];
  int   socket_fd;
  int   sg_listenfd;
  int   br;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  sg_listenfd = start_listen();
  if (sg_listenfd == EXIT_FAILURE)
    {
      return (1);
    }
  socket_fd = accept(sg_listenfd, (struct sockaddr *)&client_sin,
                     &client_sin_len);
  while(42)
    {
      if (socket_fd < 0)
        {
          write(1,"accept error",12);
          return (1);
        }
      br = read(socket_fd, buffer, BUFFSIZE);
      if (br < 1)
        {
          close(socket_fd);
          socket_fd = accept(sg_listenfd, (struct sockaddr *)&client_sin,
                             &client_sin_len);
        }
      else
        {
          if (br > BUFFSIZE)
            br = BUFFSIZE;
          buffer[br] = '\0';
          send(socket_fd, buffer, strlen(buffer),0);
        }
    }
  return (0);
}

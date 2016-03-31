#include                <SmtpServer.hh>

void             read_func(int fd)
{

}

SmtpServer::SmtpServer(const int port)
{
  this->server_socket.init(port);
}

void            SmtpServer::process_events(Events   *events)
{
  std::for_each(events->at(Epoll::READ_EVENTS).begin(),
                events->at(Epoll::READ_EVENTS).end(),
                read_func);

  std::for_each(events->at(Epoll::ERROR_EVENTS).begin(),
                events->at(Epoll::ERROR_EVENTS).end(),
                std::bind1st(std::mem_fun(&Epoll::delete_fd), &this->epoll));
}

void            SmtpServer::run()
{
  this->epoll.init(this->server_socket);
  while (42)
    {
      this->epoll.wait();
      process_events(&this->epoll.new_events);
    }
}

SmtpServer::~SmtpServer()
{
}

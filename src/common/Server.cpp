#include                <Server.hh>

Server::Server()
{
}

Server::~Server()
{
}

void            Server::process_events(Events *events)
{
  std::for_each(events->at(Epoll::READ_EVENTS).begin(),
                events->at(Epoll::READ_EVENTS).end(),
                std::bind1st(std::mem_fun(&Server::process_incomming), this));

  std::for_each(events->at(Epoll::NEW_CONN).begin(),
                events->at(Epoll::NEW_CONN).end(),
                std::bind1st(std::mem_fun(&Server::process_new), this));

  std::for_each(events->at(Epoll::ERROR_EVENTS).begin(),
                events->at(Epoll::ERROR_EVENTS).end(),
                std::bind1st(std::mem_fun(&Epoll::delete_client), &this->epoll));
}

void            Server::run()
{
  this->epoll.init(this->server_socket);
  while (42)
    {
      this->epoll.wait();
      process_events(&this->epoll.new_events);
    }
}

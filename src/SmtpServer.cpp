#include                <SmtpServer.hh>

void             SmtpServer::process_incomming(Client *client)
{
  // std::cout << "New read" << std::endl;
  this->parser.parse(client);
  // send_smtp_response(client);
  return;
}

// void            send_smtp_response(Client *client)
// {

// }

void          SmtpServer::process_new(Client *client)
{
  std::cout << "New Client connected" << std::endl;
  client->send_message("220 localhost ESMTP Mendoza\r\n");
}

SmtpServer::SmtpServer(const int port)
{
  this->server_socket.init(port);
}

void            SmtpServer::process_events(Events *events)
{
  std::for_each(events->at(Epoll::READ_EVENTS).begin(),
                events->at(Epoll::READ_EVENTS).end(),
                std::bind1st(std::mem_fun(&SmtpServer::process_incomming), this));

  std::for_each(events->at(Epoll::NEW_CONN).begin(),
                events->at(Epoll::NEW_CONN).end(),
                std::bind1st(std::mem_fun(&SmtpServer::process_new), this));

  std::for_each(events->at(Epoll::ERROR_EVENTS).begin(),
                events->at(Epoll::ERROR_EVENTS).end(),
                std::bind1st(std::mem_fun(&Epoll::delete_client), &this->epoll));
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

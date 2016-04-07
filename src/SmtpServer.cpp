#include                <SmtpServer.hh>

void             SmtpServer::process_incomming(Client *client)
{
  Parser::Action        r;

  r = this->parser.parse(client);
  if (client->get_last_state() ==  Parser::RCPT)
    {
      if (!this->mbox.user_exists(client->get_mail()))
        {
          r = Parser::MAIL_NA;
          // Erase mail?
        }
    }
  else if (client->get_last_state() ==  Parser::MAIL_PARSED)
    {
      this->mbox.send_mail(client->get_mail());
      client->set_state(Parser::START);
      // client->reset();
    }
  client->send_message(*this->responses->at(r));
  return;
}

void          SmtpServer::process_new(Client *client)
{
  std::cout << "New Client connected" << std::endl;
  client->send_message("220 localhost ESMTP Mendoza\r\n");
}

SmtpServer::SmtpServer(const int port)
{
  this->server_socket.init(port);
  this->responses = new Responses(10);
  (*this->responses)[Parser::OK] = new std::string("250 localhost Ok\r\n");
  (*this->responses)[Parser::END_DATA] = new std::string("354 End data with <CR><LF>.<CR><LF>\r\n");
  (*this->responses)[Parser::BYE] = new std::string("221 Bye\r\n");
  (*this->responses)[Parser::NOT_IMP] = new std::string("502 comand not implemented Ok\r\n");
  (*this->responses)[Parser::MAIL_NA] = new std::string("450 Requested mail action not taken: mailbox unavailable\r\n");
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
  delete (*this->responses)[Parser::OK];
  delete (*this->responses)[Parser::END_DATA];
  delete (*this->responses)[Parser::BYE];
  delete (*this->responses)[Parser::NOT_IMP];
  delete (*this->responses)[Parser::MAIL_NA];
  delete this->responses;
}

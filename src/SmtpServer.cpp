#include                <SmtpServer.hh>

void             SmtpServer::process_incomming(Client *vclient)
{
  SmtpClient    *client;
  SmtpParser::Action        r;

  client = (SmtpClient*)vclient;
  r = this->parser.parse(client);
  if (client->get_last_state() ==  SmtpParser::RCPT)
    {
      if (!this->mbox.user_exists(client->get_mail()))
        {
          r = SmtpParser::MAIL_NA;
          // Erase mail?
        }
    }
  else if (client->get_last_state() ==  SmtpParser::MAIL_PARSED)
    {
      this->mbox.send_mail(client->get_mail());
      client->set_state(SmtpParser::START);
      client->get_mail().reset();
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
  (*this->responses)[SmtpParser::OK] = new std::string("250 localhost Ok\r\n");
  (*this->responses)[SmtpParser::END_DATA] = new std::string("354 End data with <CR><LF>.<CR><LF>\r\n");
  (*this->responses)[SmtpParser::BYE] = new std::string("221 Bye\r\n");
  (*this->responses)[SmtpParser::NOT_IMP] = new std::string("502 comand not implemented Ok\r\n");
  (*this->responses)[SmtpParser::MAIL_NA] = new std::string("450 Requested mail action not taken: mailbox unavailable\r\n");
}

SmtpServer::~SmtpServer()
{
  delete (*this->responses)[SmtpParser::OK];
  delete (*this->responses)[SmtpParser::END_DATA];
  delete (*this->responses)[SmtpParser::BYE];
  delete (*this->responses)[SmtpParser::NOT_IMP];
  delete (*this->responses)[SmtpParser::MAIL_NA];
  delete this->responses;
}

#include                <PopServer.hh>
#include                <string>
#define UNUSED(x) (void)(x)

PopServer::PopServer(const int port)
{
  this->server_socket.init(port);
}

void  PopServer::processIncomming(Client *vclient)
{
  std::string     res;
  PopClient    *client;
  PopParser::Action        r;

  client = (PopClient*)vclient->getInfo();
  r = this->parser.parse(vclient);
  // last_state = client->get_last_state();
  if(r == PopParser::CAPA)
    {
      std::cout << "Server says: "<< "+OK Capability list follows etc..\r\n" << std::endl;
      vclient->send("+OK Capability list follows\r\n");
      vclient->send("USER\r\n");
      vclient->send(".\r\n");
    }
  else if((r == PopParser::USER))
    {
      res = vclient->rcv();
      res.erase(std::remove(res.begin(), res.end(), '\r'), res.end());
      res.erase(std::remove(res.begin(), res.end(), '\n'), res.end());
      res = res.substr(5, std::string::npos);
      client->setUsername(res);
      vclient->send("+OK\r\n");
    }
  else if((r == PopParser::PASS))
    {
      res = vclient->rcv();
      res.erase(std::remove(res.begin(), res.end(), '\r'), res.end());
      res.erase(std::remove(res.begin(), res.end(), '\n'), res.end());
      res = res.substr(5, std::string::npos);
      if (this->mbox.auth_user(client->getUsername(), res))
        vclient->send("+OK\r\n");
      else
        vclient->send("-ERR\r\n");
    }
  else if ((r == PopParser::STAT))
    {
      for(auto i: this->mbox.number_new_mails(client->getUsername()))
        {
          // vclient->send(i);
          std::cout << "Server says: "<< i << std::endl;
        }
      res += "+OK""\r\n";
      vclient->send(res);
    }
  else
    {
      std::cout << "Server says: "<< "+OK\r\n" << std::endl;
      vclient->send("+OK\r\n");
    }
}

void  PopServer::processNew(Client *client)
{
  std::cout << "New Client connected" << std::endl;
  std::cout << "Server says: Hello" << std::endl;
  client->setInfo((void*)(new PopClient()));
  client->send("+OK POP3 server ready\r\n");
}

PopServer::~PopServer()
{
}

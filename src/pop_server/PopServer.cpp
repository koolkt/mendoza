#include                <PopServer.hh>
#include                <string>
#define UNUSED(x) (void)(x)

PopServer::PopServer(const int port)
{
  this->server_socket.init(port);
}

void  PopServer::process_incomming(Client *vclient)
{
  int n;
  std::string     res;
  PopClient    *client;
  PopParser::Action        r;

  n = 0;
  client = (PopClient*)vclient;
  r = this->parser.parse(client);
  // last_state = client->get_last_state();
  if(r == PopParser::CAPA)
    {
      std::cout << "Server says: "<< "+OK Capability list follows etc..\r\n" << std::endl;
      client->send_message("+OK Capability list follows\r\n");
      client->send_message("USER\r\n");
      client->send_message(".\r\n");
    }
  else if((r == PopParser::USER))
    {
      res = client->get_data();
      res.erase(std::remove(res.begin(), res.end(), '\r'), res.end());
      res.erase(std::remove(res.begin(), res.end(), '\n'), res.end());
      res = res.substr(5, std::string::npos);
      client->set_username(res);
      client->send_message("+OK\r\n");
    }
   else if((r == PopParser::PASS))
    {
      res = client->get_data();
      res.erase(std::remove(res.begin(), res.end(), '\r'), res.end());
      res.erase(std::remove(res.begin(), res.end(), '\n'), res.end());
      res = res.substr(5, std::string::npos);
      if (this->mbox.auth_user(client->get_username(), res))
        client->send_message("+OK\r\n");
      else
        client->send_message("-ERR\r\n");
    }
  else if ((r == PopParser::STAT))
    {
      // int i;

      // i =0;
      // std::list<std::string> &r = this->mbox.number_new_mails(client->get_username());
      // res += "+OK " + std::to_string(n) + "\r\n";
      // client->send_message(res);
      // for (std::list<std::string>::iterator it = r.begin();
      //      r.end() != it; it++) {
      //   i++;
      //   res = std::to_string(i) + " " + *it +"\r\n";
      UNUSED(n);
      client->send_message("+OK\r\n");
      // }
    }
  else
    {
      std::cout << "Server says: "<< "+OK\r\n" << std::endl;
      client->send_message("+OK\r\n");
    }
}

void  PopServer::process_new(Client *client)
{
  std::cout << "New Client connected" << std::endl;
  std::cout << "Server says: Hello" << std::endl;
  client->send_message("+OK POP3 server ready\r\n");
}

PopServer::~PopServer()
{
}

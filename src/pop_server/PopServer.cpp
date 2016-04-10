#include                <PopServer.hh>

#define UNUSED(x) (void)(x)

PopServer::PopServer(const int port)
{
  this->server_socket.init(port);
}

void  PopServer::process_incomming(Client *vclient)
{
  PopClient    *client;
  // PopParser::State   last_state;
  PopParser::Action        r;

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

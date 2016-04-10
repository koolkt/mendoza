#include                <PopServer.hh>
#define UNUSED(x) (void)(x)

PopServer::PopServer(const int port)
{
  this->server_socket.init(port);
}

void  PopServer::process_incomming(Client *client)
{
  client->send_message("+OK 0 0\r\n");
}

void  PopServer::process_new(Client *client)
{
  std::cout << "New Client connected" << std::endl;
  client->send_message("+OK POP3 server ready\r\n");
}

PopServer::~PopServer()
{
}

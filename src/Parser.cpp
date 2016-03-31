#include        <Parser.hh>
#include        <Client.hh>

Parser::Parser()
{
}

void  Parser::parse(Client *client)
{
  std::cout << client->get_fd() << std::endl;
}

Parser::~Parser()
{
}

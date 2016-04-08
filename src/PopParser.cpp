#include        <PopParser.hh>
#define UNUSED(x) (void)(x)

PopParser::PopParser()
{
}

PopParser::Action  PopParser::parse(Client *client)
{
  UNUSED(client);
  return PopParser::NOT_IMP;
}

PopParser::~PopParser()
{
}

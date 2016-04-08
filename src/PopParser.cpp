#include        <PopParser.hh>
#include        <PopClient.hh>
#define UNUSED(x) (void)(x)

PopParser::PopParser()
{
}

PopParser::Action  PopParser::parse(PopClient *client)
{
  UNUSED(client);
  return PopParser::NOT_IMP;
}

PopParser::~PopParser()
{
}

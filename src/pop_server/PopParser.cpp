#include        <PopParser.hh>
#include        <PopClient.hh>
#define UNUSED(x) (void)(x)

PopParser::PopParser()
{
}

bool                    PopParser::capa(const std::string *data)
{
  return (data->compare(0,4,"CAPA") == 0);
}

bool                    PopParser::user(const std::string *data)
{
  return (data->compare(0,4,"USER") == 0);
}

bool                    PopParser::pass(const std::string *data)
{
  return (data->compare(0,4,"PASS") == 0);
}

bool                    PopParser::stat(const std::string *data)
{
  return (data->compare(0,4,"STAT") == 0);
}

bool                    PopParser::quit(const std::string *data)
{
  return (data->compare(0,4,"QUIT") == 0);
}

PopParser::Action  PopParser::parse(PopClient *client)
{
  // PopParser::State   last_state;
  const std::string     *data;

  data = &client->get_data();
  std::cout << "Client says: "<< *data << std::endl;
  // last_state = client->get_last_state();
  if (capa(data))
    {
      return PopParser::CAPA;
    }
  if (user(data))
    {
      return PopParser::USER;
    }
  if (pass(data))
    {
      return PopParser::PASS;
    }
  if (stat(data))
    {
      return PopParser::STAT;
    }
  if (quit(data))
    {
      return PopParser::QUIT;
    }
  return PopParser::NOT_IMP;
}

PopParser::~PopParser()
{
}

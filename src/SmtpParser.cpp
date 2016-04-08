#include        <SmtpParser.hh>
#include        <Client.hh>

SmtpParser::SmtpParser()
{
}

bool                    SmtpParser::parse_mail(Client *client)
{
  const std::string     *data;

  data = &client->get_data();
  client->get_mail().set_body(*data);
  client->set_state(SmtpParser::MAIL_PARSED);
  return true;
}

bool                    SmtpParser::data(Client *client)
{
  const std::string     *data;

  data = &client->get_data();
  if (data->compare(0,4,"DATA") == 0)
    {
      client->set_state(SmtpParser::DATA);
      return true;
    }
  return false;
}

std::vector<std::string>*        SmtpParser::get_adress(std::string s)
{
  std::string   *str;
  std::vector<std::string> *r;
  std::smatch m;
  std::regex e ("([A-Z0-9a-z._%+-]+)@([A-Za-z0-9.-]+\\.[A-Za-z]{2,6})");

  r = new std::vector<std::string>;
  while (std::regex_search (s,m,e)) {
    for (auto x:m)
      {
        std::cout << x << " ";
        str = new std::string(x);
        r->push_back(*str);
      }
    std::cout << std::endl;
    s = m.suffix().str();
  }
  return r;
}

bool                    SmtpParser::rcpt_to(Client *client)
{
  std::string     data;

  data = client->get_data();
  if (data.compare(0,7,"RCPT TO") == 0)
    {
      client->get_mail().set_dest(get_adress(data));
      client->set_state(SmtpParser::RCPT);
      return true;
    }
  return false;
}

bool                    SmtpParser::mail_from(Client *client)
{
  const std::string     *data;

  data = &client->get_data();
  if (data->compare(0,9,"MAIL FROM") == 0)
    {
      // client->set_state(SmtpParser::MAIL);
      return true;
    }
  return false;
}

bool                    SmtpParser::ehlo(Client *client)
{
  const std::string     *data;

  data = &client->get_data();
  return (data->compare(0,4,"EHLO") == 0);
}

bool                    SmtpParser::helo(Client *client)
{
  const std::string     *data;

  data = &client->get_data();
  return (data->compare(0,4,"HELO") == 0);
}

SmtpParser::Action         SmtpParser::parse(Client *client)
{
  SmtpParser::State   last_state;
  const std::string     *cdata;

  cdata = &client->get_data();
  last_state = client->get_last_state();
  if (((last_state == SmtpParser::START) || (last_state == SmtpParser::RCPT)) &&
      (helo(client) || mail_from(client) || rcpt_to(client)))
    {
      return SmtpParser::OK;
    }
  else if (last_state == SmtpParser::RCPT && data(client))
    {
      return SmtpParser::END_DATA;
    }
  else if (last_state == SmtpParser::DATA)
    {
      parse_mail(client);
      return SmtpParser::OK;
    }
  else if (cdata->compare(0,4,"QUIT") == 0)
    return SmtpParser::BYE;
  return SmtpParser::NOT_IMP;;
}

SmtpParser::~SmtpParser()
{
}

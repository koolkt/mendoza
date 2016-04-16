#include        <SmtpParser.hh>
#include        <SmtpClient.hh>

SmtpParser::SmtpParser()
{
}

bool                    SmtpParser::parseMail(Client *client)
{
  const std::string     *data;

  data = &client->rcv();
  ((SmtpClient*)client->getInfo())->getMail().set_body(*data);
  ((SmtpClient*)client->getInfo())->setState(SmtpParser::MAIL_PARSED);
  return true;
}

bool                    SmtpParser::data(Client *client)
{
  const std::string     *data;

  data = &client->rcv();
  if (data->compare(0,4,"DATA") == 0)
    {
      ((SmtpClient*)client->getInfo())->setState(SmtpParser::DATA);
      return true;
    }
  return false;
}

std::vector<std::string>*        SmtpParser::getAdress(std::string s)
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

bool                    SmtpParser::rcptTo(Client *client)
{
  std::string     data;

  data = client->rcv();
  if (data.compare(0,7,"RCPT TO") == 0)
    {
      ((SmtpClient*)client->getInfo())->getMail().set_dest(getAdress(data));
      ((SmtpClient*)client->getInfo())->setState(SmtpParser::RCPT);
      return true;
    }
  return false;
}

bool                    SmtpParser::mailFrom(Client *client)
{
  const std::string     *data;

  data = &client->rcv();
  if (data->compare(0,9,"MAIL FROM") == 0)
    {
      // client->setState(SmtpParser::MAIL);
      return true;
    }
  return false;
}

bool                    SmtpParser::ehlo(Client *client)
{
  const std::string     *data;

  data = &client->rcv();
  return (data->compare(0,4,"EHLO") == 0);
}

bool                    SmtpParser::helo(Client *client)
{
  const std::string     *data;

  data = &client->rcv();
  return (data->compare(0,4,"HELO") == 0);
}

SmtpParser::Action         SmtpParser::parse(Client *client)
{
  SmtpParser::State   last_state;
  const std::string     *cdata;

  cdata = &client->rcv();
  last_state = ((SmtpClient*)client->getInfo())->getState();
  if (((last_state == SmtpParser::START) || (last_state == SmtpParser::RCPT)) &&
      (helo(client) || mailFrom(client) || rcptTo(client)))
    {
      return SmtpParser::OK;
    }
  else if (last_state == SmtpParser::RCPT && data(client))
    {
      return SmtpParser::END_DATA;
    }
  else if (last_state == SmtpParser::DATA)
    {
      parseMail(client);
      return SmtpParser::OK;
    }
  else if (cdata->compare(0,4,"QUIT") == 0)
    return SmtpParser::BYE;
  return SmtpParser::NOT_IMP;;
}

SmtpParser::~SmtpParser()
{
}

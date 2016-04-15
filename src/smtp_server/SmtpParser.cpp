#include        <SmtpParser.hh>
#include        <SmtpClient.hh>

SmtpParser::SmtpParser()
{
}

bool                    SmtpParser::parse_mail(SmtpClient *client)
{
  const std::string     *data;

  data = &client->rcv();
  client->getMail().set_body(*data);
  client->setState(SmtpParser::MAIL_PARSED);
  return true;
}

bool                    SmtpParser::data(SmtpClient *client)
{
  const std::string     *data;

  data = &client->rcv();
  if (data->compare(0,4,"DATA") == 0)
    {
      client->setState(SmtpParser::DATA);
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

bool                    SmtpParser::rcpt_to(SmtpClient *client)
{
  std::string     data;

  data = client->rcv();
  if (data.compare(0,7,"RCPT TO") == 0)
    {
      client->getMail().set_dest(get_adress(data));
      client->setState(SmtpParser::RCPT);
      return true;
    }
  return false;
}

bool                    SmtpParser::mail_from(SmtpClient *client)
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

bool                    SmtpParser::ehlo(SmtpClient *client)
{
  const std::string     *data;

  data = &client->rcv();
  return (data->compare(0,4,"EHLO") == 0);
}

bool                    SmtpParser::helo(SmtpClient *client)
{
  const std::string     *data;

  data = &client->rcv();
  return (data->compare(0,4,"HELO") == 0);
}

SmtpParser::Action         SmtpParser::parse(SmtpClient *client)
{
  SmtpParser::State   last_state;
  const std::string     *cdata;

  cdata = &client->rcv();
  last_state = client->getState();
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

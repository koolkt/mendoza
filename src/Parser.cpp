#include        <Parser.hh>
#include        <Client.hh>

// # 220
// # EHLO [127.0.0.1]
// # 502
// # HELO [127.0.0.1]
// # 250
// # MAIL FROM:<kool@kool.com>
// # 250
// # RCPT TO:<hello@test.com>
// # 250
// # DATA
// # 354
// # From: k <kool@kool.com>
// # Subject: test
// # To: hello@test.com
// # Message-ID: <56FB5238.1050008@kool.com>
// # Date: Wed, 30 Mar 2016 06:12:40 +0200
// # User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:38.0) Gecko/20100101
// #  Thunderbird/38.7.1
// # MIME-Version: 1.0
// # Content-Type: text/plain; charset=utf-8; format=flowed
// # Content-Transfer-Encoding: 7bit

// # Hello World
// # .
// # 250
// # QUIT
#define UNUSED(x) (void)(x)
Parser::Parser()
{
}

bool                    Parser::parse_mail(Client *client)
{
  const std::string     *data;

  data = &client->get_data();
  client->get_mail().set_body(*data);
  std::cout << *data << std::endl;
  client->set_state(Parser::MAIL_PARSED);
  return(true);
}

bool                    Parser::data(Client *client)
{
  const std::string     *data;

  data = &client->get_data();
  if (data->compare(0,4,"DATA") == 0)
    {
      client->set_state(Parser::DATA);
      return true;
    }
  return false;
}

std::vector<std::string>*        Parser::get_adress(std::string s)
{
  std::vector<std::string> *r;
  std::smatch m;
  std::regex e ("([A-Z0-9a-z._%+-]+)@([A-Za-z0-9.-]+\\.[A-Za-z]{2,6})");

  r = new std::vector<std::string>(5);
  while (std::regex_search (s,m,e)) {
    for (auto x:m) {
      std::cout << x << " ";
      r->push_back(x);
      }
    std::cout << std::endl;
    s = m.suffix().str();
  }
  return r;
}

bool                    Parser::rcpt_to(Client *client)
{
  std::string     data;

  data = client->get_data();
  if (data.compare(0,7,"RCPT TO") == 0)
    {
      client->get_mail().set_dest(get_adress(data));
      client->set_state(Parser::RCPT);
      return true;
    }
  return false;
}

bool                    Parser::mail_from(Client *client)
{
  const std::string     *data;

  data = &client->get_data();
  if (data->compare(0,9,"MAIL FROM") == 0)
    {
      // client->set_state(Parser::MAIL);
      return true;
    }
  return false;
}

bool                    Parser::ehlo(Client *client)
{
  const std::string     *data;

  data = &client->get_data();
  return (data->compare(0,4,"EHLO") == 0);
}

bool                    Parser::helo(Client *client)
{
  const std::string     *data;

  data = &client->get_data();
  return (data->compare(0,4,"HELO") == 0);
}

Parser::Action         Parser::parse(Client *client)
{
  Parser::State   last_state;
  const std::string     *cdata;

  cdata = &client->get_data();
  last_state = client->get_last_state();
  if (((last_state == Parser::START) || (last_state == Parser::RCPT)) &&
      (helo(client) || mail_from(client) || rcpt_to(client)))
    {
      return Parser::OK;
    }
  else if (last_state == Parser::RCPT && data(client))
    {
      return Parser::END_DATA;
    }
  else if (last_state == Parser::DATA)
    {
      parse_mail(client);
      return Parser::OK;
    }
  else if (cdata->compare(0,4,"QUIT") == 0)
    return Parser::BYE;
  return Parser::NOT_IMP;;
}

Parser::~Parser()
{
}

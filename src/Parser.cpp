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

Parser::Parser()
{
}

void                    Parser::parse(Client *client)
{
  const std::string     *data;

  data = &client->get_data();
  if (data->compare(0,4,"HELO") == 0)
    client->send_message("250 localhost Ok\r\n");
  else if (data->compare(0,4,"EHLO") == 0)
    client->send_message("502 \r\n");
  else if (data->compare(0,9,"MAIL FROM") == 0)
    client->send_message("250 localhost Ok\r\n");
  else if (data->compare(0,7,"RCPT TO") == 0)
    client->send_message("250 localhost Ok\r\n");
  else if (data->compare(0,4,"DATA") == 0)
    client->send_message("354 End data with <CR><LF>.<CR><LF>\r\n");
  else if (data->compare(0,4,"QUIT") == 0)
    client->send_message("221 Bye\r\n");
  else
    client->send_message("250 localhost Ok\r\n");
}

Parser::~Parser()
{
}

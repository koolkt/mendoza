#pragma         once

#include        <Mailbox.hh>
#include        <Server.hh>
#include        <SmtpClient.hh>
#include        <SmtpParser.hh>

typedef std::vector<std::string*> Responses;

class           SmtpServer: public Server
{
  SmtpParser    parser;
  Mailbox       mbox;
  virtual void  processIncomming(Client *);
  virtual void  processNew(Client *);
  Responses     *responses;
public:
  SmtpServer(const int port);
  virtual ~SmtpServer();
};

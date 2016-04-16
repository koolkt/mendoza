#pragma once
#include        <SmtpParser.hh>
#include        <Mailbox.hh>
#include        <Server.hh>
#include        <SmtpClient.hh>

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

#pragma once
#include        <SmtpParser.hh>
#include        <Mailbox.hh>
#include        <Server.hh>

typedef std::vector<std::string*> Responses;

class           SmtpServer: public Server
{
  SmtpParser    parser;
  Mailbox       mbox;
  virtual void  process_incomming(Client *);
  virtual void  process_new(Client *);
  Responses     *responses;
public:
  SmtpServer(const int port);
  virtual ~SmtpServer();
};

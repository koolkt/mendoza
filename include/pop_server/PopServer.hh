#pragma         once

#include        <Mailbox.hh>
#include        <Server.hh>
#include        <PopClient.hh>
#include        <PopParser.hh>

typedef std::vector<std::string*> Responses;

class           PopServer : public Server
{
  PopParser     parser;
  virtual void  processIncomming(Client *);
  virtual void  processNew(Client *);
  Responses     *responses;
public:
  PopServer(const int);
  virtual ~PopServer();
};

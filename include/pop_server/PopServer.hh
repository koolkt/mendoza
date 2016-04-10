#pragma once
#include        <Mailbox.hh>
#include        <PopParser.hh>
#include        <Server.hh>
#include        <iostream>
#include        <Server.hh>
#include        <PopClient.hh>

typedef std::vector<std::string*> Responses;
class           PopServer : public Server
{
  PopParser    parser;
  virtual void  process_incomming(Client *);
  virtual void  process_new(Client *);
  Responses     *responses;
public:
  PopServer(const int);
  virtual ~PopServer();
};

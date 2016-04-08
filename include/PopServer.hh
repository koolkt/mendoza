#pragma once
#include        <PopParser.hh>
#include        <Mailbox.hh>
#include        <Server.hh>
#include        <iostream>
#include        <Server.hh>

typedef std::vector<std::string*> Responses;
class           PopServer : public Server
{
  PopParser    parser;
  Mailbox       mbox;
  virtual void  process_incomming(Client *);
  virtual void  process_new(Client *);
  Responses     *responses;
public:
  PopServer();
  virtual ~PopServer();
};

#pragma once
#include        <Client.hh>
#include        <algorithm>
#include        <Epoll.hh>
#include        <ServerSocket.hh>
#include        <iostream>
#include        <Mailbox.hh>

class           Server
{
protected:
  Mailbox       mbox;
  Epoll         epoll;
  ServerSocket  server_socket;
  virtual void  processIncomming(Client *) = 0;
  virtual void  processNew(Client *) = 0;
  void          processEvents(Events*);
public:
  Server();
  void run();
  virtual ~Server();
};

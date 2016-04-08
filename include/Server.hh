#pragma once
#include        <Client.hh>
#include        <algorithm>
#include        <Epoll.hh>
#include        <ServerSocket.hh>
#include        <iostream>

class           Server
{
protected:
  Epoll         epoll;
  ServerSocket  server_socket;
  virtual void  process_incomming(Client *) = 0;
  virtual void  process_new(Client *) = 0;
  void          process_events(Events*);
public:
  Server();
  void run();
  virtual ~Server();
};

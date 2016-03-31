#pragma once
#include        <iostream>
#include        <ServerSocket.hh>
#include        <Epoll.hh>
#include        <Parser.hh>
#include        <Mailbox.hh>
#include        <algorithm>
#include        <Client.hh>

class           SmtpServer
{
  ServerSocket  server_socket;
  Epoll         epoll;
  Parser        parser;
  Mailbox       mbox;
  void          process_events(Events*);
  void          process_incomming(Client *);
  void          process_new(Client *);
public:
  SmtpServer(const int port);
  void          run();
  ~SmtpServer();
};

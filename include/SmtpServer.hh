#pragma once
#include        <iostream>
#include        <ServerSocket.hh>
#include        <Epoll.hh>
#include        <Parser.hh>
#include        <Mailbox.hh>

class           SmtpServer
{
  ServerSocket  server_socket;
  Epoll         epoll;
  Parser        parser;
  Mailbox       mbox;
public:
  SmtpServer(const int port);
  void          run();
  ~SmtpServer();
};

#pragma once
#include        <iostream>
#include        <ServerSocket.hh>
#include        <Epoll.hh>
#include        <SmtpParser.hh>
#include        <Mailbox.hh>
#include        <algorithm>
#include        <Client.hh>

typedef std::vector<std::string*> Responses;

class           SmtpServer
{
  ServerSocket  server_socket;
  Epoll         epoll;
  SmtpParser        parser;
  Mailbox       mbox;
  void          process_events(Events*);
  void          process_incomming(Client *);
  void          process_new(Client *);
  Responses     *responses;
public:
  SmtpServer(const int port);
  void          run();
  ~SmtpServer();
};

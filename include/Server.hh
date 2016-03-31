#pragma once
#include <iostream>
#include <ServerSocket.hh>
#include <Epoll.hh>

class           Server
{
  ServerSocket  server_socket;
  Epoll         epoll;
public:
  Server();
  ~Server();
};

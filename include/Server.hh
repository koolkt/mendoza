#pragma once

class           Server
{
  ServerSocket  server_socket;
  Epoll         epoll;
public:
  Server();
  ~Server();
};

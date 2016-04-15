#pragma once
#include        <Socket.hh>

class           Client
{
  Socket                socket;
  std::string           buffer;
  void*                 info;
  public:
  Client();
  void                  setSocket(int fd);
  void                  setInfo(void*);
  void*                 getInfo() const;
  std::string const&    rcv();
  void                  send(const char *);
  void                  send(std::string& msg);
  int                   getFd() const;
  ~Client();
};

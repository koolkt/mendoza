#pragma once
#include        <Parser.hh>
#include        <Socket.hh>

class           Client
{
  Socket        socket;
  std::string   buffer;
  Parser::State last_state;
  public:
  Client();
  void          set_socket(int fd);
  std::string const &  get_data() const;
  void          set_state(Parser::State);
  int           get_fd() const;
  ~Client();
};

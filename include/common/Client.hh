#pragma once
#include        <SmtpParser.hh>
#include        <PopParser.hh>
#include        <Socket.hh>
#include        <Mail.hh>

class           Client
{
  std::string   username;
  Socket        socket;
  std::string   buffer;
  Mail          mail;
  public:
  Client();
  Mail &        get_mail();
  std::string const&  get_username() const;
  void          set_username(std::string);
  void          set_socket(int fd);
  std::string const &  get_data();
  void          send_message(const char *);
  void          send_message(std::string& msg);
  int           get_fd() const;
  void          set_state(SmtpParser::State);
  SmtpParser::State const & get_last_state() const;
  void          setp_state(PopParser::State);
  PopParser::State const & getp_last_state() const;
  ~Client();
};

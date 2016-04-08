#pragma once
#include        <SmtpParser.hh>
#include        <Socket.hh>
#include        <Mail.hh>

class           Client
{
  Socket        socket;
  std::string   buffer;
  SmtpParser::State last_state;
  Mail          mail;
  public:
  Client();
  Mail &          get_mail();
  void          set_socket(int fd);
  std::string const &  get_data();
  void            send_message(const char *);
  void            send_message(std::string& msg);
  void          set_state(SmtpParser::State);
  SmtpParser::State const & get_last_state() const;
  int           get_fd() const;
  ~Client();
};

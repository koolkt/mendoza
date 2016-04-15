#pragma once
#include         <SmtpParser.hh>
#include         <MailClient.hh>

class           SmtpClient : public MailClient
{
  SmtpParser::State             last_state;
  public:
  SmtpClient();
  void                          setState(SmtpParser::State);
  SmtpParser::State const&      getState() const;
  ~SmtpClient();
};

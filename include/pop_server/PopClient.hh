#pragma once
#include         <MailClient.hh>

class           PopClient : public MailClient
{
  PopParser::State             last_state;
  public:
  PopClient();
  void                          setState(PopParser::State);
  PopParser::State const&       getState() const;
  ~PopClient();
};

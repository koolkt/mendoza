#include        <Client.hh>

class           SmtpClient : public Client
{
  public:
  SmtpClient();
  void          set_state(SmtpParser::State);
  SmtpParser::State const & get_last_state() const;
  ~SmtpClient();
};

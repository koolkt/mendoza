#include        <SmtpClient.hh>

SmtpClient::SmtpClient()
{
  this->last_state = SmtpParser::START;
}

SmtpClient::~SmtpClient()
{
}

SmtpParser::State const & SmtpClient::get_last_state() const
{
  return(this->last_state);
}

void            SmtpClient::set_state(SmtpParser::State new_state)
{
  this->last_state = new_state;
}

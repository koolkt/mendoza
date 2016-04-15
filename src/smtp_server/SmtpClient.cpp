#include        <SmtpClient.hh>

SmtpClient::~SmtpClient()
{
}

SmtpClient::SmtpClient()
{
  this->last_state = SmtpParser::START;
}

SmtpParser::State const & SmtpClient::getState() const
{
  return(this->last_state);
}

void            SmtpClient::setState(SmtpParser::State new_state)
{
  this->last_state = new_state;
}

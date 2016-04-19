#include        <PopClient.hh>

PopClient::PopClient()
{
  this->last_state = PopParser::START;
}

PopClient::~PopClient()
{
}

PopParser::State const & PopClient::getState() const
{
  return(this->last_state);
}

void            PopClient::setState(PopParser::State new_state)
{
  this->last_state = new_state;
}

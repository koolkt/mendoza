#include        <PopClient.hh>

PopClient::PopClient()
{
  this->last_state = PopParser::START;
}

PopClient::~PopClient()
{
}

PopParser::State const & PopClient::get_last_state() const
{
  return(this->last_state);
}

void            PopClient::set_state(PopParser::State new_state)
{
  this->last_state = new_state;
}

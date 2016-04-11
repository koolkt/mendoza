#include        <PopClient.hh>

PopClient::PopClient()
{
  this->last_pstate = PopParser::START;
}

PopClient::~PopClient()
{
}

PopParser::State const & PopClient::get_last_state() const
{
  return(this->last_pstate);
}

void            PopClient::set_state(PopParser::State new_state)
{
  this->last_pstate = new_state;
}

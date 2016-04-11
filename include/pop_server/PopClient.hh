#include        <Client.hh>

class           PopClient : public Client
{
  public:
  PopClient();
  void          set_state(PopParser::State);
  PopParser::State const & get_last_state() const;
  ~PopClient();
};

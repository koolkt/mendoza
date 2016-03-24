#pragma         once

class           EventHandler
{
  public:
  virtual int handle(int) = 0;
  ~EventHandler(){};
};

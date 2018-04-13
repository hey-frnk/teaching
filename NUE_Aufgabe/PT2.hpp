#include "Signal.hpp"

#ifndef PT2_HPP
#define PT2_HPP

class PT2 : public Signal{
private:
  double a;
  double b;
public:
  PT2(sim simulationSpecs, double a, double b);
  double geta();
  double getb();
  std::string printInformation();
};

#endif

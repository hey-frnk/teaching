#include <string>
#include <sstream>
#include "Signal.hpp"

#ifndef CONSTANTSOURCE_HPP
#define CONSTANTSOURCE_HPP

class ConstantSource : public Signal{
private:
  double Amplitude;   // Amplitude des Signals
public:
  ConstantSource(sim simulationSpecs, double Amplitude);
  double getAmplitude();
  std::string printInformation();
};

#endif

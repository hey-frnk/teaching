#include <string>
#include <sstream>
#include "Signal.hpp"

#ifndef SINESOURCE
#define SINESOURCE

class SineSource : public Signal{
private:
  double Amplitude;   // Amplitude des Signals
  double Frequency;
  double DutyCycle;
public:
  SineSource(sim simulationSpecs, double Amplitude, double Frequency, double DutyCycle);
  double getAmplitude();
  double getFrequency();
  double getDutyCycle();
  std::string printInformation();
};

#endif

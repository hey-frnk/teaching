#include <string>
#include <sstream>
#include "Signal.hpp"

#ifndef RECTSOURCE
#define RECTSOURCE

class RectSource : public Signal{
private:
  double Amplitude;   // Amplitude des Signals
  double Frequency;
  double DutyCycle;
public:
  RectSource(sim simulationSpecs, double Amplitude, double Frequency, double DutyCycle);
  double getAmplitude();
  double getFrequency();
  double getDutyCycle();
  std::string printInformation();
};

#endif

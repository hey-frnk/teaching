/*#include <string>
#include <sstream>
#include "Signal.hpp"

#ifndef POWERSUPPLY_HPP
#define POWERSUPPLY_HPP

class PowerSupply : public Signal{              // Abstrakte Klasse Netzteil!
protected:
  std::string instanceLog;
public:
  PowerSupply(sim simulationSpecs);
  virtual void addSignal(Signal* signalInstance);          // Zwei Signalquellen addieren
  virtual void multiplySignal(Signal* signalInstance);     // Zwei Signalquellen multiplizieren
  virtual std::string printSourceInformation() = 0;
  ~PowerSupply();
};

#endif
*/

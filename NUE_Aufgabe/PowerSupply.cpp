/*#include "Signal.hpp"
#include "PowerSupply.hpp"

PowerSupply::PowerSupply(sim simulationSpecs) : Signal(simulationSpecs) {}

void PowerSupply::addSignal(Signal* signalInstance){
  Signal::addSignal(signalInstance);
  std::stringstream instanceL;
  instanceL << instanceLog << ", Added: (";
  PowerSupply* instance = dynamic_cast<PowerSupply*>(signalInstance);
  if(instance != nullptr) instanceL << instance -> printSourceInformation();
  instanceL << ")";
  instanceLog = instanceL.str();
}

void PowerSupply::multiplySignal(Signal* signalInstance){
  Signal::multiplySignal(signalInstance);
  std::stringstream instanceL;
  instanceL << instanceLog << ", Multiplied: (";
  PowerSupply* instance = dynamic_cast<PowerSupply*>(signalInstance);
  if(instance != nullptr) instanceL << instance -> printSourceInformation();
  instanceL << ")";
  instanceLog = instanceL.str();
}

PowerSupply::~PowerSupply(){}
*/

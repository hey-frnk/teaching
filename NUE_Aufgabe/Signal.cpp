#include "Signal.hpp"

Signal::Signal(sim simulationSpecs) :
  simulationSpecs(simulationSpecs)
{
  simulationData = new double[simulationSpecs.sim_sampleCount]();
}

std::string Signal::printInformation(){
  return "Signal";
}

double* Signal::getSimulationData(){
  return simulationData;
}

sim Signal::getSimulationSpecs(){
  return simulationSpecs;
}

Signal::~Signal(){
  delete[] simulationData;
}

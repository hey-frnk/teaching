#include "Signal.hpp"
#include "ConstantSource.hpp"

ConstantSource::ConstantSource(sim simulationSpecs, double Amplitude) :
  Signal(simulationSpecs), Amplitude(Amplitude)
{
  // Simulation starten: konstanter Spannungswert!
  for(int i = 0; i < simulationSpecs.sim_sampleCount; ++i) simulationData[i] = Amplitude;
  std::stringstream instanceL;
  instanceL << "Source Type: VDC, Amplitude: " << Amplitude;
  instanceLog = instanceL.str();
}

double ConstantSource::getAmplitude(){
  return Amplitude;
}

std::string ConstantSource::printInformation(){
  std::stringstream output;
  output << instanceLog;
  return output.str();
}

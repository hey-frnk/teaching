#include <iostream>
#include <cmath>
#include "Signal.hpp"
#include "SineSource.hpp"

SineSource::SineSource(sim simulationSpecs, double Amplitude, double Frequency, double DutyCycle) :
  Signal(simulationSpecs), Amplitude(Amplitude), Frequency(Frequency), DutyCycle(DutyCycle)
{
  // Simulation starten: Sinus!
  for(int i = 0; i < simulationSpecs.sim_sampleCount; ++i){
    double t_Relative = std::fmod(i * simulationSpecs.sim_sampleInterval, 1.0 / Frequency);
    if(t_Relative < DutyCycle / Frequency) simulationData[i] = Amplitude * std::sin((M_PI * t_Relative) / (DutyCycle / Frequency));
    else simulationData[i] = -Amplitude * std::sin((M_PI * (t_Relative - DutyCycle / Frequency)) / ((1 - DutyCycle) / Frequency));
  }
  std::stringstream instanceL;
  instanceL << "Source Type: SIN, Amplitude: " << Amplitude;
  instanceLog = instanceL.str();
}

double SineSource::getAmplitude(){
  return Amplitude;
}

double SineSource::getFrequency(){
  return Frequency;
}

double SineSource::getDutyCycle(){
  return DutyCycle;
}

std::string SineSource::printInformation(){
  std::stringstream output;
  output << instanceLog;
  return output.str();
}

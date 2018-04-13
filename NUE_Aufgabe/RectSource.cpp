#include <iostream>
#include <cmath>
#include "Signal.hpp"
#include "RectSource.hpp"

RectSource::RectSource(sim simulationSpecs, double Amplitude, double Frequency, double DutyCycle) :
  Signal(simulationSpecs), Amplitude(Amplitude), Frequency(Frequency), DutyCycle(DutyCycle)
{
  // Simulation starten: Rechteck!
  for(int i = 0; i < simulationSpecs.sim_sampleCount; ++i){
    double t_Relative = std::fmod(i * simulationSpecs.sim_sampleInterval, 1.0 / Frequency);
    if(t_Relative < DutyCycle / Frequency) simulationData[i] = Amplitude;
    else simulationData[i] = -Amplitude;
  }
  std::stringstream instanceL;
  instanceL << "Source Type: REC, Amplitude: " << Amplitude;
  instanceLog = instanceL.str();
}

double RectSource::getAmplitude(){
  return Amplitude;
}

double RectSource::getFrequency(){
  return Frequency;
}

double RectSource::getDutyCycle(){
  return DutyCycle;
}

std::string RectSource::printInformation(){
  std::stringstream output;
  output << instanceLog;
  return output.str();
}

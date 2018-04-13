#include <cmath>
#include "Signal.hpp"
#include "PT2.hpp"

PT2::PT2(sim simulationSpecs, double a, double b) :
  Signal(simulationSpecs), a(a), b(b)
{
  double rD = a * a - 4.0 * b;
  double B = 1.0 / (2.0 * b);
  double D = 0.0;

  if(rD > 0){ // Aperiodischer Fall
    D = std::sqrt(rD);
    for(int i = 0; i < simulationSpecs.sim_sampleCount; ++i){
      double t = simulationSpecs.sim_sampleInterval * i;
      simulationData[i] = (std::exp(B * (D - a) * t) - std::exp(-B * (D + a) * t)) / D;
    }
  }
  else if(rD < 0){  // Periodisch
    D = std::sqrt(std::fabs(rD));
    for(int i = 0; i < simulationSpecs.sim_sampleCount; ++i){
      double t = simulationSpecs.sim_sampleInterval * i;
      simulationData[i] = (2.0 * std::exp(-a * B * t) * std::sin(B * D * t)) / D;
    }
  }
  else{ // Fehlerhaft fuer ap. Grenzfall
    for(int i = 0; i < simulationSpecs.sim_sampleCount; ++i){
      simulationData[i] = 0.0;
    }
  }

  std::stringstream instanceL;
  instanceL << "System: PT2. Transfer function: H(s) = 1 / (1 + " << a << " * s + " << b << " * s^2)";
  instanceLog = instanceL.str();
}

double PT2::geta(){
  return a;
}

double PT2::getb(){
  return b;
}

std::string PT2::printInformation(){
  std::stringstream output;
  output << instanceLog;
  return output.str();
}

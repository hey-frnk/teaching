#include <string>
#include <sstream>

#ifndef SIGNAL_HPP
#define SIGNAL_HPP

typedef struct sim{
  int     sim_sampleCount;      // Wie viele Simulationspunkte?
  double  sim_sampleInterval;   // Wie ist der Zeitabstand zwischen zwei Simulationspunkten
  double  sim_sampleFrequency;  // Was ist die Simulationsfrequenz?
  double  sim_timeLength;       // Was ist die gesamte Simulationsdauer?
} sim;

class Signal{
protected:
  double* simulationData;       // Simulationswerte
  sim simulationSpecs;          // Simulationseckdaten
  std::string instanceLog;
public:
  Signal(sim simulationSpecs);
  virtual std::string printInformation();
  double* getSimulationData();
  sim getSimulationSpecs();
  virtual ~Signal();
};

#endif

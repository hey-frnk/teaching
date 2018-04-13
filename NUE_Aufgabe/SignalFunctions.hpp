// Signal Functions
#include "Signal.hpp"

// Signale addieren
Signal* addSignal(sim simulationSpecs, Signal* instance1, Signal* instance2);

// Signale multiplizieren
Signal* multiplySignal(sim simulationSpecs, Signal* instance1, Signal* instance2);

// Zeitdiskrete Faltung
Signal* convolveSignal(Signal* instance1, Signal* instance2);

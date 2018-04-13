#include "Signal.hpp"
#include "SignalFunctions.hpp"

Signal* addSignal(sim simulationSpecs, Signal* instance1, Signal* instance2){
  // Zwei Signalquellen addieren
  Signal* resultInstance = new Signal(simulationSpecs);
  double* resultData = resultInstance -> getSimulationData();
  double* instance1Data = instance1 -> getSimulationData();
  double* instance2Data = instance2 -> getSimulationData();

  for(int i = 0; i < simulationSpecs.sim_sampleCount; ++i){
    resultData[i] = instance1Data[i] + instance2Data[i];
  }

  return resultInstance;
}

Signal* multiplySignal(sim simulationSpecs, Signal* instance1, Signal* instance2){
  // Zwei Signalquellen addieren
  Signal* resultInstance = new Signal(simulationSpecs);
  double* resultData = resultInstance -> getSimulationData();
  double* instance1Data = instance1 -> getSimulationData();
  double* instance2Data = instance2 -> getSimulationData();

  for(int i = 0; i < simulationSpecs.sim_sampleCount; ++i){
    resultData[i] = instance1Data[i] * instance2Data[i];
  }

  return resultInstance;
}

Signal* convolveSignal(Signal* instance1, Signal* instance2){
  // Instance1: Data, Instance2: Kernel
  Signal* resultInstance = new Signal(instance1 -> getSimulationSpecs());
  double* resultData = resultInstance -> getSimulationData();
  double* instance1Data = instance1 -> getSimulationData();
  double* instance2Data = instance2 -> getSimulationData();

  for(int i = 0; i < instance1 -> getSimulationSpecs().sim_sampleCount; ++i){
    for(int j = 0; j < instance2 -> getSimulationSpecs().sim_sampleCount; ++j){
      if(i - j >= 0){
        resultData[i] += instance1Data[i - j] * instance2Data[j];
      }
    }
    resultData[i] *= instance1 -> getSimulationSpecs().sim_sampleInterval;
  }

  return resultInstance;
}

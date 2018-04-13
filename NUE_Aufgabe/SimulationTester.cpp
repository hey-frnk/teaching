#include <iostream>
#include <fstream>
#include "Signal.hpp"
#include "SignalFunctions.hpp"
#include "ConstantSource.hpp"
#include "SineSource.hpp"
#include "RectSource.hpp"
#include "PT2.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  // 1. Simulationsdatensatz: Alle Zeitsignale
  int     sim_sampleCount       = 5000;
  double  sim_timeLength        = 0.075;
  double  sim_sampleInterval    = sim_timeLength / sim_sampleCount;
  double  sim_sampleFrequency   = 1 / sim_sampleInterval;
  sim newSimulation = {sim_sampleCount, sim_sampleInterval, sim_sampleFrequency, sim_timeLength};

  // 2. Simulationsdatensatz: Impulsantwort, viertelsolang
  int     sim_sampleCount2       = sim_sampleCount / 4;
  double  sim_timeLength2        = sim_timeLength / 4;
  double  sim_sampleInterval2    = sim_timeLength2 / sim_sampleCount2;
  double  sim_sampleFrequency2   = 1.0 / sim_sampleInterval2;
  sim newSimulation2 = {sim_sampleCount2, sim_sampleInterval2, sim_sampleFrequency2, sim_timeLength2};

  // 3. Simulationsdatensatz: Impulsantwort, doppeltsolang
  int     sim_sampleCount3       = sim_sampleCount * 2;
  double  sim_timeLength3        = sim_timeLength * 2;
  double  sim_sampleInterval3    = sim_timeLength3 / sim_sampleCount3;
  double  sim_sampleFrequency3   = 1.0 / sim_sampleInterval3;
  sim newSimulation3 = {sim_sampleCount3, sim_sampleInterval3, sim_sampleFrequency3, sim_timeLength3};

  // Zeitvektor erstellen
  double* t = new double[newSimulation.sim_sampleCount];
  for(int i = 0; i < newSimulation.sim_sampleCount; ++i) t[i] = newSimulation.sim_sampleInterval * i;

  // Abtastsignal erstellen
  Signal* rect = new RectSource(newSimulation, 0.5, 555.0, 0.25);
  Signal* offset = new ConstantSource(newSimulation, 0.5);

  // Abtastsignal addieren
  Signal* sampleSignal = addSignal(newSimulation, rect, offset);

  // Nutzsignal generieren
  Signal* sine = new SineSource(newSimulation, 1.0, 100.0, 0.5);

  // Abtastung durchfuehren: Multiplikation
  Signal* sampledSine = multiplySignal(newSimulation, sine, sampleSignal);

  // Kanal erstellen
  Signal* channel = new PT2(newSimulation2, 1.448595984E-4, 3.582244802E-8);

  // Nach Uebertragung durch Kanal
  Signal* channelOutput = convolveSignal(sampledSine, channel);

  // Rekonstruktionstiefpass erstellen
  Signal* lowpass = new PT2(newSimulation3, 6.3E-3, 9.72E-6);

  // Nach Rueckgewinnung
  Signal* result = convolveSignal(channelOutput, lowpass);

  // Signal verstaerken
  Signal* multiplier = new ConstantSource(newSimulation, 15.0);
  Signal* amplifiedResult = multiplySignal(newSimulation, result, multiplier);

  // Ausgeben
  ofstream outputFile("output.txt");
  for(int16_t i = 0; i < newSimulation.sim_sampleCount; ++i){
    outputFile << t[i] << " " << \
    sampleSignal -> getSimulationData()[i] << " " << \
    sine -> getSimulationData()[i] << " " << \
    sampledSine -> getSimulationData()[i] << " " << \
    channelOutput -> getSimulationData()[i] << " " << \
    amplifiedResult -> getSimulationData()[i] << endl;
  }
  outputFile.close();

  // Weitere Dateien ausgeben:
  // Impulsantwort des Kanals
  ofstream chImpulse("output_chImpulse.txt");
  for(int16_t i = 0; i < newSimulation2.sim_sampleCount; ++i){
    chImpulse << newSimulation2.sim_sampleInterval * i << " " << channel -> getSimulationData()[i] << endl;
  }
  chImpulse.close();

  // Impulsantwort des TP-Rekonstruktionsfilters
  ofstream lpImpulse("output_lpImpulse.txt");
  for(int16_t i = 0; i < newSimulation3.sim_sampleCount; ++i){
    lpImpulse << newSimulation3.sim_sampleInterval * i << " " << lowpass -> getSimulationData()[i] << endl;
  }
  lpImpulse.close();

  // Speicher freigeben...
  // arrrgh diese Schreibarbeit wenn man uebersichtkeitshalber ausnahmsweise kein Array erstellt!
  delete[] t;
  delete rect;
  delete offset;
  delete sampleSignal;
  delete sine;
  delete sampledSine;
  delete channel;
  delete channelOutput;
  delete lowpass;
  delete result;
  delete multiplier;
  delete amplifiedResult;
}

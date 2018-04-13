#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

// Bibliothek zur Erstellung von BMP-Grafiken
#include "himage.h"

using namespace std;

// Mit allocateMatrix wird eine neue, uninitialisierte Matrix reserviert
double** allocateMatrix(int n){
  // Hier Code einfuegen
}

// Mit deallocateMatrix soll eine nicht mehr benoetigte Matrix freigegeben werden
void deallocateMatrix(double** arr, int n){
  // Hier Code einfuegen
}

// extend erweitert die Matrix rechts, links, oben und unten mit einer Reihe von Elementen
// Alle Werte am neuen Rand nehmen den Wert r an.
double** extend(double** arr, int& n, double r){
  n += 2; // +2 Spalten, +2 Zeilen
  double** newArr = allocateMatrix(n);  // Neue Matrix erstellen

  // Hier Code einfuegen: Alte Matrix zentriert in die neue Matrix einfuegen

  deallocateMatrix(arr, n - 2); // Alte Matrix freigeben
  return newArr;
}

// Iterationsschritt
void step(double** arr, int n, double d){
  // Hier Code einfuegen
}


// Beginn interne Funktionen. Ab hier sollte nichts mehr veraendert werden

// renderMatrix schreibt die Matrix in eine BMP-Bilddatei. Hier nix veraendern!
void renderMatrix(double** arr, int n, string filename){
  hImage* image1 = new hImage(n, n, filename + ".bmp");
  for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) image1 -> setBWPixel(i, j, 255 * (1 - arr[i][j]));
  cout << "Bitmap successfully written to :" << image1 -> saveAndReturnPath() << "." << endl;
  delete image1;
}

// Simulation. Hier nichts veraendern!
int main(){
  // Matrix-Dimension (n x n)
  // = Anzahl der Bildpunkte in der Laenge/Breite
  int n = 128;

  // Neue Matrix erstellen
  double** matrix = allocateMatrix(n);
  // Alle Elemente initialisieren mit 0
  for(int i = 0; i < n; ++i) for(int j = 0; j < n; j++) matrix[i][j] = 0;
  // Inhomogenitaet (Anfangsbedingung) hinzufuegen: Viertelkreis am Rand links unten und Rechteckstreifen am rechten Rand!
  for(int i = 0; i < n; ++i) for(int j = 0; j < n; j++) if(sqrt(i * i + j * j) <= (n >> 1)) matrix[n - i - 1][j] = 1;
  for(int i = 0; i < n; ++i) for(int j = 0; j < n; j++) if(j > (n >> 1) + (n >> 2) + (n >> 4) && j < n) matrix[i][j] = 1;

  // Rand mit definierten Werten befuellen
  matrix = extend(matrix, n, 0.2);
  renderMatrix(matrix, n, "2_Anfangszustand");

  // Erste Simulation: 10 Iterationsschritte
  for(int i = 0; i < 10; ++i) step(matrix, n, 0.1);
  renderMatrix(matrix, n, "3_Nach10Iterationen");

  // Zweite Simulation: Noch mal 20 Schritte drauf
  for(int i = 0; i < 20; ++i) step(matrix, n, 0.1);
  renderMatrix(matrix, n, "4_20IterationenMehr");

  // Dritte und vierte Simulation: 200 bzw. 800 Schritte mehr
  for(int i = 0; i < 200; ++i) step(matrix, n, 0.1);
  renderMatrix(matrix, n, "5_200IterationenMehr");
  for(int i = 0; i < 800; ++i) step(matrix, n, 0.1);
  renderMatrix(matrix, n, "6_800IterationenMehr");
}

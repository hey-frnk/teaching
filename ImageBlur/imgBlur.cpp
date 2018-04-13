#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

#include "himage.h"

using namespace std;

// Mit allocateMatrix wird eine neue, uninitialisierte Matrix reserviert
double** allocateMatrix(int n){
  double** arr = new double*[n];
  if(arr == nullptr) exit(-1);
  for(int i = 0; i < n; ++i) arr[i] = new double[n];
  return arr;
}

// Mit deallocateMatrix soll eine nicht mehr benoetigte Matrix freigegeben werden
void deallocateMatrix(double** arr, int n){
  for(int i = 0; i < n; ++i) delete[] arr[i];
  delete[] arr;
}

// extend erweitert die Matrix rechts, links, oben und unten mit einer Reihe von Elementen
// Alle Werte am neuen Rand nehmen den Wert r an.
double** extend(double** arr, int& n, double r){
  n += 2; // +2 Spalten, +2 Zeilen
  double** newArr = allocateMatrix(n);  // Neue Matrix erstellen

  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      if((i > 0) && (i < n - 1)){
        if((j > 0) && (j < n - 1)) newArr[i][j] = arr[i - 1][j - 1]; // Inneres Element? Ja -> kopieren
        else newArr[i][j] = r; // Sonst mit r auffuellen
      } else newArr[i][j] = r; // Sonst mit r auffuellen
    }
  }

  deallocateMatrix(arr, n - 2); // Alte Matrix freigeben
  return newArr;
}

// Iterationsschritt
void step(double** arr, int n, double d){
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      // Inneres Matrixelement?
      if((i > 0) && (i < n - 1)){
        if((j > 0) && (j < n - 1)){
          // Dann Iterationsschritt nach Formel anwenden
          double above = arr[i - 1][j];  // above
          double below = arr[i + 1][j];  // below
          double left = arr[i][j - 1];   // left
          double right = arr[i][j + 1];  // right
          arr[i][j] = d * (left + right + above + below) + (1 - 4 * d) * arr[i][j];
        }
      }
    }
  }
}


// Beginn interne Funktionen. Ab hier sollte nichts mehr veraendert werden

// renderMatrix schreibt die Matrix in eine BMP-Bilddatei. Hier nix veraendern!
void renderMatrix(double*** arr, int n, string filename){
  hImage* image1 = new hImage(n, n, filename + ".bmp");

  for(int i = 0; i < 3; ++i) for(int j = 0; j < n; ++j) for(int k = 0; k < n; ++k) image1->setPixel(j, k, (uint8_t)(arr[i][j][k] * 255.0), i);

  cout << "Bitmap successfully written to :" << image1 -> saveAndReturnPath() << "." << endl;
  delete image1;
}

// Simulation. Hier nichts veraendern!
int main(int argc, char const *argv[]){
  cout << "ImgBlur blurs your favorite picture!" << endl;
  // Bild einlesen
  if (argc == 1){
    cout << "Keine Datei angegeben. Programm wird beendet!" << endl;
    exit(-1);
  }

  string fileName = argv[1];

  hImage* image1 = new hImage(fileName);
  int* n = new int[3];
  for(int i = 0; i < 3; ++i) n[i] = image1 -> getWidth();

  // Neue Matrix von Matrizen erstellen
  double*** bgrMatrix = new double**[3];
  for(int i = 0; i < 3; ++i) bgrMatrix[i] = allocateMatrix(n[i]);

  // BGR einlesen
  for(int i = 0; i < 3; ++i) for(int j = 0; j < n[i]; ++j) for(int k = 0; k < n[i]; ++k) bgrMatrix[i][j][k] = (image1 -> getPixel(j, k, i)) / 255.0;

  // Rand mit definierten Werten befuellen
  // for(int i = 0; i < 3; ++i) bgrMatrix[i] = extend(bgrMatrix[i], n[i], 1.0 / 255.0);


  for(int i = 0; i < 3; ++i) for(int j = 0; j < 600; ++j) step(bgrMatrix[i], n[i], 0.1);
  renderMatrix(bgrMatrix, n[0], fileName.substr(0, fileName.length() - 4) + "_output");
}

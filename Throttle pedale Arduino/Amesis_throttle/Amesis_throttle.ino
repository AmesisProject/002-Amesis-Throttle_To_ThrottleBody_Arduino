/*Amesis_throttle v1.0 18/05/2021
GitHub

But : utiliser une pedale de VR5 170 cv branché  l'arduino pour retourné sur le port serie une valeur entre 0 et 100%

Branchement

 Pedale   /  Calculateur   /   ArduinoMega    
 1            72               5v
 2            -                -               
 3            -                -              
 4            -                -               
 5            33               Gnd
 6            34               A0

 
*/

const int PedalePin = A0;             // Pin analogique d'enté (input) du potentiometre
      int Pedale = 0;                 // lire la vleur du potentiometre
      int PedaleValeur = 0;           // valeur entre 0 et 100%



void setup() {
  // initialisation du pot serie a 9600 bps:
  Serial.begin(9600);
}



void loop() {
  // Lectue de la valeur annalogique:
  Pedale = analogRead(PedalePin);
  
  // Fonction "map" de mise à l'echelle :
  PedaleValeur = map(Pedale, 70, 474, 0, 100);
  
  // On renvoi les info sur le port serie pour la consol arduino
  
  Serial.print("Position de la pedale est à = ");
  Serial.print(PedaleValeur);
  Serial.println("%");

  // On attend 2 miliseconde pour que notre montage soit stable 
  delay(2);
}










/*
Amesis_throttle 18/05/2021
GitHub

const int Pedale = A0;  // Pin analogique d'enté (input) du potentiometre
//const int analogOutPin = 9; // Pin de sortie (outout) moteur ou led

int PedaleValeur = 0;        // lire la vleur du potentiometre
//int outputValue = 0;        // ecrie la valeur du potentiometre

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // Lectue de la valeur annalogique:
  PedalValeur = analogRead(Pedale);
  
  // Fonction "map" de mise à l'echelle :
  outputValue = map(PedaleValeur, 0, 1023, 0, 100);
  
  // change the analog out value:
  //analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("Position de la pedale est à = ");
  Serial.print(PedaleValeur);
  //Serial.print("\t output = ");
  //Serial.println(outputValue);

  // On attend 2 miliseconde pour que notre montage soit stable 
  delay(2);
}
*/

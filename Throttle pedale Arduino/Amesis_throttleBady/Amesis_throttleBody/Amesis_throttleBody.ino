/* Amesis Project 
   ^ ^
 =( '' )=
  (")_(")
Youtube   : https://www.youtube.com/channel/UCCexVZN3UYSep2lsj2jVjdg?sub_confirmation=1
GitHub    : https://github.com/AmesisProject
Discord   : https://discord.gg/vRAybmd3hk
FaceBook  : https://www.facebook.com/amesis.pro.5
Instagram : https://www.instagram.com/?hl=fr
  
  licence OpenSource non comercialisable, modifiable en citant le propriétaire AmesisProject avec l'un des liens ci dessus
  Sur base de l'exmple arduino AnalogInOutSerial
  
NomDuProjet : Amesis_throttle 
Version     : v1.0 18/05/2021
ButDuProjet : Renvoyer la valeur de la pédale (du groupe VAG "VR5 AQN" de 0 à 100 % sur le port serie.
ProjetDisponibleIciGitHub : https://github.com/AmesisProject/002-Amesis-Throttle_To_ThrottleBody_Arduino/tree/main/Throttle%20pedale%20Arduino

Merci de faire suivre sur github toute modification au amélioration du code.

Branchement :

 Pedale   /  Calculateur   /   ArduinoMega    
 1            72               5v
 2            -                -               
 3            -                -              
 4            -                -               
 5            33               Gnd
 6            34               A0

*/
//////////////////////////////
// Déclaration des variable //
//////////////////////////////

const int PedalePin = A0;             // Pin analogique d'enté (input) du potentiometre
      int Pedale = 0;                 // lire la vleur du potentiometre
      int PedaleValeur = 0;           // valeur entre 0 et 100%

      
///////////////////////////////
//Inicialisation du l'arduino//
///////////////////////////////

void setup() {
  // initialisation du port serie a 9600 bps:
  Serial.begin(9600);
}

///////////////////////////////////
//Programme en bloucle du projet //
///////////////////////////////////

void loop() {
  // Lectue de la valeur annalogique:
  Pedale = analogRead(PedalePin);
  
  // Fonction "map" de mise à l'echelle : le 70 et 474 sont les valeur de ma pédale, il se peut que d'autre pédale et des valeur differente, pour les trouver remplacer les valeur "PedaleValeur = map(Pedale, X, Y, 0, 100);" X et Y par X = 0 et Y = 1023 et controlez votre debut/fin de course de votre pédale, vous trouvereai votre propre X et Y 
  PedaleValeur = map(Pedale, 82, 919, 0, 100);
  
  // On renvoi les info sur le port serie pour la consol arduino
  Serial.print("Position de la pedale est à = ");
  Serial.print(PedaleValeur);
  Serial.println("%");

  // On attend 2 miliseconde pour que notre montage soit stable 
  delay(2);
}

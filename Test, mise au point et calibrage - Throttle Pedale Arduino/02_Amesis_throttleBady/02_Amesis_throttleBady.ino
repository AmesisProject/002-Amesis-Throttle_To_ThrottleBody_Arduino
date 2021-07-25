/* Amesis Project 
   ^ ^
 =( '' )=
  (")_(")
Youtube   : https://www.youtube.com/channel/UCCexVZN3UYSep2lsj2jVjdg?sub_confirmation=1
GitHub    : https://github.com/AmesisProject
Discord   : https://discord.gg/vRAybmd3hk
FaceBook  : https://www.facebook.com/amesis.pro.5
Instagram : https://www.instagram.com/?hl=fr
  
  licence OpenSource non comercialisable, modifiable en citant 
  le propriétaire AmesisProject avec l'un des liens ci dessus
  Sur base de l'exmple arduino AnalogInOutSerial

002-Amesis-Throttle_To_ThrottleBody_Arduino
NomDuProjet : Amesis_throttleBody 
Version     : v1.0 20/05/2021
ButDuProjet : Renvoyer la valeur du potentiometre (TPS) du papillon motorisé  (throttle body)du groupe VAG "VR5 AQN" de 0 à 100 % sur le port serie.
ProjetDisponibleIciGitHub : https://github.com/AmesisProject/002-Amesis-Throttle_To_ThrottleBody_Arduino/tree/main/Throttle%20pedale%20Arduino

Merci de faire suivre sur github toute modification ou amélioration du code.

Branchement :

 ThrottleBody   /  Calculateur   /   ArduinoMega    
 1                  -                 -
 2                  83                Gnd               
 3                  -                 -              
 4                  84                A1               
 5                  -                 -
 6                  91                +5V

*/
//////////////////////////////
// Déclaration des variable //
//////////////////////////////

const int TpsPin = A1;                // Pin analogique d'enté (input) du potentiometre tps
      int TpsNumerique = 0;                 // lire la vleur du potentiometre en numerique de 0 à 1023
      int TpsValeur = 0;           // valeur entre 0 et 100% convertie depuis la valeur 0 à 1023

      
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
  TpsNumerique = analogRead(TpsPin);
  
  // Fonction "map" de mise à l'echelle : le 70 et 474 sont les valeur de ma pédale, il se peut que d'autre pédale et des valeur differente, pour les trouver remplacer les valeur "PedaleValeur = map(Pedale, X, Y, 0, 100);" X et Y par X = 0 et Y = 1023 et controlez votre debut/fin de course de votre pédale, vous trouvereai votre propre X et Y 
  TpsValeur = map(TpsNumerique, 82, 919, 0, 100);
  
  // On renvoi les info sur le port serie pour la consol arduino
  Serial.print("Position du boitier papillon (TPS) est à = ");
  Serial.print(TpsValeur);
  Serial.println("%");

  // On attend 2 miliseconde pour que notre montage soit stable 
  delay(2);
}

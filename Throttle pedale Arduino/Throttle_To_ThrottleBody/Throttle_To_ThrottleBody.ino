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
002-Amesis-Throttle_To_ThrottleBody_Arduino  
NomDuProjet : Amesis_throttle_To_ThrottleBody
Version     : v1.0 25/05/2021
ButDuProjet : Renvoyer la valeur de la pédale et du boitier papillon (du groupe VAG "VR5 AQN" de 0 à 100 % sur le port serie.
ProjetDisponibleIciGitHub : https://github.com/AmesisProject/002-Amesis-Throttle_To_ThrottleBody_Arduino/tree/main/Throttle%20pedale%20Arduino
Merci de faire suivre sur github toute modification au amélioration du code.
Branchement :
 Pedale        /  Calculateur    /   ArduinoMega    
 1                 72                 5v
 2                 -                  -               
 3                 -                  -              
 4                 -                  -               
 5                 33                 Gnd
 6                 34                 A0

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

const int PedalePin = A0;             // Pin analogique d'enté (input) du potentiometre
      int PedaleNumerique = 0;        // lire la vleur du potentiometre en numerique de 0 à 1023
      int PedaleValeur = 0;           // valeur entre 0 et 100% simplement la conversion du 0 à 1023 en 0 à 100%

const int TpsPin = A1;                // Pin analogique d'enté (input) du potentiometre tps
      int TpsNumerique = 0;           // lire la vleur du potentiometre en numerique de 0 à 1023
      int TpsValeur = 0;              // valeur entre 0 et 100% convertie depuis la valeur 0 à 1023

      int tempsDelay = 2;             //Pour la stabilité ou la lecture 
      
///////////////////////////////
//Inicialisation du l'arduino//
///////////////////////////////

void setup() {
  
  Serial.begin(115200);                  // initialisation du port serie a 9600 bps:  
  
}

///////////////////////////////////
//Programme en bloucle du projet //
///////////////////////////////////

void loop() {
 
 //______________________________________________________________________
 //Lecture Pédale
 
  PedaleNumerique = analogRead(PedalePin);                      // Lecture de la valeur annalogique
  PedaleValeur = map(PedaleNumerique, 76, 472, 0, 100);         // Fonction "map" de mise à l'echelle : le 70 et 474 sont les valeur de ma pédale, il se peut que d'autre pédale et des valeur differente, pour les trouver remplacer les valeur "PedaleValeur = map(Pedale, X, Y, 0, 100);" X et Y par X = 0 et Y = 1023 et controlez votre debut/fin de course de votre pédale, vous trouvereai votre propre X et Y 
  
  Serial.print("Position de la pedale est à = ");               // On renvoi les info sur le port serie pour la consol arduino
  Serial.print(PedaleValeur);                                   // Revoie la valeur de la variable sur le port serie
  Serial.print("%                ");                                          // Puis l'unité
 //----------------------------------------------------------------------
 
 //______________________________________________________________________
 //Lecture Boitier Papillon

   TpsNumerique = analogRead(TpsPin);                           // Lecture de la valeur annalogiqu
   TpsValeur = map(TpsNumerique, 100, 937, 0, 100);              // Fonction "map" de mise à l'echelle : le 70 et 474 sont les valeur de ma pédale, il se peut que d'autre pédale et des valeur differente, pour les trouver remplacer les valeur "PedaleValeur = map(Pedale, X, Y, 0, 100);" X et Y par X = 0 et Y = 1023 et controlez votre debut/fin de course de votre pédale, vous trouvereai votre propre X et Y 

  Serial.print("Position du boitier papillon (TPS) est à = ");  // On renvoi les info sur le port serie pour la consol arduino
  Serial.print(TpsValeur);                                      // Revoie la valeur de la variable sur le port serie
  Serial.println("%");                                          // Puis l'unité
 //----------------------------------------------------------------------
  
  delay(tempsDelay);                               // On attend un delay en miliseconde pour que notre montage soit stable 
}

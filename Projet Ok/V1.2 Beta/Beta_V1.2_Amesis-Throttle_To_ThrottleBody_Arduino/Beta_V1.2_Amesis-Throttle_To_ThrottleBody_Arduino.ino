/* Amesis Project 
    ^ ^
  =( '')=
   (")_(")
Youtube   : https://www.youtube.com/channel/UCCexVZN3UYSep2lsj2jVjdg?sub_confirmation=1
GitHub    : https://github.com/AmesisProject
Discord   : https://discord.gg/vRAybmd3hk
FaceBook  : https://www.facebook.com/amesis.pro.5
Instagram : https://www.instagram.com/?hl=fr
Amesisproject@gmail.com
  
  licence OpenSource CC-BY-NC-SA 
  non commercialisable, modifiable en citant le propriétaire AmesisProject avec les liens ci dessus
  Sur base de l'exmple arduino AnalogInOutSerial
002-Amesis-Throttle_To_ThrottleBody_Arduino  
NomDuProjet : Beta_V1.2_Amesis-Throttle_To_ThrottleBody_Arduino
Version     : Beta V1.2 30/05/2021
ButDuProjet : Renvoyer la valeur de la position pédale et position boitier papillon pour faire tourner le papillon (du groupe VAG "VR5 AQN" de 0 à 100 % sur le port serie. Et que le papillon motorisé bouge en fonctione de la position pédal.
Problème à régler : La papillon oscille très légèrement (non perseptible à l'oeil mais on l'entend) sur la version pecédante il oscillé beaucoup trop, cela été sur au serial.begin trop lent. Je l'ai carrement supprimé pour la V Beta fonctionnelle.
A ajouter : -La librairie des PID (pour affaiblire l'oscillation)
            -Trouver le moyen des renvoyer la valeur de position papillon au speeduio car actuellement elle est renvoyé a l'arduino du projet Thottle_To_ThrottleBody et non a l'arduino du Speeduno
             se problème pourrait être réglé simplement avec le second potentiomettre integré au papillon motorisé inutilisé jusqu'a présent dans le projé.
             cette solution impose 2 arduino, un pour le projet de commande papillon avec la pedale et un avec le Speeduino
ProjetDisponibleIciGitHub : https://github.com/AmesisProject/002-Amesis-Throttle_To_ThrottleBody_Arduino/tree/main/Throttle%20pedale%20Arduino
Merci de faire suivre sur github toute modification au amélioration du code et de faire remonter les evantuel problème dans l'ongle "Issues" du projet sur GitHub

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

  //Pedale//
const int PedalePin = A0;             // Pin analogique d'enté (input) du potentiometre
      int PedaleNumerique = 0;        // lire la vleur du potentiometre en numerique de 0 à 1023
      int PedaleValeur = 0;           // valeur entre 0 et 100% simplement la conversion du 0 à 1023 en 0 à 100%

  //Papillon motorisé//    
const int TpsPin = A1;                // Pin analogique d'enté (input) du potentiometre tps
      int TpsNumerique = 0;           // lire la vleur du potentiometre en numerique de 0 à 1023
      int TpsValeur = 0;              // valeur entre 0 et 100% convertie depuis la valeur 0 à 1023

  //Pont en H L298N// (Le module L298N est un module de puissance pour allimenter le moteur DC car l'arduino ne fournis pas de puissance mes des commandes)
      int motorPin1 = 8; //Ports de commande du moteur B sens horaire
      int motorPin2 = 9; //Ports de commande du moteur B sens trigonometrique
      //int enablePin = 5; //Ports de commande de la vitesse du moteur
      
  //Généralité des boucles du code//
      int tempsDelay = 2;             //Pour la stabilité ou la lecture 
      
///////////////////////////////
//Inicialisation du l'arduino//
///////////////////////////////

void setup() {
  
  TCCR1B = TCCR1B & 0b11111000 | 0x01;    //Set PWM frequency to 31.37255 kHz Augmentation de la vitesse de l'arduino pour evité le phenomène de ocillement du papillon
  
    pinMode(motorPin1, OUTPUT);           // pin de commande de moteur pour le module L298n sens horaire ou frein
    pinMode(motorPin2, OUTPUT);           // pin de commande de moteur pour le module L298n sens trigonometrique ou frein
 // pinMode(enablePin, OUTPUT);           // pin de regulation de la vitesse, si pas besoin mettre le cavalier sur le L298N 
    
 //  Serial.begin(115200);                // initialisation du port serie (ralentie énnormement le projet si activé)  
  
}

///////////////////////////////////
//Programme en bloucle du projet //
///////////////////////////////////

void loop() {
 
 //_______________________________________________________________________________________
 //Lecture Pédale
 
  PedaleNumerique = analogRead(PedalePin);                      // Lecture de la valeur annalogique
  PedaleValeur = map(PedaleNumerique, 76, 472, 0, 1000);         // Fonction "map" de mise à l'echelle : le 70 et 474 sont les valeur de ma pédale, il se peut que d'autre pédale et des valeur differente, pour les trouver remplacer les valeur "PedaleValeur = map(Pedale, X, Y, 0, 100);" X et Y par X = 0 et Y = 1023 et controlez votre debut/fin de course de votre pédale, vous trouvereai votre propre X et Y 
  
 // Serial.print("Position de la pedale est à = ");               // On renvoi les info sur le port serie pour la consol arduino
 // Serial.print(PedaleValeur);                                   // Revoie la valeur de la variable sur le port serie
 // Serial.print("%                ");                            // Puis l'unité
 //----------------------------------------------------------------------------------------
 
 //________________________________________________________________________________________
 //Lecture Boitier Papillon

   TpsNumerique = analogRead(TpsPin);                           // Lecture de la valeur annalogiqu
   TpsValeur = map(TpsNumerique, 100, 937, 0, 1000);              // Fonction "map" de mise à l'echelle : le 70 et 474 sont les valeur de ma pédale, il se peut que d'autre pédale et des valeur differente, pour les trouver remplacer les valeur "PedaleValeur = map(Pedale, X, Y, 0, 100);" X et Y par X = 0 et Y = 1023 et controlez votre debut/fin de course de votre pédale, vous trouvereai votre propre X et Y 

  //Serial.print("Position du boitier papillon (TPS) est à = ");  // On renvoi les info sur le port serie pour la consol arduino
  //Serial.print(TpsValeur);                                      // Revoie la valeur de la variable sur le port serie
  //Serial.println("%");                                          // Puis l'unité
 //-----------------------------------------------------------------------------------------

 //_________________________________________________________________________________________
 //Formule de commande du papillon motorisé en fonction de la position pédal
 
      if ( PedaleValeur >= TpsValeur)        //si la valeur de la pedale est superieur à la valeur du potantiometre du papillon motorisé 
      {                                     //Alor on applique le code de rotation horaire du papillon
        digitalWrite(motorPin1, HIGH);      
        digitalWrite(motorPin2, LOW);
      //  Serial.print("Avant ");
      }
      
      else                                  //Sinon on Stop le moteur (freinage)
      {                                     //Aplication du code de freinage du moteur
        digitalWrite(motorPin1, HIGH); 
        digitalWrite(motorPin2, HIGH);
      // Serial.println("Stop");
      }
    
    
 //---------------------------------------------------------------------------------------------
 // delay(tempsDelay);                               // On attend un delay en miliseconde pour que notre montage soit stablepour les testes
}

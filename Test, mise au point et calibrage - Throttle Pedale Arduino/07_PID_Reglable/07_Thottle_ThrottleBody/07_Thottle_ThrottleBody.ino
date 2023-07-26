
/* Amesis Project 
   ^ ^
 =( '' )=
  (")_(")
  
  https://github.com/AmesisProject/002-Amesis-Throttle_To_ThrottleBody_Arduino
  
Youtube   : https://www.youtube.com/channel/UCCexVZN3UYSep2lsj2jVjdg?sub_confirmation=1
GitHub    : https://github.com/AmesisProject
Discord   : https://discord.gg/vRAybmd3hk
FaceBook  : https://www.facebook.com/amesis.pro.5
Instagram : https://www.instagram.com/?hl=fr
  
  licence OpenSource CC-BY-NC-SA
  licence OpenSource non comercialisable, modifiable en citant le propriétaire AmesisProject avec l'un des liens ci dessus
  
002-Amesis-Throttle_To_ThrottleBody_Arduino  
NomDuProjet : Thottle_ThrottleBody_Test_Activat
Version     : v1.07 10/07/2023
ButDuProjet : Renvoyer la valeur de la pédale et du boitier papillon (du groupe VAG "VR5 AQN" de 0 à 100 % sur le port serie. Et que le papillon motorisé bouge en fonctione de la position pédal.
ProjetDisponibleIciGitHub : https://github.com/AmesisProject/002-Amesis-Throttle_To_ThrottleBody_Arduino/tree/main/Throttle%20pedale%20Arduino
Merci de faire suivre sur github toute modification au amélioration du code.
Branchement :
 Pedale        /  Calculateur ME7.1   /   ArduinoMega    
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
/////////////
//Librairie//
/////////////
#include <PID_v1.h>

////////////////////////////
// Declarion des fonction //
////////////////////////////
void TB_LoadStatus(); 

//////////////////////////////
// Déclaration des variables //
//////////////////////////////

  //Pedale electronique//
const int PPS1_Pin = A0;           // Pin analogique d'enté (input) du potentiometre
      int PPS1_Numerique = 0;      // lire la vleur du potentiometre en numerique de 0 à 1023
      int PPS1_Position = 0;       // valeur entre 0 et 100% simplement la conversion du 0 à 1023 en 0 à 100%
const int PPS1_Calib_Mini = 166;   // Valeur de calibrage Mini capteur pedale 1
const int PPS1_Calib_Maxi = 953;   // Valeur de calibrage Maxi capteur pedale 1      

const int PPS2_Pin = A1;           // Pin analogique d'enté (input) du potentiometre
      int PPS2_Numerique = 0;      // lire la vleur du potentiometre en numerique de 0 à 1023
      int PPS2_Position = 0;       // valeur entre 0 et 100% simplement la conversion du 0 à 1023 en 0 à 100%
const int PPS2_Calib_Mini = 140;   // Valeur de calibrage Mini capteur pedale 2
const int PPS2_Calib_Maxi = 998;   // Valeur de calibrage Maxi capteur pedale 2

      int PPSM_Position;           //variable de la moyenne des capteurs pedale 1 et 2

 //Papillon motorisé//    
const int TPSPot1_Pin = A2;        // Pin analogique d'enté (input) du potentiometre tps
      int TPSPot1_Numerique = 0;   // lire la vleur du potentiometre en numerique de 0 à 1023
      int TPS1_Position = 0;       // valeur entre 0 et 100% convertie depuis la valeur 0 à 1023
      int TPS1_Calib_Mini = 0;     // Valeur de calibrage Maxi capteur TB 1
      int TPS1_Calib_Maxi =100;    // Valeur de calibrage Maxi capteur TB 1

const int TPSPot2_Pin = A3;        // Pin analogique d'enté (input) du potentiometre tps
      int TPSPot2_Numerique = 0;   // lire la vleur du potentiometre en numerique de 0 à 1023
      int TPS2_Position = 0;       // valeur entre 0 et 100% convertie depuis la valeur 0 à 1023
      int TPS2_Calib_Mini = 0;     // Valeur de calibrage Maxi capteur TB 2
      int TPS2_Calib_Maxi = 100;   // Valeur de calibrage Maxi capteur TB 2

      int TPSM_Position ;          //variable de la moyenne des capteurs du papillon 1 et 2
      
      int TPS_Neutral ;            // valeur en % de la position neutre du papillon au repos.
      int TPS_Min ;                // valeur en % de la position mini du papillon en butée fermée
      int TPS_Max ;                // valeur en % de la position Maxi du papillon en butée ouvert
    
  //Pont en H L298N// (Le module L298N est un module de puissance pour allimenter le moteur DC car l'arduino ne fournis pas de puissance mes des commandes)
      int motorPin1 = 8;           //Ports de commande du moteur B sens horaire
      int motorPin2 = 9;           //Ports de commande du moteur B sens trigonometrique
      int enablePin = 5;           //Ports de commande de la vitesse du moteur

const int PWMMini =   0;           //Valeur Mini PMW pour l'entré ENA du module pont en H 
const int PwmMaxi = 255;           //Valeur Maxi PMW pour l'entré ENA du module pont en H
      int PwmDutyMini = 0;         //Valeur de PwmMini en %  
      int PwmDutyMaxi = 100;       //Valeur de PwmMaxi en %

  //Algrorhytme PID
      double kP ;                  //Variable Proportional  
      double kI ;                  //Variable Integral
      double kD ;                  //Variable Derive

      double Input, Output, SetPoint;     
      PID throttlePID(&Input, &Output, &SetPoint, kP, kI, kD, DIRECT);  //Création de l'objet "throttlePID"
  
  //Variadle de fonctionnement
      int ModeDegradeEtat = 0 ;    //Si il y a un defaut, il faut metre cette variable à 1 pour activer le mode degradé
  //Généralité des boucles du code//
     // int tempsDelay = 2;             //Pour la stabilité ou la lecture 
      
///////////////////////////////
//Inicialisation du l'arduino//
///////////////////////////////

void setup() {
  
  TCCR1B = TCCR1B & 0b11111000 | 0x01;    //Set PWM frequency to 31.37255 kHz Augmentation de la vitesse de l'arduino pour evité le phenomène de ocillement du papillon
//TCCR0B = TCCR0B & 0b11111000 | 0x01;    //Set PWm to 62500.00 Hz
    pinMode(motorPin1, OUTPUT);           // pin de commande de moteur pour le module L298n sens horaire ou frein
    pinMode(motorPin2, OUTPUT);           // pin de commande de moteur pour le module L298n sens trigonometrique ou frein
    pinMode(enablePin, OUTPUT);           // pin de regulation de la vitesse, si pas besoin mettre le cavalier sur le L298N 
    
    Serial.begin(115200);                 // initialisation du port serie  
  
}

///////////////////////////////////
//Programme en bloucle du projet //
///////////////////////////////////

void loop() {
 
 //_______________________________________________________________________________________
 //Lecture Pédale
 
  PPS1_Numerique = analogRead(PPS1_Pin);                        // Lecture de la valeur annalogique
  PPS1_Position = map(PPS1_Numerique, 76, 472, 0, 100);         // Fonction "map" de mise à l'echelle : le 70 et 474 sont les valeur de ma pédale, il se peut que d'autre pédale et des valeur differente, pour les trouver remplacer les valeur "PPS1_Position = map(Pedale, X, Y, 0, 100);" X et Y par X = 0 et Y = 1023 et controlez votre debut/fin de course de votre pédale, vous trouvereai votre propre X et Y 
  
  Serial.print("Position de la pedale est à = ");               // On renvoi les info sur le port serie pour la consol arduino
  Serial.print(PPS1_Position);                                   // Revoie la valeur de la variable sur le port serie
  Serial.print("%                ");                            // Puis l'unité
 //----------------------------------------------------------------------------------------
 
 //________________________________________________________________________________________
 //Lecture Boitier Papillon

   TBPot1_Numerique = analogRead(TBPot1_Pin);                           // Lecture de la valeur annalogiqu
   TB_Position = map(TBPot1_Numerique, 100, 937, 0, 100);              // Fonction "map" de mise à l'echelle : le 70 et 474 sont les valeur de ma pédale, il se peut que d'autre pédale et des valeur differente, pour les trouver remplacer les valeur "PPS1_Position = map(Pedale, X, Y, 0, 100);" X et Y par X = 0 et Y = 1023 et controlez votre debut/fin de course de votre pédale, vous trouvereai votre propre X et Y 

  Serial.print("Position du boitier papillon (TPS) est à = ");  // On renvoi les info sur le port serie pour la consol arduino
  Serial.print(TB_Position);                                      // Revoie la valeur de la variable sur le port serie
  Serial.println("%");                                          // Puis l'unité
 //-----------------------------------------------------------------------------------------

 //_________________________________________________________________________________________
 //Formule de commande du papillon motorisé en fonction de la position pédal
 
      if ( PPS1_Position > TB_Position)        //si la valeur de la pedale est superieur à la valeur du potantiometre du papillon motorisé 
      {                                     //Alor on applique le code de rotation horaire du papillon
        digitalWrite(motorPin1, HIGH);      
        digitalWrite(motorPin2, LOW);
        Serial.print("Avant ");
      }
      
      else                                  //Sinon on Stop le moteur (freinage)
      {                                     //Aplication du code de freinage du moteur
        digitalWrite(motorPin1, HIGH); 
        digitalWrite(motorPin2, HIGH);
        Serial.println("Stop");
      }
    
    
 //---------------------------------------------------------------------------------------------
 // delay(tempsDelay);                               // On attend un delay en miliseconde pour que notre montage soit stablepour les testes
}



void TB_Setting (){
  //Reglage des PID
    //throttlePID.SetTunings(kP,kI,kD);          // Pour modifier les valeurs des PID
     //KP
     //Ki
     //KD
  //Reglage de la Frequence pour le moteur DC du papillon
    //Hz
  //Reglage des PWM Mini Maxi pour la vitesse de commande du moteur
    //PwmMini
    //PwmMaxi
  //Calibration de la pelade lectronique      
    //PPS1_Calib_Mini
    //PPS1_Calib_Maxi 
    //PPS2_Calib_Mini
    //PPS2_Calib_Maxi 
    //
  //Calibration du papillon electronique
    //TPS1_Calib_Mini
    //TPS1_Calib_Maxi 
    //TPS2_Calib_Mini
    //TPS2_Calib_Maxi

}

void TB_LoadStatus() {/*  
PPS1_Position TB_Position
 if (PPS1_Position <= 100){
    //Pleinne charge : Dans VCDS la pleinne charge est uniquement le moment ou la pedale est 
                       // à 100% et a ce moment la nous nous trouvons dans la derniere 
                       //ligne de KFMIOP de la cartographie des ME7.x.x
    Serial.println("Load Status : Full load / Pleinne charge ");
 }
 else if (PPS1_Position > 1 || tps) {
    //Ralentis       : Dans VCDS le ralentis interviens quand la pedale est a 0% 
                      //et sous les 1400rpm (logiquement en négatif du point more du papillon)
    Serial.println("Load Status : Idle/Ralentis ");

    //Enrichissement : Je ne suis pas sur mais apparament ça arrive quand la pedale depasse de 10% la valeur 
                       //quelle été il y a 0.5s, autrement dit, c'est quand on note une acceleration autre 
                       //que le mode WOT pleinne charge
    Serial.println("Load Status : Enrichment / Enrichissement ");

    //Décélération   : Dans VCDS La deceleration est consideré comme le frein moteur, 
                      //quand on lache la pedale jusqu'au moment de basculement de la phase de
                      //ralenti qui prend le relais vers 1400rpm (ME7.1.1 VR6) Pendant cette 
                      //Phase de deceleration, l'injection est totalement coupé
    Serial.println("Load Status : Idle / Ralentis ");



    //Charge partielle : Dans VCDS j'ai pue noté que c'été toute plage 
                         //sauf ralenti/enrichissement/déceleration/pleinne charge 
                         //(on pourrait le considéré colle le else final)
    Serial.println("Load Status : Partial load / Charge partielle ");
*/
}

void TB_Rolling_Anti_Lag (){
//Suivant les information recu du reseaux CAN
//On ouvre ou ferme le papillon pour le rolling anti lag
}

void Gear_DSG(){
  //Suivant les information recu du reseau CAN
  //Le papillon doit être commandé au passage de vitesse en DSG s
}

}

void TB_DTC() { 
  //Si la valeur de pedale1 et > a la valeur mini du calibrage alors deffaut --> save DTC EEPROM
  //si la valeur de pedale1 et < a la valeur maxi de calibrage alors deffaut --> save DTC EEPROM
  //Si la valeur de pedale2 et > a la valeur mini du calibrage alors deffaut --> save DTC EEPROM
  //si la valeur de pedale2 et < a la valeur maxi de calibrage alors deffaut --> save DTC EEPROM
  //Si la valeur de papillon1 et > a la valeur mini du calibrage alors deffaut --> save DTC EEPROM
  //si la valeur de papillon1 et < a la valeur maxi de calibrage alors deffaut --> save DTC EEPROM
  //Si la valeur de papillon2 et > a la valeur mini du calibrage alors deffaut --> save DTC EEPROM
  //si la valeur de papillon2 et < a la valeur maxi de calibrage alors deffaut --> save DTC EEPROM
  //si la velaur 


}

void TB_CalibrateRootine(){]
//le mode calibration ne peux s'appliqué que si le moteur et a 0 RPM
//if (rpm == 0 et validation user = oui)
    // alors on relève a valeur de TB_Neutral --> on note la valeur dans l'EEPROM
    //puis en active le L298N pour ouverture du papillon pendant 2s (en millis) --> on note la valeur dans l'EEPROM
    //puis on active le L298N pour fermeture du papillon pendant 2s (en millis) --> on note la valeur dans m'EEPROM
    
}

void TB_ModeDegrade(){
  if (ModeDegradeEtat == 1 ){ 
    
  }
//Si le voltage batterie est < a 11.5v alors mode degradé
//Si le voltage batterie est > a 15 v alord mode degradé
//Si les EGT depasse X degré alor mode degrader pendant x segande
//si valeur labda depasse X AFR 
//si les 2 capteur de pedale ne correspondent pas alors mode degradé
//si les 2 capteur du papillon motorisé ne corresponde pas alor mode degradé

}

void TB_CruiseControl(){
  //Vitesse vehicule
  //Vitesse Cruise
  //Button active Cruise
  //BP++
  //BP--
  //BP Annuler Cruise
  //BP Break
  //BP Cluch
}

void Communication(){
//Peut être communiquer par reseaux Can pour avoir les valeurs de :
//Info RPM
//Info Voltage Batterie
//Info EGT
//Info Lambda AFR
//Info Vitesse véhicule

}

void UserInterface(){
//Menu par liaison serie
//Boutton de manip pour reprog les colibrages.


}

void SaveEEPROM (){

}

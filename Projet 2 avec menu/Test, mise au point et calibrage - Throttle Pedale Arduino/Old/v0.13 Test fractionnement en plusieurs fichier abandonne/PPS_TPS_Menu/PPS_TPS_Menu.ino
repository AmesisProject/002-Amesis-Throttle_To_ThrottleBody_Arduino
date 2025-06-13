/**
 * @brief Interface utilisateur par la commande serie. Pour les groupes de mesures, teste des actionneurs et adaptation.
 * @file 002-Amesis-Throttle_To_ThrottleBody_Arduino 
 * @version 0.13
 * @date 11/06/2025
 * 
 * @author Amesis Project
 * @copyright Amesis Project
 * 
*    ^ ^
*  =( '')=
*  (")_(")
*  
*  https://github.com/AmesisProject/002-Amesis-Throttle_To_ThrottleBody_Arduino
*  
*Youtube   : https://www.youtube.com/channel/UCCexVZN3UYSep2lsj2jVjdg?sub_confirmation=1
*GitHub    : https://github.com/AmesisProject
*Discord   : https://discord.gg/vRAybmd3hk
*FaceBook  : https://www.facebook.com/amesis.pro.5
*Instagram : https://www.instagram.com/?hl=fr
*  
*Lisense Proprietair : Amesis Project
*  
* 
*NomDuProjet : Thottle_ThrottleBody_Test_Activat
*ButDuProjet : Renvoyer la valeur de la pédale et du boitier papillon (du groupe VAG "VR5 AQN" de 0 à 100 % sur le port serie. Et que le papillon motorisé bouge en fonctione de la position pédal.
*ProjetDisponibleIciGitHub : https://github.com/AmesisProject/002-Amesis-Throttle_To_ThrottleBody_Arduino/tree/main/Throttle%20pedale%20Arduino
*Merci de faire suivre sur github toute modification au amélioration du code.
*Branchement :
* Pedale        /  Calculateur ME7.1   /   ArduinoMega    
* 1                 72                 5v
* 2                 -                  -               
* 3                 -                  -              
* 4                 -                  -               
* 5                 33                 Gnd
* 6                 34                 A0
*
* ThrottleBody   /  Calculateur   /   ArduinoMega    
* 1                  -                 -
* 2                  83                Gnd               
* 3                  -                 -              
* 4                  84                A1               
* 5                  -                 -
* 6                  91                +5V
*
*/
/////////////
//Librairie//
/////////////

#include <Arduino.h>
//#include <PID_AutoTune_v0.h>
#include "PID_v1.h"
#include "PPS_TPS_Menu.h"
#include "Capteurs.h"
#include "Moteur.h"
#include "Menu.h"
#include "PIDGestion.h"
#include "Utilitaires.h"


///////////////////////////////
// Déclaration des variables //
///////////////////////////////
// Définition des variables globales (ne pas oublier le type !)

//Pedale electronique acceleration//
  #define  PPSPot1_Pin 4           // Pin analogique d'entré (input) du potentiometre PPS1
      int  PPSPot1_ADC = 0;         // lire la vleur du potentiometre en numerique de 0 à 1023 PPS1
      int  PPS1_Calib_Mini = 166;   // Valeur de calibrage Mini capteur pedale 1
      int  PPS1_Calib_Maxi = 953;   // Valeur de calibrage Maxi capteur pedale 1   
      int  PPS1_Position = 0;       // Valeur entre 0 et 100% convertie depuis la valeur 0 à 1023
      bool PPS1_LoHi = 0;           // Pour inverser la polarité de PPS1

  #define  PPSPot2_Pin 3         // Pin analogique d'enté (input) du potentiometre
      int  PPSPot2_ADC = 0;         // lire la vleur du potentiometre en numerique de 0 à 1023
      int  PPS2_Calib_Mini = 140;   // Valeur de calibrage Mini capteur pedale 2
      int  PPS2_Calib_Maxi = 998;   // Valeur de calibrage Maxi capteur pedale 2
      int  PPS2_Position = 0;       // valeur entre 0 et 100% simplement la conversion du 0 à 1023 en 0 à 100%
      bool PPS2_loHi = 0;           // Pour inverser la polarité de PPS2

      int  PPSPot_ADC ;             // Valeur en 0 et 1023 de la position moyenne de PPS1 et PPS2
      int  PPS_Min_ADC ;            // Valeur en 0 et 1023 de la position moyenne Mini de PPS1 et PPS2
      int  PPS_Max_ADC ;            // Valeur en 0 et 1023 de la position moyenne Maxi de PPS1 et PPS2
      int  PPS_Position ;           // Valeur en % de la position de la moyenne de PPS1 et PPS2

//Pedale de frein //
  #define PBrake_Pin A2             // Pin d'entré du bouton poisoir de la pedale de frein, peut être un potantiometre sur certin model
      int PBrake_Stat = 0 ;         // Valeur de l'état du boutton pousoir, la valeur pourra être ressue soit de la pin soit du CAN
      bool PBrake_LoHi = 0 ;        // Pour inverser la polarité de PBrake

//Pédale d'embrayage //

  #define PClutch_Pin A3            // Pin d'entré du bouton poisoir de la pedale d'embrayage, peut être un potantiometre sur certin model
      int PClutch_Stat = 0 ;        // Valeur de l'état du boutton pousoir, la valeur pourra être ressue soit de la pin soit du CAN
      bool PClutch_LoHi = 0 ;       // Pour inverser la polarité de PClutch

//Papillon motorisé//    
  #define TPSPot1_Pin A0            // Pin analogique d'enté (input) du potentiometre TPS1
      int TPSPot1_ADC = 0;          // lire la vleur du potentiometre en numerique de 0 à 1023 TPS1
      int TPS1_Calib_Mini = 0;      // Valeur de calibrage Maxi capteur TB 1
      int TPS1_Calib_Neutral ;      // Valeur entre 0 et 1023 de la position au repos du papillon
      int TPS1_Calib_Maxi =100;     // Valeur de calibrage Maxi capteur TB 1
      int TPS1_Position = 0;        // valeur entre 0 et 100% convertie depuis la valeur 0 à 1023
      bool TPS1_LoHi = 0;           // Pour inverser la poliarité de TPS1

   #define TPSPot2_Pin A1           // Pin analogique d'enté (input) du potentiometre tps
      int  TPSPot2_ADC = 0;         // lire la vleur du potentiometre en numerique de 0 à 1023
      int  TPS2_Calib_Mini = 0;     // Valeur de calibrage Mini capteur TB 2
      int  TPS2_Calib_Neutral = 2;  // Valeur de calibraga Neutre capteur TP2 (papillon au repos)
      int  TPS2_Calib_Maxi = 100;   // Valeur de calibrage Maxi capteur TB 2
      int  TPS2_Position = 0;       // valeur entre 0 et 100% convertie depuis la valeur 0 à 1023
      bool TPS2_LoHi = 0;           // Pour inverser la polarité de TPS2
      
      int TPSPot_ADC ;              // Valeur en 0 et 1023 de la position moyenne de TPS1 et TPS2
      int TPS_Min_ADC ;             // valeur entre 0 et 1023 de la position mini du papillon en butée fermé
      int TPS_Neutral_ADC ;         // valeur entre 0 et 1023 de la position au repos du papillon
      int TPS_Max_ADC ;             // valeur entre 0 et 1023 de la position mini du papillon en butée fermé
      int TPS_Position ;            // Pour le choix du PPS1 ou PPS2 sur lequel s'appuis l'algorythe pour le calcul, l'autre sera pour l'annalyse du DTC defaut pédale

      unsigned long TPSCalib_previousMillis = 0; //

//Pont en H L298// (Le module L298N est un module de puissance pour allimenter le moteur DC car l'arduino ne fournis pas de puissance mes des commandes)
      int  motorPin1 = 8;           //Ports de commande du moteur B sens horaire
      int  motorPin2 = 9;           //Ports de commande du moteur B sens trigonometrique
      int  enablePin = 5;           //Ports de commande de la vitesse du moteur
      bool motor_LoHi = 0;          //Pour inverser la polarité du moteur de papillon

      int PwmMini =   0;            //Valeur Mini PMW pour l'entré ENA du module pont en H 
      int PwmMaxi = 255;            //Valeur Maxi PMW pour l'entré ENA du module pont en H
      int PwmDutyMini = 0;          //Valeur de PwmMini en %  
      int PwmDutyMaxi = 100;        //Valeur de PwmMaxi en %
      int TPSFreq = 150 ;           //Valeur de la frequance du moteur DC du corp de papillon motorisé en Hz

      int TPSMotorMode ;            //Option de commande du moteur TPS suivant case 1/2/3/4/default 

//Algrorhytme PID
      double kP ;                   //Variable Proportional    // kP = 5.12;
      double kI ;                   //Variable Integral        // kI = 47;
      double kD ;                   //Variable Derive          // kD = 0.088;
	  
      double kP_Agressif ;          //Variable Proportional Agressif    // 
      double kI_Agressif ;          //Variable Integral Agressif        // 
      double kD_Agressif ;          //Variable Derive Agressif          // 


      double Input, Output, SetPoint;     
      PID throttlePID(&Input, &Output, &SetPoint, kP, kI, kD, DIRECT);  //Création de l'objet "throttlePID"
  
//Variable de fonctionnement
      int ActiveCalibratePPS = 0 ;  //Mettre à 1 pour activer la calibration automatique, securité RPM à zero et bat voltage mini 12v
      int ActiveCalibrateTB = 0 ;   //Mettre à 1 pour activer la calibration automatique, securité RPM à zero et bat voltage mini 12v
      int ModeDegradeEtat = 0 ;     //Si il y a un defaut, il faut metre cette variable à 1 pour activer le mode degradé

//Régulateur de vitesse      
      int Cruise_TargetKmH = 0 ;    //Cible KM/H pour le regulateur de vitesse
      int CruiseButton_ActiveCruise = 0 ;
      int Cruise_Up = 0 ;
      int Cruise_Down = 0 ;
      int Cruise_Cancel = 0 ;

//Variable pour le Voyant MIL (merci Chat GPT lol pour le code du MIL)  
const int LedMil_Pin = 13 ;                  //Pin de la Led du Voyant MIL (voyant DTC)
      unsigned long Mil_previousMillis = 0;  //Pour le système millis pour eviter que le code soit bloquant par le "delay"
const int Intervel_For_MilBlink = 1000;      //Intervalle de temps pour le clignotement voyant MIL
      int Double_MilBlink_Count = 0;         //Variable pour le système de double clignotement ( ne me plais pas vraiment me ça fonctionne) mode pour le temps de callibrage
      bool Led_Mil_On = false;               //Variable pour inisier le mode
      bool Is_MilBlinking = false;           //Variable pour savoir si la LED est en train de clignoter

//Variable externe 
      int currentStatus_RPM = 0 ;        // Speeduino currentStatus.RPM
      int currentStatus_battery10 = 12;  // Speeduino currentStatus.battery10
      int currentStatus_Clutch ;         // Speeduino pin de l'ambrayage configPage6.launchPin
      int currentStatus_break ;          // Speeduino n'a pas de capteur de frein
      int currentStatus_kmh ;            // Valeur de vitesse vehicule pour le regulateur de vitesse
         





// --- Setup et loop ---
void setup() {
//Ouverture de la liaison serie pour l'interface utilisateur 
    Serial.begin(115200);                  // initialisation du port serie 

    //Initialisatrion des varibles de l'EEPROM//

//Choix de la vitesse Hz pour le PWM
    TCCR1B = TCCR1B & 0b11111000 | 0x01;    //Pin 9 | 10 Set PWM frequency to 31372.55 Hz Augmentation de la vitesse de l'arduino pour eviter le phenomène de ocillement du papillon
  //TCCR0B = TCCR0B & 0b11111000 | 0x01;    //Pin 5 | 6 Set PWm to 62500.00 Hz

//Entrées Sortie
    pinMode(PPSPot1_Pin, INPUT) ;          // pin entré pot1 PPS (pédale éléctronique)
    pinMode(PPSPot2_Pin, INPUT) ;          // pin entré pot2 PPS (Pédale éléctronique)
    pinMode(TPSPot1_Pin, INPUT) ;          // pin entré pot1 TPs (papillon motorisé)
    pinMode(TPSPot2_Pin, INPUT) ;          // pin entré pot2 TPS (papillon motorisé)
    pinMode(LedMil_Pin, OUTPUT) ;          // pin de la led temoin
    pinMode(motorPin1, OUTPUT)  ;          // pin de commande de moteur pour le module L298n sens horaire ou frein
    pinMode(motorPin2, OUTPUT)  ;          // pin de commande de moteur pour le module L298n sens trigonometrique ou frein
    pinMode(enablePin, OUTPUT)  ;          // pin de regulation de la vitesse, si pas besoin mettre le cavalier sur le L298N 
    pinMode(13, OUTPUT)         ;          // Définir la broche 13 comme sortie pour contrôler la LED

//Interface utilisateur
  afficherMenuPrincipal();


TB_PID_Init(); //?? Copilot a mis cette ligne, je ne sais pas si elle est utile, mais je la laisse pour l'instant

}

void loop() {

  //Lire les donner EEPROM ?? ici ou dans le setup ?
 ReadSensor() ; // Appel de la fonction lire les capteurs PPS TPS
 //AverageSensor(); // Appel de la fonction qui calcule les moyenne des capteurs
 //IndicatorLightMil(LedMil_Off); // Appel de la fonction du voyant MIL 5 chois : (LedMil_Off) (LedMil_On) (LedMil_BlinkLong) (LedMil_BlinkShort) (LedMil_DoubleBlink)
 
//__________________________________________________________________________________________
  //Menu interface utilisateur (Peut être à mettre dans une fonction)
   if (Serial.available() > 0) {                   // Serial.available() Obtenez le nombre d'octets (caractères) disponibles pour la lecture à partir du port série. Il s'agit de données déjà arrivées et stockées dans le tampon de réception série (qui contient 64 octets).
    String option = Serial.readStringUntil('\n'); // readStringUntil() lit les caractères du tampon série dans une chaîne. La fonction se termine si elle expire (voir setTimeout() ).
    option.trim();                                // .trim() Obtenez une version de la chaîne sans les espaces de début et de fin supprimés. Depuis la version 1.0, trim() modifie la chaîne en place plutôt que d'en renvoyer une nouvelle.
    if (option != "") {
      gererMenu(option);
    }

    if (niveauMenu == MENU_PRINCIPAL) {
      afficherMenuPrincipal();
    } else {
      afficherSousMenu(niveauMenu);
    }
  }

//_________________________________________________________________________________________
 //Formule de commande du papillon motorisé en fonction de la position pédal
 
      if ( PPS1_Position > TPS_Position)    //si la valeur de la pedale est superieur à la valeur du potantiometre du papillon motorisé 
      {                                     //Alor on applique le code de rotation horaire du papillon
        digitalWrite(motorPin1, HIGH);      
        digitalWrite(motorPin2, LOW);
       // Serial.print("Avant ");
      }
      
      else                                  //Sinon on Stop le moteur (freinage)
      {                                     //Aplication du code de freinage du moteur
        digitalWrite(motorPin1, HIGH); 
        digitalWrite(motorPin2, HIGH);
       // Serial.println("Stop");
      }
    
    //Lecture position papillon
   // Input = map(constrain())
    
 //---------------------------------------------------------------------------------------------
 // delay(tempsDelay);                               // On attend un delay en miliseconde pour que notre montage soit stablepour les testes
}

  // TPS_RotateMotor('O'); // Ouvre le papillon
  // TPS_RotateMotor('F'); // Ferme le papillon
  // TPS_RotateMotor('S'); // Stoppe le moteur

  gererMenu(); // Gère les choix de l'utilisateur dans le menu
  TB_PID_Update();
}
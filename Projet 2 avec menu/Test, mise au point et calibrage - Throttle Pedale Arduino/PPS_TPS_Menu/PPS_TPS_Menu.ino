/**
 *   @brief Interface utilisateur par la commande serie. Pour les groupes de mesures, teste des actionneurs et adaptation.
 *   @file 002-Amesis-Throttle_To_ThrottleBody_Arduino **/
const char* VERSION = "0.17";  // Version du programme
 /** @date 29/06/2025
 * 
 *   @author Amesis Project
 *   @copyright Amesis Project
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

*---------------------------------------------------------
*Branchement :
* JoyStick Shield ArduinoMegapour les testes : 
* Boutton A     : D2 
* Boutton B     : D3
* Boutton C     : D4
* Boutton D     : D5
* Boutton E     : D6
* Boutton F     : D7
* Joy  ⬍  X     : A0 
* Joy ⬌  Y     : A1
* Joy Boutton Z : D8
* -------------------------------------------------------------

* Pedale        /  Calculateur ME7.1   /   ArduinoMega    
* 1                 72                 5v
* 2                 -                  -               
* 3                 -                  -              
* 4                 -                  -               
* 5                 33                 Gnd
* 6                 34                 A0
*--------------------------------------------------------------

* ThrottleBody   /  Calculateur   /   ArduinoMega    
* 1                  -                 -
* 2                  83                Gnd               
* 3                  -                 -              
* 4                  84                A1               
* 5                  -                 -
* 6                  91                +5V
*---------------------------------------------------------------
*/
/////////////
//Librairie//
/////////////
#include <Arduino.h>
//#include <PID_AutoTune_v0.h>
#include "PID_v1.h"
#include "Menu.h"
#include "GearDSG.h"

////////////////////////////
// Declarion des fonction //
////////////////////////////
void TB_LoadStatus(); 

//////////////////////////////
// Déclaration des variables //
//////////////////////////////

//Pedale electronique acceleration//
  #define  PPSPot1_Pin A1           // Pin analogique d'entré (input) du potentiometre PPS1
      int  PPSPot1_ADC = 0;         // lire la vleur du potentiometre en numerique de 0 à 1023 PPS1
      int  PPS1_Calib_Mini = 166;   // Valeur de calibrage Mini capteur pedale 1
      int  PPS1_Calib_Maxi = 953;   // Valeur de calibrage Maxi capteur pedale 1   
      int  PPS1_Position = 0;       // Valeur entre 0 et 100% convertie depuis la valeur 0 à 1023
      bool PPS1_LoHi = 0;           // Pour inverser la polarité de PPS1

  #define  PPSPot2_Pin A3         // Pin analogique d'enté (input) du potentiometre
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
  #define PBrake_Pin 3             // Pin d'entré du bouton poisoir de la pedale de frein, peut être un potantiometre sur certin model
      int PBrake_Stat = 0 ;         // Valeur de l'état du boutton pousoir, la valeur pourra être ressue soit de la pin soit du CAN
      bool PBrake_LoHi = 0 ;        // Pour inverser la polarité de PBrake

//Pédale d'embrayage //

  #define PClutch_Pin 2            // Pin d'entré du bouton poisoir de la pedale d'embrayage, peut être un potantiometre sur certin model
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

   #define TPSPot2_Pin A2           // Pin analogique d'enté (input) du potentiometre TPS2
      int  TPSPot2_ADC = 0;         // lire la vleur du potentiometre en numerique de 0 à 1023 TPS2
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

//Variable pour le mode Boite de vitesse DSG
int DSG_Mode = 0; // Mode par défaut pour le mode DSG
unsigned long dsgStartTime = 0;   // Mémorise le début de la séquence
unsigned long DSG_Duration = 300; // Durée par défaut en ms pour la séquence DSG
bool dsgActive = false;           // Indique si une séquence DSG est en cours
bool dsgUp = true;                // true = passage supérieur, false = rétrogradage

//Variable pour le Voyant MIL (merci Chat GPT lol pour le code du MIL)  
const int LedMil_Pin = 13 ;                  //Pin de la Led du Voyant MIL (voyant DTC)
      unsigned long Mil_previousMillis = 0;  //Pour le système millis pour eviter que le code soit bloquant par le "delay"
const int Intervel_For_MilBlink = 1000;      //Intervalle de temps pour le clignotement voyant MIL
      int Double_MilBlink_Count = 0;         //Variable pour le système de double clignotement ( ne me plais pas vraiment me ça fonctionne) mode pour le temps de callibrage
      bool Led_Mil_On = false;               //Variable pour inisier le mode
      bool Is_MilBlinking = false;           //Variable pour savoir si la LED est en train de clignoter

// Enumération des différents modes de fonctionnement du voyant MIL
enum LedMilMode {              //Commande pour la fonction IndicatorLighMil()
         LedMil_Off,          //Etein le voyant MIL
         LedMil_On,           //Allume le voyant MIL
         LedMil_BlinkLong,    //Fait clignoter lentement le voyant le voyant MIL
         LedMil_BlinkShort,   //Fait clignoter rapidement le voyant MIL
         LedMil_DoubleBlink,  //Fait un double clignotement du voyant MIL, pendant le mode calibration. pour avertir que nous somme en phase d'aprentissage.
         LedMil_Test          //Mode test du voyant
};

LedMilMode currentMode = LedMil_Off; //Mode courrent à voyant à OFF

// Enumeration des differants modes de fonctionnement du TB
enum TPSMotor {
         BrakeL,
         Close,
         Open,
         BrakeH,
         Freewheel,
};

//Variable externe 
      int currentStatus_RPM = 0 ;        // Speeduino currentStatus.RPM
      int currentStatus_battery10 = 12;  // Speeduino currentStatus.battery10
      int currentStatus_Clutch ;         // Speeduino pin de l'ambrayage configPage6.launchPin
      int currentStatus_break ;          // Speeduino n'a pas de capteur de frein
      int currentStatus_kmh ;            // Valeur de vitesse vehicule pour le regulateur de vitesse
         



     



///////////////////////////////
//Inicialisation de l'arduino//
///////////////////////////////

void setup() {
//Initialisatrion des varibles de l'EEPROM//

//Choix de la vitesse Hz pour le PWM
    TCCR1B = TCCR1B & 0b11111000 | 0x01;    //Pin 9 | 10 Set PWM frequency to 31372.55 Hz Augmentation de la vitesse de l'arduino pour eviter le phenomène de ocillement du papillon
  //TCCR0B = TCCR0B & 0b11111000 | 0x01;    //Pin 5 | 6 Set PWm to 62500.00 Hz

//Entrées Sortie
    pinMode(PPSPot1_Pin, INPUT) ;          // pin entré pot1 PPS (pédale éléctronique)
    pinMode(PPSPot2_Pin, INPUT) ;          // pin entré pot2 PPS (Pédale éléctronique)
    pinMode(TPSPot1_Pin, INPUT) ;          // pin entré pot1 TPS (papillon motorisé)
    pinMode(TPSPot2_Pin, INPUT) ;          // pin entré pot2 TPS (papillon motorisé)
    pinMode(PBrake_Pin, INPUT) ;           // pin entré pedale de frein / Ou communication Speeduino
    pinMode(PClutch_Pin, INPUT) ;          // pin entré pedale d'embrayage
    pinMode(motorPin1, OUTPUT) ;           // pin de commande de moteur pour le module L298n sens horaire ou frein
    pinMode(motorPin2, OUTPUT) ;           // pin de commande de moteur pour le module L298n sens trigonometrique ou frein
    pinMode(enablePin, OUTPUT) ;           // pin de regulation de la vitesse, si pas besoin mettre le cavalier sur le L298N
    pinMode(LedMil_Pin, OUTPUT) ;          // pin sortie voyant MIL

//Ouverture de la liaison serie pour l'interface utilisateur 
    Serial.begin(115200);                  // initialisation du port serie  
  
//Interface utilisateur
  initMenu();            //  afficherMenuPrincipal();
  GearDSG_Init();        // Initialisation du module GearDSG


}


///////////////////////////////////
//Programme en bloucle du projet //
///////////////////////////////////

void loop() {
 
 //Lire les donner EEPROM ?? ici ou dans le setup ?
 ReadSensor() ; // Appel de la fonction lire les capteurs PPS TPS
 //AverageSensor(); // Appel de la fonction qui calcule les moyenne des capteurs
 //IndicatorLightMil(LedMil_Off); // Appel de la fonction du voyant MIL 5 chois : (LedMil_Off) (LedMil_On) (LedMil_BlinkLong) (LedMil_BlinkShort) (LedMil_DoubleBlink)
 GearDSG_Loop(); // Appel de la fonction principale du module GearDSG
 
 
 //Menu interface utilisateur
   if (Serial.available() > 0) {                  // Serial.available() Obtenez le nombre d'octets (caractères) disponibles pour la lecture à partir du port série. Il s'agit de données déjà arrivées et stockées dans le tampon de réception série (qui contient 64 octets).
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

void PPS_Calibration () {//le mode calibration ne peux s'appliqué que si le moteur et a 0 RPM
 //if (rpm == 0 et validation user = 1 oui vrai)
 if (1==1){//currentStatus_RPM  == 0 && currentStatus_battery10 <= 12 && ActiveCalibratePPS == 1 ){ //Securité pour calibration
   //1.Desactiver le papillon motorisé
   //  Je ne sais pas encore si il est desactiver car nous sommes dans une fonction.
   //  Il faudrait trouver un moyen de le desactiver le temps du calibrage pour ne pas qu'il bouge le temps du calibrage
   //  Securité coupure injection et allumage

   //2.Clignotement de la led Mile
   IndicatorLightMil(LedMil_DoubleBlink); // Appel de la fonction du voyant MIL 5 chois : (LedMil_Off) (LedMil_On) (LedMil_BlinkLong) (LedMil_BlinkShort) (LedMil_DoubleBlink)

   //3.On remet toutes les variable à zero
   PPS1_Calib_Mini = 1023 ;
   PPS2_Calib_Mini = 1023 ;
   PPS1_Calib_Maxi = 0 ;
   PPS2_Calib_Maxi = 0 ;
      
   //Le while pose probleme avec TunerStudio, dans le FW Speeduino, ça coupe la communication.
   //3. On relève la valeur du PPS1 & PPS2 au Mini         
   unsigned long currentMillis = millis();  

   while (millis() - currentMillis < 5000) {       //pendant x secondes
      PPSPot1_ADC = analogRead(PPSPot1_Pin); //On lis les données du capteur PPS Pot1
       if(PPSPot1_ADC < PPS1_Calib_Mini) {
          PPS1_Calib_Mini = PPSPot1_ADC ;
        }
      PPSPot2_ADC = analogRead(PPSPot2_Pin);  //On lis les données du capteur PPS Pot2
       if(PPSPot2_ADC < PPS2_Calib_Mini) {
          PPS2_Calib_Mini = PPSPot2_ADC ;
        } 
      PPSPot1_ADC = analogRead(PPSPot1_Pin); //On lis les données du capteur PPS Pot1
       if(PPSPot1_ADC > PPS1_Calib_Maxi) {
          PPS1_Calib_Maxi = PPSPot1_ADC ;
        }
      PPSPot2_ADC = analogRead(PPSPot2_Pin); //On lis les données du capteur PPS Pot2
       if(PPSPot2_ADC > PPS2_Calib_Maxi) {
          PPS2_Calib_Maxi = PPSPot2_ADC ;
        } 

          Serial.print("Press the pedal fully several times");
          Serial.print("PPS1 = " + String(PPSPot1_ADC) + "ADC / " + String(PPS1_Position) + "% |  | "); 
          Serial.print("PPS2 = " + String(PPSPot2_ADC) + "ADC / " + String(PPS2_Position) + "% |  | "); 
          Serial.println(Quit);
    }
             
     //Save dans l'EEPROM
     Serial.println ("PPS calibrated") ;
     //Serial.println( "PPS calibrée") ;

     IndicatorLightMil(LedMil_Off) ; //6. Fin du calibrage on éteint le voyant MIL
     ActiveCalibratePPS = 0 ; //On rebascule à 0 pour la condition de l'utilisateur
  }

  else {
     Serial.println ("Engine off & bat >12v") ;
   //  Serial.println ("Veuillez couper le moteur ou veriviez que la batterie soit au minimum de 12v ") ;
    }
}

void TPS_RotateMotor(char TPSMotorMode) {

/* L298 Modul pont en H commande  (https://passionelectronique.fr/tutoriel-l298n/) :
           | ENA/B | IN1/3 | IN2/4 |  Résultat, en sortie
   case 1  |   H   |   L   |   L   |  Blocage du moteur (arrêt rapide, freinage fort)
   case 2  |   H   |   L   |   H   |  Marche arrière
   case 3  |   H   |   H   |   L   |  Marche avant 
   case 4  |   H   |   H   |   H   |  Blocage du moteur (arrêt rapide, freinage fort)   
   case 5  |   L   |   X   |   X   |  Moteur en roue libre ( à l'arrêt, sans frein)
   default |   L   |   X   |   X   |  Moteur en roue libre 

   X = peu importe | L = Low 0v | H = High +5v    */
  switch (TPSMotorMode){
   case BrakeL : //Blocage du moteur (arrêt rapide, freinage fort)
         digitalWrite(enablePin, HIGH); // Amodiffier pour les PID
         digitalWrite(motorPin1, LOW);      
         digitalWrite(motorPin2, LOW);
         break;         
   case Close : //Marche arrière
         digitalWrite(enablePin, HIGH);
         digitalWrite(motorPin1, LOW);      
         digitalWrite(motorPin2, HIGH);
         break;
   case Open : //Marche avant
         digitalWrite(enablePin, HIGH);
         digitalWrite(motorPin1, HIGH);      
         digitalWrite(motorPin2, LOW);
         break;
   
   case BrakeH : //Blocage du moteur (arrêt rapide, freinage fort) 
         digitalWrite(enablePin, HIGH);
         digitalWrite(motorPin1, HIGH);      
         digitalWrite(motorPin2, HIGH);
         break;

   case Freewheel : //Moteur en roue libre ( à l'arrêt, sans frein)
         digitalWrite(enablePin, LOW);
         digitalWrite(motorPin1, LOW);      
         digitalWrite(motorPin2, LOW);
         break; 
  
   default : //Moteur en roue libre ( à l'arrêt, sans frein)
         digitalWrite(enablePin, LOW);
         digitalWrite(motorPin1, LOW);      
         digitalWrite(motorPin2, LOW);
         break; 
 }  
}

void TPS_Calibration() {
 //le mode calibration ne peux s'appliqué que si le moteur et a 0 RPM
 //if (rpm == 0 et validation user = 1 oui vrai)
 if (1==1){//(currentStatus_RPM  == 0 && currentStatus_battery10 <= 12 && ActiveCalibrateTB == 1 ){ //Pouquoi pas rajouter 100% PPS1 ou manipe pedale frein+accel pendant x seconde
   //1.Desactiver la pedale
   //  Je ne sais pas encore si elle est desactiver car nous sommes dans une fonction.
   //  Il faudrait trouver un moyen de la desactiver le temps du calibrage pour ne pas fausser la valeur si l'utilisateur touche la pedale.
   //  Securité coupure injection et allumage
   ActiveCalibrateTB = 1;  // Active le mode calibration

   //2.Clignotement de la led Mile pour indiquer le début de la calibration
   IndicatorLightMil(LedMil_DoubleBlink); // Appel de la fonction du voyant MIL 5 chois : (LedMil_Off) (LedMil_On) (LedMil_BlinkLong) (LedMil_BlinkShort) (LedMil_DoubleBlink)

   //3.On remet toutes les variables à zero
   TPS1_Calib_Mini = 1023;
   TPS2_Calib_Mini = 1023;
   TPS1_Calib_Maxi = 0;
   TPS2_Calib_Maxi = 0;
   TPS1_Calib_Neutral = 0;
   TPS2_Calib_Neutral = 0;
   
   Serial.println("Starting TB calibration...");
   
   //Le while pose problem avec TunerStudio, dans le FW Speeduino ça coupe la communication.
   //4. On relève la valeur du TPS1 & TPS2 au Mini         
   unsigned long currentMillis = millis();  
   while (millis() - currentMillis < 2000) {  // pendant 2s
      TPS_RotateMotor(Close);  // On ferme le papillon
      TPSPot1_ADC = analogRead(TPSPot1_Pin); //On lis les données du capteur PPS Pot1
      TPSPot2_ADC = analogRead(TPSPot2_Pin); //On lis les données du capteur PPS Pot2
      
      // Mise à jour des valeurs minimales
       if(TPSPot1_ADC < TPS1_Calib_Mini) {
        TPS1_Calib_Mini = TPSPot1_ADC;
        }
       if(TPSPot2_ADC < TPS2_Calib_Mini) {
        TPS2_Calib_Mini = TPSPot2_ADC;
        } 
      
      Serial.println("\rPhase 1: Closing throttle : TPS1 Min: " + String(TPS1_Calib_Mini) + " TPS2 Min: " + String(TPS2_Calib_Mini) + "      ");
      delay(100);  // Petit délai pour ne pas surcharger le port série
    }
   Serial.println(); // Pour passer à la ligne après la phase 1

   //5. On relève la valeur du TPS1 & TPS2 au Maxi
     currentMillis = millis(); 
   while (millis() - currentMillis < 2000) {  // pendant 2s
      TPS_RotateMotor(Open);  // On ouvre le papillon
      TPSPot1_ADC = analogRead(TPSPot1_Pin); //On lis les données du capteur PPS Pot1
      TPSPot2_ADC = analogRead(TPSPot2_Pin); //On lis les données du capteur PPS Pot2
      
      // Mise à jour des valeurs maximales
       if(TPSPot1_ADC > TPS1_Calib_Maxi) {
        TPS1_Calib_Maxi = TPSPot1_ADC;
        }
       if(TPSPot2_ADC > TPS2_Calib_Maxi) {
        TPS2_Calib_Maxi = TPSPot2_ADC;
        } 
      
      Serial.println("\rPhase 2: Opening throttle : TPS1 Max: " + String(TPS1_Calib_Maxi) + " TPS2 Max: " + String(TPS2_Calib_Maxi) + "      ");
      delay(100);
    }
   Serial.println(); // Pour passer à la ligne après la phase 2
   
   //6. On relève la valeur du TPS1 & TPS2 au Neutral
     currentMillis = millis(); 
   while (millis() - currentMillis < 2000) {  // pendant 2s
      TPS_RotateMotor(Freewheel);  // Position neutre
      TPSPot1_ADC = analogRead(TPSPot1_Pin); //On lis les données du capteur PPS Pot1
      TPSPot2_ADC = analogRead(TPSPot2_Pin);  //On lis les données du capteur PPS Pot2
      
      // Mise à jour des valeurs neutres (on prend la moyenne sur la période)
      TPS1_Calib_Neutral = TPSPot1_ADC;
      TPS2_Calib_Neutral = TPSPot2_ADC;
      
      Serial.println("\rPhase 3: Finding neutral : TPS1 Neutral: " + String(TPS1_Calib_Neutral) + " TPS2 Neutral: " + String(TPS2_Calib_Neutral) + "      ");
      delay(100);
   }
   Serial.println(); // Pour passer à la ligne après la phase 3
   
   //7. Affichage des résultats
   Serial.println("\nCalibration Results:");
   Serial.println("TPS1 - Min: " + String(TPS1_Calib_Mini) + " Neutral: " + String(TPS1_Calib_Neutral) + " Max: " + String(TPS1_Calib_Maxi));
   Serial.println("TPS2 - Min: " + String(TPS2_Calib_Mini) + " Neutral: " + String(TPS2_Calib_Neutral) + " Max: " + String(TPS2_Calib_Maxi));

   //8. Fin de la calibration
   IndicatorLightMil(LedMil_Off); //6. Fin du calibrage on éteint le voyant MIL
   ActiveCalibrateTB = 0;  //On rebascule à 0 pour la condition de l'utilisateur
   Serial.println("Calibration completed!");
  }
  else {
     Serial.println("Engine must be off and battery voltage > 12V");
  //  Serial.println ("Veuillez couper le moteur ou veriviez que la batterie soit au minimum de 12v ");
    }
} 

void TB_Test() {
 //le mode test ne peux s'appliqué que si le moteur et a 0 RPM
 //if (rpm == 0 et validation user = 1 oui vrai)
 if (currentStatus_RPM  == 0 && currentStatus_battery10 <= 12 ){ 
   //1.Desactiver la pedale
   //  Je ne sais pas encore si elle est desactiver car nous sommes dans une fonction.
   //  Il faudrait trouver un moyen de la desactiver le temps du test pour ne pas fausser la valeur si l'utilisateur touche la pedale.
   //  Securité coupure injection et allumage

   //2.Clignotement de la led Mile
   IndicatorLightMil(LedMil_DoubleBlink); // Appel de la fonction du voyant MIL 5 chois : (LedMil_Off) (LedMil_On) (LedMil_BlinkLong) (LedMil_BlinkShort) (LedMil_DoubleBlink)
   
   //Le while pose problem avec TunerStudio, dans le FW Speeduino ça coupe la communication.
   //3. On ferme le papillon 2s     
   unsigned long currentMillis = millis();  

   while (millis() - currentMillis < 2000) {       //pendant 2s
      TPS_RotateMotor(Close);                      // On ferme le papillon
    }

   //4. On ouvre le papillon 2s
     currentMillis = millis(); 
   while (millis() - currentMillis < 2000) {       //pendant 2s
      TPS_RotateMotor(Open);                       // On ferme le papillon
    }
 
   //5. On remet le MIL à off
    IndicatorLightMil(LedMil_Off) ; //6. Fin du calibrage on éteint le voyant MIL
    ActiveCalibrateTB = 0 ; //On rebascule à 0 pour la condition de l'utilisateur
  }

  else {
     Serial.println ("Engine off & bat >12v");
    // Serial.println ("Veuillez couper le moteur ou veriviez que la batterie soit au minimum de 12v ");
    }
} 

void ReadSensor () {

 //Lecture Pédale
  PPSPot1_ADC = analogRead(PPSPot1_Pin);                                                                                   // Lecture de la valeur annalogique
  PPS1_Position = map(constrain(PPSPot1_ADC, PPS1_Calib_Mini, PPS1_Calib_Maxi), PPS1_Calib_Mini, PPS1_Calib_Maxi, 0, 100);  // Fonction "map" de mise à l'echelle de 0-1023 à 0-100% avec "constain" qui empèche le debordement de valeurs 
  //Serial.print("Pédale pot.1 est à = ");                                                                                         // On renvoi les info sur le port serie pour la console arduino
  //Serial.print(PPS1_Position);                                                                                                   // Revoie la valeur de la variable sur le port serie
  //Serial.print("% ");                                                                                                            // Puis l'unité
  
  PPSPot2_ADC = analogRead(PPSPot2_Pin);                                                                                   // Lecture de la valeur annalogique
  PPS2_Position = map(constrain(PPSPot2_ADC, PPS2_Calib_Mini, PPS2_Calib_Maxi), PPS2_Calib_Mini, PPS2_Calib_Maxi, 0, 100);  // Fonction "map" de mise à l'echelle de 0-1023 à 0-100% avec "constain" qui empèche le debordement de valeurs 
  //Serial.print("Pédale pot.2 est à = ");                                                                                         // On renvoi les info sur le port serie pour la console arduino           
  //Serial.print(PPS2_Position);                                                                                                   // Revoie la valeur de la variable sur le port serie                        
  //Serial.print("% ");                                                                                                            // Puis l'unité           

 //Lecture Boitier Papillon
  TPSPot1_ADC = analogRead(TPSPot1_Pin);                                                                                   // Lecture de la valeur annalogique                   
  TPS1_Position = map(constrain(TPSPot1_ADC, TPS1_Calib_Mini, TPS1_Calib_Maxi), TPS1_Calib_Mini, TPS1_Calib_Maxi, 0, 100);  // Fonction "map" de mise à l'echelle de 0-1023 à 0-100% avec "constain" qui empèche le debordement de valeurs 
  //Serial.print("TPS pot.1 est à = ");                                                                                            // On renvoi les info sur le port serie pour la console arduino
  //Serial.print(TPS1_Position);                                                                                                   // Revoie la valeur de la variable sur le port serie                         
  //Serial.print("% ");                                                                                                            // Puis l'unité                         

  TPSPot2_ADC = analogRead(TPSPot2_Pin);                                                                                   // Lecture de la valeur annalogique
  TPS2_Position = map(constrain(TPSPot2_ADC, TPS2_Calib_Mini, TPS2_Calib_Maxi),  TPS2_Calib_Mini, TPS2_Calib_Maxi, 0, 100); // Fonction "map" de mise à l'echelle de 0-1023 à 0-100% avec "constain" qui empèche le debordement de valeurs 
  //Serial.print("TPS pot.2 est à = ");                                                                                            // On renvoi les info sur le port serie pour la console arduino
  //Serial.print(TPS2_Position);                                                                                                   // Revoie la valeur de la variable sur le port serie                                
  //Serial.println("% ");                                                                                                          // Puis l'unité                                    

}

void AverageSensor() {

  //Calcule de la moyenne des doubles capteurs pédales éléctronique
  PPSPot_ADC = (PPSPot1_ADC + PPSPot2_ADC) / 2 ;
  PPS_Min_ADC = (PPS1_Calib_Mini + PPS2_Calib_Mini) / 2 ;
  PPS_Max_ADC = (PPS1_Calib_Maxi + PPS2_Calib_Maxi) / 2 ;
  PPS_Position = (PPS1_Position + PPS2_Position) / 2 ;
      
  //Calcule de la moyenne des doubles capteurs du papillon motorisé
  TPSPot_ADC = (TPSPot1_ADC + TPSPot2_ADC) / 2 ;
  TPS_Min_ADC = (TPS1_Calib_Mini + TPS2_Calib_Mini) / 2 ;
  TPS_Neutral_ADC = (TPS1_Calib_Neutral + TPS2_Calib_Neutral) / 2 ;

}

void TB_Setting () {
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

void IndicatorLightMil(char currentMode) { //Presiser (LedMil_Off) (LedMil_On) (LedMil_BlinkLong) (LedMil_BlinkShort) (LedMil_DoubleBlink) dans l'appel de la fonction
  static bool ledState = false;
  static unsigned long previousBlinkMillis = 0;
  static unsigned long blinkDuration = 0;

  switch (currentMode) {
    case LedMil_Off:
                    digitalWrite(LedMil_Pin, LOW);
                    Is_MilBlinking = false;
                    break;
      
    case LedMil_On:
                   digitalWrite(LedMil_Pin, HIGH);
                   Is_MilBlinking = false;
                   break;
      
    case LedMil_BlinkLong:
                   if (millis() - previousBlinkMillis >= Intervel_For_MilBlink) {
                   previousBlinkMillis = millis();
                   ledState = !ledState;
                   digitalWrite(LedMil_Pin, ledState);
                   }
                   Is_MilBlinking = true;
                   break;
      
    case LedMil_BlinkShort:
                   if (millis() - previousBlinkMillis >= Intervel_For_MilBlink / 5) {
                  previousBlinkMillis = millis();
                  ledState = !ledState;
                  digitalWrite(LedMil_Pin, ledState);
                  }
                  Is_MilBlinking = true;
                  break;
      
    case LedMil_DoubleBlink:
                  if (Double_MilBlink_Count < 4) {
                  if (millis() - previousBlinkMillis >= 125) {
                  previousBlinkMillis = millis();
                  ledState = !ledState;
                  digitalWrite(LedMil_Pin, ledState);
                  }
                  } else {
                  if (millis() - previousBlinkMillis >= 500) {
                  previousBlinkMillis = millis();
                  ledState = !ledState;
                  digitalWrite(LedMil_Pin, ledState);
                  Double_MilBlink_Count = 0;
                  }
                  }
                  Double_MilBlink_Count++;
                  Is_MilBlinking = true;
                  break;

    case LedMil_Test:
                  if (Double_MilBlink_Count < 4) {
                  if (millis() - previousBlinkMillis >= 250) {
                  previousBlinkMillis = millis();
                  ledState = !ledState;
                  digitalWrite(LedMil_Pin, ledState);
                  }
                  } else {
                  if (millis() - previousBlinkMillis >= 1000) {
                  previousBlinkMillis = millis();
                  ledState = !ledState;
                  digitalWrite(LedMil_Pin, ledState);
                  Double_MilBlink_Count = 0;
                  }
                  }
                  Double_MilBlink_Count++;
                  Is_MilBlinking = true;
                  break;
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

void TB_ModeDegrade() {
  if (ModeDegradeEtat == 1 ){ 

  }
//Si le voltage batterie est < a 11.5v alors mode degradé
//Si le voltage batterie est > a 15 v alord mode degradé
//Si les EGT depasse X degré alor mode degrader pendant x segande
//si valeur labda depasse X AFR 
//si les 2 capteur de pedale ne correspondent pas alors mode degradé
//si les 2 capteur du papillon motorisé ne corresponde pas alor mode degradé

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

void TB_Rolling_Anti_Lag () {
//Suivant les information recu du reseaux CAN
//On ouvre ou ferme le papillon pour le rolling anti lag
}



void TB_CruiseControl() { //TO DO

  if (CruiseButton_ActiveCruise == 1 ) {
    //Allumer le voyant du cruise par le CAN au compteur.
      
     { if (Cruise_Up = 1) {                  // 
         Cruise_TargetKmH = currentStatus_kmh + 2 ; //
        //Metre une limite de temps pour l'incrementation
       }
       else if (Cruise_Down = 1) {//Case BP--
         Cruise_TargetKmH = currentStatus_kmh - 2 ; //
         //Metre une limite de temps pour la décrementation. 
       }
       //Case BP Annuler Cruise
       else if (Cruise_Cancel) {
        CruiseButton_ActiveCruise = 0 ;
        Cruise_TargetKmH = 0 ;
       }
       else if (currentStatus_break == 1 ) {
        CruiseButton_ActiveCruise = 0 ;
        Cruise_TargetKmH = 0 ;
       }
       else if (currentStatus_Clutch == 1 ) {
        CruiseButton_ActiveCruise = 0 ;
        Cruise_TargetKmH = 0 ;
       }
     }
     {
       if (Cruise_TargetKmH < currentStatus_kmh){
       //alor on ouvre le papillon d'un point

       }
       else { 
       //sinon on ne fait rien, l'algoritheme principal s'acccupe du papillon.
       }
     }
  }
  else {
    CruiseButton_ActiveCruise = 0 ; // Cette ligne n'est peut être pas necessaire.
    Cruise_TargetKmH = 0 ;
  }
}

void Communication() {
//Peut être communiquer par reseaux Can pour avoir les valeurs de :
//Info RPM
//Info Voltage Batterie
//Info EGT
//Info Lambda AFR
//Info Vitesse véhicule

}

void UserInterface() {
//Menu par liaison serie
//Boutton de manip pour reprog les calibrages.


}

void SaveEEPROM () {
  /* Exemple d'ecriture eeprom verifier avant l'ecriture 
  void update(uint8_t value)
  {
    if (EEPROM.read(address)!=value)
    {
      EEPROM.write(address, value);
      ++counter;
    }
  }  
  */
}

//TO DO
void KFPED_MapPage(){}
void KFMIOP_MapPage(){}
void KFMIRL_MapPage(){}
void KFM_Papillon(){}
void Voltage_MapPage(){}

void Page() { //TO DO
  // Declaration des variable pour EEPROM 

  

 }






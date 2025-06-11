#include <Arduino.h>
#include "Utilitaires.h"

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
//Boutton de manip pour reprog les colibrages.


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
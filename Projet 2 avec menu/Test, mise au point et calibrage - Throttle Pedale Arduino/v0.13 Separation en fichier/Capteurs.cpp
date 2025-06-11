

#include <Arduino.h>
#include "Capteurs.h"
#include "PPS_TPS_Menu.h"

// Lecture des capteurs PPS et TPS
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

// Moyenne des capteurs 
void AverageSensor() {
    
  //Calcule de la moyenne des doubles capteurs pédales éléctronique
  PPSPot_ADC = (PPSPot1_ADC + PPSPot2_ADC) / 2 ;
  PPS_Min_ADC = (PPS1_Calib_Mini + PPS2_Calib_Mini) / 2 ;
  PPS_Max_ADC = (PPS1_Calib_Maxi + PPS2_Calib_Maxi) / 2 ;
  PPS_Position = (PPS1_Position + PPS2_Position) / 2 ;
      
  //Calcule de la moyenne des doubles capteurs du papillon motorisé
  TPSPot_ADC = (TPSPot1_ADC + TPSPot2_ADC) / 2 ;
  TPS_Min_ADC = (TPS1_Calib_Mini + TPS2_Calib_Mini) / 2 ;
  TPS_Max_ADC = (TPS1_Calib_Maxi + TPS2_Calib_Maxi) / 2 ;
  TPS_Neutral_ADC = (TPS1_Calib_Neutral + TPS2_Calib_Neutral) / 2 ;

}

// Calibration de la pédale 
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

// Calibration du papillon 
void TPS_Calibration() {
 //le mode calibration ne peux s'appliqué que si le moteur et a 0 RPM
 //if (rpm == 0 et validation user = 1 oui vrai)
 if (1==1){//(currentStatus_RPM  == 0 && currentStatus_battery10 <= 12 && ActiveCalibrateTB == 1 ){ //Pouquoi pas rajouter 100% PPS1 ou manipe pedale frein+accel pendant x seconde
   //1.Desactiver la pedale
   //  Je ne sais pas encore si elle est desactiver car nous sommes dans une fonction.
   //  Il faudrait trouver un moyen de la desactiver le temps du calibrage pour ne pas fausser la valeur si l'utilisateur touche la pedale.
   //  Securité coupure injection et allumage

   //2.Clignotement de la led Mile
   IndicatorLightMil(LedMil_DoubleBlink); // Appel de la fonction du voyant MIL 5 chois : (LedMil_Off) (LedMil_On) (LedMil_BlinkLong) (LedMil_BlinkShort) (LedMil_DoubleBlink)

   //3.On remet toutes les variable à zero
   TPS1_Calib_Mini = 1023 ;
   TPS2_Calib_Mini = 1023 ;
   TPS1_Calib_Maxi = 0 ;
   TPS2_Calib_Maxi = 0 ;
   TPS1_Calib_Neutral = 0 ;
   TPS2_Calib_Neutral = 0 ;
   
   
   //Le while pose problem avec TunerStudio, dans le FW Speeduino ça coupe la communication.
   //3. On relève la valeur du TPS1 & TPS2 au Mini         
   unsigned long currentMillis = millis();  

   while (millis() - currentMillis < 2000) {       // pendant 2s
      TPS_RotateMotor(Close);                          // Close On ferme le papillon
      TPSPot1_ADC = analogRead(TPSPot1_Pin); //On lis les données du capteur PPS Pot1
       if(TPSPot1_ADC < TPS1_Calib_Mini) {
          TPS1_Calib_Mini = TPSPot1_ADC ;
        }
      TPSPot2_ADC =analogRead(TPSPot2_Pin);  //On lis les données du capteur PPS Pot2
       if(TPSPot2_ADC < TPS2_Calib_Mini) {
          TPS2_Calib_Mini = TPSPot2_ADC ;
        } 
    }

     //4. On relève la valeur du TPS1 & TPS2 au Maxi
     currentMillis = millis(); 
   while (millis() - currentMillis < 2000) {       //pendant 2s
      TPS_RotateMotor(Open);                          //Open On Ouvre le papillon
      TPSPot1_ADC = analogRead(TPSPot1_Pin);       //On lis les données du capteur PPS Pot1
       if(TPSPot1_ADC > TPS1_Calib_Maxi) {
          TPS1_Calib_Maxi = TPSPot1_ADC ;
        }
      TPSPot2_ADC =analogRead(TPSPot2_Pin); //On lis les données du capteur PPS Pot2
       if(TPSPot2_ADC > TPS2_Calib_Maxi) {
          TPS2_Calib_Maxi = TPSPot2_ADC ;
        } 
    }
     //5. On relève la valeur du TPS1 & TPS2 au N Neutral
     currentMillis = millis(); 
   while (millis() - currentMillis < 2000) {         //Attendre 2s
      TPS_RotateMotor(Freewheel);                            //Freewheel : //Moteur en roue libre ( à l'arrêt, sans frein)
          TPS1_Calib_Neutral = TPSPot1_ADC ;
          TPS2_Calib_Neutral = TPSPot2_ADC ;
        }
         
     //Save dans l'EEPROM
     Serial.println ("TB calibrated") ;
     //Serial.println( "TB calibré. ") ;

     IndicatorLightMil(LedMil_Off) ; //6. Fin du calibrage on éteint le voyant MIL
     ActiveCalibrateTB = 0 ; //On rebascule à 0 pour la condition de l'utilisateur
  }

  else {
     Serial.println ("Engine off & bat >12v");
  //   Serial.println ("Veuillez couper le moteur ou veriviez que la batterie soit au minimum de 12v ");
    }
} 
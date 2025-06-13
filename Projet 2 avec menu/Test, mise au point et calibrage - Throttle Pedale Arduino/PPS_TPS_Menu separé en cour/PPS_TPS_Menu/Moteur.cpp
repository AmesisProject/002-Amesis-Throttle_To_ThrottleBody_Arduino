/* L298 Modul pont en H commande  (https://passionelectronique.fr/tutoriel-l298n/) :
           | ENA/B | IN1/3 | IN2/4 |  Résultat, en sortie
   case 1  |   H   |   L   |   L   |  Blocage du moteur (arrêt rapide, freinage fort)
   case 2  |   H   |   L   |   H   |  Marche arrière
   case 3  |   H   |   H   |   L   |  Marche avant 
   case 4  |   H   |   H   |   H   |  Blocage du moteur (arrêt rapide, freinage fort)   
   case 5  |   L   |   X   |   X   |  Moteur en roue libre ( à l'arrêt, sans frein)
   default |   L   |   X   |   X   |  Moteur en roue libre 

   X = peu importe | L = Low 0v | H = High +5v    */

#include <Arduino.h>
#include "Moteur.h"
#include "PPS_TPS_Menu.h"

// Enumeration des differants modes de fonctionnement du TB
enum TPSMotor {
         BrakeL,
         Close,
         Open,
         BrakeH,
         Freewheel,
};
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


// Commande du moteur du papillon motorisé
void TPS_RotateMotor(char TPSMotorMode) {

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


// Fonction de test du papillon motorisé
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

void TB_Rolling_Anti_Lag () {
//Suivant les information recu du reseaux CAN
//On ouvre ou ferme le papillon pour le rolling anti lag
}
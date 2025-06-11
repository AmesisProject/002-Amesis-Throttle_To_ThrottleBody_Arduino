
// TO DO

#include "CruiseControl.h"
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
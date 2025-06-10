/**
 * @brief Interface utilisateur par la commande serie. Pour les groupes de mesures, teste des actionneurs et adaptation.
 * @file Menu_UI.ino
 * @version 0.07
 * @date 03/082023
 * 
 * @author Amesis Project
 * @copyright Amesis Project
 * 
 */


#include <Arduino.h>
//#include <PID_AutoTune_v0.h>
#include <PID_v1.h>

/**
 * @brief 
 * 
 * @var
 */
// Définition des variables
    byte PPS1_Calib_Mini    = 0 ;
    byte PPS1_Calib_Maxi    = 250 ;
    byte PPSPot1_ADC  = 0 ;
    byte PPS1_Position      = 1 ;

    byte PPS2_Calib_Mini    = 0 ;
    byte PPS2_Calib_Maxi    = 250 ;
    byte PPSPot2_ADC  = 2 ;
    byte PPS2_Position      = 3 ;

//Pedale de frein //
      int PBrake_Pin = A2 ;        // Pin d'entré du bouton poisoir de la pedale de frein, peut être un potantiometre sur certin model
      bool PBrake_Stat = 0 ;        // Valeur de l'état du boutton pousoir, la valeur pourra être ressue soit de la pin soit du CAN
      bool PBrake_LoHi = 0 ;       // Pour inverser la polarité de PBrake

//Pédale d'embrayage //
      int PClutch_Pin = A3 ;        // Pin d'entré du bouton poisoir de la pedale d'embrayage, peut être un potantiometre sur certin model
      bool PClutch_Stat = 0 ;        // Valeur de l'état du boutton pousoir, la valeur pourra être ressue soit de la pin soit du CAN
      bool PClutch_LoHi = 0 ;        // Pour inverser la polarité de PClutch

    int TPSPot1_ADC  = 0 ;
    int TPS1_Calib_Mini    = 0 ;     // Valeur de calibrage Maxi capteur TB 1
    int TPS1_Calib_Neutral = 150 ;     // Valeur entre 0 et 1023 de la position au repos du papillon
    int TPS1_Calib_Maxi    = 200 ;    // Valeur de calibrage Maxi capteur TB 1
    int TPS1_Position      = 1 ;

    int TPSPot2_ADC  = 2 ;
    int TPS2_Calib_Mini    = 0 ;     // Valeur de calibrage Maxi capteur TB 2
    int TPS2_Calib_Neutral = 150 ;
    int TPS2_Calib_Maxi    = 200 ;   // Valeur de calibrage Maxi capteur TB 2
    int TPS2_Position      = 3 ;

    int PWMMini =   0;         
    int PWMMaxi = 255;     
    int TPSFreq = 150;   
    
 //Algrorhytme PID
      double kP ;                  //Variable Proportional    // kP = 5.12;
      double kI ;                  //Variable Integral        // kI = 47;
      double kD ;                  //Variable Derive          // kD = 0.088;   

      double kP_Agressif ;         //Variable Proportional Agressif    // kP = 5.12;
      double kI_Agressif ;         //Variable Integral Agressif        // kI = 47;
      double kD_Agressif ;         //Variable Derive Agressif          // kD = 0.088;



//Régulateur de vitesse      
      int Cruise_TargetKmH = 0 ;    //Cible KM/H pour le regulateur de vitesse
      int CruiseButton_ActiveCruise = 0 ;
      int Cruise_Up = 0 ;
      int Cruise_Down = 0 ;
      int Cruise_Cancel = 0 ;




// Définir les numéros de menu
#define MENU_PRINCIPAL                "1"      // 1
#define MENU_PEDALE                   "1.1"    //  1.1
#define MENU_PPS_LOG                  "1.1.1"  //    1.1.1
#define MENU_PPS_Calibration          "1.1.2"  //    1.1.2
#define MENU_PPS_SaveEEPROM           "1.1.3"  //    1.1.3
#define MENU_PAPILLON                 "1.2"    //  1.2
#define MENU_TPS_LOG                  "1.2.1"  //    1.2.1
#define MENU_TPS_Calibration          "1.2.2"  //    1.2.2
#define MENU_TPS_SaveEEPROM           "1.2.3"  //    1.2.3
#define MENU_REGLAGE_PWM              "1.3"    //  1.3
#define MENU_REGLAGE_FREQUENCE        "1.4"    //  1.4
#define MENU_REGLAGE_PID              "1.5"    //  1.5
#define MENU_PID_Normal               "1.5.1"  //    1.5.1
#define MENU_PID_KP                   "1.5.1.1"//        1.5.1.1
#define MENU_PID_KI                   "1.5.1.2"//        1.5.1.2
#define MENU_PID_KD                   "1.5.1.3"//        1.5.1.3
#define MENU_PID_Agressif             "1.5.2"  //    1.5.2
#define MENU_PID_KP_Agr               "1.5.2.1"//        1.5.2.1
#define MENU_PID_KI_Agr               "1.5.2.2"//        1.5.2.2
#define MENU_PID_KD_Agr               "1.5.2.3"//        1.5.2.3
#define MENU_PID_Auto                 "1.5.3"  //    1.5.3
#define MENU_ACQUISITION              "1.6"    //  1.6
#define MENU_LOG_Capteurs             "1.6.1"  //    1.6.1
#define MENU_LOG_Capteur_PPS_TPS      "1.6.1.1"//        1.6.1.1  
#define MENU_LOG_Capteur_Cruise       "1.6.1.2"//        1.6.1.2
#define MENU_TEST_Actionneurs         "1.6.2"  //    1.6.2
#define MENU_TEST_Actionneurs_MIL     "1.6.2.1"//        1.6.2.1
#define MENU_TEST_Actionneurs_TB      "1.6.2.2"//        1.6.2.2
#define MENU_RESEAU_CAN               "1.6.3"  //    1.6.3
#define MENU_DTC                      "1.7"    //  1.7
#define MENU_LIBRE_1                  "1.8"    //  1.8
#define MENU_LIBRE_2                  "1.9"    //  1.9
#define MENU_LIBRE_3                  "1.10"   //  1.10
#define MENU_RETOUR                   "11"     //11

// Variable pour stocker le numéro de menu actuel
String niveauMenu = MENU_PRINCIPAL;

/**
 * @brief Setup
 */
void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT); // Définir la broche 13 comme sortie pour contrôler la LED
  afficherMenuPrincipal();
}

void loop() {
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
}


/**
 * @brief Fonction pour afficher le menu principal 
 */
void afficherMenuPrincipal() { //Le menu principale comporte 14 lignes, pour garder cette resolution, il y a des Serial.prinrln ("") dans chaque menu pour compbler jusqu'a 14 Lignes, pour un affichage propre du=es menus.
  Serial.println("\n//" + niveauMenu + " Paramètre // ");                           // 1
  Serial.println(" 1) Pédale électronique ");                                      // 2
  Serial.println(" 2) Papillon motorisé électronique ");                           // 3
  Serial.println(" 3) Réglage des PWM pour la rapidités du moteur de papillon ");  // 4
  Serial.println(" 4) Réglage de la fréquence du moteur de papillon ");            // 5
  Serial.println(" 5) Réglage des PID ");                                          // 6
  Serial.println(" 6) Acquisition des valeurs ");                                  // 7
  Serial.println(" 7) DTC ");                                                      // 8
  Serial.println(" 8)     ^ ^");                                                   // 9
  Serial.println(" 9)   =( '')= ");                                                //10
  Serial.println("10)  ('')_('') ");                                               //11
  Serial.println("By AmesisProject Logiciel V0.07 ");                              //12
  Serial.println("......................................... ");                    //13
  Serial.println(" Entrez le numéro de l'option souhaitée : ");                    //14


}

/**
 * @brief  Fonction pour afficher les sous-menus
 */

void afficherSousMenu(String menu) {

  //!1.1
  if (menu == MENU_PEDALE) {  
    Serial.println("\n//" + niveauMenu + " Pédale éléctronique // ");
    Serial.println("1) Vérifier la calibration ");
    Serial.println("2) Lancer la procédure de calibration ");
    Serial.println("3) Enregistrer ");
    Serial.println("");
    Serial.println(" ) Info : Il est necessaire que la calibration de la pédale éléctronique ");
    Serial.println("          soit faite avant la calibrage du papillon motorisé. ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Quitter ");   
  } 

    //!1.1.1
    else if (menu == MENU_PPS_LOG){ 
          digitalWrite(13, HIGH); // Test d'appel d'une fonction
          while (niveauMenu == MENU_PPS_LOG) { //"1.1.1"
           Serial.print("PPS1 = " + String(PPSPot1_ADC) + "ADC / " + String(PPS1_Position) + "% |  | "); 
           Serial.print("PPS2 = " + String(PPSPot2_ADC) + "ADC / " + String(PPS2_Position) + "% |  | "); 
           Serial.println("Q) Quitter  ");

           //Commande pour sortir de la boucle 
           char receivedChar ;
           // Vérifie si des données sont disponibles sur la liaison série
           if (Serial.available() > 0) {
             receivedChar = Serial.read(); // Lit le caractère reçu
      
             // Si le caractère reçu est 'q', sort de la boucle while
             if (receivedChar = "q"||"Q") {
               niveauMenu = MENU_PEDALE; // Sort de la boucle while vers 1.1
             }
            }
         }  
    } 

    //!1.1.2
    else if (menu == MENU_PPS_Calibration) {
         digitalWrite(13, HIGH);// Test d'appel d'une fonction
         while (niveauMenu == MENU_PPS_Calibration) {
           //Appele de la routine PPS_Calibration();
        //  PPS_Calibration();
          Serial.print("Appuiez sur la pédale à fond plusieur fois lentement ");
          Serial.print("PPS1 = " + String(PPSPot1_ADC) + "ADC / " + String(PPS1_Position) + "% |  | "); 
          Serial.print("PPS2 = " + String(PPSPot2_ADC) + "ADC / " + String(PPS2_Position) + "% |  | "); 
          Serial.println("Q) Quitter  ");

          //Commande pour sortir de la boucle 
           char receivedChar;
           // Vérifie si des données sont disponibles sur la liaison série
           if (Serial.available() > 0) {
             receivedChar = Serial.read(); // Lit le caractère reçu
      
             // Si le caractère reçu est 'q', sort de la boucle while
             if (receivedChar = "q"||"Q") {
               niveauMenu = MENU_PEDALE; // Sort de la boucle while vers 1.1
             }
            }
         } 
    }

    //!1.1.3
    else if (menu == MENU_PPS_SaveEEPROM) {

          digitalWrite(13, LOW);// Test d'appel d'une fonction
      //  SaveEEPROM();  //Appele de la routine SaveEEPROM();
          Serial.println("\n//" + niveauMenu + " Données sauvegardées // ");
          Serial.println(""); 
          Serial.println("| PPS1 Mini = " + String(PPS1_Calib_Mini) + " ADC ");
          Serial.println("| PPS1 Maxi = " + String(PPS1_Calib_Maxi) + " ADC ");
          Serial.println("");
          Serial.println("| PPS2 Mini = " + String(PPS2_Calib_Mini) + " ADC "); 
          Serial.println("| PPS2 Maxi = " + String(PPS2_Calib_Maxi) + " ADC "); 
          Serial.println("");
          Serial.println("");
          Serial.println("");
          Serial.println("");
          Serial.println("");
          Serial.println("Q) Quitter  ");
    }

  //!1.2   
  else if (menu == MENU_PAPILLON)       {
    Serial.println("\n//" + niveauMenu + " Papillon motorisé électronique // ");
    Serial.println("1) Vérifier la calibration ");
    Serial.println("2) Lancer la procédure de calibration ");
    Serial.println("3) Enregistrer ");
    Serial.println("");
    Serial.println(" ) Info : Moteur coupé, batterie chargé. Il est nécessaire que la calibration de la ");
    Serial.println("          pédale éléctronique soit faite correctement avant de calibré le papillon ");
    Serial.println("          motorisé. Si ce n'est pas fait RDV au Menu '1.1 Pédale éléctronique'. ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Quitter  ");
  }

    //!1.2.1
    else if (menu == MENU_TPS_LOG) {
          digitalWrite(13, HIGH); // Test d'appel d'une fonction
          while (niveauMenu == MENU_TPS_LOG) {
           Serial.print("TPS1 = " + String(TPSPot1_ADC) + "ADC / " + String(TPS1_Position) + "% |  | "); 
           Serial.print("TPS2 = " + String(TPSPot2_ADC) + "ADC / " + String(TPS2_Position) + "% |  | "); 
           Serial.println("Q) Quitter  ");

           //Commande pour sortir de la boucle 
           char receivedChar;
           // Vérifie si des données sont disponibles sur la liaison série
           if (Serial.available() > 0) {
             receivedChar = Serial.read(); // Lit le caractère reçu
      
             // Si le caractère reçu est 'q', sort de la boucle while
             if (receivedChar = "q"||"Q") {
               niveauMenu = MENU_PAPILLON; // Sort de la boucle while vers 1.2
             }
            }
         }  
    } 

    //!1.2.2
    else if (menu == MENU_TPS_Calibration) {
         digitalWrite(13, HIGH); // Test d'appel d'une fonction
         while (niveauMenu == MENU_TPS_Calibration) {
           //Appele de la routine PPS_Calibration();
        //  TPS_Calibration();
          Serial.print("Ne pas toucher la pédale ! ");
          Serial.print("TPS1 = " + String(TPSPot1_ADC) + "ADC / " + String(TPS1_Position) + "% |  | "); 
          Serial.print("TPS2 = " + String(TPSPot2_ADC) + "ADC / " + String(TPS2_Position) + "% |  | "); 
          Serial.println("Q) Quitter  ");

          //Commande pour sortir de la boucle 
           char receivedChar;
           // Vérifie si des données sont disponibles sur la liaison série
           if (Serial.available() > 0) {
             receivedChar = Serial.read(); // Lit le caractère reçu
      
             // Si le caractère reçu est 'q', sort de la boucle while
             if (receivedChar = "q"||"Q") {
               niveauMenu = MENU_PAPILLON; // Sort de la boucle while vers 1.2
             }
            }
         } 
    }

    //!1.2.3
    else if (menu == MENU_TPS_SaveEEPROM) {
          digitalWrite(13, LOW);// Test d'appel d'une fonction
      //  SaveEEPROM();  //Appele de la routine SaveEEPROM();
          Serial.println("\n//" + niveauMenu + " Données sauvegardées // ");
          Serial.println(""); 
          Serial.println("| TPS1 Mini   = " + String(TPS1_Calib_Mini) +" ADC ");
          Serial.println("| TPS1 Neutre = " + String(TPS1_Calib_Neutral) +" ADC ");
          Serial.println("| TPS1 Maxi   = " + String(TPS1_Calib_Maxi) + " ADC ");
          Serial.println("");
          Serial.println("| TPS2 Mini   = " + String(TPS2_Calib_Mini) + " ADC "); 
          Serial.println("| TPS2 Neutre = " + String(TPS2_Calib_Neutral) + " ADC ");
          Serial.println("| TPS2 Maxi   = " + String(TPS2_Calib_Maxi) + " ADC "); 
          Serial.println("");
          Serial.println("");
          Serial.println("");
          Serial.println("Q) Quitter  ");
    }

  //!1.3 
  else if (menu == MENU_REGLAGE_PWM) {
    Serial.println("\n//" + niveauMenu + " Réglage des PWM pour la rapidités du moteur de papillon// ");
    Serial.println("1) PWM Mini (Valeur actuelle : " + String(PWMMini) + ") ");
    Serial.println("2) PWM Maxi (Valeur actuelle : " + String(PWMMaxi) + ") ");
    Serial.println("");
    Serial.println(" ) Info : Les valeurs mini max sont 0 - 255, elles correspondent à une vitesse ");
    Serial.println("          minimum ou maximum pour la commande du papillon électronique. ");
    Serial.println("          Par ex. dans un cas de figue X, le papillon pourrait commancer à ");
    Serial.println("          bouger qu'à partir de 20 et non de 1. Reciproquement il pourrait attiendre ");
    Serial.println("          sa vitesse maximum à 230, donc inutile de mettre 255, le pont en H ");
    Serial.println("          pourait surchauffer pour rien.");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Quitter  ");
  }

    //!1.3.1 
      //! Voir dans void gererMenu(String option) 
    
    //!1.3.2
      //! Voir dans void gererMenu(String option) 

  //!1.4 
  else if (menu == MENU_REGLAGE_FREQUENCE) {
    Serial.println("\n//" + niveauMenu + " Réglage de la fréquence du moteur de papillon // ");
    Serial.println("1) Fréquence (Hz) (Valeur actuelle : " + String(TPSFreq) + ") ");
    Serial.println("");
    Serial.println(" ) Info : Le corp de papillon motorisé éléctronique est minue d'un moteur ");
    Serial.println("          de type DC à courant continue. Ce moteur DC doit être allimenté ");
    Serial.println("          avec une certainne fréquence pour sont fonctionnement optimal en PWM. ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Quitter  ");
  }
   
    //!1.4.1
      // Voir dans void gererMenu(String option)

  //!1.5 
  else if (menu == MENU_REGLAGE_PID) {
      Serial.println("\n//" + niveauMenu + " Réglage des PID// ");
      Serial.println("1) PID Normal   | " + String(kP) + " | " + String(kI) + " | "+ String(kD) + " | "); 
      Serial.println("2) PID Agressif | " + String(kP_Agressif) + " | " + String(kI_Agressif) + " | "+ String(kD_Agressif) + " | "); 
      Serial.println("3) Activation de recherche PID automatique ");
      Serial.println("");
      Serial.println(" ) Info : Le système intègre l'algoritme de PID Proportionnel Itégral et Dérivé en ");
      Serial.println("          boucle fermée CL Pour comprendre ce qu'est les PID veyez regarder ces vidéos :");
      Serial.println("          https://www.youtube.com/watch?v=qKy98Cbcltw&t=5s");
      Serial.println("          https://www.youtube.com/watch?v=udnUTi6y8Fw");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("Q) Quitter  ");
  }

    //!1.5.1 
    else if (menu == MENU_PID_Normal) {
      Serial.println("\n//" + niveauMenu + " PID normeaux // ");
      Serial.println("1) kP normal (Valeur actuelle : " + String(kP) + ") ");
      Serial.println("2) kI normal (Valeur actuelle : " + String(kI) + ") ");
      Serial.println("3) kD normal (Valeur actuelle : " + String(kD) + ") ");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("Q) Quitter  ");
    }

      //!1.5.1.1 
      //!1.5.1.2   
      //!1.5.1.3
      // Voir dans void gererMenu(String option)


    //!1.5.2
    else if (menu == MENU_PID_Agressif) {
      Serial.println("\n//" + niveauMenu + " PID Agressifs // ");
      Serial.println("1) kP agressif (Valeur actuelle : " + String(kP_Agressif) + ") ");
      Serial.println("2) kI agressif (Valeur actuelle : " + String(kI_Agressif) + ") ");
      Serial.println("3) kD agressif (Valeur actuelle : " + String(kD_Agressif) + ") ");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("Q) Quitter  ");
    }         

      //!1.5.2.1 
      //!1.5.2.2   
      //!1.5.2.3 
      // Voir dans void gererMenu(String option)

    //!1.5.3 
    else if (menu == MENU_PID_Auto) {
         Serial.println("\n//" + niveauMenu + " Recherche automatique des PID// "); // voir avec la librairie #include <PID_AutoTune_v0.h>
         Serial.println("1) A faire ");
         Serial.println("2)  ");
         Serial.println("3)  ");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("Q) Quitter  ");
    }

  //!1.6
  else if (menu == MENU_ACQUISITION) {
    Serial.println("\n//" + niveauMenu + " Acquisition des valeurs// ");
    Serial.println("1) Groupes de mesures ");
    Serial.println("2) Teste des actionneurs ");
    Serial.println("3) Connexion ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Quitter  ");
  }

    //!1.6.1
    else if (menu == MENU_LOG_Capteurs) {
      Serial.println("\n//" + niveauMenu + " Groupes de mesures// ");
      Serial.println("1) Pédale et papillon ");
      Serial.println("2) Régulateur de vitesse ");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("Q) Quitter  ");
    }
 
       //!1.6.1.1
       else if (menu == MENU_LOG_Capteur_PPS_TPS) {
             while (niveauMenu == MENU_LOG_Capteur_PPS_TPS) {
              Serial.print("Position Pedale Sensor 1/2 = " + String(PPS1_Position) + "% / " + String(PPS2_Position) + "% |   | "); 
              Serial.print("Throttle Position Sensor 1/2 = " + String(TPS1_Position) + "% / " + String(TPS2_Position) + "% |   | "); 
              Serial.println("Q) Quitter  ");

              //Commande pour sortir de la boucle 
              char receivedChar;
              // Vérifie si des données sont disponibles sur la liaison série
              if (Serial.available() > 0) {
                receivedChar = Serial.read(); // Lit le caractère reçu
      
                // Si le caractère reçu est 'q', sort de la boucle while
                if (receivedChar = "q"||"Q") {
                  niveauMenu = MENU_LOG_Capteurs; //Sort de la boucle while vers 1.6.1 
                }
               }
         }  
    }

       //!1.6.1.2
       else if (menu == MENU_LOG_Capteur_Cruise) {
             while (niveauMenu == MENU_LOG_Capteur_Cruise) {
              Serial.print("Bouton On/Off = " + String(CruiseButton_ActiveCruise)); 
              Serial.print(" | BP Up = " + String(Cruise_Up)); 
              Serial.print(" | BP Down = " + String(Cruise_Down));
              Serial.print(" | BP Cancel = " + String(Cruise_Cancel)); 
              Serial.print(" |     "); 
              Serial.println("Q) Quitter  ");

              //Commande pour sortir de la boucle 
              char receivedChar;
              // Vérifie si des données sont disponibles sur la liaison série
              if (Serial.available() > 0) {
                receivedChar = Serial.read(); // Lit le caractère reçu
      
                // Si le caractère reçu est 'q', sort de la boucle while
                if (receivedChar = "q"||"Q") {
                  niveauMenu = MENU_LOG_Capteurs; //Sort de la boucle while vers 1.6.1 
                }
               }
         }  
    }


    //!1.6.2
    else if (menu == MENU_TEST_Actionneurs) {
           Serial.println("\n//" + niveauMenu + " Teste des actionners// ");
           Serial.println("1) Voyant MIL ");
           Serial.println("2) Papillon motorisé éléctronique ");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("Q) Quitter  ");  
    }

       //!1.6.2.1
       else if (menu == MENU_TEST_Actionneurs_MIL) {
             Serial.println("\n//" + niveauMenu + " Voyant MIL activé// ");
             Serial.println("");
             Serial.println("");
             Serial.println("");
             Serial.println("");
             Serial.println("");
             Serial.println("");
             Serial.println("");
             Serial.println("");
             Serial.println("");
             Serial.println("");
             Serial.println("");
             Serial.println("Q) Quitter  ");

              //Allumage led test pin13
              unsigned long currentMillis = millis();  
              while (millis() - currentMillis < 2000) {  //pendant 2s
                digitalWrite(13, HIGH);                  // Test d'appel d'une fonction
              }
                digitalWrite(13, LOW);                   //


                
       }

       //!1.6.2.2
       else if (menu == MENU_TEST_Actionneurs_TB) {
             //void TB_Test();  // Appel de la fonction de test du papillon motorisé
              Serial.println("\n//" + niveauMenu + " Fermeture et ouverture du TB// ");

       }

    //!1.6.3
    else if (menu == MENU_RESEAU_CAN) {
           Serial.println("\n//" + niveauMenu + " Connection au reseau CAN// ");
           Serial.println("1) Connection au Speeduino ");
           Serial.println("2) Connection à un calculateur OEM ");
           Serial.println("3) Ecoute du réseaux CAN ");
           Serial.println("");
           Serial.println(" ) Info : Non fonctionel pour le moment mais pour les futures mise à jour du FW ");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("Q) Quitter  ");  
    }

  //!1.7
  else if (menu == MENU_DTC) {
    Serial.println("\n//" + niveauMenu + " DTC// ");
    Serial.println("1) Lecture des codes défauts enregistrées en mémoire ");
    Serial.println("2) Effacement des codes défaut ");
    Serial.println("3) Libre ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Quitter  ");
  }

  //!1.8
  else if (menu == MENU_LIBRE_1) {
    Serial.println("\n//" + niveauMenu + " Libre 1// ");
    Serial.println("1) Option libre 1-1 ");
    Serial.println("2) Option libre 1-2 ");
    Serial.println("3) Option libre 1-3 ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Quitter  ");
  }

  //!1.9
  else if (menu == MENU_LIBRE_2) {
    Serial.println("\n//" + niveauMenu + " Libre 2// ");
    Serial.println("1) Option libre 2-1 ");
    Serial.println("2) Option libre 2-2 ");
    Serial.println("3) Option libre 2-3 ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Quitter  ");
  }

  //!1.10
  else if (menu == MENU_LIBRE_3) {
    Serial.println("\n//" + niveauMenu + " Libre 3// ");
    Serial.println("1) Option libre 3-1 ");
    Serial.println("2) Option libre 3-2 ");
    Serial.println("3) Option libre 3-3 ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Quitter  ");
  }

  Serial.println("Entrez le numéro de l'option souhaitée : ");
}

/**
 * @brief Fonction pour gérer les actions du menu
 */
void gererMenu(String option) {
  if (niveauMenu == MENU_PRINCIPAL) {
    if (option == "1") {
      niveauMenu = MENU_PEDALE;
    } else if (option == "2") {
      niveauMenu = MENU_PAPILLON;      
    } else if (option == "3") {
      niveauMenu = MENU_REGLAGE_PWM;
    } else if (option == "4") {
      niveauMenu = MENU_REGLAGE_FREQUENCE;
    } else if (option == "5") {
      niveauMenu = MENU_REGLAGE_PID;
    } else if (option == "6") {
      niveauMenu = MENU_ACQUISITION;
    } else if (option == "7") {
      niveauMenu = MENU_DTC;
    } else if (option == "8") {
      niveauMenu = MENU_LIBRE_1;
    } else if (option == "9") {
      niveauMenu = MENU_LIBRE_2;
    } else if (option == "10") {
      niveauMenu = MENU_LIBRE_3;
    } else if (option.equalsIgnoreCase("Q")) {
      // Déjà dans le menu principal, ne rien faire
    } else {
      Serial.println("Option invalide !");
      if (niveauMenu.length() > 1) {
        niveauMenu = niveauMenu.substring(0, niveauMenu.length() - 2); // Retour au menu précédent
      }
    }
  } 
  
  else if (  niveauMenu == MENU_PEDALE               ||   //1.1
             niveauMenu == MENU_PPS_LOG              ||   //  1.1.1
             niveauMenu == MENU_PPS_Calibration      ||   //  1.1.2
             niveauMenu == MENU_PPS_SaveEEPROM       ||   //  1.1.3
             niveauMenu == MENU_PAPILLON             ||   //1.2
             niveauMenu == MENU_TPS_LOG              ||   //  1.2.1
             niveauMenu == MENU_TPS_Calibration      ||   //  1.2.2
             niveauMenu == MENU_TPS_SaveEEPROM       ||   //  1.2.3
             niveauMenu == MENU_REGLAGE_PWM          ||   //1.3
             niveauMenu == MENU_REGLAGE_FREQUENCE    ||   //1.4
             niveauMenu == MENU_REGLAGE_PID          ||   //1.5
             niveauMenu == MENU_PID_Normal           ||   //  1.5.1
             niveauMenu == MENU_PID_Agressif         ||   //  1.5.2
             niveauMenu == MENU_PID_Auto             ||   //  1.5.3
             niveauMenu == MENU_ACQUISITION          ||   //1.6
             niveauMenu == MENU_LOG_Capteurs         ||   //  1.6.1
             niveauMenu == MENU_LOG_Capteur_PPS_TPS  ||   //      1.6.1.1
             niveauMenu == MENU_LOG_Capteur_Cruise   ||   //      1.6.1.2
             niveauMenu == MENU_TEST_Actionneurs     ||   //  1.6.2
             niveauMenu == MENU_TEST_Actionneurs_MIL ||   //      1.6.2.1
             niveauMenu == MENU_TEST_Actionneurs_TB  ||   //      1.6.2.2
             niveauMenu == MENU_RESEAU_CAN           ||   //  1.6.3
             niveauMenu == MENU_DTC                  ||   //1.7
             niveauMenu == MENU_LIBRE_1              ||   //1.8
             niveauMenu == MENU_LIBRE_2              ||   //1.9
             niveauMenu == MENU_LIBRE_3)           {    //1.10
      

      if (option.equalsIgnoreCase("Q") && niveauMenu.length() > 1) {   // .equalsIgnoreCase()Compare deux chaînes pour l'égalité. La comparaison n'est pas sensible à la casse, ce qui signifie que String("hello") est égal à String("HELLO").
         niveauMenu = niveauMenu.substring(0, niveauMenu.length() - 2); // Retour au menu précédent
      }

//!1.3.1 (Depuis le rajopur ici de 1.3.1 et 1.3.2 il y a un bug dans tous les 1er sous menu, il faut fait "q" 2 fois pour quitter)
           if (niveauMenu == MENU_REGLAGE_PWM) {
              if (option == "1") {
                 Serial.println("\n//" + niveauMenu + " Entrer la nouvelle valeur PWM Mini (compris entre 0 et 255)// ");
                 Serial.println("Valeur actuel : " + String(PWMMini));
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("Q) Quitter  ");

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               PWMMini = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("PWM Mini mis à jour : " + String(PWMMini));
              }

               //!1.3.2 (Depuis le rajopur ici de 1.3.1 et 1.3.2 il y a un bug dans tous les 1er sous menu, il faut fait "q" 2 fois pour quitter)
               else if (option == "2") {
                 Serial.println("\n//" + niveauMenu + " Entrer la nouvelle valeur PWM Maxi (compris entre 0 et 255)// ");
                 Serial.println("Valeur actuel : " + String(PWMMaxi));
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("Q) Quitter  ");

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               PWMMaxi = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("PWM Maxi mis à jour : " + String(PWMMaxi));
              }
           }

           if (niveauMenu == MENU_REGLAGE_FREQUENCE) {
              if (option == "1") {
                 Serial.println("\n//" + niveauMenu + " Entrer la nouvelle frequence // ");
                 Serial.println("Valeur actuel : " + String(TPSFreq));
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("Q) Quitter  ");

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               TPSFreq = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("Hz mis à jour : " + String(TPSFreq));
              }
            }

//!1.5.1.1 
           if (niveauMenu == MENU_PID_Normal) {
              if (option == "1") {
                 Serial.println("\n//" + niveauMenu + " Entrer la nouvelle valeur kP normal // ");
                 Serial.println("Valeur actuel : " + String(kP));
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("Q) Quitter  ");

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               kP = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("kP mis à jour : " + String(kP));
              }

             //!1.5.1.2  
             else if (option == "2") {
                 Serial.println("\n//" + niveauMenu + " Entrer la nouvelle valeur kI normal // ");
                 Serial.println("Valeur actuel : " + String(kI));
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("Q) Quitter  ");

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               kI = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("kP mis à jour : " + String(kI));
              }

              //1.5.1.3
              else if (option == "3") {
                 Serial.println("\n//" + niveauMenu + " Entrer la nouvelle valeur kD normal // ");
                 Serial.println("Valeur actuel : " + String(kD));
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("Q) Quitter  ");

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               kD = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("kP mis à jour : " + String(kD));
              }
            }

//!1.5.2.1 
           if (niveauMenu == MENU_PID_Agressif) {
              if (option == "1") {
                 Serial.println("\n//" + niveauMenu + " Entrer la nouvelle valeur kP agressif // ");
                 Serial.println("Valeur actuel : " + String(kP_Agressif));
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("Q) Quitter  ");

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               kP_Agressif = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("kP mis à jour : " + String(kP_Agressif));
              }

             //!1.5.2.2  
             else if (option == "2") {
                 Serial.println("\n//" + niveauMenu + " Entrer la nouvelle valeur kI agressif // ");
                 Serial.println("Valeur actuel : " + String(kI_Agressif));
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("Q) Quitter  ");

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               kI_Agressif = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("kP mis à jour : " + String(kI_Agressif));
              }

              //1.5.2.3
              else if (option == "3") {
                 Serial.println("\n//" + niveauMenu + " Entrer la nouvelle valeur kD agressif // ");
                 Serial.println("Valeur actuel : " + String(kD_Agressif));
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("");
                 Serial.println("Q) Quitter  ");

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               kD_Agressif = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("kP mis à jour : " + String(kD_Agressif));
              }
            }


//
      else {
           niveauMenu += "." + option; // Ajouter l'option au menu actuel
      }
  }
   
  else {
        Serial.println("Option invalide !");
        if (niveauMenu.length() > 1) {
        niveauMenu = niveauMenu.substring(0, niveauMenu.length() - 2); // Retour au menu précédent
        }
  }    
  
}




/**
 * @brief 
 * 
 * @return * Exemple Pour retourner au menu prcedant
 //x.x.x
    else if (menu == FONCTION_PPS_Calibration) {
         while (niveauMenu == "x.x.x") {
          Serial.print("Bonjour");
          Serial.println("Q) Quitter ");

          //Commande pour sortir de la boucle 
           char receivedChar;
           // Vérifie si des données sont disponibles sur la liaison série
           if (Serial.available() > 0) {
             receivedChar = Serial.read(); // Lit le caractère reçu
      
             // Si le caractère reçu est 'q', sort de la boucle while
             if (receivedChar == "q"||"Q") {
               niveauMenu = "x.x"; // Sort de la boucle while
             }
            }
         } 
    } 
*/

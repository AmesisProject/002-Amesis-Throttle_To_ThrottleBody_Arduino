//AmesisProject
//MenuTPS_Megaspeedo : v0.04
//03/08/2023

#include <Arduino.h>
//#include <PID_AutoTune_v0.h>
//#include <PID_v1.h>

// Définition des variables
    int PPSPot1_Numerique = 0 ;
    int PPS1_Position     = 1 ;
    int PPSPot2_Numerique = 2 ;
    int PPS2_Position     = 3 ;
  /*  int TPSPot1_Numerique = 0 ;
    int TPS1_Position     = 1 ;
    int TPSPot2_Numerique = 2 ;
    int TPS2_Position     = 3 ;
    int PWMMini =   0;         
    int PwmMaxi = 255;     
    int TPSFreq = 150;   */
    /*
 //Algrorhytme PID
      double kP ;                  //qVariable Proportional    // kP = 5.12;
      double kI ;                  //Variable Integral        // kI = 47;
      double kD ;                  //Variable Derive          // kD = 0.088;     

*/
// Définir les numéros de menu
#define MENU_PRINCIPAL                "1"      // 1
#define MENU_PEDALE                   "1.1"    //  1.1
#define MENU_PPS_LOG                  "1.1.1"  //    1.1.1
#define MENU_PPS_Calibration          "1.1.2"  //    1.1.2
#define MENU_PPS_SaveEEPROM           "1.1.3"  //    1.1.3
#define MENU_PAPILLON                 "1.2"    //  1.2
/*#define MENU_TPS_LOG                  "1.2.1"  //    1.2.1
#define MENU_TPS_Calibration          "1.2.2"  //    1.2.2
#define MENU_TPS_SaveEEPROM           "1.2.3"  //    1.2.3*/
#define MENU_REGLAGE_PWM              "1.3"    //  1.3
/*#define MENU_PWM_Mini                 "1.3.1"  //    1.3.1
#define MENU_PWM_Maxi                 "1.3.2"  //    1.3.2*/
#define MENU_REGLAGE_FREQUENCE        "1.4"    //  1.4
#define MENU_REGLAGE_PID              "1.5"    //  1.5
#define MENU_PID_KP                   "1.5.1"  //    1.5.1
/*#define MENU_PID_KI                   "1.5.2"  //    1.5.2
#define MENU_PID_KD                   "1.5.3"  //    1.5.3
#define MENU_PID_Auto                 "1.5.4"  //    1.5.4*/
#define MENU_ACQUISITION              "1.6"    //  1.6
/*#define MENU_LOG_Capteurs             "1.6.1"  //    1.6.1
#define MENU_TEST_Actioneurs          "1.6.2"  //    1.6.2
#define MENU_RESEAU_CAN               "1.6.3"  //    1.6.3*/
#define MENU_DTC                      "1.7"    //  1.7
#define MENU_LIBRE_1                  "1.8"    //  1.8
#define MENU_LIBRE_2                  "1.9"    //  1.9
#define MENU_LIBRE_3                  "1.10"   //  1.10
#define MENU_RETOUR                   "11"     //11

// Variable pour stocker le numéro de menu actuel
String niveauMenu = MENU_PRINCIPAL;

void setup() {
  Serial.begin(9600);
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


// Fonction pour afficher le menu principal
void afficherMenuPrincipal() { //Le menu principale comporte 14 lignes, pour garder cette resolution, il y a des Serial.prinrln ("") dans chaque menu pour compbler jusqu'a 14 Lignes, pour un affichage propre du=es menus.
  Serial.println("\n//" + niveauMenu + " Paramètre//");                           // 1
  Serial.println(" 1) Pédale électronique");                                      // 2
  Serial.println(" 2) Papillon motorisé électronique");                           // 3
  Serial.println(" 3) Réglage des PWM pour la rapidités du moteur de papillon");  // 4
  Serial.println(" 4) Réglage de la fréquence du moteur de papillon");            // 5
  Serial.println(" 5) Réglage des PID");                                          // 6
  Serial.println(" 6) Acquisition des valeurs");                                  // 7
  Serial.println(" 7) DTC");                                                      // 8
  Serial.println(" 8) Libre 1");                                                  // 9
  Serial.println(" 9) Libre 2");                                                  //10
  Serial.println("10) Libre 3");                                                  //11
  Serial.println(" Q) Retour au menu précèdent");                                 //12
  Serial.println(".........................................");                    //13
  Serial.println(" Entrez le numéro de l'option souhaitée :");                    //14


}

// Fonction pour afficher les sous-menus
void afficherSousMenu(String menu) {

  //1.1
  if (menu == MENU_PEDALE) {  
    Serial.println("\n//" + niveauMenu + " Pédale éléctronique //");
    Serial.println("1) Vérifier la calibration ");
    Serial.println("2) Lancer la procédure de calibration ");
    Serial.println("3) Enregistrer ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Retour au menu précèdent");   
  } 

    //1.1.1
    else if (menu == MENU_PPS_LOG) {
          while (niveauMenu == "1.1.1") {
           Serial.print("PPS1 = "); Serial.print(PPSPot1_Numerique); Serial.print("ADC / "); Serial.print(PPS1_Position); Serial.print("% |  | "); 
           Serial.print("PPS2 = "); Serial.print(PPSPot2_Numerique); Serial.print("ADC / "); Serial.print(PPS2_Position); Serial.print("% |  | "); 
           Serial.println("Q) Retour au menu précèdent ");

           //Commande pour sortir de la boucle 
           char receivedChar ;
           // Vérifie si des données sont disponibles sur la liaison série
           if (Serial.available() > 0) {
             receivedChar = Serial.read(); // Lit le caractère reçu
      
             // Si le caractère reçu est 'q', sort de la boucle while
             if (receivedChar == "q"||"Q") {
               niveauMenu = MENU_PEDALE; //"1.1"; // Sort de la boucle while
             }
            }
         }  
    } 

    //1.1.2
    else if (menu == MENU_PPS_Calibration) {
         while (niveauMenu == "1.1.2") {
           //Appele de la routine PPS_Calibration();
        //  PPS_Calibration();
          Serial.print("Appuiez sur la pédale à fond plusieur fois lentement");
          Serial.print("PPS1 = "); Serial.print(PPSPot1_Numerique); Serial.print("ADC / "); Serial.print(PPS1_Position); Serial.print("% |  | "); 
          Serial.print("PPS2 = "); Serial.print(PPSPot2_Numerique); Serial.print("ADC / "); Serial.print(PPS2_Position); Serial.print("% |  | "); 
          Serial.println("Q) Retour au menu précèdent ");

          //Commande pour sortir de la boucle 
           char receivedChar;
           // Vérifie si des données sont disponibles sur la liaison série
           if (Serial.available() > 0) {
             receivedChar = Serial.read(); // Lit le caractère reçu
      
             // Si le caractère reçu est 'q', sort de la boucle while
             if (receivedChar == "q"||"Q") {
               niveauMenu = MENU_PEDALE; //"1.1"; // Sort de la boucle while
             }
            }
         } 
    }

    //1.1.3
    else if (menu == MENU_PPS_SaveEEPROM) {
         while (niveauMenu == "1.1.3") {
           //Appele de la routine SaveEEPROM();
       //  SaveEEPROM();
          Serial.print("Les nouvelles données ont été sauvegardées");
          Serial.print("PPS1 = "); Serial.print(PPSPot1_Numerique); Serial.print("ADC / "); Serial.print(PPS1_Position); Serial.print("% |  | "); 
          Serial.print("PPS2 = "); Serial.print(PPSPot2_Numerique); Serial.print("ADC / "); Serial.print(PPS2_Position); Serial.print("% |  | "); 
          Serial.println("Q) Retour au menu précèdent");

          //Commande pour sortir de la boucle 
           char receivedChar;
           // Vérifie si des données sont disponibles sur la liaison série
           if (Serial.available() > 0) {
             receivedChar = Serial.read(); // Lit le caractère reçu
      
             // Si le caractère reçu est 'q', sort de la boucle while
             if (receivedChar == "q"||"Q") {
               niveauMenu = MENU_PEDALE; //"1.1"; // Sort de la boucle while
             }
            }
         } 
    }

  //1.2   
  else if (menu == MENU_PAPILLON)       {
    Serial.println("\n//" + niveauMenu + " Papillon motorisé électronique //");
    Serial.println("1) Vérifier la calibration ");
    Serial.println("2) Lancer la procédure de calibration ");
    Serial.println("3) Enregistrer ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Retour au menu précèdent");
  }
/*
    //1.2.1
    else if (menu == MENU_TPS_LOG) {
          while (niveauMenu == "1.2.1") {
           Serial.print("TPS1 = "); Serial.print(TPSPot1_Numerique); Serial.print("ADC / "); Serial.print(TPS1_Position); Serial.print("% |  | "); 
           Serial.print("TPS2 = "); Serial.print(TPSPot2_Numerique); Serial.print("ADC / "); Serial.print(TPS2_Position); Serial.print("% |  | "); 
           Serial.println("Q) Retour au menu précèdent ");

           //Commande pour sortir de la boucle 
           char receivedChar;
           // Vérifie si des données sont disponibles sur la liaison série
           if (Serial.available() > 0) {
             receivedChar = Serial.read(); // Lit le caractère reçu
      
             // Si le caractère reçu est 'q', sort de la boucle while
             if (receivedChar == "q"||"Q") {
               niveauMenu = "1.2"; // Sort de la boucle while
             }
            }
         }  
    } 

    //1.2.2
    else if (menu == MENU_TPS_Calibration) {
         while (niveauMenu == "1.2.2") {
           //Appele de la routine PPS_Calibration();
        //  TPS_Calibration();
          Serial.print("Ne pas toucher la pédale ! ");
          Serial.print("TPS1 = "); Serial.print(TPSPot1_Numerique); Serial.print("ADC / "); Serial.print(TPS1_Position); Serial.print("% |  | "); 
          Serial.print("TPS2 = "); Serial.print(TPSPot2_Numerique); Serial.print("ADC / "); Serial.print(TPS2_Position); Serial.print("% |  | "); 
          Serial.println("Q) Retour au menu précèdent ");

          //Commande pour sortir de la boucle 
           char receivedChar;
           // Vérifie si des données sont disponibles sur la liaison série
           if (Serial.available() > 0) {
             receivedChar = Serial.read(); // Lit le caractère reçu
      
             // Si le caractère reçu est 'q', sort de la boucle while
             if (receivedChar == "q"||"Q") {
               niveauMenu = "1.2"; // Sort de la boucle while
             }
            }
         } 
    }

    //1.2.3
    else if (menu == MENU_TPS_SaveEEPROM) {
         while (niveauMenu == "1.2.3") {
           //Appele de la routine SaveEEPROM();
       //  SaveEEPROM();
          Serial.print("Les nouvelles données ont été sauvegardées ");
          Serial.print("TPS1 = "); Serial.print(TPSPot1_Numerique); Serial.print("ADC / "); Serial.print(TPS1_Position); Serial.print("% |  | "); 
          Serial.print("TPS2 = "); Serial.print(TPSPot2_Numerique); Serial.print("ADC / "); Serial.print(TPS2_Position); Serial.print("% |  | "); 
          Serial.println("Q) Retour au menu précèdent ");

          //Commande pour sortir de la boucle 
           char receivedChar;
           // Vérifie si des données sont disponibles sur la liaison série
           if (Serial.available() > 0) {
             receivedChar = Serial.read(); // Lit le caractère reçu
      
             // Si le caractère reçu est 'q', sort de la boucle while
             if (receivedChar == "q"||"Q") {
               niveauMenu = "1.2"; // Sort de la boucle while
             }
            }
         } 
    }
*/
  //1.3 
  else if (menu == MENU_REGLAGE_PWM) {
    Serial.println("\n//" + niveauMenu + " Réglage des PWM pour la rapidités du moteur de papillon//");
  /*  Serial.print("1) PWM Mini (Valeur actuelle : "); Serial.print(PWMMini); Serial.println(")");
    Serial.print("2) PWM Maxi (Valeur actuelle : "); Serial.print(PwmMaxi); Serial.println(")");*/
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Retour au menu précèdent");
  }
/*
    //1.3.1
    else if (menu == MENU_PWM_Mini) {
      Serial.println("\n//" + niveauMenu + " Entrer la nouvelle valeur PWM Mini (compris entre 0 et 255)// ");
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
      Serial.println("Q) Retour au menu précèdent ");
    }
    
    //1.3.2
    else if (menu == MENU_PWM_Maxi) {
      Serial.println("\n//" + niveauMenu + " Entrer la nouvelle valeur PWM Maxi (compris entre 0 et 255)// ");
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
      Serial.println("Q) Retour au menu précèdent ");
    }
*/
  //1.4 
  else if (menu == MENU_REGLAGE_FREQUENCE) {
    Serial.println("\n//" + niveauMenu + " Réglage de la fréquence du moteur de papillon //");
    Serial.print("1) Fréquence (Hz) (Valeur actuelle : "); Serial.print("z"/*TPSFreq*/); Serial.println(")");
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
    Serial.println("Q) Retour au menu précèdent");
  }

  //1.5 
  else if (menu == MENU_REGLAGE_PID) {
    Serial.println("\n//" + niveauMenu + " Réglage des PID//");
    /*Serial.print("1) Coefficient kP % (Valeur actuelle : "); Serial.print(kP); Serial.println(")"); //1.5.1 
    Serial.print("2) Coefficient kI % (Valeur actuelle : "); Serial.print(kI); Serial.println(")"); //1.5.2 
    Serial.print("3) Coefficient kD % (Valeur actuelle : "); Serial.print(kD); Serial.println(")"); //1.5.3*/
    Serial.println("4) Activation de recherche PID automatique");                                   //1.5.4
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Retour au menu précèdent");
  }

    //1.5.1 
    else if (menu == MENU_PID_KP) {
         Serial.println("\n//" + niveauMenu + " Réglage du coefficient kP//");
         Serial.println("1) Allumer la LED 13");
         Serial.println("2) Faire clignoter la LED 13");
         Serial.println("3) Eteindre la LED 13");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("Q) Retour au menu précèdent");
    }

  /*  //1.5.2   
    else if (menu == MENU_PID_KI) {
         Serial.println("\n//" + niveauMenu + " Réglage du coefficient kI// ");
         Serial.println("1) Option 1 ");
         Serial.println("2) Option 2 ");
         Serial.println("3) Option 3 ");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("Q) Retour au menu précèdent ");
    }

    //1.5.3   
    else if (menu == MENU_PID_KD) {
         Serial.println("\n//" + niveauMenu + " Réglage du coefficient kD// ");
         Serial.println("1) Option 1 ");
         Serial.println("2) Option 2 ");
         Serial.println("3) Option 3 ");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("");
         Serial.println("Q) Retour au menu précèdent ");
    }

    //1.5.4 
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
         Serial.println("Q) Retour au menu précèdent ");
    }
*/
  //1.6
  else if (menu == MENU_ACQUISITION) {
    Serial.println("\n//" + niveauMenu + " Acquisition des valeurs//");
    Serial.println("1) Lire les valeurs des capteurs");
    Serial.println("2) Teste des actionneurs");
    Serial.println("3) Adaptation");
    Serial.println("4) Libre");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Retour au menu précèdent");
  }
/*
    //1.6.1
    else if (menu == MENU_LOG_Capteurs) {
          while (niveauMenu == "1.6.1") {
           Serial.print("Position Pedale Sensor 1/2 = "); Serial.print(PPS1_Position); Serial.print("% / "); Serial.print(PPS2_Position); Serial.print("% |   | "); 
           Serial.print("Throttle Position Sensor 1/2 = "); Serial.print(TPS1_Position); Serial.print("% / "); Serial.print(TPS2_Position); Serial.print("% |   | "); 
           Serial.println("Q) Retour au menu précèdent ");

           //Commande pour sortir de la boucle 
           char receivedChar;
           // Vérifie si des données sont disponibles sur la liaison série
           if (Serial.available() > 0) {
             receivedChar = Serial.read(); // Lit le caractère reçu
      
             // Si le caractère reçu est 'q', sort de la boucle while
             if (receivedChar == "q"||"Q") {
               niveauMenu = "1.6"; // Sort de la boucle while
             }
            }
         }  
    }

    //1.6.2
    else if (menu == MENU_TEST_Actioneurs) {
           Serial.println("\n//" + niveauMenu + " Acquisition des valeurs// ");
           Serial.println("1) Lire les valeurs des capteurs ");
           Serial.println("2) Teste des actionneurs ");
           Serial.println("3) Adaptation ");
           Serial.println("4) Libre ");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("Q) Retour au menu précèdent ");  
    }

    //1.6.3
    else if (menu == MENU_RESEAU_CAN) {
           Serial.println("\n//" + niveauMenu + " Connection au reseau CAN// ");
           Serial.println("1) Connetion au Speeduino ");
           Serial.println("2) Connection a un calculateur OEM ");
           Serial.println("3) Ecoute du réseaux CAN ");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("Q) Retour au menu précèdent ");  
    }
*/
  //1.7
  else if (menu == MENU_DTC) {
    Serial.println("\n//" + niveauMenu + " DTC//");
    Serial.println("1) Lecture des codes défauts enregistrées en mémoire");
    Serial.println("2) Effacement des codes défaut");
    Serial.println("3) Libre");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Retour au menu précèdent");
  }

  //1.8
  else if (menu == MENU_LIBRE_1) {
    Serial.println("\n//" + niveauMenu + " Libre 1//");
    Serial.println("1) Option libre 1-1");
    Serial.println("2) Option libre 1-2");
    Serial.println("3) Option libre 1-3");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Retour au menu précèdent");
  }

  //1.9
  else if (menu == MENU_LIBRE_2) {
    Serial.println("\n//" + niveauMenu + " Libre 2//");
    Serial.println("1) Option libre 2-1");
    Serial.println("2) Option libre 2-2");
    Serial.println("3) Option libre 2-3");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Retour au menu précèdent");
  }

  //1.10
  else if (menu == MENU_LIBRE_3) {
    Serial.println("\n//" + niveauMenu + " Libre 3//");
    Serial.println("1) Option libre 3-1");
    Serial.println("2) Option libre 3-2");
    Serial.println("3) Option libre 3-3");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("Q) Retour au menu précèdent");
  }

  Serial.println("Entrez le numéro de l'option souhaitée :");
}

// Fonction pour gérer les actions du menu
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
  
  else if (niveauMenu == MENU_PEDALE              ||   //1.1
             niveauMenu == MENU_PPS_LOG           ||   //  1.1.1
             niveauMenu == MENU_PPS_Calibration   ||   //  1.1.2
             niveauMenu == MENU_PPS_SaveEEPROM    ||   //  1.1.3
             niveauMenu == MENU_PAPILLON          ||   //1.2
 /*            niveauMenu == MENU_TPS_LOG           ||   //  1.2.1
             niveauMenu == MENU_TPS_Calibration   ||   //  1.2.2
             niveauMenu == MENU_TPS_SaveEEPROM    ||   //  1.2.3*/
             niveauMenu == MENU_REGLAGE_PWM       ||   //1.3
     /*        niveauMenu == MENU_PWM_Mini          ||   //  1.3.1
             niveauMenu == MENU_PWM_Maxi          ||   //  1.3.2*/
             niveauMenu == MENU_REGLAGE_FREQUENCE ||   //1.4
             niveauMenu == MENU_REGLAGE_PID       ||   //1.5
             niveauMenu == MENU_PID_KP            ||   //  1.5.1
   /*          niveauMenu == MENU_PID_KI            ||   //  1.5.2
             niveauMenu == MENU_PID_KD            ||   //  1.5.3
             niveauMenu == MENU_PID_Auto          ||   //  1.5.4*/
             niveauMenu == MENU_ACQUISITION       ||   //1.6
   /*          niveauMenu == MENU_LOG_Capteurs      ||   //  1.6.1
             niveauMenu == MENU_TEST_Actioneurs   ||   //  1.6.2
             niveauMenu == MENU_RESEAU_CAN        ||   //  1.6.3*/
             niveauMenu == MENU_DTC               ||   //1.7
             niveauMenu == MENU_LIBRE_1           ||   //1.8
             niveauMenu == MENU_LIBRE_2           ||   //1.9
             niveauMenu == MENU_LIBRE_3)           {    //1.10
      

      if (option.equalsIgnoreCase("Q") && niveauMenu.length() > 1) {   // .equalsIgnoreCase()Compare deux chaînes pour l'égalité. La comparaison n'est pas sensible à la casse, ce qui signifie que String("hello") est égal à String("HELLO").
         niveauMenu = niveauMenu.substring(0, niveauMenu.length() - 2); // Retour au menu précédent
      }
      
 
      else {
        if (niveauMenu == MENU_PID_KP) {
           // Gérer les actions spécifiques au sous-sous-menu "Réglage du coefficient kP"
            if (option == "1") { 
                                digitalWrite(13, HIGH); // Allumer la LED 13
                               } 
            else if (option == "2") { 
                                     for (int i = 0; i < 5; i++) {
                                     digitalWrite(13, HIGH); // Allumer la LED 13
                                     delay(200);
                                     digitalWrite(13, LOW); // Éteindre la LED 13
                                     delay(200);
                                     }
                                    } 
            else if (option == "3") {
                                     digitalWrite(13, LOW); // Éteindre la LED 13
                                    }
            else {
                  Serial.println("Option invalide !");
                 }
        } 

       //  
       else {
           niveauMenu += "." + option; // Ajouter l'option au menu actuel
          }
      }
  } 
  
  else {
        Serial.println("Option invalide !");
        if (niveauMenu.length() > 1) {
        niveauMenu = niveauMenu.substring(0, niveauMenu.length() - 2); // Retour au menu précédent
        }
  }
}





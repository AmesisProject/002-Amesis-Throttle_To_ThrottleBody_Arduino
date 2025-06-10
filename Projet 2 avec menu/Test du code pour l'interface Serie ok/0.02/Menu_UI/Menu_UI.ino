//AmesisProject
//MenuTPS_Megaspeedo : v0.02
//01/08/2023

#include <Arduino.h>
// Définition des variables
    int PPSPot1_Numerique = 0;
    int PPS1_Position = 1 ;
    int PPSPot2_Numerique =2 ;
    int PPS2_Position = 3 ;


// Définir les numéros de menu
#define MENU_PRINCIPAL "1"
#define MENU_CALIB_PEDALE "1.1"
#define MENU_PEDALE_LOG "1.1.1"
#define MENU_CALIB_PAPILLON "1.2"
#define MENU_REGLAGE_PWM "1.3"
#define MENU_REGLAGE_FREQUENCE "1.4"
#define MENU_REGLAGE_PID "1.5"
#define MENU_PID_KP "1.5.1"
#define MENU_PID_KI "1.5.2"
#define MENU_PID_KD "1.5.3"
#define MENU_ACQUISITION "1.6"
#define MENU_DTC "1.7"
#define MENU_LIBRE_1 "1.8"
#define MENU_LIBRE_2 "1.9"
#define MENU_LIBRE_3 "1.10"
#define MENU_RETOUR "11"

// Variable pour stocker le numéro de menu actuel
String niveauMenu = MENU_PRINCIPAL;

// Fonction pour afficher le menu principal
void afficherMenuPrincipal() {
  Serial.println("\n//" + niveauMenu + " Paramètre//");
  Serial.println("1) Calibration pédale électronique");
  Serial.println("2) Calibration papillon électronique");
  Serial.println("3) Réglage des PWM pour la rapidités du moteur de papillon");
  Serial.println("4) Réglage de la fréquence du moteur de papillon");
  Serial.println("5) Réglage des PID");
  Serial.println("6) Acquisition des valeurs");
  Serial.println("7) DTC");
  Serial.println("8) Libre 1");
  Serial.println("9) Libre 2");
  Serial.println("10) Libre 3");
  Serial.println("Q) Retour au menu précèdent");
  Serial.println("Entrez le numéro de l'option souhaitée :");
}

// Fonction pour afficher les sous-menus
void afficherSousMenu(String menu) {
  if (menu == MENU_CALIB_PEDALE) {
    Serial.println("\n//" + niveauMenu + " Calibration pédale//");
    Serial.println("1) Vérifier la calibration");
    Serial.println("2) Lancer la procédure de calibration");
    Serial.println("3) Enregistrer");
    Serial.println("4) Libre");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_PEDALE_LOG) {
    Serial.println("\n//" + niveauMenu + " Log papillon électronique//");
    Serial.print("Potentiometre 1 = "); Serial.print(PPSPot1_Numerique); Serial.print(" <=> "); Serial.print(PPS1_Position); Serial.println("% ");
    Serial.print("Potentiometre 2 = "); Serial.print(PPSPot2_Numerique); Serial.print(" <=> "); Serial.print(PPS2_Position); Serial.println("% ");
    Serial.println("");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_CALIB_PAPILLON) {
    Serial.println("\n//" + niveauMenu + " Calibration papillon électronique//");
    Serial.println("1) Vérifier la calibration");
    Serial.println("2) Lancer la procédure de calibration");
    Serial.println("3) Enregistrer");
    Serial.println("4) Libre");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_REGLAGE_PWM) {
    Serial.println("\n//" + niveauMenu + " Réglage des PWM pour la rapidités du moteur de papillon//");
    Serial.println("1) PWM Mini");
    Serial.println("2) PWM Maxi");
    Serial.println("3) Info");
    Serial.println("4) Libre");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_REGLAGE_FREQUENCE) {
    Serial.println("\n//" + niveauMenu + " Réglage de la fréquence du moteur de papillon//");
    Serial.println("1) Fréquence Mini");
    Serial.println("2) Fréquence Maxi");
    Serial.println("3) Info");
    Serial.println("4) Libre");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_REGLAGE_PID) {
    Serial.println("\n//" + niveauMenu + " Réglage des PID//");
    Serial.println("1) Coefficient kP");
    Serial.println("2) Coefficient kI");
    Serial.println("3) Coefficient kD");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_PID_KP) {
    Serial.println("\n//" + niveauMenu + " Réglage du coefficient kP//");
    Serial.println("1) Allumer la LED 13");
    Serial.println("2) Faire clignoter la LED 13");
    Serial.println("3) Eteindre la LED 13");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_PID_KI) {
    Serial.println("\n//" + niveauMenu + " Réglage du coefficient kI//");
    Serial.println("1) Option 1");
    Serial.println("2) Option 2");
    Serial.println("3) Option 3");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_PID_KD) {
    Serial.println("\n//" + niveauMenu + " Réglage du coefficient kD//");
    Serial.println("1) Option 1");
    Serial.println("2) Option 2");
    Serial.println("3) Option 3");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_ACQUISITION) {
    Serial.println("\n//" + niveauMenu + " Acquisition des valeurs//");
    Serial.println("1) Lire les valeurs des capteurs");
    Serial.println("2) Teste des actionneurs");
    Serial.println("3) Adaptation");
    Serial.println("4) Libre");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_DTC) {
    Serial.println("\n//" + niveauMenu + " DTC//");
    Serial.println("1) Lecture des codes défauts enregistrées en mémoire");
    Serial.println("2) Effacement des codes défaut");
    Serial.println("3) Libre");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_LIBRE_1) {
    Serial.println("\n//" + niveauMenu + " Libre 1//");
    Serial.println("1) Option libre 1-1");
    Serial.println("2) Option libre 1-2");
    Serial.println("3) Option libre 1-3");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_LIBRE_2) {
    Serial.println("\n//" + niveauMenu + " Libre 2//");
    Serial.println("1) Option libre 2-1");
    Serial.println("2) Option libre 2-2");
    Serial.println("3) Option libre 2-3");
    Serial.println("Q) Retour au menu précèdent");
  } else if (menu == MENU_LIBRE_3) {
    Serial.println("\n//" + niveauMenu + " Libre 3//");
    Serial.println("1) Option libre 3-1");
    Serial.println("2) Option libre 3-2");
    Serial.println("3) Option libre 3-3");
    Serial.println("Q) Retour au menu précèdent");
  }
  Serial.println("Entrez le numéro de l'option souhaitée :");
}

// Fonction pour gérer les actions du menu
void gererMenu(String option) {
  if (niveauMenu == MENU_PRINCIPAL) {
    if (option == "1") {
      niveauMenu = MENU_CALIB_PEDALE;
    } else if (option == "2") {
      niveauMenu = MENU_CALIB_PAPILLON;
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
  } else if (niveauMenu == MENU_CALIB_PEDALE || niveauMenu == MENU_CALIB_PAPILLON || niveauMenu == MENU_REGLAGE_PWM || niveauMenu == MENU_REGLAGE_FREQUENCE || niveauMenu == MENU_REGLAGE_PID || niveauMenu == MENU_PID_KP || niveauMenu == MENU_PID_KI || niveauMenu == MENU_PID_KD || niveauMenu == MENU_ACQUISITION || niveauMenu == MENU_DTC || niveauMenu == MENU_LIBRE_1 || niveauMenu == MENU_LIBRE_2 || niveauMenu == MENU_LIBRE_3) {
    if (option.equalsIgnoreCase("Q") && niveauMenu.length() > 1) {
      niveauMenu = niveauMenu.substring(0, niveauMenu.length() - 2); // Retour au menu précédent
    } else {
      if (niveauMenu == MENU_PID_KP) {
        // Gérer les actions spécifiques au sous-sous-menu "Réglage du coefficient kP"
        if (option == "1") {
          digitalWrite(13, HIGH); // Allumer la LED 13
        } else if (option == "2") {
          for (int i = 0; i < 5; i++) {
            digitalWrite(13, HIGH); // Allumer la LED 13
            delay(500);
            digitalWrite(13, LOW); // Éteindre la LED 13
            delay(500);
          }
        } else if (option == "3") {
          digitalWrite(13, LOW); // Éteindre la LED 13
        } else {
          Serial.println("Option invalide !");
        }
      } else {
        niveauMenu += "." + option; // Ajouter l'option au menu actuel
      }
    }
  } else {
    Serial.println("Option invalide !");
    if (niveauMenu.length() > 1) {
      niveauMenu = niveauMenu.substring(0, niveauMenu.length() - 2); // Retour au menu précédent
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); // Définir la broche 13 comme sortie pour contrôler la LED
  afficherMenuPrincipal();
}

void loop() {
  if (Serial.available() > 0) {
    String option = Serial.readStringUntil('\n');
    option.trim();
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

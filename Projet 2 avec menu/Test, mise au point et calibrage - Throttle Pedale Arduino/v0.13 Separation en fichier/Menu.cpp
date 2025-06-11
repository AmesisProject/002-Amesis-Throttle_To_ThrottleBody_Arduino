#include <Arduino.h>
#include "Menu.h"
#include "Capteurs.h"
#include "Moteur.h"

// Fonctions pour l'interce utilisateur
void afficherMenuPrincipal() { //Le menu principale comporte 14 lignes, pour garder cette resolution, il y a des Serial.prinrln ("") dans chaque menu pour compbler jusqu'a 14 Lignes, pour un affichage propre du=es menus.
  Serial.println("\n//" + niveauMenu + " Setting// ");  // 1
  Serial.println(" 1) PPS");                            // 2
  Serial.println(" 2) TB");                             // 3
  Serial.println(" 3) PWM TB");                         // 4
  Serial.println(" 4) Hz TB");                          // 5
  Serial.println(" 5) PID ");                           // 6
  Serial.println(" 6) Acquisition");                    // 7
  Serial.println(" 7) DTC");                            // 8
  Serial.println(" 8)    ^ ^");                        // 9
  Serial.println(" 9)  =( '')=");                      //10
  Serial.println("10) ('')_('')");                     //11
  Serial.println("By AmesisProject TB V0.09");          //12
  Serial.println("...................");                //13
  Serial.println(" Enter a number :");                  //14


}


void afficherSousMenu(String menu) {

  //!1.1
  if (menu == MENU_PEDALE) {  
    Serial.println("\n//" + niveauMenu + " Pédal//");
    Serial.println("1) Read "+ String(PPS1_Calib_Mini) + " " + String(PPS1_Calib_Maxi));
    Serial.println("2) Calibration");
    Serial.println("3) Save");
    Serial.println("");
    Serial.println("");// ) Info : Il est necessaire que la calibration de la pédale éléctronique ");
    Serial.println("");//          soit faite avant la calibrage du papillon motorisé. ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println(Quit);   
  } 

    //!1.1.1
    else if (menu == MENU_PPS_LOG){ 
          digitalWrite(13, HIGH); // Test d'appel d'une fonction
          while (niveauMenu == MENU_PPS_LOG) { //"1.1.1"
           ReadSensor (); 
           Serial.print("PPS1 = " + String(PPSPot1_ADC) + "ADC / " + String(PPS1_Position) + "% |  | "); 
           Serial.print("PPS2 = " + String(PPSPot2_ADC) + "ADC / " + String(PPS2_Position) + "% |  | "); 
           Serial.println(Quit);

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
      
           //Appele de la routine PPS_Calibration();
          PPS_Calibration();
          niveauMenu = MENU_PEDALE; // Sort de la boucle while vers 1.1
             
    }    

    //!1.1.3
    else if (menu == MENU_PPS_SaveEEPROM) {

          digitalWrite(13, LOW);// Test d'appel d'une fonction
      //  SaveEEPROM();  //Appele de la routine SaveEEPROM();
          Serial.println("\n//" + niveauMenu + " Saved data// ");
          Serial.println(""); 
          Serial.println("| PPS1 Min = " + String(PPS1_Calib_Mini) + " ADC ");
          Serial.println("| PPS1 Max = " + String(PPS1_Calib_Maxi) + " ADC ");
          Serial.println("");
          Serial.println("| PPS2 Min = " + String(PPS2_Calib_Mini) + " ADC "); 
          Serial.println("| PPS2 Max = " + String(PPS2_Calib_Maxi) + " ADC "); 
          Serial.println("");
          Serial.println("");
          Serial.println("");
          Serial.println("");
          Serial.println("");
          Serial.println(Quit);
    }

  //!1.2   
  else if (menu == MENU_PAPILLON)       {
    Serial.println("\n//" + niveauMenu + " Throttle Body// ");
    Serial.println("1) Read " + String(TPS1_Calib_Mini) + " " + String(TPS1_Calib_Neutral) + " " + String(TPS1_Calib_Maxi));
    Serial.println("2) Calibration");
    Serial.println("3) Save");
    Serial.println("");
    Serial.println("");// ) Info : Moteur coupé, batterie chargé. Il est nécessaire que la calibration de la ");
    Serial.println("");//          pédale éléctronique soit faite correctement avant de calibré le papillon ");
    Serial.println("");//          motorisé. Si ce n'est pas fait RDV au Menu '1.1 Pédale éléctronique'. ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println(Quit);
  }

    //!1.2.1
    else if (menu == MENU_TPS_LOG) {
          digitalWrite(13, HIGH); // Test d'appel d'une fonction
          while (niveauMenu == MENU_TPS_LOG) {
           ReadSensor ();
           Serial.print("TPS1 = " + String(TPSPot1_ADC) + "ADC / " + String(TPS1_Position) + "% |  | "); 
           Serial.print("TPS2 = " + String(TPSPot2_ADC) + "ADC / " + String(TPS2_Position) + "% |  | "); 
           Serial.println(Quit);

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
         TPS_Calibration();
         niveauMenu = MENU_PAPILLON;

    }

    //!1.2.3
    else if (menu == MENU_TPS_SaveEEPROM) {
          digitalWrite(13, LOW);// Test d'appel d'une fonction
      //  SaveEEPROM();  //Appele de la routine SaveEEPROM();
          Serial.println("\n//" + niveauMenu + " Saved data// ");
          Serial.println(""); 
          Serial.println("| TPS1 Min   = " + String(TPS1_Calib_Mini) +" ADC ");
          Serial.println("| TPS1 Neutral = " + String(TPS1_Calib_Neutral) +" ADC ");
          Serial.println("| TPS1 Max   = " + String(TPS1_Calib_Maxi) + " ADC ");
          Serial.println("");
          Serial.println("| TPS2 Min   = " + String(TPS2_Calib_Mini) + " ADC "); 
          Serial.println("| TPS2 Neutral = " + String(TPS2_Calib_Neutral) + " ADC ");
          Serial.println("| TPS2 Max   = " + String(TPS2_Calib_Maxi) + " ADC "); 
          Serial.println("");
          Serial.println("");
          Serial.println("");
          Serial.println(Quit);
    }

  //!1.3 
  else if (menu == MENU_REGLAGE_PWM) {
    Serial.println("\n//" + niveauMenu + " Adjusting PWMs for TB speeds//"); //Réglage des PWM pour la rapidités du moteur de papillon// ");
    Serial.println("1) PWM Min (" + CurrentValue + String(PwmMini) + ") ");
    Serial.println("2) PWM Max (" + CurrentValue + String(PwmMaxi) + ") ");
    Serial.println("");
    Serial.println("");// ) Info : Les valeurs mini max sont 0 - 255, elles correspondent à une vitesse ");
    Serial.println("");//          minimum ou maximum pour la commande du papillon électronique. ");
    Serial.println("");//          Par ex. dans un cas de figue X, le papillon pourrait commancer à ");
    Serial.println("");//          bouger qu'à partir de 20 et non de 1. Reciproquement il pourrait attiendre ");
    Serial.println("");//          sa vitesse maximum à 230, donc inutile de mettre 255, le pont en H ");
    Serial.println("");//          pourait surchauffer pour rien.");
    Serial.println("");
    Serial.println("");
    Serial.println(Quit);
  }

    //!1.3.1 
      //! Voir dans void gererMenu(String option) 
    
    //!1.3.2
      //! Voir dans void gererMenu(String option) 

  //!1.4 
  else if (menu == MENU_REGLAGE_FREQUENCE) {
    Serial.println("\n//" + niveauMenu + " Adjusting Hz for TB// ");
    Serial.println("1) Hz ("+ CurrentValue + String(TPSFreq) + ") ");
    Serial.println("");
    Serial.println("");// ) Info : Le corp de papillon motorisé éléctronique est minue d'un moteur ");
    Serial.println("");//          de type DC à courant continue. Ce moteur DC doit être allimenté ");
    Serial.println("");//          avec une certainne fréquence pour sont fonctionnement optimal en PWM. ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println(Quit);
  }
   
    //!1.4.1
      // Voir dans void gererMenu(String option)

  //!1.5 
  else if (menu == MENU_REGLAGE_PID) {
      Serial.println("\n//" + niveauMenu + " PID adjustment// ");
      Serial.println("1) Normal     | " + String(kP) + " | " + String(kI) + " | "+ String(kD) + " | "); 
      Serial.println("2) Aggressive | " + String(kP_Agressif) + " | " + String(kI_Agressif) + " | "+ String(kD_Agressif) + " | "); 
      Serial.println("3) Automatic PID");
      Serial.println("");
      Serial.println("");// ) Info : Le système intègre l'algoritme de PID Proportionnel Itégral et Dérivé en ");
      Serial.println("");//          boucle fermée CL Pour comprendre ce qu'est les PID veyez regarder ces vidéos :");
      Serial.println("");//          https://www.youtube.com/watch?v=qKy98Cbcltw&t=5s");
      Serial.println("");//          https://www.youtube.com/watch?v=udnUTi6y8Fw");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println(Quit);
  }

    //!1.5.1 
    else if (menu == MENU_PID_Normal) {
      Serial.println("\n//" + niveauMenu + " Normal PID// ");
      Serial.println("1) kP : " + String(kP) + ") ");
      Serial.println("2) kI : " + String(kI) + ") ");
      Serial.println("3) kD : " + String(kD) + ") ");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println(Quit);
    }

      //!1.5.1.1 
      //!1.5.1.2   
      //!1.5.1.3
      // Voir dans void gererMenu(String option)


    //!1.5.2
    else if (menu == MENU_PID_Agressif) {
      Serial.println("\n//" + niveauMenu + " Aggressive PID // ");
      Serial.println("1) kP : " + String(kP_Agressif) + ") ");
      Serial.println("2) kI : " + String(kI_Agressif) + ") ");
      Serial.println("3) kD : " + String(kD_Agressif) + ") ");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println(Quit);
    }         

      //!1.5.2.1 
      //!1.5.2.2   
      //!1.5.2.3 
      // Voir dans void gererMenu(String option)

    //!1.5.3 
    else if (menu == MENU_PID_Auto) {
         Serial.println("\n//" + niveauMenu + " Automatic PID// "); // voir avec la librairie #include <PID_AutoTune_v0.h>
         Serial.println("1) To do");
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
         Serial.println(Quit);
    }

  //!1.6
  else if (menu == MENU_ACQUISITION) {
    Serial.println("\n//" + niveauMenu + " Acquisition//");
    Serial.println("1) Read");
    Serial.println("2) Actuator testing");
    Serial.println("3) Connexion");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println(Quit);
  }

    //!1.6.1
    else if (menu == MENU_LOG_Capteurs) {
      Serial.println("\n//" + niveauMenu + " Read value//");
      Serial.println("1) PPS");
      Serial.println("2) Cruise control");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println(Quit);
    }
 
       //!1.6.1.1
       else if (menu == MENU_LOG_Capteur_PPS_TPS) {
             while (niveauMenu == MENU_LOG_Capteur_PPS_TPS) {
              Serial.print("PPS 1&2 = " + String(PPS1_Position) + "% / " + String(PPS2_Position) + "% |   | "); 
              Serial.print("TPS 1&2 = " + String(TPS1_Position) + "% / " + String(TPS2_Position) + "% |   | "); 
              Serial.println(Quit);

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
              Serial.print("Button O/I = " + String(CruiseButton_ActiveCruise)); 
              Serial.print(" | BP Up = " + String(Cruise_Up)); 
              Serial.print(" | BP Down = " + String(Cruise_Down));
              Serial.print(" | BP Cancel = " + String(Cruise_Cancel)); 
              Serial.print(" |     "); 
              Serial.println(Quit);

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
           Serial.println("\n//" + niveauMenu + " Actuator testing// ");
           Serial.println("1) Led MIL");
           Serial.println("2) TB");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println(Quit);  
    }

       //!1.6.2.1
       else if (menu == MENU_TEST_Actionneurs_MIL) {
             Serial.println("\n//" + niveauMenu + " Led MIL// ");
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
             Serial.println(Quit);

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
              Serial.println("\n//" + niveauMenu + " Closing/Opening TB// ");

       }

    //!1.6.3
    else if (menu == MENU_RESEAU_CAN) {
           Serial.println("\n//" + niveauMenu + " Network// ");
           Serial.println("1) To Speeduino");
           Serial.println("2) To ECU OEM");
           Serial.println("3) CAN");
           Serial.println("");
           Serial.println("");// ) Info : Non fonctionel pour le moment mais pour les futures mise à jour du FW ");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println("");
           Serial.println(Quit);  
    }

  //!1.7
  else if (menu == MENU_DTC) {
    Serial.println("\n//" + niveauMenu + " DTC// ");
    Serial.println("1) Read DTC");
    Serial.println("2) Erase DTC ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println(Quit);
  }

  //!1.8
  else if (menu == MENU_LIBRE_1) {
    Serial.println("\n//" + niveauMenu + " Free1// ");
    Serial.println("1) 1-1");
    Serial.println("2) 1-2 ");
    Serial.println("3) 1-3 ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println(Quit);
  }

  //!1.9
  else if (menu == MENU_LIBRE_2) {
    Serial.println("\n//" + niveauMenu + " Free2// ");
    Serial.println("1) 2-1 ");
    Serial.println("2) 2-2 ");
    Serial.println("3) 2-3 ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println(Quit);
  }

  //!1.10
  else if (menu == MENU_LIBRE_3) {
    Serial.println("\n//" + niveauMenu + " Free3// ");
    Serial.println("1) 3-1 ");
    Serial.println("2) 3-2 ");
    Serial.println("3) 3-3 ");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println(Quit);
  }

  Serial.println("Enter a number :");
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
      Serial.println("Invalid");
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
             niveauMenu == MENU_LIBRE_3)           {      //1.10
      

      if (option.equalsIgnoreCase("Q") && niveauMenu.length() > 1) {   // .equalsIgnoreCase()Compare deux chaînes pour l'égalité. La comparaison n'est pas sensible à la casse, ce qui signifie que String("hello") est égal à String("HELLO").
         niveauMenu = niveauMenu.substring(0, niveauMenu.length() - 2); // Retour au menu précédent
      }

//!1.3.1 (Depuis le rajopur ici de 1.3.1 et 1.3.2 il y a un bug dans tous les 1er sous menu, il faut fait "q" 2 fois pour quitter)
           if (niveauMenu == MENU_REGLAGE_PWM) {
              if (option == "1") {
                 Serial.println("\n//" + niveauMenu + " New value PWM Min// ");
                 Serial.println(CurrentValue + String(PwmMini));
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
                 Serial.println(Quit);

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               PwmMini = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("PWM Min = " + String(PwmMini));
              }

               //!1.3.2 (Depuis le rajopur ici de 1.3.1 et 1.3.2 il y a un bug dans tous les 1er sous menu, il faut fait "q" 2 fois pour quitter)
               else if (option == "2") {
                 Serial.println("\n//" + niveauMenu + " New value PWM Max// ");
                 Serial.println(CurrentValue + String(PwmMaxi));
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
                 Serial.println(Quit);

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               PwmMaxi = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("PWM Max = " + String(PwmMaxi));
              }
           }

           if (niveauMenu == MENU_REGLAGE_FREQUENCE) {
              if (option == "1") {
                 Serial.println("\n//" + niveauMenu + " New Hz// ");
                 Serial.println(CurrentValue + String(TPSFreq));
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
                 Serial.println(Quit);

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               TPSFreq = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("Hz = " + String(TPSFreq));
              }
            }

//!1.5.1.1 
           if (niveauMenu == MENU_PID_Normal) {
              if (option == "1") {
                 Serial.println("\n//" + niveauMenu + " New kP normal// ");
                 Serial.println(CurrentValue + String(kP));
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
                 Serial.println(Quit);

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               kP = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("kP = " + String(kP));
              }

             //!1.5.1.2  
             else if (option == "2") {
                 Serial.println("\n//" + niveauMenu + " New kI normal// ");
                 Serial.println(CurrentValue + String(kI));
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
                 Serial.println(Quit);

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               kI = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("kP = " + String(kI));
              }

              //1.5.1.3
              else if (option == "3") {
                 Serial.println("\n//" + niveauMenu + " New kD normal// ");
                 Serial.println(CurrentValue + String(kD));
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
                 Serial.println(Quit);

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               kD = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("kP = " + String(kD));
              }
            }

//!1.5.2.1 
           if (niveauMenu == MENU_PID_Agressif) {
              if (option == "1") {
                 Serial.println("\n//" + niveauMenu + " New kP agressif// ");
                 Serial.println(CurrentValue + String(kP_Agressif));
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
                 Serial.println(Quit);

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               kP_Agressif = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("kP = " + String(kP_Agressif));
              }

             //!1.5.2.2  
             else if (option == "2") {
                 Serial.println("\n//" + niveauMenu + " New kI agressif// ");
                 Serial.println(CurrentValue + String(kI_Agressif));
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
                 Serial.println(Quit);

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               kI_Agressif = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("kP = " + String(kI_Agressif));
              }

              //1.5.2.3
              else if (option == "3") {
                 Serial.println("\n//" + niveauMenu + " New kD agressif// ");
                 Serial.println(CurrentValue + String(kD_Agressif));
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
                 Serial.println(Quit);

               while (Serial.available() <= 0) {
                 // Attendre que des données soient disponibles sur le port série
               }
               kD_Agressif = Serial.parseInt(); // Lire l'entier entré par l'utilisateur
               Serial.println("kP = " + String(kD_Agressif));
              }
            }


//
      else {
           niveauMenu += "." + option; // Ajouter l'option au menu actuel
      }
  }
   
  else {
        Serial.println("Invalid");
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

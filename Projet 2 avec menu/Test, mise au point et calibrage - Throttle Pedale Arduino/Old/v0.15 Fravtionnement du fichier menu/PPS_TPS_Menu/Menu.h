#ifndef MENU_H
#define MENU_H

#include <Arduino.h>

// Version du programme
extern const char* VERSION;

// Variables externes du programme principal
extern int PPS1_Calib_Mini;
extern int PPS1_Calib_Maxi;
extern int PPS2_Calib_Mini;
extern int PPS2_Calib_Maxi;
extern int PPSPot1_ADC;
extern int PPSPot2_ADC;
extern int PPS1_Position;
extern int PPS2_Position;

extern int TPS1_Calib_Mini;
extern int TPS1_Calib_Maxi;
extern int TPS1_Calib_Neutral;
extern int TPS2_Calib_Mini;
extern int TPS2_Calib_Maxi;
extern int TPS2_Calib_Neutral;
extern int TPSPot1_ADC;
extern int TPSPot2_ADC;
extern int TPS1_Position;
extern int TPS2_Position;

extern int PwmMini;
extern int PwmMaxi;
extern int TPSFreq;

extern double kP;
extern double kI;
extern double kD;
extern double kP_Agressif;
extern double kI_Agressif;
extern double kD_Agressif;

extern int CruiseButton_ActiveCruise;
extern int Cruise_Up;
extern int Cruise_Down;
extern int Cruise_Cancel;

// Fonctions externes
extern void ReadSensor();
extern void PPS_Calibration();
extern void TPS_Calibration();

// Définition des numéros de menu
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

// Variables du menu
extern String niveauMenu;
extern String Quit;
extern String CurrentValue;

// Fonctions du menu
/**
 * @brief Initialise le menu et affiche le menu principal
 */
void initMenu();

/**
 * @brief Affiche le menu principal avec toutes les options disponibles
 */
void afficherMenuPrincipal();

/**
 * @brief Affiche un sous-menu spécifique en fonction du niveau de menu passé en paramètre
 * @param menu Le niveau de menu à afficher (ex: "1.1", "1.2", etc.)
 */
void afficherSousMenu(String menu);

/**
 * @brief Gère la navigation dans les menus en fonction de l'option choisie par l'utilisateur
 * @param option L'option sélectionnée par l'utilisateur
 */
void gererMenu(String option);

/**
 * @brief Gère les réglages PWM du menu 1.3
 * @param option L'option sélectionnée par l'utilisateur
 */
void handlePWMMenu(String option);

/**
 * @brief Gère les réglages de fréquence du menu 1.4
 * @param option L'option sélectionnée par l'utilisateur
 */
void handleFrequencyMenu(String option);

/**
 * @brief Gère les réglages PID normaux du menu 1.5.1
 * @param option L'option sélectionnée par l'utilisateur
 */
void handleNormalPIDMenu(String option);

/**
 * @brief Gère les réglages PID agressifs du menu 1.5.2
 * @param option L'option sélectionnée par l'utilisateur
 */
void handleAgressifPIDMenu(String option);

/**
 * @brief Obtient une nouvelle valeur PID de l'utilisateur
 * @param paramName Le nom du paramètre PID à modifier
 * @param param La référence vers la variable à modifier
 */
void getNewPIDValue(String paramName, double &param);

/**
 * @brief Imprime un nombre spécifié de lignes vides
 * @param count Le nombre de lignes vides à imprimer
 */
void printEmptyLines(int count);

#endif 


#ifndef PPS_TPS_MENU_H
#define PPS_TPS_MENU_H

// Déclaration des variables globales pour la pédale d'accélérateur
extern int PPSPot1_Pin;
extern int PPSPot1_ADC;
extern int PPS1_Calib_Mini;
extern int PPS1_Calib_Maxi;
extern int PPS1_Position;
extern bool PPS1_LoHi;

extern int PPSPot2_Pin;
extern int PPSPot2_ADC;
extern int PPS2_Calib_Mini;
extern int PPS2_Calib_Maxi;
extern int PPS2_Position;
extern bool PPS2_loHi;

extern int PPSPot_ADC;
extern int PPS_Min_ADC;
extern int PPS_Max_ADC;
extern int PPS_Position;

// Déclaration des variables globales pour le papillon motorisé
extern int TPSPot1_Pin;
extern int TPSPot1_ADC;
extern int TPS1_Calib_Mini;
extern int TPS1_Calib_Neutral;
extern int TPS1_Calib_Maxi;
extern int TPS1_Position;
extern bool TPS1_LoHi;

extern int TPSPot2_Pin;
extern int TPSPot2_ADC;
extern int TPS2_Calib_Mini;
extern int TPS2_Calib_Neutral;
extern int TPS2_Calib_Maxi;
extern int TPS2_Position;
extern bool TPS2_LoHi;

extern int TPSPot_ADC;
extern int TPS_Min_ADC;
extern int TPS_Neutral_ADC;
extern int TPS_Max_ADC;
extern int TPS_Position;

// Déclaration des variables globales pour le moteur (pont en H)
extern int motorPin1;
extern int motorPin2;
extern int enablePin;
extern bool motor_LoHi;
extern int PwmMini;
extern int PwmMaxi;

#endif
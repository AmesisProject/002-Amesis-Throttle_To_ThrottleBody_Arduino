#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <Arduino.h>
#include <EEPROM.h>

// ============================================================================
// ORGANISATION OPTIMALE DE LA MÉMOIRE EEPROM
// ============================================================================

// Constantes de validation EEPROM
#define EEPROM_MAGIC_NUMBER 0xAA55    // Numéro magique pour valider l'EEPROM
#define EEPROM_VERSION 1              // Version des données EEPROM

// ============================================================================
// ADRESSES EEPROM ORGANISÉES PAR TYPE DE VARIABLE
// ============================================================================

// --- VALIDATION (2 bytes) ---
#define EEPROM_MAGIC_NUMBER_ADDR 0    // 2 bytes - Numéro magique
#define EEPROM_VERSION_ADDR 2         // 1 byte  - Version des données

// --- CALIBRATION PPS (8 bytes) ---
#define EEPROM_PPS1_MIN_ADDR 3        // 2 bytes - PPS1_Calib_Mini
#define EEPROM_PPS1_MAX_ADDR 5        // 2 bytes - PPS1_Calib_Maxi
#define EEPROM_PPS2_MIN_ADDR 7        // 2 bytes - PPS2_Calib_Mini
#define EEPROM_PPS2_MAX_ADDR 9        // 2 bytes - PPS2_Calib_Maxi

// --- CALIBRATION TPS (12 bytes) ---
#define EEPROM_TPS1_MIN_ADDR 11       // 2 bytes - TPS1_Calib_Mini
#define EEPROM_TPS1_NEUTRAL_ADDR 13   // 2 bytes - TPS1_Calib_Neutral
#define EEPROM_TPS1_MAX_ADDR 15       // 2 bytes - TPS1_Calib_Maxi
#define EEPROM_TPS2_MIN_ADDR 17       // 2 bytes - TPS2_Calib_Mini
#define EEPROM_TPS2_NEUTRAL_ADDR 19   // 2 bytes - TPS2_Calib_Neutral
#define EEPROM_TPS2_MAX_ADDR 21       // 2 bytes - TPS2_Calib_Maxi

// --- PARAMÈTRES PWM (6 bytes) ---
#define EEPROM_PWM_MINI_ADDR 23       // 2 bytes - PwmMini
#define EEPROM_PWM_MAXI_ADDR 25       // 2 bytes - PwmMaxi
#define EEPROM_PWM_DUTY_MINI_ADDR 27  // 1 byte  - PwmDutyMini
#define EEPROM_PWM_DUTY_MAXI_ADDR 28  // 1 byte  - PwmDutyMaxi

// --- FRÉQUENCE TPS (2 bytes) ---
#define EEPROM_TPS_FREQ_ADDR 29       // 2 bytes - TPSFreq

// --- PARAMÈTRES PID NORMALS (12 bytes) ---
#define EEPROM_PID_KP_ADDR 31         // 4 bytes - kP (double)
#define EEPROM_PID_KI_ADDR 35         // 4 bytes - kI (double)
#define EEPROM_PID_KD_ADDR 39         // 4 bytes - kD (double)

// --- PARAMÈTRES PID AGRESSIFS (12 bytes) ---
#define EEPROM_PID_KP_AGR_ADDR 43     // 4 bytes - kP_Agressif (double)
#define EEPROM_PID_KI_AGR_ADDR 47     // 4 bytes - kI_Agressif (double)
#define EEPROM_PID_KD_AGR_ADDR 51     // 4 bytes - kD_Agressif (double)

// --- PARAMÈTRES DSG (5 bytes) ---
#define EEPROM_DSG_MODE_ADDR 55       // 1 byte  - DSG_Mode
#define EEPROM_DSG_DURATION_ADDR 56   // 4 bytes - DSG_Duration (unsigned long)

// --- POLARITÉS (5 bytes) ---
#define EEPROM_PPS1_LOHI_ADDR 60      // 1 byte  - PPS1_LoHi (bool)
#define EEPROM_PPS2_LOHI_ADDR 61      // 1 byte  - PPS2_loHi (bool)
#define EEPROM_TPS1_LOHI_ADDR 62      // 1 byte  - TPS1_LoHi (bool)
#define EEPROM_TPS2_LOHI_ADDR 63      // 1 byte  - TPS2_LoHi (bool)
#define EEPROM_MOTOR_LOHI_ADDR 64     // 1 byte  - motor_LoHi (bool)

// --- MODE MOTEUR TPS (1 byte) ---
#define EEPROM_TPS_MOTOR_MODE_ADDR 65 // 1 byte  - TPSMotorMode

// --- RÉGULATEUR DE VITESSE (4 bytes) ---
#define EEPROM_CRUISE_TARGET_ADDR 66  // 2 bytes - Cruise_TargetKmH
#define EEPROM_CRUISE_BUTTON_ADDR 68  // 1 byte  - CruiseButton_ActiveCruise
#define EEPROM_CRUISE_UP_ADDR 69      // 1 byte  - Cruise_Up

// --- MODE DÉGRADÉ (1 byte) ---
#define EEPROM_MODE_DEGRADE_ADDR 70   // 1 byte  - ModeDegradeEtat

// ============================================================================
// FONCTIONS DE GESTION EEPROM
// ============================================================================

// Fonctions principales
void SaveEEPROM();
void LoadEEPROM();
bool IsEEPROMValid();
void ResetEEPROM();
void DisplayEEPROMStatus();

// Fonctions de sauvegarde par section
void SaveEEPROM_PPS();
void SaveEEPROM_TPS();
void SaveEEPROM_PWM();
void SaveEEPROM_Frequency();
void SaveEEPROM_PID_Normal();
void SaveEEPROM_PID_Agressif();
void SaveEEPROM_DSG();
void SaveEEPROM_Polarities();
void SaveEEPROM_MotorMode();
void SaveEEPROM_Cruise();
void SaveEEPROM_DegradeMode();

// Fonctions de chargement par section
void LoadEEPROM_PPS();
void LoadEEPROM_TPS();
void LoadEEPROM_PWM();
void LoadEEPROM_Frequency();
void LoadEEPROM_PID_Normal();
void LoadEEPROM_PID_Agressif();
void LoadEEPROM_DSG();
void LoadEEPROM_Polarities();
void LoadEEPROM_MotorMode();
void LoadEEPROM_Cruise();
void LoadEEPROM_DegradeMode();

// Fonctions utilitaires
void SaveEEPROM_Section(uint16_t startAddr, const void* data, size_t size);
void LoadEEPROM_Section(uint16_t startAddr, void* data, size_t size);
void PrintEEPROM_Section(const char* sectionName, uint16_t startAddr, size_t size);

// ============================================================================
// CALCUL DE LA TAILLE TOTALE UTILISÉE
// ============================================================================
// Validation: 3 bytes
// PPS: 8 bytes
// TPS: 12 bytes
// PWM: 6 bytes
// Fréquence: 2 bytes
// PID Normal: 12 bytes
// PID Agressif: 12 bytes
// DSG: 5 bytes
// Polarités: 5 bytes
// Mode moteur: 1 byte
// Cruise: 4 bytes
// Mode dégradé: 1 byte
// TOTAL: 71 bytes sur ~4096 bytes disponibles (Arduino Mega)

#endif 
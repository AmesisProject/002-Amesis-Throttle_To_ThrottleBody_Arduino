#include "EEPROM_Manager.h"
#include "Menu.h"

// ============================================================================
// FONCTIONS PRINCIPALES
// ============================================================================

void SaveEEPROM() {
  // Écrire le numéro magique et la version
  EEPROM.put(EEPROM_MAGIC_NUMBER_ADDR, EEPROM_MAGIC_NUMBER);
  EEPROM.put(EEPROM_VERSION_ADDR, EEPROM_VERSION);
  
  // Sauvegarder toutes les sections
  SaveEEPROM_PPS();
  SaveEEPROM_TPS();
  SaveEEPROM_PWM();
  SaveEEPROM_Frequency();
  SaveEEPROM_PID_Normal();
  SaveEEPROM_PID_Agressif();
  SaveEEPROM_DSG();
  SaveEEPROM_Polarities();
  SaveEEPROM_MotorMode();
  SaveEEPROM_Cruise();
  SaveEEPROM_DegradeMode();
  
  Serial.println("Toutes les donnees sauvegardees en EEPROM");
}

void LoadEEPROM() {
  // Vérifier si l'EEPROM contient des données valides
  if (!IsEEPROMValid()) {
    Serial.println("EEPROM invalide ou vide - Utilisation des valeurs par defaut");
    return;
  }
  
  // Charger toutes les sections
  LoadEEPROM_PPS();
  LoadEEPROM_TPS();
  LoadEEPROM_PWM();
  LoadEEPROM_Frequency();
  LoadEEPROM_PID_Normal();
  LoadEEPROM_PID_Agressif();
  LoadEEPROM_DSG();
  LoadEEPROM_Polarities();
  LoadEEPROM_MotorMode();
  LoadEEPROM_Cruise();
  LoadEEPROM_DegradeMode();
  
  // Mettre à jour l'objet PID avec les nouvelles valeurs
  throttlePID.SetTunings(kP, kI, kD);
  
  Serial.println("Toutes les donnees chargees depuis EEPROM");
}

bool IsEEPROMValid() {
  uint16_t magicNumber;
  uint8_t version;
  
  EEPROM.get(EEPROM_MAGIC_NUMBER_ADDR, magicNumber);
  EEPROM.get(EEPROM_VERSION_ADDR, version);
  
  return (magicNumber == EEPROM_MAGIC_NUMBER && version == EEPROM_VERSION);
}

void ResetEEPROM() {
  // Effacer toutes les données EEPROM utilisées
  for (int i = 0; i < 100; i++) {
    EEPROM.write(i, 0xFF);
  }
  Serial.println("EEPROM reinitialisee - Utilisation des valeurs par defaut");
}

// Fonction utilitaire pour aligner à droite (compatible Arduino)
String padRight(String s, int n) {
  while (s.length() < n) s += " ";
  return s;
}

void DisplayEEPROMStatus() {
  Serial.println("=== Status EEPROM ===");
  Serial.print("EEPROM valide: ");
  Serial.println(IsEEPROMValid() ? "OUI" : "NON");

  if (IsEEPROMValid()) {
    Serial.println("Nom                | Valeur        | Adresse | Taille");
    Serial.println("------------------------------------------------------");
    Serial.println("--- PPS ---");
    Serial.print(padRight("PPS1_Calib_Mini", 19)); Serial.print("| "); Serial.print(padRight(String(PPS1_Calib_Mini), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PPS1_MIN_ADDR), 7)); Serial.print("| 2\n");
    Serial.print(padRight("PPS1_Calib_Maxi", 19)); Serial.print("| "); Serial.print(padRight(String(PPS1_Calib_Maxi), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PPS1_MAX_ADDR), 7)); Serial.print("| 2\n");
    Serial.print(padRight("PPS2_Calib_Mini", 19)); Serial.print("| "); Serial.print(padRight(String(PPS2_Calib_Mini), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PPS2_MIN_ADDR), 7)); Serial.print("| 2\n");
    Serial.print(padRight("PPS2_Calib_Maxi", 19)); Serial.print("| "); Serial.print(padRight(String(PPS2_Calib_Maxi), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PPS2_MAX_ADDR), 7)); Serial.print("| 2\n");

    Serial.println("--- TPS ---");
    Serial.print(padRight("TPS1_Calib_Mini", 19)); Serial.print("| "); Serial.print(padRight(String(TPS1_Calib_Mini), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_TPS1_MIN_ADDR), 7)); Serial.print("| 2\n");
    Serial.print(padRight("TPS1_Calib_Neutral", 19)); Serial.print("| "); Serial.print(padRight(String(TPS1_Calib_Neutral), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_TPS1_NEUTRAL_ADDR), 7)); Serial.print("| 2\n");
    Serial.print(padRight("TPS1_Calib_Maxi", 19)); Serial.print("| "); Serial.print(padRight(String(TPS1_Calib_Maxi), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_TPS1_MAX_ADDR), 7)); Serial.print("| 2\n");
    Serial.print(padRight("TPS2_Calib_Mini", 19)); Serial.print("| "); Serial.print(padRight(String(TPS2_Calib_Mini), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_TPS2_MIN_ADDR), 7)); Serial.print("| 2\n");
    Serial.print(padRight("TPS2_Calib_Neutral", 19)); Serial.print("| "); Serial.print(padRight(String(TPS2_Calib_Neutral), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_TPS2_NEUTRAL_ADDR), 7)); Serial.print("| 2\n");
    Serial.print(padRight("TPS2_Calib_Maxi", 19)); Serial.print("| "); Serial.print(padRight(String(TPS2_Calib_Maxi), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_TPS2_MAX_ADDR), 7)); Serial.print("| 2\n");

    Serial.println("--- PWM ---");
    Serial.print(padRight("PwmMini", 19)); Serial.print("| "); Serial.print(padRight(String(PwmMini), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PWM_MINI_ADDR), 7)); Serial.print("| 2\n");
    Serial.print(padRight("PwmMaxi", 19)); Serial.print("| "); Serial.print(padRight(String(PwmMaxi), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PWM_MAXI_ADDR), 7)); Serial.print("| 2\n");
    Serial.print(padRight("PwmDutyMini", 19)); Serial.print("| "); Serial.print(padRight(String(PwmDutyMini), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PWM_DUTY_MINI_ADDR), 7)); Serial.print("| 1\n");
    Serial.print(padRight("PwmDutyMaxi", 19)); Serial.print("| "); Serial.print(padRight(String(PwmDutyMaxi), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PWM_DUTY_MAXI_ADDR), 7)); Serial.print("| 1\n");

    Serial.println("--- FREQ ---");
    Serial.print(padRight("TPSFreq", 19)); Serial.print("| "); Serial.print(padRight(String(TPSFreq), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_TPS_FREQ_ADDR), 7)); Serial.print("| 2\n");

    Serial.println("--- PID Normal ---");
    Serial.print(padRight("kP", 19)); Serial.print("| "); Serial.print(padRight(String(kP), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PID_KP_ADDR), 7)); Serial.print("| 4\n");
    Serial.print(padRight("kI", 19)); Serial.print("| "); Serial.print(padRight(String(kI), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PID_KI_ADDR), 7)); Serial.print("| 4\n");
    Serial.print(padRight("kD", 19)); Serial.print("| "); Serial.print(padRight(String(kD), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PID_KD_ADDR), 7)); Serial.print("| 4\n");

    Serial.println("--- PID Agressif ---");
    Serial.print(padRight("kP_Agressif", 19)); Serial.print("| "); Serial.print(padRight(String(kP_Agressif), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PID_KP_AGR_ADDR), 7)); Serial.print("| 4\n");
    Serial.print(padRight("kI_Agressif", 19)); Serial.print("| "); Serial.print(padRight(String(kI_Agressif), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PID_KI_AGR_ADDR), 7)); Serial.print("| 4\n");
    Serial.print(padRight("kD_Agressif", 19)); Serial.print("| "); Serial.print(padRight(String(kD_Agressif), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PID_KD_AGR_ADDR), 7)); Serial.print("| 4\n");

    Serial.println("--- DSG ---");
    Serial.print(padRight("DSG_Mode", 19)); Serial.print("| "); Serial.print(padRight(String(DSG_Mode), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_DSG_MODE_ADDR), 7)); Serial.print("| 1\n");
    Serial.print(padRight("DSG_Duration", 19)); Serial.print("| "); Serial.print(padRight(String(DSG_Duration), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_DSG_DURATION_ADDR), 7)); Serial.print("| 4\n");

    Serial.println("--- Polarites ---");
    Serial.print(padRight("PPS1_LoHi", 19)); Serial.print("| "); Serial.print(padRight(String(PPS1_LoHi), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PPS1_LOHI_ADDR), 7)); Serial.print("| 1\n");
    Serial.print(padRight("PPS2_loHi", 19)); Serial.print("| "); Serial.print(padRight(String(PPS2_loHi), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_PPS2_LOHI_ADDR), 7)); Serial.print("| 1\n");
    Serial.print(padRight("TPS1_LoHi", 19)); Serial.print("| "); Serial.print(padRight(String(TPS1_LoHi), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_TPS1_LOHI_ADDR), 7)); Serial.print("| 1\n");
    Serial.print(padRight("TPS2_LoHi", 19)); Serial.print("| "); Serial.print(padRight(String(TPS2_LoHi), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_TPS2_LOHI_ADDR), 7)); Serial.print("| 1\n");
    Serial.print(padRight("motor_LoHi", 19)); Serial.print("| "); Serial.print(padRight(String(motor_LoHi), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_MOTOR_LOHI_ADDR), 7)); Serial.print("| 1\n");

    Serial.println("--- Autres ---");
    Serial.print(padRight("TPSMotorMode", 19)); Serial.print("| "); Serial.print(padRight(String(TPSMotorMode), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_TPS_MOTOR_MODE_ADDR), 7)); Serial.print("| 1\n");
    Serial.print(padRight("Cruise_TargetKmH", 19)); Serial.print("| "); Serial.print(padRight(String(Cruise_TargetKmH), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_CRUISE_TARGET_ADDR), 7)); Serial.print("| 2\n");
    Serial.print(padRight("ModeDegradeEtat", 19)); Serial.print("| "); Serial.print(padRight(String(ModeDegradeEtat), 13)); Serial.print("| "); Serial.print(padRight(String(EEPROM_MODE_DEGRADE_ADDR), 7)); Serial.print("| 1\n");
  } else {
    Serial.println("Utilisation des valeurs par defaut");
  }
  Serial.println("===================");
}

// ============================================================================
// FONCTIONS DE SAUVEGARDE PAR SECTION
// ============================================================================

void SaveEEPROM_PPS() {
  EEPROM.put(EEPROM_MAGIC_NUMBER_ADDR, EEPROM_MAGIC_NUMBER);
  EEPROM.put(EEPROM_VERSION_ADDR, EEPROM_VERSION);
  EEPROM.put(EEPROM_PPS1_MIN_ADDR, PPS1_Calib_Mini);
  EEPROM.put(EEPROM_PPS1_MAX_ADDR, PPS1_Calib_Maxi);
  EEPROM.put(EEPROM_PPS2_MIN_ADDR, PPS2_Calib_Mini);
  EEPROM.put(EEPROM_PPS2_MAX_ADDR, PPS2_Calib_Maxi);
  Serial.println("Calibration PPS sauvegardee");
}

void SaveEEPROM_TPS() {
  EEPROM.put(EEPROM_MAGIC_NUMBER_ADDR, EEPROM_MAGIC_NUMBER);
  EEPROM.put(EEPROM_VERSION_ADDR, EEPROM_VERSION);
  EEPROM.put(EEPROM_TPS1_MIN_ADDR, TPS1_Calib_Mini);
  EEPROM.put(EEPROM_TPS1_NEUTRAL_ADDR, TPS1_Calib_Neutral);
  EEPROM.put(EEPROM_TPS1_MAX_ADDR, TPS1_Calib_Maxi);
  EEPROM.put(EEPROM_TPS2_MIN_ADDR, TPS2_Calib_Mini);
  EEPROM.put(EEPROM_TPS2_NEUTRAL_ADDR, TPS2_Calib_Neutral);
  EEPROM.put(EEPROM_TPS2_MAX_ADDR, TPS2_Calib_Maxi);
  Serial.println("Calibration TPS sauvegardee");
}

void SaveEEPROM_PWM() {
  EEPROM.put(EEPROM_MAGIC_NUMBER_ADDR, EEPROM_MAGIC_NUMBER);
  EEPROM.put(EEPROM_VERSION_ADDR, EEPROM_VERSION);
  EEPROM.put(EEPROM_PWM_MINI_ADDR, PwmMini);
  EEPROM.put(EEPROM_PWM_MAXI_ADDR, PwmMaxi);
  EEPROM.put(EEPROM_PWM_DUTY_MINI_ADDR, PwmDutyMini);
  EEPROM.put(EEPROM_PWM_DUTY_MAXI_ADDR, PwmDutyMaxi);
  Serial.println("Parametres PWM sauvegardes");
}

void SaveEEPROM_Frequency() {
  EEPROM.put(EEPROM_MAGIC_NUMBER_ADDR, EEPROM_MAGIC_NUMBER);
  EEPROM.put(EEPROM_VERSION_ADDR, EEPROM_VERSION);
  EEPROM.put(EEPROM_TPS_FREQ_ADDR, TPSFreq);
  Serial.println("Frequence TPS sauvegardee");
}

void SaveEEPROM_PID_Normal() {
  EEPROM.put(EEPROM_MAGIC_NUMBER_ADDR, EEPROM_MAGIC_NUMBER);
  EEPROM.put(EEPROM_VERSION_ADDR, EEPROM_VERSION);
  EEPROM.put(EEPROM_PID_KP_ADDR, kP);
  EEPROM.put(EEPROM_PID_KI_ADDR, kI);
  EEPROM.put(EEPROM_PID_KD_ADDR, kD);
  Serial.println("Parametres PID Normal sauvegardes");
}

void SaveEEPROM_PID_Agressif() {
  EEPROM.put(EEPROM_MAGIC_NUMBER_ADDR, EEPROM_MAGIC_NUMBER);
  EEPROM.put(EEPROM_VERSION_ADDR, EEPROM_VERSION);
  EEPROM.put(EEPROM_PID_KP_AGR_ADDR, kP_Agressif);
  EEPROM.put(EEPROM_PID_KI_AGR_ADDR, kI_Agressif);
  EEPROM.put(EEPROM_PID_KD_AGR_ADDR, kD_Agressif);
  Serial.println("Parametres PID Agressif sauvegardes");
}

void SaveEEPROM_DSG() {
  EEPROM.put(EEPROM_MAGIC_NUMBER_ADDR, EEPROM_MAGIC_NUMBER);
  EEPROM.put(EEPROM_VERSION_ADDR, EEPROM_VERSION);
  EEPROM.put(EEPROM_DSG_MODE_ADDR, DSG_Mode);
  EEPROM.put(EEPROM_DSG_DURATION_ADDR, DSG_Duration);
  Serial.println("Parametres DSG sauvegardes");
}

void SaveEEPROM_Polarities() {
  EEPROM.put(EEPROM_MAGIC_NUMBER_ADDR, EEPROM_MAGIC_NUMBER);
  EEPROM.put(EEPROM_VERSION_ADDR, EEPROM_VERSION);
  EEPROM.put(EEPROM_PPS1_LOHI_ADDR, PPS1_LoHi);
  EEPROM.put(EEPROM_PPS2_LOHI_ADDR, PPS2_loHi);
  EEPROM.put(EEPROM_TPS1_LOHI_ADDR, TPS1_LoHi);
  EEPROM.put(EEPROM_TPS2_LOHI_ADDR, TPS2_LoHi);
  EEPROM.put(EEPROM_MOTOR_LOHI_ADDR, motor_LoHi);
  Serial.println("Polarites sauvegardees");
}

void SaveEEPROM_MotorMode() {
  EEPROM.put(EEPROM_MAGIC_NUMBER_ADDR, EEPROM_MAGIC_NUMBER);
  EEPROM.put(EEPROM_VERSION_ADDR, EEPROM_VERSION);
  EEPROM.put(EEPROM_TPS_MOTOR_MODE_ADDR, TPSMotorMode);
  Serial.println("Mode moteur TPS sauvegarde");
}

void SaveEEPROM_Cruise() {
  EEPROM.put(EEPROM_MAGIC_NUMBER_ADDR, EEPROM_MAGIC_NUMBER);
  EEPROM.put(EEPROM_VERSION_ADDR, EEPROM_VERSION);
  EEPROM.put(EEPROM_CRUISE_TARGET_ADDR, Cruise_TargetKmH);
  EEPROM.put(EEPROM_CRUISE_BUTTON_ADDR, CruiseButton_ActiveCruise);
  EEPROM.put(EEPROM_CRUISE_UP_ADDR, Cruise_Up);
  Serial.println("Parametres Cruise sauvegardes");
}

void SaveEEPROM_DegradeMode() {
  EEPROM.put(EEPROM_MAGIC_NUMBER_ADDR, EEPROM_MAGIC_NUMBER);
  EEPROM.put(EEPROM_VERSION_ADDR, EEPROM_VERSION);
  EEPROM.put(EEPROM_MODE_DEGRADE_ADDR, ModeDegradeEtat);
  Serial.println("Mode degrade sauvegarde");
}

// ============================================================================
// FONCTIONS DE CHARGEMENT PAR SECTION
// ============================================================================

void LoadEEPROM_PPS() {
  EEPROM.get(EEPROM_PPS1_MIN_ADDR, PPS1_Calib_Mini);
  EEPROM.get(EEPROM_PPS1_MAX_ADDR, PPS1_Calib_Maxi);
  EEPROM.get(EEPROM_PPS2_MIN_ADDR, PPS2_Calib_Mini);
  EEPROM.get(EEPROM_PPS2_MAX_ADDR, PPS2_Calib_Maxi);
}

void LoadEEPROM_TPS() {
  EEPROM.get(EEPROM_TPS1_MIN_ADDR, TPS1_Calib_Mini);
  EEPROM.get(EEPROM_TPS1_NEUTRAL_ADDR, TPS1_Calib_Neutral);
  EEPROM.get(EEPROM_TPS1_MAX_ADDR, TPS1_Calib_Maxi);
  EEPROM.get(EEPROM_TPS2_MIN_ADDR, TPS2_Calib_Mini);
  EEPROM.get(EEPROM_TPS2_NEUTRAL_ADDR, TPS2_Calib_Neutral);
  EEPROM.get(EEPROM_TPS2_MAX_ADDR, TPS2_Calib_Maxi);
}

void LoadEEPROM_PWM() {
  EEPROM.get(EEPROM_PWM_MINI_ADDR, PwmMini);
  EEPROM.get(EEPROM_PWM_MAXI_ADDR, PwmMaxi);
  EEPROM.get(EEPROM_PWM_DUTY_MINI_ADDR, PwmDutyMini);
  EEPROM.get(EEPROM_PWM_DUTY_MAXI_ADDR, PwmDutyMaxi);
}

void LoadEEPROM_Frequency() {
  EEPROM.get(EEPROM_TPS_FREQ_ADDR, TPSFreq);
}

void LoadEEPROM_PID_Normal() {
  EEPROM.get(EEPROM_PID_KP_ADDR, kP);
  EEPROM.get(EEPROM_PID_KI_ADDR, kI);
  EEPROM.get(EEPROM_PID_KD_ADDR, kD);
}

void LoadEEPROM_PID_Agressif() {
  EEPROM.get(EEPROM_PID_KP_AGR_ADDR, kP_Agressif);
  EEPROM.get(EEPROM_PID_KI_AGR_ADDR, kI_Agressif);
  EEPROM.get(EEPROM_PID_KD_AGR_ADDR, kD_Agressif);
}

void LoadEEPROM_DSG() {
  EEPROM.get(EEPROM_DSG_MODE_ADDR, DSG_Mode);
  EEPROM.get(EEPROM_DSG_DURATION_ADDR, DSG_Duration);
}

void LoadEEPROM_Polarities() {
  EEPROM.get(EEPROM_PPS1_LOHI_ADDR, PPS1_LoHi);
  EEPROM.get(EEPROM_PPS2_LOHI_ADDR, PPS2_loHi);
  EEPROM.get(EEPROM_TPS1_LOHI_ADDR, TPS1_LoHi);
  EEPROM.get(EEPROM_TPS2_LOHI_ADDR, TPS2_LoHi);
  EEPROM.get(EEPROM_MOTOR_LOHI_ADDR, motor_LoHi);
}

void LoadEEPROM_MotorMode() {
  EEPROM.get(EEPROM_TPS_MOTOR_MODE_ADDR, TPSMotorMode);
}

void LoadEEPROM_Cruise() {
  EEPROM.get(EEPROM_CRUISE_TARGET_ADDR, Cruise_TargetKmH);
  EEPROM.get(EEPROM_CRUISE_BUTTON_ADDR, CruiseButton_ActiveCruise);
  EEPROM.get(EEPROM_CRUISE_UP_ADDR, Cruise_Up);
}

void LoadEEPROM_DegradeMode() {
  EEPROM.get(EEPROM_MODE_DEGRADE_ADDR, ModeDegradeEtat);
}

// ============================================================================
// FONCTIONS UTILITAIRES
// ============================================================================

void SaveEEPROM_Section(uint16_t startAddr, const void* data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    EEPROM.write(startAddr + i, ((uint8_t*)data)[i]);
  }
}

void LoadEEPROM_Section(uint16_t startAddr, void* data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    ((uint8_t*)data)[i] = EEPROM.read(startAddr + i);
  }
}

void PrintEEPROM_Section(const char* sectionName, uint16_t startAddr, size_t size) {
  Serial.print(sectionName);
  Serial.print(" (");
  Serial.print(startAddr);
  Serial.print("-");
  Serial.print(startAddr + size - 1);
  Serial.print("): ");
  for (size_t i = 0; i < size; i++) {
    Serial.print(EEPROM.read(startAddr + i), HEX);
    Serial.print(" ");
  }
  Serial.println();
} 
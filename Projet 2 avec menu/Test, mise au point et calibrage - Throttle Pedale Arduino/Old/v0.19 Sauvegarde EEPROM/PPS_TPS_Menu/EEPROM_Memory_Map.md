# Organisation de la Mémoire EEPROM - Throttle Body Arduino

## Vue d'ensemble

L'EEPROM est organisée de manière optimale pour économiser l'espace mémoire tout en permettant un accès rapide aux données. L'Arduino Mega dispose de 4096 bytes d'EEPROM, nous utilisons seulement 71 bytes.

## Carte Mémoire Détaillée

### Adresses 0-2: Validation (3 bytes)
```
0-1: EEPROM_MAGIC_NUMBER_ADDR    - Numéro magique (0xAA55)
2:   EEPROM_VERSION_ADDR         - Version des données (1)
```

### Adresses 3-10: Calibration PPS (8 bytes)
```
3-4: EEPROM_PPS1_MIN_ADDR       - PPS1_Calib_Mini (int16)
5-6: EEPROM_PPS1_MAX_ADDR       - PPS1_Calib_Maxi (int16)
7-8: EEPROM_PPS2_MIN_ADDR       - PPS2_Calib_Mini (int16)
9-10: EEPROM_PPS2_MAX_ADDR      - PPS2_Calib_Maxi (int16)
```

### Adresses 11-22: Calibration TPS (12 bytes)
```
11-12: EEPROM_TPS1_MIN_ADDR     - TPS1_Calib_Mini (int16)
13-14: EEPROM_TPS1_NEUTRAL_ADDR - TPS1_Calib_Neutral (int16)
15-16: EEPROM_TPS1_MAX_ADDR     - TPS1_Calib_Maxi (int16)
17-18: EEPROM_TPS2_MIN_ADDR     - TPS2_Calib_Mini (int16)
19-20: EEPROM_TPS2_NEUTRAL_ADDR - TPS2_Calib_Neutral (int16)
21-22: EEPROM_TPS2_MAX_ADDR     - TPS2_Calib_Maxi (int16)
```

### Adresses 23-28: Paramètres PWM (6 bytes)
```
23-24: EEPROM_PWM_MINI_ADDR     - PwmMini (int16)
25-26: EEPROM_PWM_MAXI_ADDR     - PwmMaxi (int16)
27:   EEPROM_PWM_DUTY_MINI_ADDR - PwmDutyMini (uint8)
28:   EEPROM_PWM_DUTY_MAXI_ADDR - PwmDutyMaxi (uint8)
```

### Adresses 29-30: Fréquence TPS (2 bytes)
```
29-30: EEPROM_TPS_FREQ_ADDR     - TPSFreq (int16)
```

### Adresses 31-42: Paramètres PID Normal (12 bytes)
```
31-34: EEPROM_PID_KP_ADDR       - kP (double)
35-38: EEPROM_PID_KI_ADDR       - kI (double)
39-42: EEPROM_PID_KD_ADDR       - kD (double)
```

### Adresses 43-54: Paramètres PID Agressif (12 bytes)
```
43-46: EEPROM_PID_KP_AGR_ADDR   - kP_Agressif (double)
47-50: EEPROM_PID_KI_AGR_ADDR   - kI_Agressif (double)
51-54: EEPROM_PID_KD_AGR_ADDR   - kD_Agressif (double)
```

### Adresses 55-59: Paramètres DSG (5 bytes)
```
55:   EEPROM_DSG_MODE_ADDR      - DSG_Mode (uint8)
56-59: EEPROM_DSG_DURATION_ADDR - DSG_Duration (uint32)
```

### Adresses 60-64: Polarités (5 bytes)
```
60: EEPROM_PPS1_LOHI_ADDR       - PPS1_LoHi (bool)
61: EEPROM_PPS2_LOHI_ADDR       - PPS2_loHi (bool)
62: EEPROM_TPS1_LOHI_ADDR       - TPS1_LoHi (bool)
63: EEPROM_TPS2_LOHI_ADDR       - TPS2_LoHi (bool)
64: EEPROM_MOTOR_LOHI_ADDR      - motor_LoHi (bool)
```

### Adresses 65-69: Autres paramètres (5 bytes)
```
65: EEPROM_TPS_MOTOR_MODE_ADDR  - TPSMotorMode (uint8)
66-67: EEPROM_CRUISE_TARGET_ADDR - Cruise_TargetKmH (int16)
68: EEPROM_CRUISE_BUTTON_ADDR   - CruiseButton_ActiveCruise (uint8)
69: EEPROM_CRUISE_UP_ADDR       - Cruise_Up (uint8)
70: EEPROM_MODE_DEGRADE_ADDR    - ModeDegradeEtat (uint8)
```

## Optimisations Mémoire

### 1. Alignement des Types
- Les `int16` sont alignés sur 2 bytes
- Les `double` sont alignés sur 4 bytes
- Les `bool` et `uint8` utilisent 1 byte chacun

### 2. Groupement Logique
- Variables liées sont groupées ensemble
- Validation en début de mémoire
- Calibrations en premier (PPS, TPS)
- Paramètres de contrôle ensuite (PWM, PID, DSG)
- Paramètres système en fin

### 3. Extensibilité
- Espace libre après l'adresse 70
- Version des données pour compatibilité future
- Numéro magique pour validation

## Utilisation

### Sauvegarde par Section
```cpp
SaveEEPROM_PPS();        // Sauvegarde calibration PPS
SaveEEPROM_TPS();        // Sauvegarde calibration TPS
SaveEEPROM_PWM();        // Sauvegarde paramètres PWM
SaveEEPROM_PID_Normal(); // Sauvegarde PID normal
// etc...
```

### Chargement au Démarrage
```cpp
LoadEEPROM();  // Charge toutes les données automatiquement
```

### Validation
```cpp
if (IsEEPROMValid()) {
    // Données valides, charger
} else {
    // Utiliser valeurs par défaut
}
```

## Commandes Menu

Chaque section du menu dispose d'une option "Save" :

- **Menu 1.1.3** : Save PPS en EEPROM
- **Menu 1.2.3** : Save TPS en EEPROM
- **Menu 1.3** : Save PWM (commande "save")
- **Menu 1.4** : Save Fréquence (commande "save")
- **Menu 1.5.1** : Save PID Normal (commande "save")
- **Menu 1.5.2** : Save PID Agressif (commande "save")
- **Menu 1.6.3** : Save DSG (commande "save")

## Commandes Rapides

Commandes à taper directement dans le moniteur série :

```
save_pps     - Sauvegarde calibration PPS
save_tps     - Sauvegarde calibration TPS
save_pwm     - Sauvegarde paramètres PWM
save_freq    - Sauvegarde fréquence TPS
save_pid_n   - Sauvegarde PID Normal
save_pid_a   - Sauvegarde PID Agressif
save_dsg     - Sauvegarde paramètres DSG
save_all     - Sauvegarde tout
load_all     - Recharge tout
reset_eeprom - Réinitialise EEPROM
eeprom_status - Affiche statut EEPROM
```

## Avantages de cette Organisation

1. **Économie mémoire** : Seulement 71 bytes utilisés sur 4096
2. **Accès rapide** : Adresses calculées à la compilation
3. **Modularité** : Sauvegarde/chargement par section
4. **Extensibilité** : Facile d'ajouter de nouvelles variables
5. **Validation** : Numéro magique et version pour sécurité
6. **Compatibilité** : Version des données pour évolutions futures 
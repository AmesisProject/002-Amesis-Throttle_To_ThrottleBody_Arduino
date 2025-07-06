# Guide d'Intégration des Commandes Save dans le Menu

## Vue d'ensemble

Maintenant que les calibrations ne sauvegardent plus automatiquement en EEPROM, vous devez ajouter les commandes "Save" dans chaque section du menu pour permettre à l'utilisateur de sauvegarder manuellement ses paramètres.

## 1. Menu PPS (1.1.3) - Save PPS

### Dans Menu.cpp, ajouter dans la fonction gererMenu() :

```cpp
else if (menu == MENU_PPS_SaveEEPROM) {
  SaveEEPROM_PPS();  // Sauvegarde uniquement les valeurs PPS
  Serial.println("Calibration PPS sauvegardee en EEPROM");
  Serial.println("Menu 1.1.3 - Save PPS en EEPROM");
  Serial.println("11 - Retour");
}
```

### Dans afficherSousMenu() pour le menu PEDALE :

```cpp
else if (menu == MENU_PEDALE) {
  Serial.println("=== Menu Pedale ===");
  Serial.println("1.1.1 - Log PPS");
  Serial.println("1.1.2 - Calibration PPS");
  Serial.println("1.1.3 - Save PPS en EEPROM");  // ← Option Save
  Serial.println("11 - Retour");
}
```

## 2. Menu TPS (1.2.3) - Save TPS

### Dans Menu.cpp, ajouter dans la fonction gererMenu() :

```cpp
else if (menu == MENU_TPS_SaveEEPROM) {
  SaveEEPROM_TPS();  // Sauvegarde uniquement les valeurs TPS
  Serial.println("Calibration TPS sauvegardee en EEPROM");
  Serial.println("Menu 1.2.3 - Save TPS en EEPROM");
  Serial.println("11 - Retour");
}
```

### Dans afficherSousMenu() pour le menu PAPILLON :

```cpp
else if (menu == MENU_PAPILLON) {
  Serial.println("=== Menu Papillon ===");
  Serial.println("1.2.1 - Log TPS");
  Serial.println("1.2.2 - Calibration TPS");
  Serial.println("1.2.3 - Save TPS en EEPROM");  // ← Option Save
  Serial.println("11 - Retour");
}
```

## 3. Menu PWM (1.3) - Save PWM

### Modifier handlePWMMenu() dans Menu.cpp :

```cpp
void handlePWMMenu(String option) {
  if (option == "save") {
    SaveEEPROM_PWM();
    Serial.println("Parametres PWM sauvegardes en EEPROM");
    Serial.println("Menu 1.3 - Reglage PWM");
    Serial.println("Entrez une nouvelle valeur ou commande:");
    Serial.println("save - Sauvegarder PWM en EEPROM");
    Serial.println("11 - Retour");
  }
  else if (option == "11") {
    niveauMenu = MENU_PRINCIPAL;
    afficherMenuPrincipal();
  }
  // ... autres options PWM existantes
}
```

## 4. Menu Fréquence (1.4) - Save Fréquence

### Modifier handleFrequencyMenu() dans Menu.cpp :

```cpp
void handleFrequencyMenu(String option) {
  if (option == "save") {
    SaveEEPROM_Frequency();
    Serial.println("Frequence TPS sauvegardee en EEPROM");
    Serial.println("Menu 1.4 - Reglage Frequence");
    Serial.println("Entrez une nouvelle valeur ou commande:");
    Serial.println("save - Sauvegarder Frequence en EEPROM");
    Serial.println("11 - Retour");
  }
  else if (option == "11") {
    niveauMenu = MENU_PRINCIPAL;
    afficherMenuPrincipal();
  }
  // ... autres options fréquence existantes
}
```

## 5. Menu PID Normal (1.5.1) - Save PID Normal

### Modifier handleNormalPIDMenu() dans Menu.cpp :

```cpp
void handleNormalPIDMenu(String option) {
  if (option == "save") {
    SaveEEPROM_PID_Normal();
    throttlePID.SetTunings(kP, kI, kD);  // Mettre à jour l'objet PID
    Serial.println("Parametres PID Normal sauvegardes en EEPROM");
    Serial.println("Menu 1.5.1 - PID Normal");
    Serial.println("Entrez une nouvelle valeur ou commande:");
    Serial.println("save - Sauvegarder PID Normal en EEPROM");
    Serial.println("11 - Retour");
  }
  else if (option == "11") {
    niveauMenu = MENU_REGLAGE_PID;
    afficherSousMenu(MENU_REGLAGE_PID);
  }
  // ... autres options PID normal existantes
}
```

## 6. Menu PID Agressif (1.5.2) - Save PID Agressif

### Modifier handleAgressifPIDMenu() dans Menu.cpp :

```cpp
void handleAgressifPIDMenu(String option) {
  if (option == "save") {
    SaveEEPROM_PID_Agressif();
    Serial.println("Parametres PID Agressif sauvegardes en EEPROM");
    Serial.println("Menu 1.5.2 - PID Agressif");
    Serial.println("Entrez une nouvelle valeur ou commande:");
    Serial.println("save - Sauvegarder PID Agressif en EEPROM");
    Serial.println("11 - Retour");
  }
  else if (option == "11") {
    niveauMenu = MENU_REGLAGE_PID;
    afficherSousMenu(MENU_REGLAGE_PID);
  }
  // ... autres options PID agressif existantes
}
```

## 7. Menu DSG (1.6.3) - Save DSG

### Dans gererMenu(), ajouter :

```cpp
else if (menu == MENU_DSG_Duree) {
  if (option == "save") {
    SaveEEPROM_DSG();
    Serial.println("Parametres DSG sauvegardes en EEPROM");
    Serial.println("Menu 1.6.3.2 - DSG Duree");
    Serial.println("Entrez une nouvelle valeur ou commande:");
    Serial.println("save - Sauvegarder DSG en EEPROM");
    Serial.println("11 - Retour");
  }
  else if (option == "11") {
    niveauMenu = MENU_DSG;
    afficherSousMenu(MENU_DSG);
  }
  // ... autres options DSG existantes
}
```

## 8. Commandes Globales EEPROM

### Ajouter dans gererMenu() pour des commandes globales :

```cpp
// Commandes globales (peuvent être utilisées depuis n'importe quel menu)
else if (option == "save_all") {
  SaveEEPROM();  // Sauvegarde toutes les données
  Serial.println("Toutes les donnees sauvegardees en EEPROM");
}
else if (option == "load_all") {
  LoadEEPROM();  // Recharge toutes les données
  Serial.println("Toutes les donnees rechargees depuis EEPROM");
}
else if (option == "reset_eeprom") {
  Serial.println("ATTENTION: Reinitialisation de l'EEPROM dans 3 secondes...");
  delay(3000);
  ResetEEPROM();
  Serial.println("EEPROM reinitialisee. Redemarrez l'Arduino pour appliquer les valeurs par defaut.");
}
else if (option == "eeprom_status") {
  DisplayEEPROMStatus();
}
```

## 9. Affichage des Options Save dans les Menus

### Modifier afficherSousMenu() pour inclure les options Save :

```cpp
void afficherSousMenu(String menu) {
  if (menu == MENU_REGLAGE_PWM) {
    Serial.println("=== Menu Reglage PWM ===");
    Serial.println("Entrez une nouvelle valeur ou commande:");
    Serial.println("save - Sauvegarder PWM en EEPROM");  // ← Option Save
    Serial.println("11 - Retour");
  }
  
  else if (menu == MENU_REGLAGE_FREQUENCE) {
    Serial.println("=== Menu Reglage Frequence ===");
    Serial.println("Entrez une nouvelle valeur ou commande:");
    Serial.println("save - Sauvegarder Frequence en EEPROM");  // ← Option Save
    Serial.println("11 - Retour");
  }
  
  else if (menu == MENU_PID_Normal) {
    Serial.println("=== Menu PID Normal ===");
    Serial.println("Entrez une nouvelle valeur ou commande:");
    Serial.println("save - Sauvegarder PID Normal en EEPROM");  // ← Option Save
    Serial.println("11 - Retour");
  }
  
  else if (menu == MENU_PID_Agressif) {
    Serial.println("=== Menu PID Agressif ===");
    Serial.println("Entrez une nouvelle valeur ou commande:");
    Serial.println("save - Sauvegarder PID Agressif en EEPROM");  // ← Option Save
    Serial.println("11 - Retour");
  }
  
  else if (menu == MENU_DSG_Duree) {
    Serial.println("=== Menu DSG Duree ===");
    Serial.println("Entrez une nouvelle valeur ou commande:");
    Serial.println("save - Sauvegarder DSG en EEPROM");  // ← Option Save
    Serial.println("11 - Retour");
  }
  
  // ... autres menus existants
}
```

## 10. Workflow Utilisateur

### Exemple de workflow pour calibration PPS :

1. **Utilisateur** : Sélectionne "1.1.2 - Calibration PPS"
2. **Système** : Lance la calibration PPS
3. **Système** : Affiche "PPS calibrated - Utilisez le menu 1.1.3 pour sauvegarder en EEPROM"
4. **Utilisateur** : Sélectionne "1.1.3 - Save PPS en EEPROM"
5. **Système** : Sauvegarde les valeurs PPS et confirme

### Exemple de workflow pour réglage PID :

1. **Utilisateur** : Sélectionne "1.5.1 - PID Normal"
2. **Système** : Affiche le menu PID avec option "save"
3. **Utilisateur** : Modifie les valeurs kP, kI, kD
4. **Utilisateur** : Tape "save" pour sauvegarder
5. **Système** : Sauvegarde les valeurs PID et confirme

## 11. Commandes Rapides pour Test

### Commandes à taper directement dans le moniteur série :

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

## Avantages de cette Approche

1. **🎯 Contrôle utilisateur** : L'utilisateur décide quand sauvegarder
2. **🛡️ Sécurité** : Pas de sauvegarde accidentelle
3. **📝 Flexibilité** : Peut tester plusieurs valeurs avant de sauvegarder
4. **⚡ Performance** : Sauvegarde seulement ce qui est nécessaire
5. **🔄 Modularité** : Chaque section a sa propre sauvegarde 
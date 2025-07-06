# Guide d'Utilisation - Sauvegarde EEPROM dans le Menu

## Vue d'ensemble

Le système de menu a été étendu avec des fonctionnalités complètes de sauvegarde et de chargement EEPROM. Toutes les données de calibration et de configuration peuvent maintenant être sauvegardées de manière sélective ou globale.

## Commandes Globales EEPROM

Ces commandes peuvent être utilisées depuis n'importe quel menu :

- **`save_all`** : Sauvegarde toutes les données en EEPROM
- **`load_all`** : Recharge toutes les données depuis l'EEPROM
- **`reset_eeprom`** : Réinitialise l'EEPROM (attention !)
- **`eeprom_status`** : Affiche le statut de l'EEPROM

## Menu Principal EEPROM (Option 8)

Le menu principal inclut maintenant une option "8) EEPROM" qui donne accès à :

1. **Save All Data** - Sauvegarde toutes les données
2. **Load All Data** - Recharge toutes les données
3. **EEPROM Status** - Affiche le statut de l'EEPROM
4. **Reset EEPROM** - Réinitialise l'EEPROM (avec confirmation)

## Sauvegardes Sélectives par Menu

### Menu PPS (1.1.3)
- **Option 3** : Sauvegarde uniquement les valeurs de calibration PPS
- Affiche les valeurs sauvegardées après confirmation

### Menu TPS (1.2.3)
- **Option 3** : Sauvegarde uniquement les valeurs de calibration TPS
- Affiche les valeurs sauvegardées après confirmation

### Menu PWM (1.3)
- **Option `save`** : Sauvegarde les paramètres PWM (Min/Max)
- Permet de continuer à modifier les valeurs après sauvegarde

### Menu Fréquence (1.4)
- **Option `save`** : Sauvegarde la fréquence TPS
- Permet de continuer à modifier la valeur après sauvegarde

### Menu PID Normal (1.5.1)
- **Option `save`** : Sauvegarde les paramètres PID normaux (kP, kI, kD)
- Met à jour l'objet PID en temps réel
- Retour au menu PID principal après sauvegarde

### Menu PID Agressif (1.5.2)
- **Option `save`** : Sauvegarde les paramètres PID agressifs (kP, kI, kD)
- Retour au menu PID principal après sauvegarde

### Menu DSG (1.6.3)
- **Option `save`** : Sauvegarde les paramètres DSG (mode et durée)
- Retour au menu Acquisition après sauvegarde

## Workflow Recommandé

### 1. Calibration Initiale
1. Effectuer la calibration PPS (Menu 1.1.2)
2. Effectuer la calibration TPS (Menu 1.2.2)
3. Sauvegarder PPS (Menu 1.1.3, Option 3)
4. Sauvegarder TPS (Menu 1.2.3, Option 3)

### 2. Réglages de Performance
1. Ajuster les paramètres PWM (Menu 1.3)
2. Sauvegarder PWM (Menu 1.3, Option `save`)
3. Ajuster la fréquence (Menu 1.4)
4. Sauvegarder fréquence (Menu 1.4, Option `save`)

### 3. Réglages PID
1. Ajuster PID normal (Menu 1.5.1)
2. Sauvegarder PID normal (Menu 1.5.1, Option `save`)
3. Ajuster PID agressif (Menu 1.5.2)
4. Sauvegarder PID agressif (Menu 1.5.2, Option `save`)

### 4. Configuration DSG
1. Configurer DSG (Menu 1.6.3)
2. Sauvegarder DSG (Menu 1.6.3, Option `save`)

### 5. Sauvegarde Globale (Optionnel)
- Utiliser le menu EEPROM (Menu 8) pour une sauvegarde complète
- Ou utiliser la commande `save_all` depuis n'importe quel menu

## Avantages du Système

### Contrôle Granulaire
- Sauvegarde sélective par section
- Évite les sauvegardes accidentelles
- Permet de tester plusieurs configurations

### Sécurité
- Confirmation avant réinitialisation EEPROM
- Validation des données par numéro magique
- Gestion des versions de données

### Flexibilité
- Commandes globales accessibles partout
- Menu dédié pour la gestion EEPROM
- Retour facile aux menus précédents

## Messages de Confirmation

Chaque sauvegarde affiche :
- Confirmation de la sauvegarde
- Valeurs sauvegardées
- Instructions pour continuer

## Gestion des Erreurs

- Vérification de l'intégrité des données
- Messages d'erreur explicites
- Fallback vers les valeurs par défaut si nécessaire

## Notes Importantes

1. **Pas de sauvegarde automatique** : Les calibrations ne sauvegardent plus automatiquement
2. **Validation manuelle** : L'utilisateur doit explicitement choisir de sauvegarder
3. **Contrôle total** : L'utilisateur a le contrôle complet sur ce qui est sauvegardé
4. **Sécurité** : Confirmation requise pour les opérations destructives

## Commandes Rapides

Pour un accès rapide aux fonctions EEPROM :
- `save_all` : Sauvegarde complète
- `load_all` : Rechargement complet
- `eeprom_status` : Vérification du statut
- Menu 8 : Accès au menu EEPROM complet 
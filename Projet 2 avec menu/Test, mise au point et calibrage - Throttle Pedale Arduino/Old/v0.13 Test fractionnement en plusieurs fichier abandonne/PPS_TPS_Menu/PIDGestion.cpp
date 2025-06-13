//Algrorhytme PID

#include <Arduino.h>
#include "PIDGestion.h"
#include "PPS_TPS_Menu.h"
#include "PID_v1.h"



// Initialisation du PID
void TB_PID_Init() {
    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(PwmMini, PwmMaxi);
}

// Mise à jour du PID (à appeler dans loop)
void TB_PID_Update() {
    Input = TPSPot_ADC;      // Exemple : la position actuelle du papillon
    Setpoint = PPSPot_ADC;   // Exemple : la consigne venant de la pédale
    myPID.Compute();
    analogWrite(enablePin, Output); // Commande le moteur avec la sortie PID
}

// Affichage des paramètres PID sur le port série
void TB_PID_Display() {
    Serial.print(F("Kp: ")); Serial.print(Kp);
    Serial.print(F(" Ki: ")); Serial.print(Ki);
    Serial.print(F(" Kd: ")); Serial.println(Kd);
}
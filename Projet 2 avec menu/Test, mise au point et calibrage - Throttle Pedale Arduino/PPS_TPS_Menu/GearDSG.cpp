#include "GearDSG.h"
extern unsigned long DSG_Duration;
extern bool dsgActive;
extern unsigned long dsgStartTime;
extern bool dsgUp;

// ===============================
// Module de gestion du mode DSG
// ===============================
// Ce module permet de simuler une séquence DSG (passage de vitesse)
// en commandant le papillon motorisé pendant un court instant.
//
// GearDSG_Trigger() démarre la séquence
// GearDSG_Loop() doit être appelée régulièrement (dans loop())
// GearDSG_IsActive() permet de savoir si une séquence DSG est en cours

/**
 * @brief Initialise le module DSG (remise à zéro des variables)
 */
void GearDSG_Init() {
    // Variables internes au module
    // static bool dsgActive = false;           // Indique si une séquence DSG est en cours
    // static unsigned long dsgStartTime = 0;   // Mémorise le début de la séquence
    // static bool dsgUp = true;                // true = passage supérieur, false = rétrogradage
}

/**
 * @brief Fonction à appeler dans loop().
 *        Si une séquence DSG est active, commande le papillon selon le sens du passage.
 *        Quand la durée est écoulée, remet le papillon en mode normal.
 */
void GearDSG_Loop() {
    // Variables internes au module
    // static bool dsgActive = false;           // Indique si une séquence DSG est en cours
    // static unsigned long dsgStartTime = 0;   // Mémorise le début de la séquence
    // static bool dsgUp = true;                // true = passage supérieur, false = rétrogradage
    if (dsgActive) {
        // Pendant la séquence DSG, on agit sur le papillon
        if (millis() - dsgStartTime < DSG_Duration) {
            if (dsgUp) {
                // Passage supérieur : ouvrir le papillon (adapter selon ton besoin)
                // TPS_RotateMotor(Open);
            } else {
                // Rétrogradage : fermer le papillon (adapter selon ton besoin)
                // TPS_RotateMotor(Close);
            }
        } else {
            // Fin de la séquence DSG
            dsgActive = false;
            // Remettre le papillon en mode normal (adapter si besoin)
            // TPS_RotateMotor(Freewheel);
        }
    }
}

/**
 * @brief Déclenche une séquence DSG (passage de vitesse)
 * @param gearUp true = passage supérieur, false = rétrogradage
 *
 * - Met dsgActive à true (active la séquence)
 * - Mémorise le moment de début
 * - Mémorise le sens du passage
 *
 * Ensuite, c'est GearDSG_Loop() qui gère la suite automatiquement
 */
void GearDSG_Trigger(bool gearUp) {
    dsgActive = true;
    dsgStartTime = millis();
    dsgUp = gearUp;
}

/**
 * @brief Indique si une séquence DSG est en cours
 * @return true si le papillon est commandé par le module DSG, false sinon
 *
 * Utile pour savoir si tu dois suspendre la commande normale du papillon
 */
bool GearDSG_IsActive() {
    return dsgActive;
}

unsigned long GearDSG_GetDuration() {
    return DSG_Duration;
}

void GearDSG_SetDuration(unsigned long duration) {
    DSG_Duration = duration;
} 
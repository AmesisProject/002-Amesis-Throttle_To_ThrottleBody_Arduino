#ifndef GEAR_DSG_H
#define GEAR_DSG_H

#include <Arduino.h>

/**
 * @brief Initialise le module GearDSG (si besoin)
 */
void GearDSG_Init();

/**
 * @brief Fonction principale à appeler dans la loop pour gérer le mode DSG.
 *        Elle doit être appelée régulièrement pour surveiller et commander le papillon lors des passages de vitesse.
 */
void GearDSG_Loop();

/**
 * @brief Déclenche la séquence de passage de vitesse DSG.
 * @param gearUp true pour passage supérieur, false pour rétrograder
 */
void GearDSG_Trigger(bool gearUp);

/**
 * @brief Indique si une séquence DSG est en cours.
 * @return true si une séquence DSG est active, false sinon
 */
bool GearDSG_IsActive();

#endif // GEAR_DSG_H 
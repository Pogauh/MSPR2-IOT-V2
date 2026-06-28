#pragma once

/**
 * @brief Gère l'affichage des mesures sur l'écran LCD I2C.
 */
class LcdManager {
public:

    /**
     * @brief Initialise l'écran LCD et affiche un message de démarrage.
     */
    void begin();

    /**
     * @brief Affiche les mesures de température et d'humidité.
     *
     * @param temperature Température mesurée (°C).
     * @param humidity Humidité mesurée (%).
     */
    void show(float temperature, float humidity);
};
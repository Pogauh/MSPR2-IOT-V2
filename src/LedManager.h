#pragma once
#include <Arduino.h>

/**
 * @brief Gère l'état des LEDs en fonction des mesures de température
 *        et d'humidité.
 */
class LEDManager {
public:

    /**
     * @brief Initialise les broches des LEDs.
     */
    void begin();

    /**
     * @brief Met à jour l'état des LEDs selon les seuils définis.
     *
     * @param temp Température mesurée (°C).
     * @param hum Humidité mesurée (%).
     */
    void update(float temp, float hum);

private:
    int LED_RED = 22;
    int LED_GREEN = 23;
};
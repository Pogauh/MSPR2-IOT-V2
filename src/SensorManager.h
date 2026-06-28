#pragma once

#include <DHTesp.h>

/**
 * @brief Représente une mesure du capteur.
 */
struct Measurement {
    float temperature;
    float humidity;
};

/**
 * @brief Gère l'initialisation et la lecture du capteur DHT11.
 */
class SensorManager {
public:

    /**
     * @brief Initialise le capteur DHT11.
     */
    void begin();

    /**
     * @brief Lit les mesures du capteur.
     *
     * @param measurement Structure contenant les valeurs lues.
     * @return true si la lecture a réussi, false sinon.
     */
    bool read(Measurement& measurement);

private:
    DHTesp dht;
};
#pragma once

#include <Arduino.h>

/**
 * @brief Gère la synchronisation de l'heure via un serveur NTP.
 */
class TimeManager {
public:

    /**
     * @brief Initialise la synchronisation avec le serveur NTP.
     */
    void begin();

    /**
     * @brief Retourne la date et l'heure au format ISO 8601.
     *
     * @return Date et heure au format "YYYY-MM-DDTHH:MM:SS".
     */
    String getDateISO();
};
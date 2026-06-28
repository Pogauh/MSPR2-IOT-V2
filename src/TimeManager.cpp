#include "TimeManager.h"
#include "Config.h"
#include <time.h>

void TimeManager::begin() {

    // Configure la synchronisation de l'horloge avec le serveur NTP
    configTime(
        GMT_OFFSET_SEC,
        DAYLIGHT_OFFSET_SEC,
        NTP_SERVER
    );

    struct tm timeinfo;

    // Attend que la synchronisation soit terminée
    while (!getLocalTime(&timeinfo)) {
        Serial.println("Synchronisation NTP...");
        delay(1000);
    }

    Serial.println("Heure synchronisée !");
}

String TimeManager::getDateISO() {

    struct tm timeinfo;

    // Retourne une valeur par défaut si l'heure n'est pas disponible
    if (!getLocalTime(&timeinfo)) {
        return "unknown";
    }

    char buffer[25];

    // Formate la date au format ISO 8601
    strftime(
        buffer,
        sizeof(buffer),
        "%Y-%m-%dT%H:%M:%S",
        &timeinfo
    );

    return String(buffer);
}
#include "LEDManager.h"
#include "Config.h"

void LEDManager::begin() {

    // Configuration des broches des LEDs en sortie
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);

    // Extinction des LEDs au démarrage
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
}

void LEDManager::update(float temp, float hum) {

    // Vérifie si les mesures sont comprises dans les seuils définis
    bool tempOk = (temp >= TEMP_MIN && temp <= TEMP_MAX);
    bool humOk  = (hum >= HUM_MIN && hum <= HUM_MAX);

    // LED verte si les mesures sont conformes,
    // sinon LED rouge
    if (tempOk && humOk) {
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_RED, LOW);
    }
    else {
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_RED, HIGH);
    }
}
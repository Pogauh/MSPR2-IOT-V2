#include "SensorManager.h"
#include "Config.h"

void SensorManager::begin() {

    // Initialisation du capteur DHT11
    dht.setup(DHT_PIN, DHTesp::DHT11);
}

bool SensorManager::read(Measurement& measurement) {

    // Lecture des mesures du capteur
    measurement.temperature = dht.getTemperature();
    measurement.humidity = dht.getHumidity();

    // Retourne l'état de la lecture
    return dht.getStatus() == DHTesp::ERROR_NONE;
}
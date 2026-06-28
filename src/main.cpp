#include <Arduino.h>

#include "SensorManager.h"
#include "TimeManager.h"
#include "MqttManager.h"
#include "WifiManagerCustom.h"
#include "Config.h"
#include "LEDManager.h"
#include "LcdManager.h"

// Gestionnaires des différents composants de l'ESP32
SensorManager sensorManager;
TimeManager timeManager;
MqttManager mqttManager;
WifiManagerCustom wifiManager;
LEDManager ledManager;
LcdManager lcdManager;

void setup() {

    // Initialisation de la communication série pour le débogage
    Serial.begin(115200);
    delay(1000);

    Serial.println("=== ESP32 START ===");

    // Connexion automatique au réseau Wi-Fi
    wifiManager.begin();

    // Synchronisation de l'horloge via un serveur NTP
    timeManager.begin();

    // Initialisation de la connexion au broker MQTT
    mqttManager.begin();

    // Initialisation du capteur DHT11
    sensorManager.begin();

    // Initialisation des LEDs d'état
    ledManager.begin();

    // Initialisation de l'écran LCD
    lcdManager.begin();
}

void loop() {

    // Maintient la connexion MQTT active
    mqttManager.loop();

    Measurement measurement;

    // Lecture des mesures du capteur
    if (sensorManager.read(measurement)) {

        // Construction du message JSON à envoyer au backend
        String payload =
            "{"
            "\"temperature\":" +
            String(measurement.temperature, 2) +
            ","
            "\"humidite\":" +
            String(measurement.humidity, 2) +
            ","
            "\"dateMesure\":\"" +
            timeManager.getDateISO() +
            "\","
            "\"idCapteur\":\"" +
            String(CAPTEUR_ID) +
            "\""
            "}";

        Serial.println(payload);

        // Publication des données sur le broker MQTT
        bool sent = mqttManager.publish(payload);

        if (sent) {
            Serial.println("Les mesures ont été envoyées avec succès via MQTT.");
        } else {
            Serial.println("Erreur d'envoi MQTT.");
        }
    }
    else {

        // La lecture du capteur a échoué
        Serial.println("Erreur lecture DHT11");
    }

    // Mise à jour des LEDs selon les valeurs mesurées
    ledManager.update(measurement.temperature, measurement.humidity);

    // Affichage des mesures sur l'écran LCD
    lcdManager.show(measurement.temperature, measurement.humidity);

    // Attente avant la prochaine acquisition
    delay(DELAY_MESURE_MS);
}
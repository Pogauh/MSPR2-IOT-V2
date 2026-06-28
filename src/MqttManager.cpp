#include "MqttManager.h"
#include "Config.h"

void MqttManager::begin() {

    // Configure le client avec l'adresse du broker MQTT
    mqttServer = MQTT_BROKER;

    Serial.print("MQTT Broker fixe : ");
    Serial.println(mqttServer);

    client.setServer(
        mqttServer.c_str(),
        MQTT_PORT
    );
}

void MqttManager::connect() {

    // Tente de se connecter au broker tant que la connexion n'est pas établie
    while (!client.connected()) {

        Serial.print("Connexion MQTT...");

        String clientId =
            "ESP32-" + String(random(1000, 9999));

        if (client.connect(clientId.c_str())) {

            Serial.println(" OK");

        } else {

            Serial.print(" ECHEC rc=");
            Serial.println(client.state());

            delay(3000);
        }
    }
}

void MqttManager::loop() {

    // Vérifie la connexion et traite les échanges MQTT
    if (!client.connected()) {
        connect();
    }

    client.loop();
}

bool MqttManager::publish(const String& payload) {

    // Publie le message sur le topic configuré
    return client.publish(
        MQTT_TOPIC,
        payload.c_str()
    );
}
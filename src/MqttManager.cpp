#include "MqttManager.h"
#include "Config.h"

void MqttManager::begin() {

    // Configure le client avec l'adresse du broker MQTT
    // (saisie dans le portail Wi-Fi, ou valeur par défaut de Config.h)
    mqttServer = loadMQTTConfig();

    Serial.print("MQTT Broker : ");
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

String MqttManager::loadMQTTConfig() {

    // Lit l'adresse enregistrée, sinon retourne celle de Config.h
    Preferences prefs;
    prefs.begin(PREFS_NAMESPACE, false);
    String server = prefs.getString(PREFS_KEY_MQTT_BROKER, MQTT_BROKER);
    prefs.end();

    return server;
}

bool MqttManager::saveMQTTConfig(const String& server) {

    String value = server;
    value.trim();

    // Refuse une adresse vide ou contenant des caractères invalides
    if (value.length() == 0) {
        return false;
    }

    for (unsigned int i = 0; i < value.length(); i++) {
        char c = value[i];
        if (!isalnum(c) && c != '.' && c != '-') {
            return false;
        }
    }

    Preferences prefs;
    prefs.begin(PREFS_NAMESPACE, false);
    prefs.putString(PREFS_KEY_MQTT_BROKER, value);
    prefs.end();

    return true;
}
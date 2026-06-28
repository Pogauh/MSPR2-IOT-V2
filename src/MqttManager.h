#pragma once

#include <PubSubClient.h>
#include <WiFi.h>
#include <Preferences.h>
#include <WiFiManager.h>

/**
 * @brief Gère la connexion et les échanges avec le broker MQTT.
 */
class MqttManager {

public:

    /**
     * @brief Initialise la configuration du client MQTT.
     */
    void begin();

    /**
     * @brief Maintient la connexion avec le broker MQTT.
     */
    void loop();

    /**
     * @brief Publie un message sur le topic configuré.
     *
     * @param payload Message à publier au format JSON.
     * @return true si l'envoi a réussi, false sinon.
     */
    bool publish(const String& payload);

private:
    WiFiClient espClient;
    PubSubClient client{espClient};

    Preferences prefs;

    String mqttServer;

    /**
     * @brief Établit la connexion au broker MQTT.
     */
    void connect();

    /**
     * @brief Charge l'adresse du broker MQTT depuis la mémoire persistante.
     *
     * @return Adresse IP ou nom d'hôte du broker.
     */
    String loadMQTTConfig();

    /**
     * @brief Enregistre l'adresse du broker MQTT dans la mémoire persistante.
     *
     * @param server Adresse IP ou nom d'hôte du broker.
     */
    void saveMQTTConfig(String server);
};
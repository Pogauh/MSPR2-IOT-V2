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

    /**
     * @brief Charge l'adresse du broker MQTT depuis la mémoire persistante.
     *
     * @return Adresse saisie dans le portail Wi-Fi, ou MQTT_BROKER (Config.h) par défaut.
     */
    static String loadMQTTConfig();

    /**
     * @brief Enregistre l'adresse du broker MQTT dans la mémoire persistante.
     *
     * @param server Adresse IP ou nom d'hôte du broker.
     * @return true si l'adresse est valide et enregistrée, false sinon.
     */
    static bool saveMQTTConfig(const String& server);

private:
    WiFiClient espClient;
    PubSubClient client{espClient};

    String mqttServer;

    /**
     * @brief Établit la connexion au broker MQTT.
     */
    void connect();
};
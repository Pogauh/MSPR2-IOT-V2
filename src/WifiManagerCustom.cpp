#include "WifiManagerCustom.h"

#include <WiFiManager.h>
#include <Arduino.h>

#include "Config.h"
#include "MqttManager.h"

void WifiManagerCustom::begin() {

    // Mode station uniquement (l'ESP32 est par défaut en STA + AP)
    WiFi.mode(WIFI_STA);

    // Champ du portail pour saisir l'adresse du broker MQTT
    // (pré-rempli avec l'adresse enregistrée, ou celle de Config.h par défaut)
    String currentBroker = MqttManager::loadMQTTConfig();
    WiFiManagerParameter brokerParam(
        "broker",
        "Adresse IP du broker MQTT",
        currentBroker.c_str(),
        MQTT_BROKER_MAX_LENGTH,
        "required placeholder=\"192.168.1.100\" pattern=\"[A-Za-z0-9.\\-]+\""
    );

    WiFiManager wm;
    wm.addParameter(&brokerParam);

    // Enregistre l'adresse du broker dès que le formulaire du portail est validé
    wm.setSaveParamsCallback([&brokerParam]() {
        if (MqttManager::saveMQTTConfig(brokerParam.getValue())) {
            Serial.print("Broker MQTT enregistré : ");
            Serial.println(brokerParam.getValue());
        } else {
            Serial.println("Adresse du broker MQTT invalide, ignorée");
        }
    });

    // Délai maximal de connexion au réseau mémorisé (en secondes)
    wm.setConnectTimeout(WIFI_TIMEOUT_MS / 1000);

    // Ferme le portail après un délai sans configuration : l'ESP32 redémarre
    // et réessaie (utile si le routeur n'est pas encore prêt au démarrage)
    wm.setConfigPortalTimeout(WIFI_PORTAL_TIMEOUT_S);

    bool ok;

    if (resetRequested()) {

        // Bouton BOOT appuyé : ouvre le portail même si le réseau mémorisé est disponible
        Serial.println("Ouverture du portail de configuration Wi-Fi");
        ok = wm.startConfigPortal(WIFI_PORTAL_SSID);

    } else {

        // Tente une connexion automatique ou démarre un portail de configuration
        ok = wm.autoConnect(WIFI_PORTAL_SSID);
    }

    if (!ok) {
        Serial.println("Echec WiFi ou portail fermé, redémarrage");
        ESP.restart();
    }

    // Affiche les informations de connexion
    Serial.print("WiFi connecté à ");
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.localIP());
}

bool WifiManagerCustom::resetRequested() {

    // Le bouton BOOT relie GPIO 0 à la masse lorsqu'il est appuyé
    pinMode(WIFI_RESET_PIN, INPUT_PULLUP);

    Serial.println("Appuyer sur BOOT pour reconfigurer le Wi-Fi...");

    unsigned long start = millis();
    while (millis() - start < WIFI_RESET_WINDOW_MS) {
        if (digitalRead(WIFI_RESET_PIN) == LOW) {
            return true;
        }
        delay(20);
    }

    return false;
}
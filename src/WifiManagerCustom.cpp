#include "WifiManagerCustom.h"

#include <WiFiManager.h>
#include <Arduino.h>

void WifiManagerCustom::begin() {

    WiFiManager wm;

    // Définit le délai maximal de connexion au réseau Wi-Fi
    wm.setConnectTimeout(30);

    // Tente une connexion automatique ou démarre un portail de configuration
    bool ok = wm.autoConnect("ESP32-Setup");

    if (!ok) {
        Serial.println("Echec WiFi");
        ESP.restart();
    }

    // Affiche les informations de connexion
    Serial.println("WiFi connecté");
    Serial.println(WiFi.localIP());
}
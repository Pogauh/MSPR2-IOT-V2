#include "WifiManagerCustom.h"

#include <WiFi.h>
#include <Arduino.h>

#include "Config.h"

void WifiManagerCustom::begin() {

    // Connexion directe au réseau défini dans Config.h
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connexion au WiFi ");
    Serial.println(WIFI_SSID);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - start > WIFI_TIMEOUT_MS) {
            Serial.println("Echec WiFi");
            ESP.restart();
        }
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    // Affiche les informations de connexion
    Serial.println("WiFi connecté");
    Serial.println(WiFi.localIP());
}
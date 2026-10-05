#pragma once

// Seuils de fonctionnement des capteurs
constexpr float TEMP_MIN = 26.0f;
constexpr float TEMP_MAX = 32.0f;

constexpr float HUM_MIN = 53.0f;
constexpr float HUM_MAX = 57.0f;

// Configuration Wi-Fi (connexion en dur, sans portail WiFiManager)
constexpr char WIFI_SSID[] = "Freebox-C279FA";
constexpr char WIFI_PASSWORD[] = "Lacoloc59";
constexpr unsigned long WIFI_TIMEOUT_MS = 30000;

// Configuration MQTT
constexpr int MQTT_PORT = 1883;
constexpr char MQTT_TOPIC[] = "futurekawa/bresil/entrepot1/data";
constexpr char MQTT_BROKER[] = "192.168.1.101";

// Configuration du serveur NTP
constexpr char NTP_SERVER[] = "pool.ntp.org";
constexpr long GMT_OFFSET_SEC = 3600;
constexpr int DAYLIGHT_OFFSET_SEC = 3600;

// Configuration du capteur DHT11
constexpr int DHT_PIN = 32;

// Identifiant unique du capteur utilisé par le backend
constexpr char CAPTEUR_ID[] = "4da39f51-970b-4b9d-9a2a-d092af0d10f2";

// Intervalle entre deux acquisitions de mesures (en millisecondes)
constexpr int DELAY_MESURE_MS = 10000;
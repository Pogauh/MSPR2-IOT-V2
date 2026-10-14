#pragma once

// Seuils de fonctionnement des capteurs
constexpr float TEMP_MIN = 26.0f;
constexpr float TEMP_MAX = 32.0f;

constexpr float HUM_MIN = 53.0f;
constexpr float HUM_MAX = 57.0f;

// Configuration Wi-Fi (WiFiManager : le réseau est saisi via le portail)
constexpr char WIFI_PORTAL_SSID[] = "ESP32-Setup";            // Nom du point d'accès ouvert par l'ESP32
constexpr unsigned long WIFI_TIMEOUT_MS = 30000;               // Délai de connexion au réseau mémorisé
constexpr unsigned long WIFI_PORTAL_TIMEOUT_S = 180;           // Durée du portail avant redémarrage (secondes)
constexpr int WIFI_RESET_PIN = 0;                              // Bouton BOOT de l'ESP32 (GPIO 0)
constexpr unsigned long WIFI_RESET_WINDOW_MS = 3000;           // Fenêtre au démarrage pour appuyer sur BOOT

// Configuration MQTT
constexpr int MQTT_PORT = 1883;
constexpr char MQTT_TOPIC[] = "futurekawa/bresil/entrepot1/data";
constexpr char MQTT_BROKER[] = "10.171.216.89";                // Valeur par défaut, modifiable depuis le portail Wi-Fi
constexpr int MQTT_BROKER_MAX_LENGTH = 64;                     // Taille maximale de l'adresse saisie dans le portail
constexpr char PREFS_NAMESPACE[] = "futurekawa";               // Espace de stockage en flash (NVS)
constexpr char PREFS_KEY_MQTT_BROKER[] = "mqtt_broker";        // Clé de l'adresse du broker

// Configuration du serveur NTP
constexpr char NTP_SERVER[] = "pool.ntp.org";
constexpr long GMT_OFFSET_SEC = 3600;
constexpr int DAYLIGHT_OFFSET_SEC = 3600;

// Configuration du capteur DHT11
constexpr int DHT_PIN = 32;

// Identifiant unique du capteur utilisé par le backend
constexpr char CAPTEUR_ID[] = "4da39f51-970b-4b9d-9a2a-d092af0d10f2";

// Intervalle entre deux acquisitions de mesures (en millisecondes)
constexpr int DELAY_MESURE_MS = 60000;
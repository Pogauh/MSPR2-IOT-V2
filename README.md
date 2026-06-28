# FutureKawa - Module IoT ESP32

## Présentation

Ce projet constitue la partie **IoT** du projet **FutureKawa**.

Il permet à un **ESP32** équipé d'un capteur **DHT11** de mesurer périodiquement la température et l'humidité d'un entrepôt, puis de transmettre ces données à un broker MQTT afin qu'elles soient traitées par le backend Spring Boot.

Le projet est volontairement découpé en plusieurs composants afin de respecter une architecture modulaire et faciliter la maintenance.

---

# Fonctionnalités

- Connexion automatique au Wi-Fi via WiFiManager
- Synchronisation de l'heure via NTP
- Lecture des mesures du capteur DHT11
- Affichage des mesures sur un écran LCD I2C
- Indication visuelle par LEDs :
  - 🟢 Vert : valeurs dans les seuils
  - 🔴 Rouge : dépassement des seuils
- Publication des mesures au format JSON sur MQTT
- Architecture orientée composants

---

# Architecture

```
src
│
├── main.cpp
│
├── Config.h
│
├── SensorManager.h
├── SensorManager.cpp
│
├── WifiManagerCustom.h
├── WifiManagerCustom.cpp
│
├── TimeManager.h
├── TimeManager.cpp
│
├── MqttManager.h
├── MqttManager.cpp
│
├── LEDManager.h
├── LEDManager.cpp
│
├── LcdManager.h
└── LcdManager.cpp
```

Chaque composant possède une responsabilité unique.

| Composant         | Rôle                        |
| ----------------- | --------------------------- |
| SensorManager     | Lecture du DHT11            |
| WifiManagerCustom | Connexion Wi-Fi             |
| TimeManager       | Synchronisation NTP         |
| MqttManager       | Communication MQTT          |
| LEDManager        | Gestion des LEDs            |
| LcdManager        | Gestion de l'écran LCD      |
| Config            | Paramètres de configuration |
| main.cpp          | Orchestration générale      |

---

# Matériel utilisé

- ESP32 DevKit V4 (AZDelivery)
- DHT11
- Écran LCD I2C 16x2
- 2 LEDs
- Résistances
- Breadboard

---

# Câblage

## DHT11

| DHT11 | ESP32   |
| ----- | ------- |
| VCC   | 3.3V    |
| GND   | GND     |
| DATA  | GPIO 32 |

---

## LCD I2C

| LCD | ESP32   |
| --- | ------- |
| SDA | GPIO 4  |
| SCL | GPIO 16 |
| VCC | 5V      |
| GND | GND     |

Adresse I2C utilisée :

```
0x27
```

---

## LEDs

### LED verte

GPIO 23

### LED rouge

GPIO 22

---

# Dépendances PlatformIO

```ini
lib_deps =
    beegee-tokyo/DHT sensor library for ESPx
    knolleary/PubSubClient
    tzapu/WiFiManager
    johnrickman/LiquidCrystal_I2C
```

---

# Configuration

Toute la configuration est centralisée dans :

```
Config.h
```

On y retrouve notamment :

- Broker MQTT
- Topic MQTT
- Port MQTT
- Adresse du serveur NTP
- Seuils de température
- Seuils d'humidité
- GPIO du capteur
- Identifiant du capteur
- Période de mesure

Exemple :

```cpp
constexpr char MQTT_BROKER[] = "192.168.1.73";
constexpr char MQTT_TOPIC[] = "futurekawa/bresil/entrepot1/data";
```

---

# Fonctionnement

Au démarrage :

1. Connexion au Wi-Fi
2. Synchronisation de l'heure
3. Initialisation MQTT
4. Initialisation du DHT11
5. Initialisation des LEDs
6. Initialisation du LCD

Ensuite, toutes les **10 secondes** :

- lecture du DHT11
- affichage LCD
- mise à jour des LEDs
- création d'un JSON
- publication MQTT

---

# Format des messages MQTT

Les mesures sont publiées au format JSON.

Exemple :

```json
{
  "temperature": 28.3,
  "humidite": 55.8,
  "dateMesure": "2026-06-15T14:35:21",
  "idCapteur": "4da39f51-970b-4b9d-9a2a-d092af0d10f2"
}
```

Topic :

```
futurekawa/bresil/entrepot1/data
```

---

# Gestion des LEDs

Les seuils sont définis dans `Config.h`.

## LED verte

Ici, nous avons pris l'exemple du Brésil.
La LED verte est donc allumée lorsque :

```
26°C ≤ Température ≤ 32°C

ET

53% ≤ Humidité ≤ 57%
```

## LED rouge

La LED rouge est allumée lorsqu'au moins un seuil est dépassé.

---

# Affichage LCD

Le LCD affiche en permanence :

```
Temp: 28.3 C
Hum : 55.2 %
```

---

# Synchronisation horaire

L'heure est obtenue via le serveur NTP :

```
pool.ntp.org
```

Les dates envoyées au backend sont au format ISO 8601.

Exemple :

```
2026-06-15T14:30:12
```

---

# Broker MQTT

Le projet utilise un broker Mosquitto.

Exemple :

```
Broker :
192.168.1.73

Port :
1883
```

---

# Compilation

```bash
pio run
```

---

# Téléversement

```bash
pio run --target upload
```

---

# Moniteur série

```bash
pio device monitor
```

---

# Exemple de sortie

```
=== ESP32 START ===

WiFi connecté

192.168.1.98

Heure synchronisée !

MQTT Broker fixe :
192.168.1.73

Connexion MQTT... OK

{
"temperature":28.40,
"humidite":54.70,
"dateMesure":"2026-06-15T14:30:10",
"idCapteur":"4da39f51-970b-4b9d-9a2a-d092af0d10f2"
}

Les mesures ont été envoyées avec succès via MQTT.
```

---

# Intégration avec FutureKawa

L'ESP32 n'enregistre aucune donnée localement.

Son unique rôle est :

```
Capteur DHT11
        │
        ▼
ESP32
        │
        ▼
MQTT (Mosquitto)
        │
        ▼
Backend Spring Boot
        │
        ▼
PostgreSQL
```

Le backend est responsable :

- de la réception des mesures MQTT ;
- de leur validation ;
- de leur stockage en base de données ;
- du déclenchement des alertes métier.

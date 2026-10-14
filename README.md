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

# Configuration du Wi-Fi (WiFiManager)

Aucun identifiant Wi-Fi n'est écrit dans le code. Le réseau est saisi une seule fois via un portail captif, puis mémorisé dans la flash de l'ESP32.

**Première utilisation, ou réseau mémorisé introuvable :**

1. L'ESP32 tente de se connecter au réseau mémorisé pendant 30 s.
2. En cas d'échec (ou s'il n'y a aucun réseau mémorisé), il ouvre le point d'accès `ESP32-Setup`.
3. Se connecter à ce point d'accès avec un téléphone ou un PC : le portail s'ouvre automatiquement (sinon aller sur `192.168.4.1`).
4. Choisir **Configure WiFi**, sélectionner le réseau, saisir le mot de passe, vérifier l'**adresse IP du broker MQTT** (pré-remplie), puis **Save**.
5. L'ESP32 se connecte et mémorise le réseau et le broker : les démarrages suivants sont automatiques.

Si personne ne configure le portail pendant 3 minutes, l'ESP32 redémarre et réessaie.

**Changer de réseau alors que l'ancien est encore disponible :**

1. Redémarrer l'ESP32 (bouton EN).
2. Appuyer sur le bouton **BOOT** pendant les 3 secondes qui suivent le message `Appuyer sur BOOT pour reconfigurer le Wi-Fi...`.
3. Le portail s'ouvre, reprendre les étapes 3 à 5 ci-dessus.

**Broker MQTT :** l'adresse saisie dans le portail est mémorisée en flash, comme le réseau Wi-Fi. `MQTT_BROKER` dans `Config.h` n'est que la valeur par défaut, utilisée tant que rien n'a été saisi.

**Changer uniquement le broker :** ouvrir le portail avec le bouton BOOT, laisser le réseau et le mot de passe vides, modifier l'adresse du broker, **Save**, puis redémarrer l'ESP32 (bouton EN) : la nouvelle adresse est utilisée.

---

# Fonctionnement

Au démarrage :

1. Connexion au Wi-Fi
2. Synchronisation de l'heure
3. Initialisation MQTT
4. Initialisation du DHT11
5. Initialisation des LEDs
6. Initialisation du LCD

Ensuite, toutes les **60 secondes** :

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

#pragma once

/**
 * @brief Gère la connexion de l'ESP32 à un réseau Wi-Fi.
 */
class WifiManagerCustom {
public:

    /**
     * @brief Se connecte au Wi-Fi défini dans Config.h (redémarre en cas d'échec).
     */
    void begin();
};
#pragma once

/**
 * @brief Gère la connexion de l'ESP32 à un réseau Wi-Fi via WiFiManager.
 */
class WifiManagerCustom {
public:

    /**
     * @brief Se connecte au dernier réseau mémorisé, ou ouvre un portail
     *        de configuration si aucun réseau n'est disponible
     *        (redémarre en cas d'échec).
     */
    void begin();

private:

    /**
     * @brief Laisse quelques secondes pour appuyer sur le bouton BOOT
     *        afin de forcer l'ouverture du portail de configuration.
     *
     * @return true si le bouton a été appuyé, false sinon.
     */
    bool resetRequested();
};
#include "LcdManager.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialisation de l'écran LCD I2C (adresse 0x27, 16 colonnes, 2 lignes)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void LcdManager::begin() {

    // Initialisation du bus I2C (SDA = GPIO 4, SCL = GPIO 16)
    Wire.begin(4, 16);

    // Initialisation de l'écran et activation du rétroéclairage
    lcd.init();
    lcd.backlight();

    // Affichage d'un message de démarrage
    lcd.setCursor(0, 0);
    lcd.print("System ready");
    delay(1500);

    lcd.clear();
}

void LcdManager::show(float temperature, float humidity) {

    // Rafraîchissement de l'affichage avec les dernières mesures
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature, 1);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Hum : ");
    lcd.print(humidity, 1);
    lcd.print(" %");
}
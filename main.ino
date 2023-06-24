#include "Arduino.h"
#include "rfid/rfid.h"
#include "database/database.h"

const int LED_PIN = 13;
const int RANDOM_SEED_PIN = 0;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    Serial.begin(9600);

    SPI.begin();
    mfrc522.PCD_Init();

    randomSeed(analogRead(RANDOM_SEED_PIN));

    databaseConfiguration();
}

void loop() {
    validateCard();
}

#include "rfid.h"
#include "../database/database.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);

void validateCard() {
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return;
    }

    if (!mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    String cardId = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    Card card = selectByCardId(cardId)

    if (card != nullptr) {
        Serial.println(
                "[INFO] Card with id: " + cardId +
                " is " +
                (card->status == true ? "active" : "inactive"));

        delay(1000)
    }

    delete card
}

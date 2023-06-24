#ifndef RFID_H
#define RFID_H

#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

extern MFRC522 mfrc522;

void validateCard();

#endif

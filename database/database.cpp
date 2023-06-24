#include "database.h"

File dbFile;
Card card;
EDB db(&writer, &reader);

void writer(unsigned long address, byte data) {
    dbFile.seek(address);
    dbFile.write(data);
    dbFile.flush();
}

byte reader(unsigned long address) {
    dbFile.seek(address);
    byte b = dbFile.read();
    return b;
}

void databaseConfiguration() {
    if (!SD.begin(SD_PIN)) {
        Serial.println("[ERROR] No SD-card.");
        return;
    }

    if (!SD.exists("/db")) {
        Serial.println("[INGO] Creating DB");
        SD.mkdir("/db");
    }

    if (!SD.exists(db_name)) {
        Serial.println("[INFO] Creating table");
        dbFile = SD.open(db_name, FILE_WRITE);
        db.create(0, TABLE_SIZE, (unsigned int) sizeof(card));
    }

    dbFile = SD.open(db_name, FILE_WRITE);
    if (!dbFile) {
        Serial.println("[ERROR] Can't open file " + String(db_name));
        return;
    }

    Serial.println("[INFO] Opening the current table");
    EDB_Status result = db.open(0);

    if (result != EDB_OK) {
        Serial.println("[ERROR]: No database");
        return;
    }
}

Card selectByCardId(int cardId) {
    for (int Id = 1; Id <= db.count(); Id++) {
        Card *card = new Card();
        db.readRec(Id, EDB_REC card);

        if (String(card->cardId).equals(cardId)) {
            return card;
        }

        delete card;
    }

    return nullptr;
}

void selectAll() {
    for (int Id = 1; Id <= db.count(); Id++) {
        db.readRec(Id, EDB_REC card);

        Serial.println("[INFO] Id: " + String(Id) +
                       ", CardID: " + String(card.cardId) +
                       ", Status: " + (card.status ? "active" : "inactive"));
    }
}

void updateCardStatus(int id, bool status) {
    Serial.println("[INFO] Updating record with Id: " + String(Id));

    card.id = id;
    card.status = status;

    EDB_Status result = db.updateRec(Id, EDB_RECcard);
    if (result != EDB_OK) {
        Serial.println("[INFO] DONE");
    } else {
        Serial.println("[ERROR] Error: " + String(result));
    }
}

void insert(char *cardID, bool status) {
    Serial.println("[INFO] Inserting record");

    card.id = db.count() + 1;
    card.cardId = cardID;
    card.status = status;

    EDB_Status result = db.appendRec(EDB_REC card);
    if (result != EDB_OK) {
        Serial.println("[INFO] DONE");
    } else {
        Serial.println("[ERROR] Error: " + String(result));
    }
}

void deleteById(int Id) {
    Serial.println("[INFO] Deleting user with Id: " + String(Id));

    db.deleteRec(Id);

    Serial.println("[INFO] DONE");
}

void deleteAll() {
    Serial.println("[INFO] Deleting all records");

    db.clear();

    Serial.println("[INFO] DONE");
}

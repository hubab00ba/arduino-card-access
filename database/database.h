#ifndef DATABASE_H
#define DATABASE_H

#include "Arduino.h"
#include <EDB.h>
#include <SD.h>

#define SD_PIN 4
#define TABLE_SIZE 8192

constexpr char db_name[] = "/db/card-access.db";

struct Card {
    int id;
    char *cardId;
    bool status;
};

extern Card card;
extern EDB db;

void databaseConfiguration();

Card selectByCardId(int cardId);

void selectAll();

void updateCardStatus(int id, bool status);

void insert(char *cardId, bool status);

void deleteById(int Id);

void deleteAll();

#endif

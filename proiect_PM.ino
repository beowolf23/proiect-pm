#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9     // Pinul de reset al modulului RC522
#define SS_PIN    10    // Pinul slave select al modulului RC522

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crearea obiectului MFRC522

void setup() {
  pinMode(8, OUTPUT);

  Serial.begin(9600);  // Inițializarea comunicării seriale
  SPI.begin();         // Inițializarea SPI
  mfrc522.PCD_Init();  // Inițializarea modulului RC522
  Serial.println("Asteptare card...");
}

void loop() {

  // Detectarea cardului RFID
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Afișarea ID-ului cardului
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
    Serial.print("Card detectat: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    mfrc522.PICC_HaltA();  // Oprește comunicarea cu cardul
  }
}
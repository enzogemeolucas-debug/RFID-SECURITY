#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define BUZZER 7

MFRC522 rfid(SS_PIN, RST_PIN);
Servo myservo;

void setup() {
  Serial.begin(9600);

  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  SPI.begin();

  rfid.PCD_Init();
  myservo.attach(3);
  myservo.write(0);


}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent() ) {
    return;
  }
  if (! rfid.PICC_ReadCardSerial()) {
    return;
  }
  for (byte i = 0; i < rfid.uid.size; i++) {
  Serial.print(rfid.uid.uidByte[i], HEX);
  Serial.print(" ");
}
  Serial.println();

  //you can change this to your RFID UID card or tag 
  if (rfid.uid.uidByte[0] == 0x7B &&
    rfid.uid.uidByte[1] == 0x19 &&
    rfid.uid.uidByte[2] == 0xBE &&
    rfid.uid.uidByte[3] == 0x06) {
      Serial.println("Access granted!");
      myservo.write(90);
      digitalWrite(BUZZER, HIGH);
      delay(100);
      digitalWrite(BUZZER, LOW);
      delay(100);
      digitalWrite(BUZZER, HIGH);
      delay(100);
      digitalWrite(BUZZER, LOW);
    
      delay(3000);
      myservo.write(0);
    } else {
      Serial.println("Access denied!");
      digitalWrite(BUZZER, HIGH);
      delay(500);
      digitalWrite(BUZZER, LOW);
      myservo.write(0);
      delay(3000);
    }
}
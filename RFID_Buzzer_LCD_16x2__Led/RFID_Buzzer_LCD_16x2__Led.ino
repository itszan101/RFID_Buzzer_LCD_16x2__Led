#include <PN532.h>
#include <PN532_HSU.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
PN532_HSU pn532hsu(Serial);
PN532 nfc(pn532hsu);


int tom1 = 8;
int tom2 = 9;
int i = 0;
int ii = 0;
int buttonval;
int buttonState;
int buzzer = A0;
int ledPin = 9;

void setup()
{
  lcd.begin(16,2);
  Serial.begin(115200);
  pinMode(tom1, INPUT);
  pinMode(tom2, INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(ledPin,OUTPUT);
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Didn't fix PN532 board");
    while (1);
  }
  Serial.print("Found chip PN5");
  Serial.println( (versiondata>>24) & 0xFF, HEX);
  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig();
  Serial.println("Waiting for an ISO14443A card");
}

void loop()
{
  buttonval = digitalRead(tom1);     
if (buttonval != buttonState) {         
  if (buttonval == LOW) {               
    i++;               
    Serial.println(i); //this is were the code for input/output code for the pins would go(like turning on an led etc).
    if (i >= 4) {
      i = 0;
    }
  }
}
buttonState = buttonval;
switch (i) {
  case 1:
    pingActive();
    break;
  case 2:
    pingActive2();
    break;
  case 3:
    pingActive3();
    break;
  case 4:
    pingActive();
    break;
  }
}

  void pingActive()
  {
    
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0,};
  uint8_t uidLength;

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success) {
    for (uint8_t i=0; i<uidLength; i++){
      Serial.print(" 0x");
      Serial.print(uid[i], HEX);
    }
    if((uid[0]==0x62)&&(uid[1]==0x7)&&(uid[2]==0xB0)&&(uid[3]==0x5E)){
      digitalWrite(ledPin,LOW);
      digitalWrite(buzzer,HIGH);
      delay(75);
      digitalWrite(buzzer,LOW);
      delay(75);
      digitalWrite(buzzer,HIGH);
      delay(75);
      digitalWrite(buzzer,LOW);
      delay(75);
      Serial.print(" Deni Saputra ");
      lcd.setCursor(1,0);
      lcd.print(" Deni Saputra ");
    }
    else if((uid[0]==0x96)&&(uid[1]==0xD8)&&(uid[2]==0xED)&&(uid[3]==0x48)){
      digitalWrite(ledPin,LOW);
      digitalWrite(buzzer,HIGH);
      delay(75);
      digitalWrite(buzzer,LOW);
      delay(75);
      digitalWrite(buzzer,HIGH);
      delay(75);
      digitalWrite(buzzer,LOW);
      delay(75);
      Serial.print(" Sampel ");
      lcd.setCursor(1,0);
      lcd.print(" RFID Sampel");
    }
    else if((uid[0]==0xF2)&&(uid[1]==0xD7)&&(uid[2]==0x96)&&(uid[3]==0x5E)){
      digitalWrite(ledPin,LOW);
      digitalWrite(buzzer,HIGH);
      delay(75);
      digitalWrite(buzzer,LOW);
      delay(75);
      digitalWrite(buzzer,HIGH);
      delay(75);
      digitalWrite(buzzer,LOW);
      delay(75);
      Serial.print(" Ahmad Fauzan ");
      lcd.setCursor(1,0);
      lcd.print("Ahmad Fauzan");
    }
    else{
      digitalWrite(buzzer,HIGH);
      digitalWrite(ledPin,HIGH);
      delay(1000);
      digitalWrite(buzzer,LOW);
      digitalWrite(ledPin,LOW);
      delay(1000);
      digitalWrite(buzzer,HIGH);
      digitalWrite(ledPin,HIGH);
      delay(1000);
      digitalWrite(buzzer,LOW);
      digitalWrite(ledPin,LOW);
      delay(1000);
      Serial.print(" Unknown Card ");
      lcd.setCursor(1,0);
      lcd.print(" Unknown Card ");
    }
    delay(1000);
    Serial.println();
  }
  else{
    Serial.println("Menunggu kartu...");
    lcd.setCursor(0,0);
    lcd.print("                 ");
  }
  digitalWrite(ledPin,LOW);
  }

void pingActive2()
{
  Serial.println();
  lcd.clear();
}

void pingActive3()
{
       digitalWrite(ledPin,HIGH);
      delay(75);
      digitalWrite(ledPin,LOW);
      delay(75);
      digitalWrite(ledPin,HIGH);
      delay(75);
      digitalWrite(ledPin,LOW);
      delay(75);
}

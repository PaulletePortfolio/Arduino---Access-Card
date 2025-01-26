#include <SPI.h>
#include <RFID.h>
#include <LiquidCrystal.h>

#define SDA_DIO 9
#define RESET_DIO 8
int BUZZER_PIN = 7;
int LED_VERDE_PIN = 11;
int LED_VERMELHO_PIN = 6;

RFID RC522(SDA_DIO, RESET_DIO); 
LiquidCrystal lcd(12, 13, 5, 4, 3, 2);

const String validUID = "UID VÁLIDO";  

void setup() {
  Serial.begin(9600);
  SPI.begin();
  RC522.init();
  lcd.begin(16, 2);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_VERDE_PIN, OUTPUT);
  pinMode(LED_VERMELHO_PIN, OUTPUT);
}

void loop() {
  if (RC522.isCard()) {
    RC522.readCardSerial();
    Serial.println("Card detected:");

    String idRFID = getID(RC522.serNum);
    Serial.print("ID: ");
    Serial.println(idRFID);

    

    if (idRFID == "DB16631BB5") {
      Serial.println("Permitido");
      acessoPermitido();
    } else {
      Serial.println("Negado");
      acessoNegado();
    }

    delay(2000);
  }
}

String getID(unsigned char serNum[5]) {
  String returnable = "";
  for (int i = 0; i < 5; i++) { 
    returnable += String(serNum[i] < 0x10 ? "0" : "");
    returnable += String(serNum[i], HEX);
  }
  returnable.toUpperCase();
  return returnable;
}

void acessoPermitido() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Acesso Permitido");
  digitalWrite(LED_VERDE_PIN, HIGH);
  digitalWrite(LED_VERMELHO_PIN, LOW);
  tone(BUZZER_PIN, 1000, 200); 
  delay(200);
  tone(BUZZER_PIN, 1500, 200);
  delay(200);
  digitalWrite(LED_VERDE_PIN, LOW);
}

void acessoNegado() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Acesso Negado");
  digitalWrite(LED_VERDE_PIN, LOW);
  digitalWrite(LED_VERMELHO_PIN, HIGH);
  tone(BUZZER_PIN, 500, 400);  
  delay(400);
  digitalWrite(LED_VERMELHO_PIN, LOW);
}

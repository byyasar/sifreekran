#include <Wire.h> // I2C kütüphanesi
#include <LiquidCrystal_I2C.h> // I2C LCD kütüphanesi
#include <Keypad.h> // Keypad kütüphanesi
#include "lcd.h" // LCD işlemlerini içeren dosya
#include "mykeypad.h" // Keypad işlemlerini içeren dosya
#include "password.h" // Şifre işlemlerini içeren dosya

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C adresi 0x27 olan 20x4 LCD tanımlaması

const byte ROWS = 4; // Keypad satır sayısı
const byte COLS = 4; // Keypad sütun sayısı
char keys[ROWS][COLS] = { // Keypad tuş dizilimi
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Keypad satır pinleri
byte colPins[COLS] = {5, 4, 3, 2}; // Keypad sütun pinleri

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // Keypad tanımlaması

unsigned long lastActivityTime; // Son aktivite zamanı
const unsigned long timeoutDuration = 10000; // 10 saniye zaman aşımı süresi
bool inPasswordEntryMode = false; // Şifre giriş modu durumu

void setup() {
  lcdInit(); // LCD'yi başlat
  showWelcomeScreen(); // Hoş geldiniz ekranını göster
  lastActivityTime = millis(); // Son aktivite zamanını güncelle
}

void loop() {
  char key = keypad.getKey(); // Tuş durumu oku

  if (key) {
    lastActivityTime = millis(); // Tuşa basıldıysa son aktivite zamanını güncelle
    handleKey(key); // Tuşu işle
  }

  if (inPasswordEntryMode) {
    unsigned long timeLeft = (timeoutDuration - (millis() - lastActivityTime)) / 1000; // Kalan süreyi hesapla
    if (timeLeft > 0) {
      showCountdown(timeLeft); // Kalan süreyi göster
    } else {
      showWelcomeScreen(); // Zaman aşımı olduysa hoş geldiniz ekranını göster
    }
  }
}

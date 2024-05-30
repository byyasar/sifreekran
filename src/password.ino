#include "password.h"
#include "lcd.h"

extern LiquidCrystal_I2C lcd; // LCD nesnesi

char enteredPassword[7]; // Girilen şifre için dizi
byte passwordIndex = 0; // Şifre dizisinin indeksi
const char correctPassword[7] = "123456"; // Doğru şifre

extern bool inPasswordEntryMode; // Şifre giriş modu durumu

void verifyPassword() {
  enteredPassword[6] = '\0'; // Şifre dizisini null ile sonlandır
  if (strcmp(enteredPassword, correctPassword) == 0) {
    lcd.clear(); // LCD'yi temizle
    lcd.setCursor(0, 1); // İkinci satıra git
    lcd.print("Sifre dogru!"); // "Şifre doğru!" yazısını yaz
  } else {
    lcd.clear(); // LCD'yi temizle
    lcd.setCursor(0, 1); // İkinci satıra git
    lcd.print("Sifre yanlis!"); // "Şifre yanlış!" yazısını yaz
  }
  delay(2000); // 2 saniye bekle
  showWelcomeScreen(); // Hoş geldiniz ekranını göster
}

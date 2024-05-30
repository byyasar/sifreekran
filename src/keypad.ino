#include "mykeypad.h"
#include "password.h" // Şifre işlemlerini içeren dosya
#include "lcd.h" // LCD işlemlerini içeren dosya

extern const byte ROWS; // Keypad satır sayısı
extern const byte COLS; // Keypad sütun sayısı
extern char keys[ROWS][COLS]; // Keypad tuş dizilimi
extern byte rowPins[ROWS]; // Keypad satır pinleri
extern byte colPins[COLS]; // Keypad sütun pinleri
extern Keypad keypad; // Keypad nesnesi

void handleKey(char key) {
  if (!inPasswordEntryMode) {
    if (key == '#') {
      inPasswordEntryMode = true; // Şifre giriş moduna geç
      showPasswordScreen(); // Şifre giriş ekranını göster
    }
  } else {
    switch (key) {
      case 'C':
        if (passwordIndex > 0) {
          passwordIndex--; // Şifre dizisi indeksini azalt
          lcd.setCursor(7 + passwordIndex, 1); // Şifre konumuna git (orta hizalama için 7 ekledik)
          lcd.print("_"); // Mevcut karakteri alt çizgiyle değiştir
        }
        break;
      case 'D':
        if (passwordIndex == 6) {
          verifyPassword(); // Şifreyi doğrula
        }
        break;
      default:
        if (passwordIndex < 6 && isDigit(key)) {
          enteredPassword[passwordIndex] = key; // Girilen tuşu şifre dizisine ekle
          lcd.setCursor(7 + passwordIndex, 1); // Şifre konumuna git (orta hizalama için 7 ekledik)
          lcd.print(key); // Girilen tuşu yaz
          delay(250); // 500ms bekle
          lcd.setCursor(7 + passwordIndex, 1); // Şifre konumuna geri git
          lcd.print("*"); // Karakteri yıldız ile değiştir
          passwordIndex++; // Şifre dizisi indeksini artır
        }
        break;
    }
  }
}

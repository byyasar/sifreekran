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
          lcd.setCursor(passwordIndex, 2); // Şifre konumuna git
          lcd.print(" "); // Mevcut karakteri sil
          lcd.setCursor(passwordIndex, 2); // Şifre konumuna geri git
        }
        break;
      case '*':
        if (passwordIndex == 6) {
          verifyPassword(); // Şifreyi doğrula
        }
        break;
      default:
        if (passwordIndex < 6 && isDigit(key)) {
          enteredPassword[passwordIndex] = key; // Girilen tuşu şifre dizisine ekle
          lcd.setCursor(passwordIndex, 2); // Şifre konumuna git
          lcd.print(key); // Girilen tuşu yaz
          delay(500); // 500ms bekle
          lcd.setCursor(passwordIndex, 2); // Şifre konumuna geri git
          lcd.print("*"); // Karakteri yıldız ile değiştir
          passwordIndex++; // Şifre dizisi indeksini artır
        }
        break;
    }
  }
}

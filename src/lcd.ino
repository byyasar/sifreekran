#include "lcd.h"
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;    // LCD nesnesi
extern bool inPasswordEntryMode; // Şifre giriş modu durumu

// Custom characters for clock icon
uint8_t saatChar[4][8] = {{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1F}, {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1F}, {0xC, 0x6, 0x3, 0x1, 0x3, 0x6, 0xC, 0x1F}, {0x6, 0xC, 0x18, 0x10, 0x18, 0xC, 0x6, 0x1F}};

void lcdInit()
{
    lcd.init();      // LCD'yi başlat
    lcd.backlight(); // LCD arka ışığını aç
    for (int i = 0; i < 4; i++)
    {
        lcd.createChar(i, saatChar[i]); // Özel karakterleri oluştur
    }
}

void showWelcomeScreen()
{
    lcd.clear();                  // LCD'yi temizle
    lcd.setCursor(0, 0);          // İlk satıra git
    lcd.print("Hosgeldiniz");     // "Hoşgeldiniz" yazısını yaz
    lcd.setCursor(0, 1);          // İkinci satıra git
    lcd.print("# ile sifre gir"); // "# ile şifre gir" yazısını yaz
    passwordIndex = 0;            // Şifre dizisi indeksini sıfırla
    inPasswordEntryMode = false;  // Şifre giriş modunu kapat
}

void showPasswordScreen()
{
    lcd.clear();                     // LCD'yi temizle
    lcd.setCursor(0, 0);             // İlk satıra git
    lcd.print("Sifrenizi giriniz:"); // "Şifrenizi giriniz:" yazısını yaz
    lcd.setCursor(0, 2);             // Üçüncü satıra git
    inPasswordEntryMode = true;      // Şifre giriş modunu aç
}

void showCountdown(unsigned long seconds)
{
    lcd.setCursor(16, 2); // Display at the right of the 4th line
    for (int i = 0; i < 2; i++)
    {
        lcd.write(i); // Saat ikonunu göster
    }
    lcd.setCursor(16, 3); // Display at the right of the 4th line
    for (int i = 2; i < 4; i++)
    {
        lcd.write(i); // Display clock icon
    }
    lcd.setCursor(18, 3); // Dördüncü satırın en sağına git
    if (seconds < 10)
    {
        lcd.print(" "); // Tek haneli sayıların hizalaması için boşluk ekle
    }
    lcd.print(seconds); // Kalan saniyeyi yazdır
}

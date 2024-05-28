#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const byte ROWS = 4; // Keypad rows
const byte COLS = 4; // Keypad columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Connect keypad ROW0, ROW1, ROW2, ROW3 to these pins
byte colPins[COLS] = {5, 4, 3, 2}; // Connect keypad COL0, COL1, COL2, COL3 to these pins

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char enteredPassword[7]; // Password array
byte passwordIndex = 0;
const char correctPassword[7] = "123456"; // Example password
unsigned long lastActivityTime;
const unsigned long timeoutDuration = 10500; // 10 seconds
bool inPasswordEntryMode = false;

// Custom characters for clock icon
uint8_t saatChar[4][8] = {{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1F}, {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1F}, {0xC, 0x6, 0x3, 0x1, 0x3, 0x6, 0xC, 0x1F}, {0x6, 0xC, 0x18, 0x10, 0x18, 0xC, 0x6, 0x1F}};

void setup()
{
  lcd.init();
  lcd.backlight();
  for (int i = 0; i < 4; i++)
  {
    lcd.createChar(i, saatChar[i]); // Create custom characters
  }
  showWelcomeScreen();
  lastActivityTime = millis();
}

void loop()
{
  char key = keypad.getKey();

  if (key)
  {
    lastActivityTime = millis();
    handleKey(key);
  }

  if (inPasswordEntryMode)
  {
    unsigned long timeLeft = (timeoutDuration - (millis() - lastActivityTime)) / 1000;
    if (timeLeft > 0)
    {
      showCountdown(timeLeft);
    }
    else
    {
      showWelcomeScreen();
    }
  }
}

void showWelcomeScreen()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hosgeldiniz");
  lcd.setCursor(0, 1);
  lcd.print("# ile sifre gir");
  passwordIndex = 0;
  inPasswordEntryMode = false;
}

void showPasswordScreen()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sifrenizi giriniz:");
  lcd.setCursor(0, 2);
  inPasswordEntryMode = true;
}

void showCountdown(unsigned long seconds)
{
  lcd.setCursor(16, 2); // Display at the right of the 4th line
  for (int i = 0; i < 2; i++)
  {
    lcd.write(i); // Display clock icon
  }
  lcd.setCursor(16, 3); // Display at the right of the 4th line
  for (int i = 2; i < 4; i++)
  {
    lcd.write(i); // Display clock icon
  }
  lcd.setCursor(18, 3);
  if (seconds < 10)
  {
    lcd.print(" "); // Add a space for single-digit alignment
  }
  lcd.print(seconds);
}

void handleKey(char key)
{
  if (!inPasswordEntryMode)
  {
    if (key == '#')
    {
      inPasswordEntryMode = true;
      showPasswordScreen();
    }
  }
  else
  {
    switch (key)
    {
    case 'C':
      if (passwordIndex > 0)
      {
        passwordIndex--;
        lcd.setCursor(passwordIndex, 2);
        lcd.print(" ");
        lcd.setCursor(passwordIndex, 2);
      }
      break;
    case '*':
      if (passwordIndex == 6)
      {
        verifyPassword();
      }
      break;
    default:
      if (passwordIndex < 6 && isDigit(key))
      {
        enteredPassword[passwordIndex] = key;
        lcd.setCursor(passwordIndex, 2);
        lcd.print(key);
        delay(500);
        lcd.setCursor(passwordIndex, 2);
        lcd.print("*");
        passwordIndex++;
      }
      break;
    }
  }
}

void verifyPassword()
{
  enteredPassword[6] = '\0'; // Null-terminate the string
  if (strcmp(enteredPassword, correctPassword) == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Sifre dogru!");
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Sifre yanlis!");
  }
  delay(2000);
  showWelcomeScreen();
}

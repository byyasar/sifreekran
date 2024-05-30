#ifndef KEYPAD_H
#define KEYPAD_H

#include <Keypad.h>

extern const byte ROWS;
extern const byte COLS;
extern char keys[ROWS][COLS];
extern byte rowPins[ROWS];
extern byte colPins[COLS];
extern Keypad keypad;

void handleKey(char key);

#endif

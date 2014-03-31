#include "Arduino.h"

extern "C" {
    #include "lcd.hh"
}

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void lcd_begin (int a, int b) {
    lcd.begin(a, b);
}

void lcd_setCursor (int x, int y) {
    lcd.setCursor(x, y);
}

void lcd_write (char c) {
    lcd.write(c);
}

void lcd_print (int v) {
    lcd.print(v);
}

/*
Create character using creatChar function
*/
 
#include <LiquidCrystal.h> // Sample using LiquidCrystal library

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //select pins used on LCD panel

int y = 250; // set animation speed (milliseconds)
int x = 100; // second animation speed (milliseconds)

void setup() {
  lcd.begin(16, 2); // initialize lcd.begin(columns, rows)
  lcd.clear();
  lcd.setCursor(6,0); // bring cursor to (column, row)
  lcd.print("PACMAN");
};

void loop() { // patern is display then delay
  pac0();
  delay(y);
  pac1();
  delay(x);
  pac2();
  delay(y);
  pac3();
  delay(x);
  pac4();
  delay(y);
  pac5();
  delay(x);
  pac6();
  delay(y);
  pac7();
  delay(x);
  pac8();
  delay(y);
  pac9();
  delay(x);
  pac10();
  delay(y);
  pac11();
  delay(x);
  pac12();
  delay(y);
  pac13();
  delay(y);
  pac12();
  delay(y);
  pac13();
  delay(y);
  pac12();
  delay(y);
  pac13();
  delay(y);
};

void pac0() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman0[8] = { 
  B00000,
  B01111,
  B11110,
  B11100,
  B11110,
  B01111,
  B00000,
};
  byte food[8] = {
  B00000,
  B00000,
  B00000,
  B01100,
  B01100,
  B00000,
  B00000,
};
  byte cherry[8] = {
  B00100,
  B00110,
  B00101,
  B00100,
  B01110,
  B01110,
  B01110,
  B00000,
};
  byte ghost0[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B10101,
  B00000,
};
lcd.createChar(0,pacman0);
lcd.createChar(1,food);
lcd.createChar(2,cherry);
lcd.createChar(3,ghost0);
lcd.setCursor(1,2);
lcd.write(byte(0));
lcd.setCursor(2,2);
lcd.write(byte(1));
lcd.setCursor(3,2);
lcd.write(byte(1));
lcd.setCursor(4,2);
lcd.write(byte(1));
lcd.setCursor(5,2);
lcd.write(byte(1));
lcd.setCursor(6,2);
lcd.write(byte(2));
lcd.setCursor(8,2);
lcd.write(byte(3));
}

void pac1() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman1[8] = { 
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000,
};
  byte food[8] = {
  B00000,
  B00000,
  B00000,
  B01100,
  B01100,
  B00000,
  B00000,
};
  byte cherry[8] = {
  B00100,
  B00110,
  B00101,
  B00100,
  B01110,
  B01110,
  B01110,
  B00000,
};
  byte ghost1[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B01010,
  B00000,
};
byte pacclear[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
lcd.createChar(0,pacman1);
lcd.createChar(1,food);
lcd.createChar(2,cherry);
lcd.createChar(3,ghost1);
lcd.createChar(4,pacclear);
lcd.setCursor(1,2);
lcd.write(byte(4));
lcd.setCursor(2,2);
lcd.write(byte(0));
lcd.setCursor(3,2);
lcd.write(byte(1));
lcd.setCursor(4,2);
lcd.write(byte(1));
lcd.setCursor(5,2);
lcd.write(byte(1));
lcd.setCursor(6,2);
lcd.write(byte(2));
lcd.setCursor(8,2);
lcd.write(byte(3));
}

void pac2() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman0[8] = { 
  B00000,
  B01111,
  B11110,
  B11100,
  B11110,
  B01111,
  B00000,
};
  byte food[8] = {
  B00000,
  B00000,
  B00000,
  B01100,
  B01100,
  B00000,
  B00000,
};
  byte cherry[8] = {
  B00100,
  B00110,
  B00101,
  B00100,
  B01110,
  B01110,
  B01110,
  B00000,
};
  byte ghost1[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B01010,
  B00000,
};
lcd.createChar(0,pacman0);
lcd.createChar(1,food);
lcd.createChar(2,cherry);
lcd.createChar(3,ghost1);
lcd.setCursor(2,2);
lcd.write(byte(0));
lcd.setCursor(3,2);
lcd.write(byte(1));
lcd.setCursor(4,2);
lcd.write(byte(1));
lcd.setCursor(5,2);
lcd.write(byte(1));
lcd.setCursor(6,2);
lcd.write(byte(2));
lcd.setCursor(8,2);
lcd.write(byte(3));
}

void pac3() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman1[8] = { 
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000,
};
  byte food[8] = {
  B00000,
  B00000,
  B00000,
  B01100,
  B01100,
  B00000,
  B00000,
};
  byte cherry[8] = {
  B00100,
  B00110,
  B00101,
  B00100,
  B01110,
  B01110,
  B01110,
  B00000,
};
  byte ghost0[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B10101,
  B00000,
};
byte pacclear[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
lcd.createChar(0,pacman1);
lcd.createChar(1,food);
lcd.createChar(2,cherry);
lcd.createChar(3,ghost0);
lcd.createChar(4,pacclear);
lcd.setCursor(2,2);
lcd.write(byte(4));
lcd.setCursor(3,2);
lcd.write(byte(0));
lcd.setCursor(4,2);
lcd.write(byte(1));
lcd.setCursor(5,2);
lcd.write(byte(1));
lcd.setCursor(6,2);
lcd.write(byte(2));
lcd.setCursor(8,2);
lcd.write(byte(3));
}

void pac4() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman0[8] = { 
  B00000,
  B01111,
  B11110,
  B11100,
  B11110,
  B01111,
  B00000,
};
  byte food[8] = {
  B00000,
  B00000,
  B00000,
  B01100,
  B01100,
  B00000,
  B00000,
};
  byte cherry[8] = {
  B00100,
  B00110,
  B00101,
  B00100,
  B01110,
  B01110,
  B01110,
  B00000,
};
  byte ghost0[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B10101,
  B00000,
};
lcd.createChar(0,pacman0);
lcd.createChar(1,food);
lcd.createChar(2,cherry);
lcd.createChar(3,ghost0);
lcd.setCursor(3,2);
lcd.write(byte(0));
lcd.setCursor(4,2);
lcd.write(byte(1));
lcd.setCursor(5,2);
lcd.write(byte(1));
lcd.setCursor(6,2);
lcd.write(byte(2));
lcd.setCursor(8,2);
lcd.write(byte(3));
}

void pac5() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman1[8] = { 
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000,
};
  byte food[8] = {
  B00000,
  B00000,
  B00000,
  B01100,
  B01100,
  B00000,
  B00000,
};
  byte cherry[8] = {
  B00100,
  B00110,
  B00101,
  B00100,
  B01110,
  B01110,
  B01110,
  B00000,
};
  byte ghost1[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B01010,
  B00000,
};
byte pacclear[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
lcd.createChar(0,pacman1);
lcd.createChar(1,food);
lcd.createChar(2,cherry);
lcd.createChar(3,ghost1);
lcd.createChar(4,pacclear);
lcd.setCursor(3,2);
lcd.write(byte(4));
lcd.setCursor(4,2);
lcd.write(byte(0));
lcd.setCursor(5,2);
lcd.write(byte(1));
lcd.setCursor(6,2);
lcd.write(byte(2));
lcd.setCursor(8,2);
lcd.write(byte(3));
}

void pac6() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman0[8] = { 
  B00000,
  B01111,
  B11110,
  B11100,
  B11110,
  B01111,
  B00000,
};
  byte food[8] = {
  B00000,
  B00000,
  B00000,
  B01100,
  B01100,
  B00000,
  B00000,
};
  byte cherry[8] = {
  B00100,
  B00110,
  B00101,
  B00100,
  B01110,
  B01110,
  B01110,
  B00000,
};
  byte ghost1[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B01010,
  B00000,
};
lcd.createChar(0,pacman0);
lcd.createChar(1,food);
lcd.createChar(2,cherry);
lcd.createChar(3,ghost1);
lcd.setCursor(4,2);
lcd.write(byte(0));
lcd.setCursor(5,2);
lcd.write(byte(1));
lcd.setCursor(6,2);
lcd.write(byte(2));
lcd.setCursor(8,2);
lcd.write(byte(3));
}

void pac7() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman1[8] = { 
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000,
};
  byte cherry[8] = {
  B00100,
  B00110,
  B00101,
  B00100,
  B01110,
  B01110,
  B01110,
  B00000,
};
  byte ghost0[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B10101,
  B00000,
};
byte pacclear[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
lcd.createChar(0,pacman1);
lcd.createChar(1,cherry);
lcd.createChar(2,ghost0);
lcd.createChar(3,pacclear);
lcd.setCursor(4,2);
lcd.write(byte(3));
lcd.setCursor(5,2);
lcd.write(byte(0));
lcd.setCursor(6,2);
lcd.write(byte(1));
lcd.setCursor(8,2);
lcd.write(byte(2));
}

void pac8() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman0[8] = { 
  B00000,
  B01111,
  B11110,
  B11100,
  B11110,
  B01111,
  B00000,
};
  byte cherry[8] = {
  B00100,
  B00110,
  B00101,
  B00100,
  B01110,
  B01110,
  B01110,
  B00000,
};
  byte ghost0[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B10101,
  B00000,
};
lcd.createChar(0,pacman0);
lcd.createChar(1,cherry);
lcd.createChar(2,ghost0);
lcd.setCursor(5,2);
lcd.write(byte(0));
lcd.setCursor(6,2);
lcd.write(byte(1));
lcd.setCursor(8,2);
lcd.write(byte(2));
}

void pac9() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman1[8] = { 
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000,
};
  byte ghost1[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B01010,
  B00000,
};
byte pacclear[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
lcd.createChar(0,pacman1);
lcd.createChar(1,ghost1);
lcd.createChar(2,pacclear);
lcd.setCursor(5,2);
lcd.write(byte(2));
lcd.setCursor(6,2);
lcd.write(byte(0));
lcd.setCursor(8,2);
lcd.write(byte(1));
}

void pac10() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman0[8] = { 
  B00000,
  B01111,
  B11110,
  B11100,
  B11110,
  B01111,
  B00000,
};
  byte ghost1[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B01010,
  B00000,
};
lcd.createChar(0,pacman0);
lcd.createChar(1,ghost1);
lcd.setCursor(6,2);
lcd.write(byte(0));
lcd.setCursor(8,2);
lcd.write(byte(1));
}

void pac11() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman1[8] = { 
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000,
};
  byte ghost1[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B01010,
  B00000,
};
byte pacclear[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
lcd.createChar(0,pacman1);
lcd.createChar(1,ghost1);
lcd.createChar(2,pacclear);
lcd.setCursor(6,2);
lcd.write(byte(2));
lcd.setCursor(7,2);
lcd.write(byte(0));
lcd.setCursor(8,2);
lcd.write(byte(1));
}

void pac12() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman0[8] = { 
  B00000,
  B01111,
  B11110,
  B11100,
  B11110,
  B01111,
  B00000,
};
  byte ghost2[8] = {
  B11111,
  B10001,
  B00000,
  B01010,
  B00000,
  B01010,
  B11111,
};
lcd.createChar(0,pacman0);
lcd.createChar(1,ghost2);
lcd.setCursor(7,2);
lcd.write(byte(0));
lcd.setCursor(8,2);
lcd.write(byte(1));
}

void pac13() { //array of byes 5x7 - setting to 1 turns on (comma between each byte)
  byte pacman0[8] = { 
  B00000,
  B01111,
  B11110,
  B11100,
  B11110,
  B01111,
  B00000,
};
  byte ghost3[8] = {
  B11111,
  B10001,
  B00000,
  B01010,
  B00000,
  B10101,
  B11111,
};
lcd.createChar(0,pacman0);
lcd.createChar(1,ghost3);
lcd.setCursor(7,2);
lcd.write(byte(0));
lcd.setCursor(8,2);
lcd.write(byte(1));
}


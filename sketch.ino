#include <algorithm>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

typedef struct Eye{
  int xo ; //27
  int xi ; //55
};
Eye right = { 79, 107 };
Eye left = { 20, 48 };

int eyeYo = 17 ;
int eyeYi = 44 ;
int eyeWidth = 28 ;
bool isOpen = false ;

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

// func def
void bukaMata() ; //setelah kedip 100%
void kedip() ; //mungkin setelah buka mata 80%
//polinomial sampling with random

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay() ;
}

void loop() {
  //chooseAction(); 
  bukaMata() ;
  delay(2000) ;
  kedip() ;
}

void chooseAction() {
  int act = 1 ;
  switch (act) {
    case 0: bukaMata() ;
      break;
    case 1: kedip() ;
      break; 
    default: break;
  }
}

void bukaMata() { 
  for (int j = eyeYo; j < eyeYi; j++) {
    oled.drawLine(left.xo, j, left.xi, j, WHITE) ; 
    oled.drawLine(right.xo, j, right.xi, j, WHITE) ;
    if (j % 15 == 0) oled.display();
  }
  oled.display();
  isOpen = true ;
}

void kedip() {
  for (int j = eyeYi; j >= eyeYo; j--) {
    oled.drawLine(left.xo, j, left.xi, j, NULL) ; 
    oled.drawLine(right.xo, j, right.xi, j, NULL) ;
    if (j % 15 == 0) oled.display();
  }
  oled.display();
  isOpen = false ;
}

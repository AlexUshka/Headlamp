
#define BTN1 7				// кнопка подключена сюда (BTN_PIN --- КНОПКА --- GND)
#include "GyverButton.h"
GButton butt1(BTN1);

void setup() {
  Serial.begin(9600);
}

void loop() {
  butt1.tick();

  
   // проверяем одиночный клик
  if (butt1.isSingle()) Serial.println("Single1");

   // проверка на двойной клик
  if (butt1.isDouble()) Serial.println("Double1");
  
   // проверка на удержание
  if (butt1.isHold()) Serial.println("Holded");      
}

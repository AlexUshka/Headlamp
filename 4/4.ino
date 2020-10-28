#include "OneButton.h"
boolean butt_flag = 0;
int ledState = LOW;
long previousMillis = 0;
long interval = 500;
unsigned long last_press;
unsigned long timerbut;
OneButton button(3, true);


void setup() {
unsigned long last_press;
unsigned long previousTime = millis();

Serial.begin(9600);
pinMode(4, OUTPUT);

button.attachClick(myClickFunction);
button.attachDoubleClick(myDoubleClickFunction);
button.attachDuringLongPress(mylongPress);
button.setDebounceTicks(80);
}
void loop() {

if (butt_flag == 1) {
  unsigned long currentMillis = millis();
if(currentMillis - previousMillis > interval) {
  previousMillis = currentMillis;
  if (ledState == LOW)
    ledState = HIGH;
  else
    ledState = LOW;
digitalWrite(4, ledState);
}
}
if (butt_flag == 0) {
  digitalWrite(4, 0);
}

if (butt_flag == 2) {
  digitalWrite(4, 1);

}
delay(10);
}

void myClickFunction() {
  Serial.println("Button 1 click.");
} // click1

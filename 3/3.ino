boolean butt_flag = 0;
int ledState = LOW;
long previousMillis = 0;
long interval = 500;
unsigned long last_press;
unsigned long timerbut;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(3, INPUT_PULLUP);
pinMode(4, OUTPUT);
unsigned long last_press;
unsigned long previousTime = millis();
//digitalWrite(5, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
boolean button1 = !digitalRead(3);
//if (button1 == 1){
//  timerbut = timerbut + 1;
//  Serial.println(timerbut);
//}
//if (button1 == 0){
//  timerbut = 0;

//}
if (button1 == 1 && butt_flag == 0 && millis() - last_press > 100) {
    butt_flag = 1;
    //Serial.println(button1);
    Serial.println("but1");
    Serial.println(butt_flag);
    last_press = millis();
  }
if (button1 == 1 && butt_flag == 1 && millis() - last_press > 4000) {
    butt_flag = 0;
    Serial.println("but2");
    Serial.println(butt_flag);
    last_press = millis();
  }

//if (button1 == 1 && millis() - last_press < 100) {
//    butt_flag = 0;
//    Serial.println("but3");
//    Serial.println(butt_flag);
    //last_press = millis();
//  }

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


//unsigned long currentMillis = millis();
//if(currentMillis - previousMillis > interval) {
//  previousMillis = currentMillis;
//  if (ledState == LOW)
//    ledState = HIGH;
//  else
//    ledState = LOW;
//digitalWrite(4, ledState);
//}
//}

}

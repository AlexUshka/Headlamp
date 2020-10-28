unsigned long last_press;    // таймер нажатия кнопки
boolean butt_flag;
boolean press1;
     //----------------- переменные "lock mode"-------------------
boolean lock1, lock2;                     // переменные двойного нажатия кнопок
boolean lock_flag;                        // переменная  LOCK ON/OFF
boolean ledlock_flag1, ledlock_flag2;     // пременные вкл/выкл диода 3
boolean val1, val2;                       // переменная обнуления таймеров
unsigned long time_lock, time_on, ms1;    // переменные таймеров
byte led_level;                           // значение диода 3 на маяке
  //-----------------------------------------------------------
   // ----------------- маяк ---------------------
                boolean majak_flag;
                uint32_t ms = 0;
                byte led_stat = 0;
  // ----------------- маяк --------------------
 // ---------------- диммер 1-------------------
     boolean dimm_flag1, dimm_case1;
     byte brightness = 15;
     byte fadeAmount = 5;
     byte brightness1 = 15;
     byte fadeAmount1 = 5; 
     unsigned long last_time;   // переменная для задержки по димеру 1 светодиод
     unsigned long last_time1;  // переменная по задержки по димеру 2 светодиод
  // ----------------- диммер 1 ------------------
  // -------------------- LOGIC 1 ----------------------------------------
boolean but1, but2, flag1, flag2, button;
byte val;
  // -------------------- LOGIC 1 ----------------------------------------
#define led1 9                            // Светодиод 1 пин 9
#define led2 10                           // Светодиод 2 пин 10
#define ledred 3                          // обявление пин 3. красным диодом 3.
#define BTN1 7
#define BTN2 8
#include "GyverButton.h"
GButton butt1(BTN1);
GButton butt2(BTN2);

void setup() {
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(ledred,OUTPUT); 
}

void loop() {
   butt1.tick();   // обезательная функция отработки кнопки 1
  butt2.tick();   // обезательная функция отработки кнопки 2
  majak1 ();
  dimmer1 ();
  
  // ------------------- ОПРОС КНОПКИ 1 ---------------------------------
  // ---------------- одинарное нажатие -----------------------------
  if (butt1.isSingle()){
    Serial.println("Single1");
    Serial.println(button);
    Serial.println(millis() - last_press);
   press1 = 1;
   Serial.println(press1);  
  }
  if(press1 == 1 && button == 0){
    button = 1;
    Serial.println("hui");
    but1 = 1;
    last_press = millis();
  }
  // ---------------- проверка на удержание ------------------------
  if (butt1.isHold()){
    Serial.println("Holding1");
  dimm_flag1 = 1;                // переменная вкл/выкл димера 
    but2 = 1;
  }
  // ------------------ проверка на двойной клик -------------------------
  if (butt1.isDouble()){
    Serial.println("Double1");
   //   lock1 = 1;                  // переменная LOCK MODE
  }
   // ---------------- выключение -----------------------------
  if (button == 1  && press1 == 1 && millis() - last_press > 4000){
  //{
    Serial.println("Single1_val6");
    Serial.println("millis() - last_press");
    Serial.println(but1);
    Serial.println(button);
    button = 0;
      last_press = millis();
    val = 6;
  }
 
  //Serial.println(button);
  // ------------------- ОПРОС КНОПКИ 1 ---------------------------------
  // -------------------- LOGIC 1 ----------------------------------------
  if(but1 == 1&& flag1 == 0){
    val = 1; flag2 = 1;
  }
  if(but1 == 1&& but2 == 1&& flag2 == 1){
    val = 3; but1 = 0;
  }
  if(but2 == 1&& flag2 == 0){
    val = 2; flag1 = 1; flag2 = 0; 
  }
  if(but2 == 1&& but1 == 1&& flag2 == 0){
    val = 4; flag2 = 1; but1 = 0;
  }
  if(but1 == 1&& but2 == 1&& flag2 == 1){
    val = 5; but1 = 0;
  }
  press1 = 0;
  
  // -------------------- LOGIC 1 ----------------------------------------
 if(Serial.available()){
  val = Serial.parseInt();
  }
 switch(val){
 case 1: //Serial.println(val);
 analogWrite(led1,15);
  break;
  case 2: Serial.println("2-2"); analogWrite(ledred,125); 
  break;
  case 3: Serial.println("3-3"); dimm_case1 = 1;
  break;
  case 4: Serial.println("4-4"); majak_flag = 1;
  break;
  case 5: Serial.println("5-5"); val = 2;
  break;
  case 6: analogWrite(ledred,0);analogWrite(led1,0);analogWrite(led2,0); majak_flag = 0; dimm_case1 = 0; but1 = 0; but2 = 0; flag1 = 0; flag2 = 0;
  break;
   }
   //but1 = 0;
}

//----------------------- ДИММЕР1 ---------------------
void dimmer1 () {
    if (dimm_flag1 && dimm_case1){
                   if (millis() - last_time > 100){    // отработка задержки
                      last_time = millis();    
                          analogWrite(led1,brightness);
                               brightness = brightness+fadeAmount;
                                      if (brightness==15||brightness==125)
                                    {
                                            analogWrite(led1,0);
                                            fadeAmount =- fadeAmount;
                                    }
                    } 
               }
 dimm_flag1 = 0;               
}
// --------------------МАЯК ------------------------
void majak1 () {
  if (majak_flag){
    Serial.println("majak");
   if( ( millis() - ms1 ) > 500 ){           // Событие срабатывающее каждые 500 мс   
       ms1 = millis();
led_stat = map(led_stat, 0,1,0,125);         // масштабируем переменную
       analogWrite(ledred, led_stat);        // Инвертируем светодиод
       led_stat = !led_stat;
   }
}
}

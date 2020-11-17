     // ---------------- контроль температуры --------------------
#include <OneWire.h>
// пин подкл датчика DS18B20
#define DS         11
//#define led1       10                   // светодиод отладки 10 пин
unsigned long time_ds18;                 // переменная таймера отсчета запроса к температуре
OneWire  ds1(DS);
float TempDS18B20;
boolean temp_control;
     // ---------------- контроль температуры --------------------
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
     boolean dimm_flag1, dimm_flag2, dimm_case1, dimm_case2; 
     byte brightness1 = 15;        // значения старта диммера1
     byte fadeAmount1 = 5;         // прирост диммера1
     byte brightness2 = 15;       // значения старта диммера2
     byte fadeAmount2 = 5;         // прирост диммера1
     unsigned long last_time1;     // переменная для задержки по димеру 1 светодиод
     unsigned long last_time2;  // переменная по задержки по димеру 2 светодиод
  // ----------------- диммер 1 ------------------
  // -------------------- LOGIC 1 ----------------------------------------
boolean but1, but2, but3;                        // нажатие кнопки 1, одинарное / зажатие 
boolean flag1, flag2, flag4, flag5, flag1_1, flag4_1, flag6, flag7;
boolean flag8;                              // переменная разрешения включения lock mode
boolean flag3;                              // переменная на переобнуление таймера на выкл        
byte val;                                   // выбор режимов
unsigned long last_press;                   // таймер нажатия кнопки
boolean button;                             // запуск таймера на выкл
boolean press1, press2, press3;                     // переменные нажатия кнопки на обнуления таймера на выкл
boolean press_off;                          // переменная на выкл
  // -------------------- LOGIC 1 ----------------------------------------
  // -------------------- LOGIC 2 ----------------------------------------
boolean but10, but11, but12, but13, but_adap;         // опрос кнопки // одинарное/удержание/двойное/тройное/удержание адаптивный режим
boolean flag10; 
boolean flag11, flag12, flag13;                                      // переменная диммера, удержание после нажатия / переменная обнуления таймера 100% / переменная включения 100%
boolean  flag14, flag15, flag16;
boolean flag_100_xtime;                                      // флаг включения режима 100% х минут.
boolean adap_flag, flag_time_adap,  max_time_flag, flag_off_adapt;
boolean adaptive;   
byte val1_1;                                           // переменная кейса кнопки 2
byte save_dimm1, save_dimm2;                           // сохраняем состояния димеров для режима "100%" и "100% 3мин"
unsigned long time_but12;
unsigned long time_adap;
unsigned long max_time;
unsigned long last_press2;                                     // таймер нажатия кнопки 2
boolean button2;                                               // запуск таймера на выкл 2
boolean press10, press11, press12, press13;                // переменные нажатия кнопки на обнуления таймера на выкл 2
boolean press_off2;                                            // переменная на выкл 2
  // -------------------- LOGIC 2 ----------------------------------------
#define led1 9                            // Светодиод 1 пин 9
#define led2 10                           // Светодиод 2 пин 10
#define ledblue 3                         // обявление пин 3. синий диодом 3.
#define ledred 5                          // красный
#define ledgreen 6                        // зеленый
#define BTN1 7                            // кнопка 1 пин 7
#define BTN2 8                            // кнопка 2 пин 8
#include "GyverButton.h"
GButton butt1(BTN1);
GButton butt2(BTN2);

void setup() {
  butt2.setDebounce(50);        // настройка антидребезга (по умолчанию 80 мс)
  butt2.setTimeout(800);        // настройка таймаута на удержание (по умолчанию 500 мс)
  butt2.setClickTimeout(600);   // настройка таймаута между кликами (по умолчанию 300 мс)
  
   TCCR1A = 0b00000001; // смена частоты шим на пинах 9. 10. 8 bit
   TCCR1B = 0b00000001; // x1 fast pwm 62.5 кГц // смена частоты шим
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(ledred,OUTPUT); 
  pinMode(ledblue,OUTPUT);
  pinMode(ledgreen,OUTPUT);
}

void loop() {       //-------------------------------------------------------- LOOP ----------------------------------------------------------------
  temperature_control();
  butt1.tick();   // обезательная функция отработки кнопки 1
  butt2.tick();   // обезательная функция отработки кнопки 2
  majak1 ();
  dimmer1 ();
  dimmer2 ();
  adaptive_mode();
  lock();
  
  // ------------------- ОПРОС КНОПКИ 1 ---------------------------------
  // ---------------- одинарное нажатие -----------------------------
  if (butt1.isSingle()){
    //Serial.println(millis() - last_press);
    if(flag_100_xtime == 0){        // проверка выключен ли режим 100% 3 мин
      Serial.println("Single1");
      press1 = 1; but1 = 1; 
      press_off = 1; 
  }
  }
  // ---------------- проверка на удержание ------------------------
  if (butt1.isHold()){
    if(flag_100_xtime == 0){         // проверка выключен ли режим 100% 3 мин
      Serial.println("Holding1");
      press2 = 1; but2 = 1;
      dimm_flag1 = 1;                // переменная вкл/выкл димера 
  }
  }
  // ------------------ проверка на двойной клик -------------------------
  if (butt1.isDouble()){
    if(flag_100_xtime == 0){         // проверка выключен ли режим 100% 3 мин
     Serial.println("Double1");
     lock1 = 1;                // переменная LOCK MODE
     but3 = 1;
     press3 = 1;
  }
  } 
  // ------------------- ОПРОС КНОПКИ 1 ---------------------------------
  
  
  
  // ------------------- ОПРОС КНОПКИ 2 ---------------------------------
  // ---------------- одинарное нажатие 2   -----------------------------
  if (butt2.isSingle()){
     //Serial.println(millis() - last_press);
     if(flag_100_xtime == 0){         // проверка выключен ли режим 100% 3 мин
      Serial.println("Single2");
      but10 = 1;
      press10 = 1;
      press_off2 = 1;
  }
  }
  // ---------------- проверка на удержание 2 ---------------------------
  if (butt2.isHold()){
    if(flag_100_xtime == 0){        // проверка выключен ли режим 100% 3 мин
      Serial.println("Holding2");
      but11 = 1;
      dimm_flag2 = 1;                // переменная вкл/выкл димера
      but_adap = 1;
  }
  }
//Serial.println(but_adap);
  // ------------------ проверка на двойной клик 2 ----------------------
  if (butt2.isDouble()){
    if(flag_100_xtime == 0){         // проверка выключен ли режим 100% 3 мин
      Serial.println("Double2");
      but12 = 1;
       if(but12 == 1 && flag13 == 0 && flag8 == 0){                 // проверяем небыл ли включен режим на флаг 13 
          lock2 = 1;                // переменная LOCK MODE
          Serial.println(lock2);
       }
     }
  }
  // ----------------- проверка на тройной клик 2 -----------------------
  if (butt2.isTriple()){
    Serial.println("Triple");
    but13 = 1;      
  }
  
  // ------------------- ОПРОС КНОПКИ 2 ---------------------------------
  // -------------------- LOGIC 2 ----------------------------------------
       // ----------------------------------------------  100% push mode -----------------------------------------------------------
  if((but12 == 1) && !flag12){                                            // обнуляем таймер 
     time_but12 = millis();
     flag12 = 1; 
     //Serial.println(millis() - time_but12);
  }
  if(but12 == 1 && millis() - time_but12 > 1010){     //  test
    but12 = 0; flag12 = 0; //flag13 = 0;                // test
    Serial.println("OFF but12");
 }
  if((but12 == 1 && flag13 == 1) && millis() - time_but12 > 1000){    // flag 13 test
     if(val1_1 == 13){val1_1 = 11;}                         // возврашаем состояния вал1 в 11.
     if(val == 7){val = 1;}                                 // возврашаем состояния вал в 1.
    but12 = 0; but11 = 0; flag12 = 0; flag13 = 0;
    analogWrite(led1,0);analogWrite(led2,0);
    Serial.println("OFF bust 100%");
    if(dimm_case1 == 1){                                       // функция перезаписи значения диммера 1
         brightness1 = save_dimm1;
         analogWrite(led1,brightness1);
         Serial.println(brightness1);
      }
       if(dimm_case2 == 1){                                    // функция перезаписи значения диммера 2
         brightness2 = save_dimm2;
         analogWrite(led2,brightness2);
         Serial.println(brightness2);
       }
  }
  if(but12 == 1 && but11 == 1){
     if(but12 == 1 && val1_1 == 11){val1_1 = 13;}          // смена вал1 если 11 на 13
     if(but12 == 1 && val == 1){val = 7;}                  // смена вал если 1 на 7
    but11 = 0; 
    flag12 = 0; flag13 = 1;  
    analogWrite(led1,255);analogWrite(led2,255);
    dimm_flag2 = 0;
    Serial.println("100%");
   // but_adap = 0;
    Serial.println("val1_1");
    Serial.println(val1_1);
     Serial.println(brightness2);
  }
  
       // ----------------------------------------------- однократное нажатие / диммер -----------------------------------------
  if(but10 == 1 && flag10 == 0){                                                // кнопка 2 / LED2 // && flag13 == 0
    but10 = 0; flag11 = 1;
    val1_1 = 11;
    Serial.println("led2 15%");
  }
  if(but11 == 1 && flag11 == 1 && flag13 == 0){                                 // диммер 2 / LED2    //max_time_flag =/test
     
    val1_1 = 12;                                                               
    Serial.println("dimm 2");
    Serial.println("val1_1");
    Serial.println(val1_1);
  }
  but11 = 0; 
        //  ------------------------------------------------------ adaptive mode ------------------------------------------------ 
  if(but_adap == 1 && flag11 == 0 && adap_flag == 0 && flag_time_adap == 0 && flag13 == 0 && flag_off_adapt == 0){            
    flag_time_adap = 1;
    time_adap = millis();                                                               // обнуление таймера на вкл 
    Serial.println("flag_time_adap");
  }
  if(but_adap == 0 && flag_time_adap == 1){                                             // сброс таймера если режим не включился
    flag_time_adap = 0;
    but11 = 0;
    dimm_flag2 = 0;
    Serial.println("flag_time_adap 0");
  }
  if((but_adap == 1 && adap_flag == 0 && flag11 == 0 && flag13 == 0 && flag_off_adapt == 0) && millis() - time_adap > 1000){   // таймер вкл режима                        
    adap_flag = 1; 
    adaptive = !adaptive;                                                                // переменная вкл/выкл адаптивного режима
    Serial.println("adaptive");
    Serial.println(adaptive);
    flag_time_adap = 0;
    but11 = 0;                                 // отпускание кнопки удержания
    dimm_flag2 = 0;
  }
     if(but_adap == 0 && adap_flag == 1 && flag11 == 0){                                 // отпускаем переменную нажатия кнопки при отпусканиии кнопки
         adap_flag = 0;
       //  Serial.println(but_adap); 
       }
  if(adaptive == 1 && adap_flag == 1 && flag15 == 0){                                   // отработка красного светодиода адаптивный режим вкл
    ledlock_flag1 = 1; flag15 = 1;
   // Serial.println(adap_flag);
  }
  if(adaptive == 0 && adap_flag == 1 && flag16 == 0){                                   // отработка красного светодиода адаптивный режим выкл
    ledlock_flag2 = 1; flag16 = 1;
    //Serial.println(adap_flag);
  }
  if(but_adap == 0){                                                                    // отпускание флагов на однократную отработку красного светодиода
    flag15 = 0; flag16 = 0;
  }
       but_adap = 0;                             
  
       // ------------------------------------------------------ 100% 3 минуты --------------------------------------------------
  if(but13 == 1 && flag14 == 0){                               // обнуляем таймер, вкл                          
    but13 = 0; flag14 = 1;
    Serial.println("100% 3min");                                          
    max_time_flag = 1;
    max_time = millis();
  }
  if(but13 == 1 && flag14 == 1){                               //выключаем вторым нажатием  
    but13 = 0; flag14 = 0; flag13 = 0; flag8 = 0;
    max_time_flag = 0;
    flag_off_adapt = 0;
    flag_100_xtime = 0;
    analogWrite(led1,0); analogWrite(led2,0);
    Serial.println("100% off1");
    if(dimm_case1 == 1){                                       // функция перезаписи значения диммера 1
         brightness1 = save_dimm1;
         analogWrite(led1,brightness1);
         Serial.println(brightness1);
      }
       if(dimm_case2 == 1){                                    // функция перезаписи значения диммера 2
         brightness2 = save_dimm2;
         analogWrite(led2,brightness2);
         Serial.println(brightness2);
       }
  }
  if(max_time_flag == 1 ){                                     // режим вкл диоды
    analogWrite(led1,255);analogWrite(led2,255);
    flag_off_adapt = 1; flag13 = 1; flag8 = 1;
    flag_100_xtime = 1;
    Serial.println("100% on");
   // Serial.println(brightness2);
       }

  if(max_time_flag == 1 && millis() - max_time > 5000){        // время автовыключения режима
     analogWrite(led1,0); analogWrite(led2,0);
      max_time_flag = 0; flag14 = 0; flag13 = 0; flag8 = 0;
      flag_off_adapt = 0;
      flag_100_xtime = 0;
      Serial.println(val1_1);
     Serial.println(val);
      Serial.println("100% off");
      Serial.println(dimm_case1);
      if(dimm_case1 == 1){                                   // функция перезаписи значения диммера 1
         brightness1 = save_dimm1;
         analogWrite(led1,brightness1);
         Serial.println(brightness1);
      }
       if(dimm_case2 == 1){                                  // функция перезаписи значения диммера 2
         brightness2 = save_dimm2;
         analogWrite(led2,brightness2);
         Serial.println(brightness2);
       }
  } 
     // ------------------------ обнуляем и запускаем таймер на выкл 2 --------------------
   
  if(press10 == 1 && button2 == 0){      //||press11 == 1
    button2 = 1;
    Serial.println("off2");
     Serial.println(press10);
      //Serial.println(press11);
       Serial.println(button2); 
    last_press2 = millis();
   //  Serial.println(val1_1);
  }
   
   // ---------------- выключение 2 -----------------------------
  if (button2 == 1 && press_off2 == 1 && millis() - last_press2 > 1500){
    Serial.println("Single1_val1_120");
   // Serial.println(but1);
   // Serial.println(button);
   button2 = 0;
   press10 = 0; press11 = 0; press12 = 0; press13 = 0;
   val1_1 = 20;
  }
   press_off2 = 0;                  
    
  // -------------------- LOGIC 2 ----------------------------------------
  // -------------------- LOGIC 1 ----------------------------------------
  if((press1 == 1||press2 == 1) && flag3 == 1){               // переобнуляем таймер на выкл, если было нажатие  
    Serial.println("lui"); 
    button = 0;
    flag3 = 0;
  }
  if(press3 == 1 && press2 == 1){                             // обнуления таймера на выкл, при работе синий / зеленый / красный
    press3 = 0;
         flag3 = 1; 
  }
  if(but1 == 1&& flag1 == 0){                                                // кнопка 1 / LED1
    but1 = 0; flag2 = 1; 
    val = 1;
    Serial.println("led1 15%");
  }
  if(but2 == 1&& flag2 == 1){                                                // диммер
    but2 = 0;  
    val = 3;                                                               
    Serial.println("dimm 1"); 
  }
  if(but2 == 1 && flag2 == 0 && flag7 == 0){                                // удержание кнопки 1 / красный
    but2 = 0; flag1 = 1; flag1_1 = 1; flag4 = 0;
    but3 = 0;                                                   // отпускаем кнопку дабл при вкл
    val = 2; 
    Serial.println("red");
        flag3 = 1;                                              // обнуляем таймер OFF нажатия
  }
  if(but1 == 1&& flag1 == 1 && flag4 == 0){                                // маяк //
    but1 = 0; flag1_1 = 0; flag7 = 1;
    but3 = 0;
    val = 4; 
    Serial.println("majak");
        flag3 = 1;                                             // обнуляем таймер OFF нажатия
  }
  if(but3 == 1 && flag1_1 == 1){                                           //blue
    flag1_1 = 0; but3 = 0; flag5 = 1; flag4 = 1; flag7 = 1;
    val = 5; 
    Serial.println("blue");
        flag3 = 1;
  }
  if(but3 == 1 && flag5 == 1){                                            //green
    flag5 = 0;  but3 = 0; flag6 = 1; flag4 = 1; flag7 = 1;
    val = 6; 
    Serial.println("green");
        flag3 = 1;
  }
  if(but3 == 1 && flag6 == 1){                                            // red
    but3 = 0; flag6 = 0; but2 = 1; flag7 = 0;
    Serial.println("val2");
  }
 //Serial.println(val);
// Serial.println(val1_1);
 
   // ------------------------ обнуляем и запускаем таймер на выкл --------------------
   
  if((press1 == 1||press2 == 1) && button == 0){   
    button = 1;
    Serial.println("hui"); 
    last_press = millis();
  }
   
   // ---------------- выключение -----------------------------
  if (button == 1 && press_off == 1 && millis() - last_press > 1500){
    Serial.println("Single1_val10");
   // Serial.println(but1);
   // Serial.println(button);
   button = 0;
   press1 = 0; press2 = 0; press3 = 0;
   val = 10;
  }
   press_off = 0;  //but3 = 0;                   
  // -------------------- LOGIC 1 ----------------------------------------
   
  // ----------------------------- MENU ----------------------------------
 if(Serial.available()){
  val = Serial.parseInt();
  }
 switch(val){
 case 1: analogWrite(led1,10); flag8 = 1;             
  break;
  case 2: analogWrite(ledred,125); analogWrite(ledgreen,0); flag8 = 1;
  break;
  case 3: dimm_case1 = 1; flag8 = 1;
  break;
  case 4: majak_flag = 1; flag8 = 1;
  break;
  case 5: analogWrite(ledblue,125); analogWrite(ledred,0); flag8 = 1;
  break;
  case 6: analogWrite(ledgreen,255); analogWrite(ledblue,0); flag8 = 1;
  break;
  case 7: // режим 100% использует case 7
  break;
  case 8: 
  break;
  case 9: 
  break;
  case 10:analogWrite(ledred,0);analogWrite(led1,0);analogWrite(ledblue,0);analogWrite(ledgreen,0); //analogWrite(led2,0);               // выключение
  majak_flag = 0; dimm_case1 = 0; flag8 = 0;                                                                                                     // выкл маяк / димер / lock mode allow access
  but1 = 0; but2 = 0; flag1 = 0; flag2 = 0; flag3 = 0; flag4 = 0; flag5 = 0; flag1_1 = 0; flag4_1 = 0; flag6 = 0; flag7 = 0;
  brightness1 = 15;                                                                                                                    // возвращаем диммер в 15%
  val = 0;     // test
  break;
        }
 if(Serial.available()){
  val1_1 = Serial.parseInt();
  }
  switch(val1_1){
  case 11: analogWrite(led2,10); flag8 = 1;
  break;
  case 12: dimm_case2 = 1; flag8 = 1;
  break;
  case 13:  // режим 100% использует case 13
  break;
  case 14: val1_1 = 12;
  break;
  case 15: 
  break;
  case 16: 
  break;
  case 17: 
  break;
  case 18: 
  break;
  case 19: 
  break;
  case 20: analogWrite(led2,0);
  but10 = 0; but11 = 0; but12 = 0; but13 = 0;
  flag10 = 0; flag11 = 0; flag8 = 0;                                                 // adap_flag = 0; flag15 = 0; flag16 = 0; flag12 = 0;
  dimm_case2 = 0;
  brightness2 = 15; 
  val1_1 = 0;
  break;
        }
        }
    
// -------------------------------------------------------------- LOOP ------------------------------------------------------------------------------

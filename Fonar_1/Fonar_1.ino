/*
  Отработка нажатия кнопки: нажатие, двойное нажатие, удержание.
  Логика работы:
  нажали (с антидребезгом)
  если отпустили до hold, считать отпущенной
  если удерживаем больше hold, считать зажатой
  если отпустили и прошло больше double_timer, считать 1 нажатием
  если отпустили и прошло меньше double_timer и нажали снова, считать что нажата 2 раз
  если была нажата 2 раз и отпущена, считать что была нажата 2 раза

  Я специально вывел отдельные флажки, которые нужно опускать каждый раз после отработки нажатия.
  Это сделано для того, чтобы пользоваться разными режимами нажатия абсолютно в любом месте программы
*/
 //----------------- переменные "lock mode"-------------------
boolean lock1, lock2;                     // переменные двойного нажатия кнопок
boolean lock_flag;                        // переменная  LOCK ON/OFF
boolean ledlock_flag1, ledlock_flag2;     // пременные вкл/выкл диода 3
boolean val1, val2;                       // переменная обнуления таймеров
unsigned long time_lock, time_on, ms1;    // переменные таймеров
byte led_level;                           // значение диода 3 на маяке
  //-----------------------------------------------------------
                // ---------------- диммер 1-------------------
     boolean dimm_flag;
     byte brightness = 15;
     byte fadeAmount = 5;
     byte brightness1 = 15;
     byte fadeAmount1 = 5; 
     unsigned long last_time;   // переменная для задержки по димеру 1 светодиод
     unsigned long last_time1;  // переменная по задержки по димеру 2 светодиод
               // ----------------- диммер 1 ------------------
               // ----------------- маяк ---------------------
                uint32_t ms = 0;
                byte led_stat = 0;
               // ----------------- маяк --------------------
#define ledred 3                          // обявление пин 3. красным диодом 3. 
#define button1B 7  // пин кнопки button1
#define button2B 8  // пин кнопки button2

boolean button1S;   // храним состояния кнопок (S - State)
boolean button1F;   // флажки кнопок (F - Flag)
boolean button1R;   // флажки кнопок на отпускание (R - Release)
boolean button1P;   // флажки кнопок на нажатие (P - Press)
boolean button1H;   // флажки кнопок на удержание (многократный вызов) (H - Hold)
boolean button1HO;  // флажки кнопок на удержание (один вызов при нажатии) (HO - Hold Once)
boolean button1D;   // флажки кнопок на двойное нажатие (D - Double)
boolean button1DP;  // флажки кнопок на двойное нажатие и отпускание (D - Double Pressed)

#define double_timer 500   // время (мс), отведённое на второе нажатие
#define hold 1500           // время (мс), после которого кнопка считается зажатой
#define debounce 80        // (мс), антидребезг
unsigned long button1_timer; // таймер последнего нажатия кнопки
unsigned long button1_double; // таймер двойного нажатия кнопки

void setup() {
                    TCCR1A = 0b00000001; // смена частоты шим на пинах 9. 10. 8 bit
                    TCCR1B = 0b00000001; // x1 fast pwm 62.5 кГц // смена частоты шим
  Serial.begin(9600);
  pinMode(button1B, INPUT_PULLUP);          
  pinMode (button2B, INPUT_PULLUP);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(ledred,OUTPUT);
}

void loop() {
   dimmer1();             // -------------- диммер ---------------
   lock();                // режим LOCK ON/OFF
  //-------опрос кнопок--------
  button1S = !digitalRead(button1B);
  buttons(); //отработка кнопок
  //-------опрос кнопок--------

  // отработка режимов (опускание флага обязательно!)
  if (button1P) {
    Serial.println("pressed");
    button1P = 0;
  }
  if (button1D) {
    Serial.println("double");
     lock1 = 1;                   // переменная LOCK MODE
    button1D = 0;
  }
  if (button1H && button1HO) {
    Serial.println("hold once");
    button1HO = 0;
  }
  
     if (button1H) {
    Serial.println("hold");
     dimm_flag = 1;               // переменная вкл/выкл димера
    
    button1H = 0;
    }
  
}

//------------------------ОТРАБОТКА КНОПОК-------------------------
void buttons() {
  //-------------------------button1--------------------------
  // нажали (с антидребезгом)
  if (button1S && !button1F && millis() - button1_timer > debounce) {
    button1F = 1;
    button1HO = 1;
    button1_timer = millis();
  }
  // если отпустили до hold, считать отпущенной
  if (!button1S && button1F && !button1R && !button1DP && millis() - button1_timer < hold) {
    button1R = 1;
    button1F = 0;
    button1_double = millis();
  }
  // если отпустили и прошло больше double_timer, считать 1 нажатием
  if (button1R && !button1DP && millis() - button1_double > double_timer) {
    button1R = 0;
    button1P = 1;
  }
  // если отпустили и прошло меньше double_timer и нажата снова, считать что нажата 2 раз
  if (button1F && !button1DP && button1R && millis() - button1_double < double_timer) {
    button1F = 0;
    button1R = 0;
    button1DP = 1;
  }
  // если была нажата 2 раз и отпущена, считать что была нажата 2 раза
  if (button1DP && millis() - button1_timer < hold) {
    button1DP = 0;
    button1D = 1;
    button1_timer = millis();
  }
  // Если удерживается более hold, то считать удержанием
  if (button1F && !button1D && !button1H && millis() - button1_timer > hold) {
    button1H = 1;
  }
  // Если отпущена после hold, то считать, что была удержана
  if (!button1S && button1F && millis() - button1_timer > hold) {
    button1F = 0;
    button1H = 0;
    button1_timer = millis();
  }
  //-------------------------button1--------------------------
}
//------------------------ОТРАБОТКА КНОПОК-------------------------

//----------------------- ДИММЕР -----------------------
void dimmer1 () {
    if (dimm_flag){
                   if (millis() - last_time > 100){    // отработка задержки
                      last_time = millis();    
                          analogWrite(9,brightness);
                               brightness = brightness+fadeAmount;
                                      if (brightness==15||brightness==125)
                                    {
                                            analogWrite(9,0);
                                            fadeAmount =- fadeAmount;
                                    }
                    } 
               }
}
// --------------------ДИММЕР ----------------------

// --------------------МАЯК ------------------------
void majak1 () {
   if( ( millis() - ms1 ) > 500 ){           // Событие срабатывающее каждые 500 мс   
       ms1 = millis();
led_stat = map(led_stat, 0,1,0,125);         // масштабируем переменную
       analogWrite(ledred, led_stat);        // Инвертируем светодиод
       led_stat = !led_stat;
   }
}
// --------------------МАЯК ------------------------

void lock(){
  // ---------------------------------- Отработка кнопок LOCK ------------------------
if((lock1 ==1||lock2 == 1) && !val1) {    //обнуляем таймер ожидания второго нажатия
  time_lock = millis();val1 = 1;}
  if((lock1==1||lock2 ==1) && (millis() -time_lock) > 3000){ //запускаем таймер
      lock1 = 0;lock2 = 0; val1 = 0; Serial.println("zero");
      }
if(lock1 == 1 && lock2 == 1 && lock_flag == 0) {  //режим "блок" включить
   Serial.println("lock on"); 
   lock1 = 0; lock2 = 0; val1 = 0;lock_flag = 1; 
   ledlock_flag1 = 1;                             // переменная вкл отработки Led 3
     }
if(lock1 == 1 && lock2 == 1 && lock_flag == 1) {  //режим "блок" выключить  
   lock1 = 0; lock2 = 0; val1 = 0; lock_flag = 0;
   Serial.println("lock off");
   ledlock_flag2 = 1;                            // переменная вкл отработки Led 3 
     }
 // -------------------------------- отработка кнопок  LOCK -------------------------
 // -------------------------------- отработка вкл/выкл Led 3 & LOCK MODE ------------
     if((ledlock_flag1||ledlock_flag2) && !val2){    //обнуление таймера LOCK
   time_on = millis(); val2 = 1;}
if(ledlock_flag1 && (millis() - time_on)<500){   //время работы таймера LOCK On
    //  Serial.println("on led"); 
    analogWrite(ledred,125);                    
   }
if(ledlock_flag1 && (millis() - time_on)>500){      // таймер выключения диода. (вешать функцию выкл контроллер)
   ledlock_flag1 = 0; val2 = 0; analogWrite(ledred,0);
    // Serial.println("off"); 
   }
if(ledlock_flag2 && (millis() - time_on)<1400){      // время работы таймера LOCK Off
  if( (millis() - ms1 ) > 350 ){                     // ------- маяк 2 -------
    //Serial.println("on led");
       ms1 = millis();
   led_level = map(led_level, 0,1,0,125);       
       analogWrite(ledred, led_level); 
       led_level = !led_level;                       // -------- маяк 2 ------
   }
  }
if(ledlock_flag2 && (millis() - time_on)>1400){      // время работы таймера на выкл Led, (вешать функцию вкл контроллера)
   ledlock_flag2 = 0; val2 = 0;  analogWrite(ledred,0);
    //Serial.println("off");
  }
 // -------------------------------- отработка вкл/выкл Led 3 & LOCK MODE ------------   
}

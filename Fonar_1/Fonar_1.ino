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
byte val; // переменная свича
//boolean led_flag;    // храним состояние светодиода 1

                // ---------------- диммер 1-------------------
     byte brightness = 15;
     byte fadeAmount = 5;
     byte brightness1 = 15;
     byte fadeAmount1 = 5;
     
     unsigned long last_time;   // переменная для задержки по димеру 1 светодиод
     unsigned long last_time1;  // переменная по задержки по димеру 2 светодиод
               // ----------------- диммер 1 ------------------
               
                uint32_t ms, ms1 = 0;
                byte led_stat = 0;
     
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
    pinMode(3,OUTPUT);
}

void loop() {
  //-------опрос кнопок--------
  button1S = !digitalRead(button1B);
  buttons(); //отработка кнопок
  //-------опрос кнопок--------

  // отработка режимов (опускание флага обязательно!)
  if (button1P) {
    Serial.println("pressed");
      majak1();
    button1P = 0;
  }
  if (button1D) {
    Serial.println("double");
          analogWrite(10,255);
    button1D = 0;
  }
  if (button1H && button1HO) {
    Serial.println("hold once");
    button1HO = 0;
  }
  
     if (button1H) {
    Serial.println("hold");
      dimmer1();    // ---------------------- диммер -----------------
    
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
    if (digitalRead(7)==LOW){
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
   ms = millis();
// Событие срабатывающее каждые 500 мс   
   if( ( ms - ms1 ) > 500 ){
       ms1 = ms;
// Инвертируем светодиод
led_stat = map(led_stat, 0,1,0,125);       
       analogWrite(3, led_stat); 
       led_stat = !led_stat;
   }
}
// --------------------МАЯК ------------------------

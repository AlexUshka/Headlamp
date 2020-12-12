   #include <GyverPower.h>
 //  #define millis() (millis() << (CLKPR & 0xF))
//#define micros() (micros() << (CLKPR & 0xF)) 
//#define delay(x) delay((x) >> (CLKPR & 0xf))
//#define delayMicroseconds(x) delayMicroseconds((x) >> (CLKPR & 0xf))                                           
     // ------------------------- коректировка миллис ------------ 

    // ----------------- battery control -------------------------
#define analogPin 1        // пин делителя напряжения
int value = 0;            // значение с делителя

int ledState;             // ledState used to set the LED
byte val_blink;
boolean flag_time_blink, flag_time_blink2;     // переменные сигнализации о разряде
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillis1 = 0;

const long interval = 500;           // interval at which to blink (milliseconds)

    // ----------------- battery control -------------------------
     // ---------------- контроль температуры --------------------
#include <OneWire.h>
// пин подкл датчика DS18B20
#define DS         11                      // пин подключения датчика
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
#define power_on_drive 12                          // подача питания на драйвера
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

GButton myButt1;  //  тест холла
GButton myButt2;  // тест холла

void setup() {
 // power.setSystemPrescaler(PRESCALER_16);   // замедляем в 16 раз
  
  // с понижением системной частоты "уйдут" все завязанные на частоте блоки периферии!
  // чтобы сериал завёлся (если нужен), умножаем скорость на замедление
  // иначе не заведётся на указанной скорости
//  Serial.begin(9600 * 16L);  
//  Serial.println("serial test");

  
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
  pinMode(power_on_drive,OUTPUT);
// ------------------------------------ прерывание --------------------------------------
   // кнопка подключена к GND и D2
  pinMode(2, INPUT_PULLUP);
  // подключаем прерывание на пин D2(Arduino NANO)
 // attachInterrupt(0, isr, FALLING); 
  power.setSleepMode(POWERDOWN_SLEEP);
}

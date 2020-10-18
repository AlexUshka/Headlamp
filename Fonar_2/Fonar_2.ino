
                // ---------------- диммер 1-------------------
     byte brightness = 15;
     byte fadeAmount = 5;
     byte brightness1 = 15;
     byte fadeAmount1 = 5;
     
     unsigned long last_time;   // переменная для задержки по димеру 1 светодиод
     unsigned long last_time1;  // переменная по задержки по димеру 2 светодиод
               // ----------------- диммер 1 ------------------
              // ------------------- Маяк ---------------------
                uint32_t ms, ms1 = 0;
                byte led_stat = 0;
             // ------------------- Маяк ---------------------

#define button1 7  // пин кнопки button1
#define button2 8  // пин кнопки button2
             
void setup() {
                  // --------------------------- смена частоты ------------------
                     TCCR1A = 0b00000001; // смена частоты шим на пинах 9. 10. 8 bit
                    TCCR1B = 0b00000001; // x1 fast pwm 62.5 кГц // смена частоты шим
                  // ---------------------------смена частоты--------------------  
  Serial.begin(9600);
  
  pinMode(button1, INPUT_PULLUP);
  pinMode (button2, INPUT_PULLUP);
    pinMode(9,OUTPUT);  // Диод 1 белый
    pinMode(10,OUTPUT); // Диод 2 белый
    pinMode(3,OUTPUT); // красны диод

}

void loop() {
  // put your main code here, to run repeatedly:

}



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

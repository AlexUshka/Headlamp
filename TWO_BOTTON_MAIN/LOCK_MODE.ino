// ------------------------------ LOCK MODE -----------------------------  
 void lock(){
  // ---------------------------------- Отработка кнопок LOCK ------------------------

    if((lock1 == 1||lock2 == 1) && !val1) {    //обнуляем таймер ожидания второго нажатия
       time_lock = millis();val1 = 1;
     }
  
  if((lock1==1||lock2 ==1) && (millis() -time_lock) > 3000){ //запускаем таймер
      lock1 = 0;lock2 = 0; val1 = 0; 
      Serial.println("zero");
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
   // flag15 = 0; 
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
   // flag16 = 0;
  }
 // -------------------------------- отработка вкл/выкл Led 3 & LOCK MODE ------------   
} 

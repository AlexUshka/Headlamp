void battery_control() {
   
  value = analogRead(analogPin);            // считываем показатель делителя
  //Serial.println(value);

if(value < 630 && value > 510){            // выводим показатель 100% заряжена
  //Serial.println("power 100%");
}

else if(value < 500 && value > 487){      // переключаем на режим 10% при напряжении 6,9 вольта
  val_blink = 1;
  
 }

 
else if(value < 477 && value > 440){      // переключаем на аварийный режим 10% при напряжении 6.65 вольта
  val_blink = 2;                  
  }

  
  else if(value < 428){                   // выключение полностью
    
    flag_time_blink2 = 0;
    flag_time_blink = 0;
    val_blink = 0;
  }
  
  if(val_blink == 1 && flag_time_blink == 0){
  previousMillis1 = millis();
  ledState = 0;
  flag_time_blink = 1;
  }
  if(val_blink == 2 && flag_time_blink2 == 0){
  previousMillis1 = millis();
  ledState = 0;
  flag_time_blink2 = 1;
  }
  //Serial.println(val);
  if((flag_time_blink == 1 || flag_time_blink2 == 1) && millis() - previousMillis1 <= 2995){
    
  if (millis() - previousMillis >= interval) {
     previousMillis = millis();
     Serial.println(ledState);
     Serial.println(val_blink);
    if (ledState == 0) {
      ledState = 20;
    } else {
      ledState = 0;
    }
    analogWrite(led1, ledState); analogWrite(led2, ledState);
  }
  }
 
}

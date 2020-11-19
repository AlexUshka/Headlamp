void temperature_control(){
 // -------------------------------- контроль температуры --------------------------- 
 if( millis() - time_ds18 > 1000){      // таймер опроса датчика
    time_ds18 = millis();
  
  byte data1[2];
  
  ds1.reset();
  ds1.write(0xCC);
  ds1.write(0x44);

// Читаем данные с ds18b20
  ds1.reset();
  ds1.write(0xCC);
  ds1.write(0xBE);
  data1[0] = ds1.read();
  data1[1] = ds1.read();

    TempDS18B20 = ((data1[1] << 8) | data1[0]) * 0.0625;

  //Serial.println(TempDS18B20);
  //Serial.println(press1);
  //Serial.println(press10);
  //Serial.println(press11);
  //Serial.println(flag_100_xtime);
 }
  if(TempDS18B20 < 29.50){                         // отпускание защиты при падении температуры до заданной
    temp_control = 0;
  }
 
  if(TempDS18B20 > 29.50){                            // срабатывание датчика при заданной температуре
     temp_control = 1;
  }
  if(temp_control && press1){                         // контроль температуры при нажатии на кнопку1
    analogWrite(led1,10); 
    
   // brightness1 = 10;
  }
  if(temp_control && press10){                            // контроль температуры при нажатии на кнопку2
    analogWrite(led2,10);
    
  //  brightness2 = 10;   
  }
  if(temp_control && flag_100_xtime){                     // отключаем режим 100% х время
    analogWrite(led1,10); analogWrite(led2,10);
    but13 = 1;
  }
  if(temp_control && press11){                            // отключаем реджим 100%
    analogWrite(led1,10); analogWrite(led2,10);
  }
 // -------------------------------- контроль температуры --------------------------- 
}                                            

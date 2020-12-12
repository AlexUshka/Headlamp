//----------------------- ДИММЕР1 ---------------------
void dimmer1 () {
    if (dimm_flag1 && dimm_case1){
        if (millis() - last_time1 > 100){                        // отработка задержки
            last_time1 = millis(); 
            save_dimm1 = brightness1;                           // записываем состояние диммера 1
            analogWrite(led1,brightness1);
            brightness1 = brightness1+fadeAmount1;
                  if (brightness1 == 10||brightness1 == 125){      // отработка крайних положений
                         analogWrite(led1,5);                   // величина крайних положений
                         fadeAmount1 =- fadeAmount1;              // смена направления
                          }
                    } 
               }
 dimm_flag1 = 0;               
}
//----------------------- ДИММЕР2 ---------------------------------------
void dimmer2 () {
    if (dimm_flag2 && dimm_case2){
        if (millis() - last_time2 > 100){                        // отработка задержки
            last_time2 = millis();
            save_dimm2 = brightness2;                            // записываем состояние диммера 2
            analogWrite(led2,brightness2);
            brightness2 = brightness2+fadeAmount2;
                     if (brightness2 == 10||brightness2 == 125){      // отработка крайних положений
                         analogWrite(led2,5);                   // величина крайних положений
                         fadeAmount2 =- fadeAmount2;              // смена направления
                          }
                    } 
               }
 dimm_flag2 = 0;               
}

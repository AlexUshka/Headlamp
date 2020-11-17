
 // --------------------МАЯК ---------------------------------------------
void majak1 () {
  if (majak_flag){
   if( ( millis() - ms1 ) > 400 ){           // Событие срабатывающее каждые *** мс   
       ms1 = millis();
led_stat = map(led_stat, 1,0,125,0);         // масштабируем переменную
       analogWrite(ledred, led_stat);        // Инвертируем светодиод
       led_stat = !led_stat;
      }
   }
}

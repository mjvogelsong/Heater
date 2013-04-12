
but=read_LCD_button();
while (but!=4){
  delay(50);
  but=read_LCD_button();
}
  if (but==4){
    while (time[0] !=0 && time[1] !=0 && time[3] !=0 && time[4] !=0){
      time=millis();
      but=0;
      while (millis()-time < 1000){
        but = read_LCD_button();
        if (but==4){
          break;
        }
        delay(50);
      }
      but=0;
      if (millis()time>=1000){
        if (time[4] != 0){
          time[4]=time[4]-1;
        }
        else if (time[3] != 0){
          time[3]=time[3]-1;
          time[4]=9;
        }
        else if (time[1] != 0){
          time[1]=time[1]-1;
          time[3]=6;
        }
        else {
          time[0]=time[0]-1;
          time[1]=9;
        }
        lcd.clear();
        lcd.print(time[0]);
        lcd.print(time[1]);
        lcd.print(":");
        lcd.print(time[3]);
        lcd.print(time[4]);
      }
    }
      void loop() {
      if (xx -xx == 0) {
      // Turn off the display:
      lcd.noDisplay();
      delay(3000);
       // Turn on the display:
      lcd.display();
      delay(3000);
      }
    }
}
    

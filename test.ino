#include <Wire.h>

#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

int trig = 2;
int echo = 1;
int press=0;


hd44780_I2Cexp lcd;

void setup() {
  lcd.begin(16,2);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  float duration = pulseIn(echo, HIGH);
  float dis = ((float)(340*duration) / 10000) / 2;

  float buttonDis = -1;
  int val = digitalRead(3);
  int val_0 = digitalRead(7);


  
  if(val_0 == LOW){
    press +=1;
    delay(400);
  }
  if(press%2 == 0){
    lcd.setCursor(0,0);
    lcd.print("  No signal     ");
    lcd.setCursor(0,1);
    lcd.print("-  Stop Sensor -");
  }else{
    if(val == LOW){
      buttonDis = dis;
      delay(250);
    }
    lcd.clear();
    if(press == 1){
       lcd.setCursor(0,0);
       lcd.print("- Start Sensor -"); 
       delay(2000);
       press+=2;
    }
//    
    if(buttonDis > 0){
      if(buttonDis > 300){
        lcd.setCursor(0,0);
        lcd.print("Distance Error");
        lcd.setCursor(0,1);
        lcd.print("Please check it");
        delay(200);
      }else{
        lcd.setCursor(0,0);
        lcd.print("Distance : ");
        lcd.setCursor(8,1);
        
        lcd.print(dis);
        lcd.print("cm");
        delay(200);  
      }
    }else{
      if(dis<5){
        lcd.setCursor(2,0);
        lcd.print("!! Warning !!");
        lcd.setCursor(0,1);
        lcd.print("!! within 5cm !!");
        delay(200);
      }else if(dis<10){
        lcd.setCursor(0,0);
        lcd.print("There is an item");
        lcd.setCursor(3,1);
        lcd.print("within 10cm.");
        delay(200);
      }else if(dis>10){
        lcd.setCursor(2,0);
        lcd.print("no item");
        lcd.setCursor(5,1);
        lcd.print("within 10cm.");
        delay(200);
      }
    }
  }
}

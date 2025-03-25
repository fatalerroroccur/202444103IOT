#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("LCD init");
  delay(2000);
  lcd.clear();
  pinMode(13,INPUT);
  pinMode(12,OUTPUT);
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.clear();
  long dur,dis;
  digitalWrite(12,LOW);
  delayMicroseconds(2);
  digitalWrite(12,HIGH);
  delayMicroseconds(10);
  digitalWrite(12,LOW);

  dur = pulseIn(13,HIGH);
  
  dis = dur / 58.2;
  Serial.println(dur );
  Serial.println(dis);

  lcd.print(dis);
  delay(1000);
}
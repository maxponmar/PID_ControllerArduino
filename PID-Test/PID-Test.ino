#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  
// Variables
int sensorInput;                    
float temp;                         
int potInput;                       
float Vout= 0;                      
float R1= 10000;                    
float R2= 0;                        
float buffer= 0;  

//int temporal=0;  
void setup()
{
  //temporal=0;
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("  Temperatura  ");
}


void loop()
{
  /*if (temporal==255)
    temporal-=10;
  else
    temporal+=10;
  analogWrite(2, temporal);
  delay(500);*/
  sensorInput = analogRead(0);
  temp = (float)sensorInput / 1024;
  temp *= 4.8;
  temp -= 0.5;
  temp *= 100;
  lcd.setCursor(0,1);
  lcd.print(temp);

  potInput= analogRead(1);
  if(potInput) {
  buffer= potInput * 5;
  Vout= (buffer)/1024.0;
  buffer= (5/Vout) -1;
  R2= R1 * buffer; }
  R2=0.0014*R2+22.95;

  lcd.setCursor(7, 1);
  lcd.print("I:");
  lcd.print(R2);

  // PID HERE!!!
  
  delay(1000);
}

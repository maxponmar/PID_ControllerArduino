#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <PID_v1.h>

LiquidCrystal_I2C lcd(0x27,16,2);  
// Variables
int sensorInput;                                            
int potInput;                       
double Vout= 0;                      
double R1= 10000;                    
double R2= 0;                        
double buffer= 0;  

// INPUT
double tempInput; 
// Output
double tempOutput;
double pidOutput;

int salidaFoco;
int salidaAbanico;

// PID
double Kp=54, Ki=13, Kd=5; 
PID myPID(&tempOutput, &pidOutput, &tempInput, Kp, Ki, Kd, DIRECT);
 
void setup()
{
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("  Temperatura  ");

  myPID.SetMode(AUTOMATIC);
  myPID.SetTunings(Kp, Ki, Kd);
}


void loop()
{
  //analogWrite(2, 255);
  sensorInput = analogRead(0);
  tempOutput = (float)sensorInput / 1024;
  //temp = ((temp*4.7)-0.5)*100;
  tempOutput *= 4.7;
  tempOutput -= 0.5;
  tempOutput *= 100;
  lcd.setCursor(0,1);
  lcd.print(tempOutput);
  
  potInput= analogRead(1);
  if(potInput) {
  buffer= potInput * 5;
  Vout= (buffer)/1024.0;
  buffer= (5/Vout) -1;
  R2= R1 * buffer; }
  tempInput=0.0028*R2+31.86;
  lcd.setCursor(7, 1);
  lcd.print("I:");
  lcd.print(tempInput);

  myPID.Compute();

  salidaFoco = (int)pidOutput;
  salidaAbanico = 255-salidaFoco;

  analogWrite(2, salidaFoco);
  analogWrite(3, salidaAbanico);
  
  String msg1 = "Temp deseada: ";
  String msg2 = "Temp actual: ";
  String msg3 = "Salida Foco: ";
  String msg4 = "Salida Abanico: ";
  Serial.println(msg1 + tempInput);
  Serial.println(msg2 + tempOutput);
  Serial.println(msg3 + salidaFoco);
  Serial.println(msg4 + salidaAbanico);
  Serial.println("");
  
  delay(1000);
}

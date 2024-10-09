#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  //Change the HEX address
#include <Servo.h> 

int led1 = 13;
int led2 = 12;
int led3 = 11;

Servo myservo1;

int IR1 = 2;
int IR2 = 3;

int Slot = 4;           //Enter Total number of parking Slots

int flag1 = 0;
int flag2 = 0;

void setup() {
lcd.begin(2,16);
lcd.backlight();
pinMode(IR1, INPUT);
pinMode(IR2, INPUT);
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);


myservo1.attach(9);
myservo1.write(0);

lcd.setCursor (0,0);
lcd.print("     ARDUINO    ");
lcd.setCursor (0,1);
lcd.print(" PARKING SYSTEM ");
delay (2000);
lcd.clear();
digitalWrite(led1, LOW);
digitalWrite(led2, LOW);
digitalWrite(led3, LOW);
}

void loop(){

if(digitalRead (IR1) == LOW && flag1==0){
  if(Slot>0){
    flag1=1;
    if(flag2==0){
    myservo1.write(90); 
    Slot = Slot-1;
    digitalWrite(led1 , HIGH);
    digitalWrite(led2 , LOW);
    digitalWrite(led3 , LOW);
    delay(400);
    }
  }
  else{                            
  lcd.setCursor (0,0);
  lcd.print("    SORRY    ");
  lcd.setCursor (0,1);
  lcd.print("  Parking Full  ");
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  delay (400);
  lcd.clear(); 
  }
}

if(digitalRead (IR2) == LOW && flag2==0){
  flag2=1;
  if(flag1==0){
    myservo1.write(90); 
    Slot = Slot+1;
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    delay(400);
  }
}

if(flag1==1 && flag2==1){
  delay(600);
  myservo1.write(0);
  flag1=0, flag2=0;
  delay(1000);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

lcd.setCursor (0,0);
lcd.print("    WELCOME!    ");
lcd.setCursor (0,1);
lcd.print("Slot Left: ");
lcd.print(Slot);
}
#include <LiquidCrystal.h>
#include <Servo.h>
#define PRZYCISK 7
#define PRZYCISKKK 8
#define PRZEKAZNIK 13
#define PRZEKAZNIK 10



unsigned long aktualnyCzas = 0;
unsigned long zapamietanyCzas = 0;
unsigned long roznicaCzasu = 0;
 int minuty = 0;
 int godziny = 16;
 int sekundy = 0;
 int wloncz =6; 
 int wyloncz =22;
 int wlonczz =7; 
 int wylonczz =21;
 int serwopozycja =0;
 int serwowloncz=16;

 Servo myservo;  // create servo object to control a servo


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



 
void setup(){
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  
  lcd.begin(16, 2);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(13,HIGH);
  digitalWrite(10,HIGH);

   myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  

}
 
void loop(){
  int sensorVal = digitalRead(7);
  int sensorVal2 = digitalRead(8);
  
//tu prubuje nastawiac czas czyli odejmowac np sekundy
  if (sensorVal2 ==LOW){
  if (sekundy >10){
  sekundy = sekundy -30;
  delay(500);
  }
  }
  
  
 aktualnyCzas = millis(); //Pobierz liczbe milisekund od startu
 roznicaCzasu =aktualnyCzas -zapamietanyCzas;
 if (roznicaCzasu>=1000UL)
 {

Serial.println(sensorVal);
Serial.println(sensorVal2);

//tu zeruje zegar
  if (sensorVal == LOW){
    godziny =16;
    minuty =0;
    sekundy =0;
  }
//tu pulapki czasowe dla aktywacji przekaznikow
  if (godziny==wloncz){
  digitalWrite(13,LOW);  
  }
 if (godziny==wyloncz){
  digitalWrite(13,HIGH);
 }
 if (godziny==wlonczz){
  digitalWrite(10,LOW);  
  }
 if (godziny==wylonczz){
  digitalWrite(10,HIGH);
 }
if (godziny==serwowloncz && minuty==15)
{
  for (serwopozycja = 0; serwopozycja <= 180; serwopozycja += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(serwopozycja);              // tell servo to go to position in variable 'serwopozycja'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (serwopozycja = 180; serwopozycja >= 180; serwopozycja -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(serwopozycja);              // tell servo to go to position in variable 'serwopozycja'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

}
  
   sekundy ++ ;
   if (sekundy == 60){
   minuty = minuty + 1;
    sekundy = 0;
   }
    if (minuty ==60 ){
     godziny ++ ;
    minuty = 0;
    }
     if(godziny == 24)   {
     godziny = 0;
     }
 
     zapamietanyCzas = aktualnyCzas;
    lcd.clear();
    if (godziny <10)
    lcd.print(0);
    lcd.print(godziny);
    lcd.print(":");
    if (minuty <10)
    lcd.print(0);
    lcd.print(minuty );
    lcd.print(":");
    if (sekundy <10)
    lcd.print(0);
     lcd.print(sekundy);

     lcd.setCursor(0,2);
     lcd.print("+");
     lcd.print(wloncz);
     lcd.print(" -");
     lcd.print(wyloncz);
     lcd.print(" +");
     lcd.print(wlonczz);
     lcd.print(" -");
     lcd.print(wylonczz);
     
     
     
  }
}    

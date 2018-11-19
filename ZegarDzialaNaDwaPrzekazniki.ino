#include <LiquidCrystal.h>
#define PRZYCISK 7
#define PRZYCISKKK 8
#define PRZEKAZNIK 13
#define PRZEKAZNIK 10



unsigned long aktualnyCzas = 0;
unsigned long zapamietanyCzas = 0;
unsigned long roznicaCzasu = 0;
 int minuty = 0;
 int godziny = 0;
 int sekundy = 0;
 int wloncz =25; 
 int wyloncz = 50;
 int wlonczz =30; 
 int wylonczz = 45;

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
  

}
 
void loop(){
  int sensorVal = digitalRead(7);
  int sensorVal2 = digitalRead(8);
  
//tu prubuje nastawiac czas czyli odejmowac np sekundy
  if (sensorVal2 ==LOW){
  if (sekundy >10){
  sekundy = sekundy -10;
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
    godziny =0;
    minuty =0;
    sekundy =0;
  }
//tu pulapki czasowe dla aktywacji przekaznikow
  if (sekundy==wloncz){
  digitalWrite(13,LOW);  
  }
 if (sekundy==wyloncz){
  digitalWrite(13,HIGH);
 }
 if (sekundy==wlonczz){
  digitalWrite(10,LOW);  
  }
 if (sekundy==wylonczz){
  digitalWrite(10,HIGH);
 }

  
   sekundy  = 1 + sekundy;
   if (sekundy == 60){
   minuty = minuty + 1;
    sekundy = 0;
   }
    if (minuty ==60 ){
     godziny = godziny + 1 ;
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

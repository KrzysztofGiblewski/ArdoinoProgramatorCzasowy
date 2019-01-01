#include <LiquidCrystal.h>
#include <Servo.h>
#define PRZYCISK 7
#define PRZYCISKKK 8
#define PRZEKAZNIK 13
#define PRZEKAZNIK 10




unsigned long aktualnyCzas = 0;
unsigned long zapamietanyCzas = 0;
unsigned long roznicaCzasu = 0;
 int minuty = 15;
 int godziny = 16;
 int sekundy = 0;
 int wloncz =6; 
 int wyloncz =22;
 int wlonczz =7; 
 int wylonczz =21;
 int wlonczKarm1 =9;
 int wlonczKarm2 =16;
  int serwopozycja =0;
 int serwowloncz=16;
 int ilosc=3;     //ile karmy podac ile razy posypać

 Servo myservo;  // create servo object to control a servo


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



 
void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(13,HIGH);
  digitalWrite(10,HIGH);
   pinMode(LED_BUILTIN, OUTPUT);               //wbudowana dioda led na plytce

   myservo.attach(9);  //  pin 9 sygnal dla serwa servo 
   myservo.write(0);    //  ustawiam serwo na kąt 0 stopni          


}
 
void loop(){
  int sensorVal = digitalRead(7); //przycisk z masy do pinu 7
  int sensorVal2 = digitalRead(8);
  
//tu prubuje nastawiac czas dodaje 15 min a drugim przyciskiem odejmuje 1 min
  if (sensorVal2 ==LOW)
  {
     if (minuty>45)
      {
       minuty= (minuty+15)-60;
        if (godziny<24)
          godziny+=1;
        else
          godziny=1; 
      }
     else minuty+=15;
     delay(500);
  }
   if (sensorVal == LOW)
   {
        if (minuty>0)
        minuty--;
        else
       {
          godziny--;
          minuty=59;
        }
        delay(500);
   }
  
  
 aktualnyCzas = millis(); //Pobierz liczbe milisekund od startu
 roznicaCzasu =aktualnyCzas -zapamietanyCzas;
 if (roznicaCzasu>=1000UL)
 {
    Serial.print("godzina: ");
    Serial.print(godziny);
    Serial.print(" : ");  
    Serial.print(minuty);
    Serial.print(" : ");
    Serial.println(sekundy);

      
       digitalWrite(LED_BUILTIN, HIGH); //dodałem migającą diodę wbudowanaą na płytce
       delay(50);
       digitalWrite(LED_BUILTIN,LOW);
      
       


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
 // pułapka dla serwa
  if (godziny==wlonczKarm1 && minuty ==0 && sekundy==10)
    for(int i=0; i<ilosc; i++)
    {
     myservo.write(180);              
     delay(1000);
     myservo.write(0); 
     delay(1000);
    }

  if (godziny==wlonczKarm2 && minuty ==0 && sekundy==10)
    for(int i=0; i<ilosc; i++)
    {
     myservo.write(180);              
     delay(1000);
     myservo.write(0); 
     delay(1000);
    }



   sekundy ++ ;
   if (sekundy == 60)
   {
    minuty++;
    sekundy = 0;
   }
    if (minuty ==60 )
    {
     godziny ++ ;
     minuty = 0;
    }
     if(godziny == 24)  
    {
     godziny = 0;
    }
 
     zapamietanyCzas = aktualnyCzas; 
 
    lcd.setCursor(0,0);
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
         lcd.print(" Karmie ");

      lcd.setCursor(0,1);
//     lcd.print(" ");
//     lcd.print(wloncz);
//     lcd.print("+");
//     lcd.print(wyloncz);
//     lcd.print(" +");
//     lcd.print(wlonczz);
//     lcd.print(" -");
//     lcd.print(wylonczz);
     lcd.print("o ");
     lcd.print(wlonczKarm1);
     lcd.print(" i o ");
     lcd.print(wlonczKarm2);
     lcd.print(" po ");
     lcd.print(ilosc);
     lcd.print(" porcje");
    

  
 }
 
 }    

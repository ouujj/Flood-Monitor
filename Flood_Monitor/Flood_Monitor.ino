#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define flood_Level_pin A0
#define Level_bit1 14
#define Level_bit2 12
#define Level_bit3 13

byte last_suit , current_suit= 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{ 
  Serial.begin (115200);
  pinMode(flood_Level_pin,INPUT);
  pinMode(Level_bit1,INPUT_PULLUP);
  pinMode(Level_bit2,INPUT_PULLUP);
 pinMode(Level_bit3,INPUT_PULLUP);
  //Scan I2C Device Address
  Serial.println ();
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;

  Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);
    }
  }
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");

  //Initial LCD Display

  lcd.begin();
  lcd.backlight();
  LCD1();
}

void loop() {
  int Levelb1 = digitalRead(Level_bit1);
  Serial.println(Levelb1);
  ReadFloodRLevelBit();
  delay(100);

}
void LCD1() {

  LiquidCrystal_I2C lcd(0x27, 16, 2);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("LCD1602 I2c No1");
  lcd.setCursor(2, 1);
  lcd.print("CPE LAB SUT");

}

void situation(String siut) {
  
if(last_suit != current_suit){
  LiquidCrystal_I2C lcd(0x27, 16, 2);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("FLOOD LEVEL: ");
  lcd.setCursor(2, 1);
  lcd.print(siut);
  Serial.println("FLOOD LEVEL: "+siut);
  last_suit = current_suit;  
}


}


void ReadFloodRLevel(){
     int Level = analogRead(flood_Level_pin);
     Serial.print("Rew Level: ");
     Serial.println(Level);
     
     if(Level <= 23 ){
      situation("Normal");
      current_suit = 0;
      }
     else if(Level > 24 &&  Level <= 100) {
        situation("a Few ");
        current_suit = 1;
     }
     else if(Level > 101 &&  Level <= 512) {
        situation("hard");
        current_suit = 2;
      }
     else  {
      situation("Danger");
      current_suit = 3;
     }
  
}
void ReadFloodRLevelBit(){
  
     int Levelb1 = digitalRead(Level_bit1);
    byte Levelb2 = digitalRead(Level_bit2)*2;
     byte Levelb3 = digitalRead(Level_bit3)*4;
    byte Level = Levelb1+Levelb2+Levelb3;
   
     Serial.print("Rew Level: ");
     Serial.println(Level);
     
     if( Level == 0){
      situation("Normal");
      current_suit = 0;
      }
     else if(Level == 1 ) {
        situation("a Few ");
        current_suit = 1;
     }
     else if(Level == 3) {
        situation("hard");
        current_suit = 2;
      }
     else if(Level == 7)  {
      situation("Danger");
      current_suit = 3;
     }
     else{
      situation("Error");
      current_suit = 4;
      }
  
}

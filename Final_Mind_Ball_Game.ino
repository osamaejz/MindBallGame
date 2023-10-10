#include <Mindwave.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
//#include <Arduino.h>
//#include "BasicStepperDriver.h"

Mindwave mindwave1;
Mindwave mindwave2;

const int rs = 32, en = 30, d4 = 28, d5 = 26, d6 = 24, d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define MOTOR_STEPS 200
#define RPM 120
#define MICROSTEPS 2
#define DIR 8
#define STEP 9
#define SLEEP 7
// reset is ground

//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);
#define buzz 10

int player_one_score = 0;
int player_two_score = 0;
int start_pin = 23;
int left = 7;
int right = 7;
int steps = 0;
int val = 0;

void onMindwaveData1(){
  Serial.print("\t1.\tquality: ");
  Serial.print(mindwave1.quality());
  Serial.print("\tattention: ");
  Serial.print(mindwave1.attention());
  Serial.print("\tmeditation: ");
  Serial.print(mindwave1.meditation());
  Serial.print("\tlast update: ");
  Serial.print(mindwave1.lastUpdate());
  Serial.print("ms ago");
  Serial.println();
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Player1  Player2");
    lcd.setCursor(3,1);
    lcd.print(player_one_score);
    lcd.setCursor(12,1);
    lcd.print(player_two_score);
    lcd.setCursor(0,2);
    lcd.print("Attent1  Attent2");
    lcd.setCursor(3,3);
    lcd.print((mindwave1.attention()));  
    lcd.setCursor(12,3);
    lcd.print((mindwave2.attention()));
    
}

void onMindwaveData2(){
    Serial.print("\t2.\tquality: ");
    Serial.print(mindwave2.quality());
    Serial.print("\tattention: ");
    Serial.print(mindwave2.attention());
    Serial.print("\tmeditation: ");
    Serial.print(mindwave2.meditation());
    Serial.print("\tlast update: ");
    Serial.print(mindwave2.lastUpdate());
    Serial.print("ms ago");
    Serial.println(); 
    lcd.setCursor(0,0);
    lcd.print("Player1  Player2");
    lcd.setCursor(3,1);
    lcd.print(player_one_score);
    lcd.setCursor(12,1);
    lcd.print(player_two_score);
    lcd.setCursor(0,2);
    lcd.print("Attent1  Attent2");
    lcd.setCursor(3,3);
    lcd.print((mindwave1.attention()));  
    lcd.setCursor(12,3);
    lcd.print((mindwave2.attention())); 
}

void introduction(){
    lcd.setCursor(0,0);
    lcd.print("MIND CONTROLLING");
    lcd.setCursor(6,1);
    lcd.print("BALL");
    lcd.setCursor(6,2);
    lcd.print("GAME");
}

void start(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Pair  Both  ");
  lcd.setCursor(0,1);
  lcd.print("  Headsets  To   ");
  lcd.setCursor(0,2);
  lcd.print(" Start The Game");
}

void setup() {
  // put your setup code here, to run once:
  
  pinMode(buzz, OUTPUT);
//  stepper.begin(RPM, MICROSTEPS);
  Serial.begin(9600);
  Serial1.begin(MINDWAVE_BAUDRATE);
  Serial2.begin(MINDWAVE_BAUDRATE);
  lcd.begin(16,4);
  introduction();
  delay(3000);
  lcd.clear();
  start();
  delay(3000);
  lcd.clear();

  
  
  
}

void loop() {
  //digitalWrite(34,HIGH);
  Serial.println("abc");
/* 
  if (EEPROM.read(0) =! 255 && EEPROM.read(1) =! 255):
  {
    r_in_mem = EEPROM.read(0);
    l_in_mem = EEPROM.read(1);
  }
 
  Serial.print("\tattention 1: ");
  Serial.print(mindwave1.attention());
  delay(500);
  Serial.print("\nattention 2: ");
  Serial.print(mindwave2.attention());
  delay(500);
  
  if(Serial1.available()>0)
  {
    Serial.print("\nHeadset 1 connected");
  }
  
  if(Serial2.available()>0)
  {
    Serial.print("\nHeadset 2 connected");
  }
  */
  // put your main code here, to run repeatedly:
  mindwave1.update(Serial1,onMindwaveData1);
  mindwave2.update(Serial2,onMindwaveData2);
//Serial.print("asd");
  if(mindwave1.attention() > 40){
    
  //  stepper.enable();
  //  stepper.rotate(85);// 7 steps to reach the goal
  //  stepper.disable();
    delay(500);
      
    left--;
    right++;   
    }
    EEPROM.write(0, right);// value of right in memory
    EEPROM.write(1, left); // value of left in memory
  
  if(mindwave2.attention() > 40){
   // stepper.enable();
   // stepper.rotate(-85);// 7 steps to reach the goal
   // stepper.disable();
    delay(500);
    left++;
    right--;
    }
    EEPROM.write(0, right);// value of right in memory
    EEPROM.write(1, left); // value of left in memory
  
    if(left == 0){
      tone(buzz,1000);
      delay(2000);
      noTone(buzz);
      player_one_score++;
      for(int l = 0; l <8 ; l++){
     // stepper.enable();
     // stepper.rotate(-85);// 7 steps to reach the goal
     // stepper.disable();
      delay(500);
      
      left++;
      right--;
      EEPROM.write(0, right);// value of right in memory
      EEPROM.write(1, left); // value of left in memory
      }
    }
    if(right == 0){
      player_two_score++;
      tone(buzz,1000);
      delay(2000);
      noTone(buzz);for(int l = 0; l <8 ; l++){
     // stepper.enable();
     // stepper.rotate(85);// 7 steps to reach the goal
     // stepper.disable();
      delay(500);
      
      left--;
      right++;

      EEPROM.write(0, right);// value of right in memory
      EEPROM.write(1, left); // value of left in memory  
      }
    }

  if(player_one_score == 3){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("   Player One   ");
    lcd.setCursor(0,2);
    lcd.print("      Wins      ");
    tone(buzz,1000);
    delay(5000);
    noTone(buzz);
    delay(3000);
    player_one_score = 0;
    player_two_score = 0;
  }
 if(player_two_score == 3){
    
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("   Player Two   ");
    lcd.setCursor(0,2);
    lcd.print("      Wins      ");
    tone(buzz,1000);
    delay(5000);
    noTone(buzz);
    delay(3000);
    player_one_score = 0;
    player_two_score = 0;

    
  }
 if(digitalRead(34)==LOW){
   if(left<7){
    for(int i = left; i <8 ; i++){
//      stepper.enable();
 //     stepper.rotate(-85);// 7 steps to reach the goal
   //   stepper.disable(); 
      left++;
      right--;
      player_one_score = 0;
      player_two_score = 0;
    
      }
   }
   if(right<7){
    for(int i = right; i <8 ; i++){
//     stepper.enable();
  //   stepper.rotate(85);// 7 steps to reach the goal
    // stepper.disable();
     left--;
     right++;
     player_one_score = 0;
     player_two_score = 0;
    
      }
   }
 }







  
}

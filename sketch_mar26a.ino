#include <Keypad.h>
#include <LiquidCrystal.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>

LiquidCrystal lcd(PD_1, PD_2, PD_3, PE_1, PE_2, PE_3);
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

const byte ROWS = 4; 
const byte COLS = 4; 
char pass[5];
int i = 0;
int enterNextLoop = 1;
int pos = 0;
int redLed = 2;
int blueLed = 3;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {32, 33, 34, 35}; 
byte colPins[COLS] = {36, 37, 38, 39}; 

Servo s1;
Servo s2;
MPU6050 mpu6050(Wire);

////////////////////////////////////////////////////////////////   SETUP    /////////////////////////////////////////////////
void setup(){

  pinMode(redLed, OUTPUT);     
  pinMode(blueLed, OUTPUT);   

  pinMode(PD_0, OUTPUT);
  analogWrite(PD_0, 80);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome Paras!!");
  delay(2000);

  
  while(1){
    
    digitalWrite(redLed, HIGH);
    digitalWrite(blueLed, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("System Config...");
    lcd.setCursor(0,1);
    lcd.print("Stay Stable.");
    
    Serial.begin(9600);
    s1.attach(6);
    s2.attach(5);
  
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);

    s1.write(10);
    s2.write(90);             
   
    // initialized the password as 00000.
    for(int i=0; i<5; i++){
      pass[i] == '0';
      }
      i=0;
     digitalWrite(blueLed, LOW);
     Serial.println("\n\nEnter password >>\nClick \"#\" for help.");
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Enter Password");
     lcd.setCursor(0,1);
     lcd.print("-->");
   
     while(1){
      char customKey = customKeypad.getKey();
      if(customKey == 'D'){
        Serial.println("Logged Out!!\n System Reboot.");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Logging Out...");
        delay(3000);
        enterNextLoop = 0;
        digitalWrite(redLed, HIGH);
        digitalWrite(blueLed, HIGH);
        break;
      }else{
        enterNextLoop = 1;
      }
      if(customKey=='#'){
        Serial.println("\nHINT: Paras's mobile number!!");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("HINT: Paras's mobile");
        continue;
      }
        
      if(customKey){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Password:");
        
        pass[i++] = customKey;

        lcd.setCursor(0,1);
        lcd.write(pass);
        Serial.print(customKey);
        delay(100);
        }
        if(i>=5){
          // here comes the code to check unlock
          if(pass[0]== '3' & pass[1]== '7' & pass[2]== '0' & pass[3]== '2' & pass[4]== '4'){
            Serial.println("\nVarified User!!");
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("User Varified!!");
            digitalWrite(redLed, LOW);
            delay(1000);
            Serial.println("\nAccess Granted.");
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Access Granted.");     
            blueBlink();
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Camera Stabilized...");
            delay(2000);
            break;
          }else{
            Serial.println("\nInvalid... \nTry Again.");
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Invalid...");
            lcd.setCursor(0,1);
            lcd.print("Try Again.");
            redBlink();
          }
          i=0;
      }
  }

if(enterNextLoop){
   while(1){
      char customKey2 = customKeypad.getKey();
      if(customKey2 == 'D'){
        Serial.println("Logged Out!!\n System Reboot.");
        delay(3000);
        digitalWrite(redLed, HIGH);
        digitalWrite(blueLed, HIGH);
        break;
      }
      mpu6050.update();
      Serial.print("angleX : ");
      Serial.print(mpu6050.getAngleX());
      s1.write(120+mpu6050.getAngleY());
      
      Serial.print("\tangleY : ");
      Serial.print(mpu6050.getAngleY());
      s2.write(-mpu6050.getAngleX()+90);
      
      //Serial.print("\tangleZ : ");
      //Serial.println(mpu6050.getAngleZ());
      //s3.write(90-mpu6050.getAngleZ());
   }
  }
 }
}

  void blueBlink(){
          for(int i=0; i<7; i++){
            digitalWrite(blueLed, HIGH);
            delay(100);
            digitalWrite(blueLed, LOW);
            delay(100);
            }
          digitalWrite(blueLed, HIGH);
  }

  void redBlink(){
        for(int i=0; i<7; i++){
          digitalWrite(redLed, HIGH);
          delay(100);
          digitalWrite(redLed, LOW);
          delay(100);
        } 
        digitalWrite(redLed, HIGH);      
  }

  
void loop(){
// nothing to write here as this is not used.
  //while loops are used in setup to work with authenticity check.
}

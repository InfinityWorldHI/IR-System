/*this code was created by H.I Electronics Tesch Channal/
 * 
 * you can modify this code as you want
 * this code could help you to control any device using any remote control easily.
 * just replace IR button code HEX with yours
 * 
 * if this was helpfull for you please don't forget to like & share this video and if you want
 * more hit subscribe button
 * 
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
//#include<SPI.h>
#include<Servo.h>
//#include<LiquidCrystal.h>
#include<IRremote.h>

Servo lockservo;
//LiquidCrystal lcd(2);
//Pins
#define blueLed 7 //Green LED pin.
#define redLed 8 //Red Led pin.
#define buzzer 4 //Buzzer pin.
#define servopin 9
#define led1 5
#define led2 6
#define emergencybutton 10 //Reset user password forgotten
//Relay pins
#define relay1 A0
#define relay2 A1
#define relay3 A2
#define relay4 A3
#define relay5 A4
#define relay6 A5

#define RECV_PIN 3 //IR Reciever pin (PWM).

IRrecv irrecv(RECV_PIN);
decode_results results;

String defaultpass = "123456"; //Root Password
String userpass = "";          //User password

//remote buttons.. changed with yours 
String btn1 = "9716be3f"; //Your button 1 IR HEX code in lower case. ex: ff63ad
String btn2 = "3d9ae3f7"; 
String btn3 = "6182021b";
String btn4 = "8c22657b";
String btn5 = "488f3cbb";
String btn6 = "449e79f";
String btn7 = "32c6fdf7";
String btn8 = "1bc0157b";
String btn9 = "3ec3fc1b";
String btn0 = "c101e57b";
String btnReset = "20fe4dbb";     //Reset button uses to logout and make the program lock
String btnResetPass = "e5cfbd7f"; //Reset button uses to change the user password
String btnIncrease = "a3c8eddb";  //Brightness controlling
String btnDecrease = "f076c13b";  //Brightness controlling
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
//Buzzer sound
bool shouldBeep = true;
bool unlockSound = true;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

bool locked = true;
bool set = false;
bool statled1 = false;//for led 1 status
bool statled2 = false;//for led 2 status
bool statservo = false;//for servo status
bool statrelay1 = false;//for relay 1 status
bool statrelay2 = false;//for relay 2 status1
bool statrelay3 = false;//for relay 3 status
bool statrelay4 = false;//for relay 4 status
bool statrelay5 = false;//for relay 5 status
bool statrelay6 = false;//for relay 6 status
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

String inputPass = "";
String chin = "";
String statser;
int level;// pwm 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

void setup() {
  irrecv.enableIRIn();
  //lcd.begin(16,2);
  lockservo.attach(servopin);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(emergencybutton, INPUT_PULLUP);

  pinMode(relay1, OUTPUT);// connected to Relay 1
  pinMode(relay2, OUTPUT);// connected to Relay 2
  pinMode(relay3, OUTPUT);// connected to Relay 3
  pinMode(relay4, OUTPUT);// connected to Relay 4
  pinMode(relay5, OUTPUT);// connected to Relay 5
  pinMode(relay3, OUTPUT);// connected to Relay 3 
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

  Serial.begin(9600);
  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  //lcd.print("IR control device");
}

void loop() {
  
    if (irrecv.decode(&results)) {
       //lcd.setCursor(0,1);
      if (String(results.value, HEX) == btn1) {
        Serial.print("1");
        if(statled1 == false){
          level = 255;
          statled1 = true;
        }
        else{
          level = 0;
          statled1 = false;
        }
         chin="1";
         delay(5);
         commadit();
      }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

      else if (String(results.value, HEX) == btn2) {
        Serial.print("2");
        if(statled2 == false){
          level = 255;
          statled2 = true;
        }
        else{
          level = 0;
          statled2 = false;
        }
         chin="2";
         delay(5);
         commadit();
      }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

      else if (String(results.value, HEX) == btn3) {
        Serial.print("3");
        if(statservo == false){
          level = 180;
          statservo = true;
          statser = "ON";
        }
        else{
          level = 0;
          statservo = false;
          statser = "OFF";
        }
         chin="3";
         commadit();
      }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

      else if (String(results.value, HEX) == btn4) {
        Serial.print("4");
         chin="4";
         commadit();
      }
      else if (String(results.value, HEX) == btn5) {
        Serial.print("5");
         chin="5";
         commadit();
      }
      else if (String(results.value, HEX) == btn6) {
        Serial.print("6");
         chin="6";
         commadit();
      }
      else if (String(results.value, HEX) == btn7) {
        Serial.print("7");
         chin="7";
         commadit();
      }
      else if (String(results.value, HEX) == btn8) {
        Serial.print("8");
         chin="8";
         commadit();
      }
      else if (String(results.value, HEX) == btn9) {
        Serial.print("9");
         chin="9";
         commadit();
      }
      else if (String(results.value, HEX) == btn0) {
        Serial.print("0");
         chin="0";
         commadit();
      }
      else if (String(results.value, HEX) == btnIncrease) {
        Serial.print("Brigthness");
        if(level <= 235){
          level =level + 20;
        }
         commadit();
      }
      else if (String(results.value, HEX) == btnDecrease) {
        Serial.print("Brigthness");
        if(level >= 20){
          level =level - 20;
        }
         commadit();
      }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

      else if (String(results.value, HEX) == btnReset) {
        if(locked == false){
          //lcd.clear();
          //lcd.print("IR control device");
          //lcd.setCursor(10,1);
          //lcd.print("Reset");
          Serial.println("\nRESET");
          resetPass();
        }
        else{
          //do nothing
        }
      }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//Changeing user password   
      else if (String(results.value, HEX) == btnResetPass){
            if(set == true){
                  if(inputPass != ""){
                           set = false;
                           Serial.println("\nPassword changing...");
                           delay(10);
                           setnewpass();
                               }
                  else{
                          //lcd.setCursor(0,1);
                          //lcd.print("Enter Userpass 6");
                          Serial.println("\nPlease enter password");
                       }
                       }        
            else if(set == false){
                          //lcd.clear();
                          //lcd.setCursor(0,0);
                          //lcd.print("Change Password");
                          Serial.println("\nChange Password...");
                          setpass();
                       }
            else if(locked == true){
            //lcd.clear();
            //lcd.setCursor(0,0);
            //lcd.print("Plz login Root");
                       }
      }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
      irrecv.resume(); // Receive the next value
    }
    
    if (locked == true) {
      digitalWrite(redLed, HIGH);
      digitalWrite(blueLed, LOW);
    }
    else {
      digitalWrite(redLed, LOW);
      digitalWrite(blueLed, HIGH);
    }
 //if you forgat user password just enter the new pass and click emergencybutton button
 //to set new password
 if(digitalRead(emergencybutton) == LOW){
  setnewpass();
 }
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
//main command manger
void commadit(){
  if(locked == true){
    updatePass(chin);
  }
  else if(locked == false){
    option(chin);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
bool updatePass(String character) {
  if (locked == false)
    return false;
  beep();
  //lcd.print("*");
    inputPass += character;
    if (inputPass.length() < defaultpass.length()) {
     //do no thing
    }
    else {
      if(set == false){
      if (defaultpass == inputPass || userpass == inputPass ) {//both passwords can login
        locked = false;
        digitalWrite(blueLed, HIGH);
        digitalWrite(redLed, LOW);
        //lcd.print("OK");
        delay(1100);
        //lcd.clear();
        //lcd.print("IR control device");
        Serial.println("\nUNLOCKED");
        if (unlockSound == true) {
          delay(60);
          digitalWrite(buzzer, HIGH);
          delay(150);
          digitalWrite(buzzer, LOW);
          delay(100);
          digitalWrite(buzzer, HIGH);
          delay(200);
          digitalWrite(buzzer, LOW);
        }
      }
      else {
        inputPass = "";
        digitalWrite(buzzer, HIGH);
        delay(800);
        digitalWrite(buzzer, LOW);
        //lcd.setCursor(0,1);
        //lcd.print("Wrong Password!");
        delay(1100);
        //lcd.clear();
        //lcd.print("IR control device");
        Serial.println("\nWRONG PASSWORD!");
        }
     }
    }
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

void resetPass() {
  inputPass = "";
  locked = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

void beep() {
  if (shouldBeep == true) {
    digitalWrite(buzzer, HIGH);
    delay(60);
    digitalWrite(buzzer, LOW);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

void setpass(){
    if(defaultpass == inputPass){//just root password can change user password
      set = true;
      locked = true;
      inputPass = "";
      //lcd.setCursor(0,1);
      //lcd.print("Enter Userpass 6");
      delay(1300);
      //lcd.clear();
      //lcd.print("Change Password");
      Serial.println("\nEnter New password 6 numbers");
    }
  else{
      //lcd.setCursor(0,1);
      //lcd.print("Enter Rootpass");
      delay(1300);
      //lcd.clear();
      //lcd.print("Change Password");
      Serial.println("\nEnter Root password");
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

void setnewpass(){
  userpass = inputPass;
  //lcd.setCursor(0,1);
  //lcd.print("UserPass update");
  delay(1300);
  //lcd.clear();
  //lcd.print("IR control device");
  Serial.println("\nThe password has been updated to ");
  Serial.print(userpass);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
//here you can add how many options you want
bool option(String character){
  if(chin == "1"){//if button 1 pressed LED1 turn on or off
              //lcd.clear();
              //lcd.setCursor(0,0);
              //lcd.print("You Select :");
              //lcd.setCursor(0,1);
              //lcd.print("LED 1 ");
              //lcd.print(level);
              analogWrite(led1,level);
            if(level >= 235){
              //lcd.print(" MAX"); 
              }
            else if(level <= 30){
              //lcd.print(" LOW");
              }
    delay(5);
  }
  else if(chin == "2"){//if button 2 pressed LED2 turn on or off
             //lcd.clear();
             //lcd.setCursor(0,0);
             //lcd.print("You Select :");
             //lcd.setCursor(0,1);
             //lcd.print("LED 2 ");
             //lcd.print(level);
             analogWrite(led2,level);
           if(level >= 235){
             //lcd.print(" MAX");
             }
           else if(level <= 30){
             //lcd.print(" LOW");
            }
    delay(5);
  }
  else if(chin == "3"){//if button 3 pressed Servo Open the thing or closed
    //lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print("You Select :");
    //lcd.setCursor(0,1);
    //lcd.print("Servo ");
    //lcd.print(statser);
    if(level >=0 && level <= 180){
      lockservo.write(level);
    }
  }
  else if(chin == "4"){//if button 4 pressed trun on or off relay 1
    if( statrelay1 == false ){
      digitalWrite(relay1, LOW);// turn relay 1 on
      statrelay1 = true;
    }
    else if( statrelay1 == true ){
      digitalWrite(relay1, HIGH);// turn relay 1 off
      statrelay1 = false;
    }
  }
  else if(chin == "5"){//if button 5 pressed trun on or off relay 2
    if( statrelay2 == false ){
      digitalWrite(relay2, LOW);// turn relay 2 on
      statrelay2 = true;
    }
    else if( statrelay2 == true ){
      digitalWrite(relay2, HIGH);// turn relay 2 off
      statrelay2 = false;
    }
  }
  else if(chin == "6"){//if button 6 pressed trun on or off relay 3
    if( statrelay3 == false ){
      digitalWrite(relay3, LOW);// turn relay 3 on
      statrelay3 = true;
    }
    else if( statrelay3 == true ){
      digitalWrite(relay3, HIGH);// turn relay 3 off
      statrelay3 = false;
    }
  }
  else if(chin == "7"){//if button 7 pressed trun on or off relay 4
    if( statrelay4 == false ){
      digitalWrite(relay4, LOW);// turn relay 4 on
      statrelay4 = true;
    }
    else if( statrelay4 == true ){
      digitalWrite(relay4, HIGH);// turn relay 4 off
      statrelay4 = false;
    }
  }
  else if(chin == "8"){//if button 8 pressed trun on or off relay 5
    if( statrelay5 == false ){
      digitalWrite(relay5, LOW);// turn relay 5 on
      statrelay5 = true;
    }
    else if( statrelay5 == true ){
      digitalWrite(relay5, HIGH);// turn relay 5 off
      statrelay5 = false;
    }
  }
  else if(chin == "9"){//if button 9 pressed trun on or off relay 6
    if( statrelay6 == false ){
      digitalWrite(relay6, LOW);// turn relay 6 on
      statrelay6 = true;
    }
    else if( statrelay2 == true ){
      digitalWrite(relay6, HIGH);// turn relay 6 off
      statrelay6 = false;
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      


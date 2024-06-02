//Ultrasonic Sensor
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 10;
const int echoPin = 11;
int travelTime;

float distance;
int level;

const int redLedPin = 4;
const int yellowLedPin = 7;
const int greenLedPin = 8;
const int buzzerPin = 9;

//float switches
const int lowlevelfloat = 12;
const int maxlevelfloat = 13;


//Water Pump Control
const int dryRunPin = 3;
const int relayPin = 2;
String state = "Full";

const int pumpmanual = 5;
const int automanual = 6;
void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.print("WATER LEVEL:");
  lcd.setCursor(0, 1);
  lcd.print("PUMP:OFF MANUAL");


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(dryRunPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);

  //float switches connect them to ground
  pinMode(lowlevelfloat, INPUT_PULLUP);
  pinMode(maxlevelfloat, INPUT_PULLUP);

    pinMode(pumpmanual, INPUT_PULLUP);//push button
    pinMode(automanual, INPUT_PULLUP);//toggle switch

  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

}
void loop() {
  // put your main code here, to run repeatedly:
  sendSoundWave();                       //Send a sound Wave
    travelTime = pulseIn(echoPin, HIGH);   //Get Travel Time
    distance = travelTime * 0.034 / 2;

    level = map(distance, 33,16, 0, 10);

    lcd.setCursor(12, 0);
   if(distance<0)distance=0; //to avoid sensor errors
   if(level<0)level=0;//to avoid sensor errors
   lcd.print(level);
   lcd.print("   ");

   lcd.setCursor(5, 1);
   if(relayPin==1)lcd.print("ON ");
   else if(relayPin==0) lcd.print("OFF");


  if (digitalRead(dryRunPin) == 1) {
    //Dry Run Protection
    digitalWrite(relayPin, HIGH); //turn off
    lcd.setCursor(0, 1);
      lcd.print("PUMP:OFF DRY RUN");

    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    buzzer2();



  } else {
    digitalWrite(redLedPin, LOW);
    if(digitalRead(lowlevelfloat) == LOW && digitalRead(maxlevelfloat) == LOW){
      if(digitalRead(automanual) == LOW){
        lcd.setCursor(9, 1);
        lcd.print("AUTO   ");
        digitalWrite(yellowLedPin, LOW);
       digitalWrite(greenLedPin, LOW);


       if (state == "Empty") {
       //turn on water pump
       digitalWrite(relayPin, LOW);
       lcd.setCursor(0, 1);
        lcd.print("PUMP:ON ");

       sendSoundWave();                       //Send a sound Wave
       travelTime = pulseIn(echoPin, HIGH);   //Get Travel Time
         distance = travelTime * 0.034 / 2;
       if (distance < 16) {
        digitalWrite(relayPin, HIGH);
        state = "Full";
        digitalWrite(greenLedPin, LOW);
        digitalWrite(yellowLedPin, LOW);

        buzzer1();
       }

       } else if (state == "Full") {
       //turn off water pump
       digitalWrite(relayPin, HIGH);
       lcd.setCursor(0, 1);
         lcd.print("PUMP:OFF ");


       sendSoundWave();                       //Send a sound Wave
       travelTime = pulseIn(echoPin, HIGH);   //Get Travel Time
       distance = travelTime * 0.034 / 2;
       if (distance > 18) {
        digitalWrite(relayPin, LOW);
        state = "Empty";

        digitalWrite(yellowLedPin, LOW);
        digitalWrite(greenLedPin, LOW);
        buzzer3();

      }

    }
      }else if(digitalRead(automanual) == HIGH){
        //for switching between auto mode and manual mode
        lcd.setCursor(9, 1);
        lcd.print("MANUAL ");
        if(digitalRead(pumpmanual) == LOW){
          lcd.setCursor(0, 1);
          lcd.print("PUMP:ON ");
          digitalWrite(relayPin, LOW);
          delay(50);

        }
        else if(digitalRead(pumpmanual) == HIGH){
          lcd.setCursor(0, 1);
        lcd.print("PUMP:OFF ");
          digitalWrite(relayPin, HIGH);
          delay(50);

        }
      }

    }
    //hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
    else if(digitalRead(lowlevelfloat) == LOW && digitalRead(maxlevelfloat) == HIGH){
      // TANK IS MAXIMUM
      digitalWrite(relayPin, HIGH);//SHUT OFF PUMP
      lcd.setCursor(0, 1);
      lcd.print("PUMP:OFF TANKMAX");
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(redLedPin, LOW);
        digitalWrite(greenLedPin, HIGH);
      buzzer2();
      //SCREEN MAX LEVEL



    }
    else if(digitalRead(lowlevelfloat) == HIGH && digitalRead(maxlevelfloat) == LOW){
      digitalWrite(relayPin, LOW);
      lcd.setCursor(0, 1);
     lcd.print("PUMP:ON SENS ERR");
     //TURN ON PUMP to maintain liquid above low level float
     digitalWrite(yellowLedPin, HIGH);
      digitalWrite(greenLedPin, LOW);
      digitalWrite(redLedPin, LOW);
      buzzer2();

      //SCREEN NO LIQUID IN TANK


    }
    else{
      lcd.setCursor(0, 1);
      lcd.print("   FLOAT ERROR     ");
      digitalWrite(relayPin, HIGH);
      digitalWrite(yellowLedPin, HIGH);
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(redLedPin, HIGH);
      buzzer3();
      //SCREEN ERROR

    }



  }

  delay(110);
}

void sendSoundWave() {

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}
//buzzer tones for diffrent alarms
void buzzer1(){
  for(int i= 0;i<3; i++){
          tone(buzzerPin, 1500);
          delay(200);
          noTone(buzzerPin);
          delay(300);
          tone(buzzerPin, 1000);
          delay(200);
          noTone(buzzerPin);
        }
}
void buzzer2(){
  for(int i= 0;i<3; i++){
          tone(buzzerPin, 900);
          delay(400);
          noTone(buzzerPin);
          delay(400);

        }
}
void buzzer3(){
  for(int i= 0;i<3; i++){
          tone(buzzerPin, 2000);
          delay(600);
          noTone(buzzerPin);
          delay(500);

        }
}

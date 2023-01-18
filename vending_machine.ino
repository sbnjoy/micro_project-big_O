#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 10 //MOSI of RFID 
#define RST_PIN 9 //RST of RFID 
#define LED_G 4 //define green LED pin
#define LED_R 5 //define red LED
//#define BUZZER 2 //buzzer pin

const int temp1 = 0;
const int temp2 = 0;
const int buzzerPin = 11;
const int flamePin = 2;
int Flame = HIGH; 

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(buzzerPin, OUTPUT); 
pinMode(flamePin, INPUT);
  //pinMode(BUZZER, OUTPUT);
  //noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  Flame = digitalRead(flamePin);
  if (Flame== LOW)
  { 
    Serial.println("Fire is Detected");
    digitalWrite(buzzerPin, HIGH); 
  } 
  else
  { 
    Serial.println("No Fire is Detected");
    digitalWrite(buzzerPin, LOW);
  }
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();


   if (content.substring(1) == "F2 AA 79 33"|| content.substring(1) == "13 A1 A9 10") //change here the UID of the card/cards that you want to give access
  {
    if(content.substring(1) == "F2 AA 79 33"){
      if(temp1 == 0){
        Serial.println("Authorized access");  
        delay(500);
        myServo.write(180);
        delay(2000);
        myServo.write(0);
        delay(2000);
        myServo.write(180);
        //digitalWrite(LED_G, LOW);
        temp1 == 1;
      }
    }
    else{
      Serial.println(" Access denied");
    }
    if(content.substring(1) == "13 A1 A9 10"){
      if(temp2 == 0){
        Serial.println("Authorized access");  
        delay(500);
        myServo.write(180);
        delay(2000);
        myServo.write(0);
        delay(2000);
        myServo.write(180);
        //digitalWrite(LED_G, LOW);
        temp2 == 1;
      }
    }
    else{
      Serial.println(" Access denied");
    }
    
//    Serial.println("Authorized access");
//    Serial.println();
//    delay(500);
//    digitalWrite(LED_G, HIGH);
//    //tone(BUZZER, 500);
//    delay(300);
//    //noTone(BUZZER);
//    myServo.write(180);
//    delay(3000);
//    myServo.write(0);
//    digitalWrite(LED_G, LOW);
  }
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(LED_R, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(5000);
    digitalWrite(buzzerPin, LOW);
    //tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_R, LOW);
    //noTone(BUZZER);
  }
      
  
}

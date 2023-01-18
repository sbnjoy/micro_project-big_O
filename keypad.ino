#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//#include <ESP8266HTTPClient.h>
#include <Keypad.h>
#include <Wire.h>


const byte ROWS = 4; //Four rows
const byte COLS = 4; //Four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'S','0','H','D'}
};
//byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
byte rowPins[ROWS] = {D1, D2, D3, D4};
byte colPins[COLS] = {D5, D6, D7, D8};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


String v_passcode="";
String id="";
String shirt="";
String pant="";

const char* ssid = "FahadOvi";
const char* password = "00000000";
char server[] = "192.168.117.19";

WiFiClient client;

void setup(){
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");

  delay(500);
}

void loop(){
  char key = keypad.getKey();
  //Serial.println(v_passcode);
  //delay(3000);
  
  if (key != NO_KEY){
    //Serial.println(key);
    
    
    v_passcode = v_passcode + key;
    Serial.println(v_passcode);
    
    if(key=='S'){
      Serial.println("Enter Values between (0-6)!!!!!");
      Serial.println("7. Enter Student ID");
      Serial.println("8. Amount of Shirt");
      Serial.println("9. Amount of Pant");
      v_passcode="";
      id="";
      shirt="";
      pant="";
    }
    if(key=='7')
    {
      Serial.println("Enter Student ID: ");
        
    }
    if(key=='8')
    {
      Serial.println("Amount of Shirt: ");
        
    }
    if(key=='9')
    {
      Serial.println("Amount of Pant: ");
        
    }
    
    if(key=='D')
    {
//        Serial.println(v_passcode);   
//        v_passcode=""; 

      if(v_passcode[0]=='7'){
        id = id + v_passcode;
      }
      else if(v_passcode[0]=='8'){
        shirt = shirt + v_passcode;
      }
      else if(v_passcode[0]=='9'){
        pant = pant + v_passcode;
      }
      v_passcode="";
      
     
   }
   if(key=='H'){
      Serial.print("ID: ");
      Serial.print(id);
      Serial.print(" Shirt: ");
      Serial.print(shirt);
      Serial.print(" Pant: ");
      Serial.println(pant);
      Sending_To_phpmyadmindatabase(); 
      delay(3000);
    }
  
    }        
  }

 void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /microproject/laundry.php?id=");
    client.print("GET /microproject/laundry.php?id=");     //YOUR URL
    Serial.println(id);
    client.print(id);
    client.print("&shirt=");
    Serial.println("&shirt=");
    client.print(shirt);
    Serial.println(shirt);
    client.print("&pant=");
    Serial.println("&pant=");
    client.print(pant);
    Serial.println(pant);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host:192.168.117.19");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
  

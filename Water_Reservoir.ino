int relay = 8;
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(relay, OUTPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = SensorX();
   
   Serial.println(x);
   
  //  digitalWrite(relay, HIGH);
  //  delay(2000);
  //  digitalWrite(relay, LOW);  
  //  delay(2000);
  if(x >= 15){
    digitalWrite(relay, LOW);
  }
  else{
    digitalWrite(relay, HIGH);
  }
}


int SensorX() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  
  return distance;
}

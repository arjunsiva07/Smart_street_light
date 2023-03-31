#include <SoftwareSerial.h>
// defines pins numbers
const int buttonPin = 2;
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 8;
const int ledPina = 12;
const int ledPinb = 7;
const int ldrPin = A0;
const int voldivPin = A1;

// defines variables
long duration;
int sendflag=0;
long distance;
long safetyDistance;
int counter=0;

void setup() {
  //setup all pins as input / output
  pinMode(buttonPin, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ledPin, OUTPUT);
  pinMode(ledPina,OUTPUT);
  pinMode(ledPinb, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(voldivPin, INPUT);
  Serial.begin(9600); // Starts the serial communication
}


void loop() { 
  int buttonState=LOW;
  int a;
  if (Serial.available() > 0){
    a=Serial.read();
    Serial.println(a);}
    if(a==49){
      digitalWrite(ledPin,HIGH);//to switch on Green Light for 2 seconds
      delay(2000);
      digitalWrite(ledPin,LOW);
      }
    if(a==50){
      digitalWrite(ledPina,HIGH);//to switch on Green Orange for 2 seconds
      delay(2000);  
      digitalWrite(ledPina,LOW);
      }
    if(a==51){
      digitalWrite(ledPinb,HIGH);//to switch on Green Red for 2 seconds
      delay(2000);
      digitalWrite(ledPinb,LOW);
      }
    if(a==52){
      for(int i=0;i<3;i++){
        digitalWrite(ledPin,HIGH);//alert lighting
        delay(200);
        digitalWrite(ledPin,LOW);
        digitalWrite(ledPina,HIGH);
        delay(200);
        digitalWrite(ledPina,LOW);
        digitalWrite(ledPinb,HIGH);
        delay(200);
        digitalWrite(ledPinb,LOW);
        }
      }
    if(a==53){
      digitalWrite(ledPin,LOW);//to switch off Green Light for 2 seconds 
      }
    if(a==54){
      digitalWrite(ledPina,LOW);//to switch off Orange Light for 2 seconds 
      }
    if(a==55){
      digitalWrite(ledPinb,LOW);//to switch off Red Light for 2 seconds 
      }
    if(a==56){
      for(int i=0;i<4;i++){
        digitalWrite(ledPin,HIGH);//to switch ON ALL Lights for 2 seconds 
        digitalWrite(ledPina,HIGH);
        digitalWrite(ledPinb,HIGH);
        delay(400);
        digitalWrite(ledPin,LOW);
        digitalWrite(ledPina,LOW);
        digitalWrite(ledPinb,LOW);
        delay(400);
        }
      }
      
    buttonState = digitalRead(buttonPin);//check if SOS button has been pressed
    if ((buttonState == HIGH)&&(sendflag==0)){
      Serial.println("SOS, this message is delivered to the police station"); // send a byte with the value 45
      Serial.println();
      digitalWrite(ledPin,HIGH);
      delayMicroseconds(500);
      digitalWrite(ledPina,HIGH);
      delayMicroseconds(500);
      digitalWrite(ledPinb,HIGH);
      delayMicroseconds(500);//deliver SOS message to android via bluetooth and blink lights
      sendflag=1;
      }
    else{
      digitalWrite(ledPin,LOW);
      digitalWrite(ledPina,LOW);
      digitalWrite(ledPinb,LOW);
      sendflag=0; 
      }
    
    int ldrStatus = analogRead(ldrPin);//read sunlight intensity
    if (ldrStatus >= 650){
      digitalWrite(ledPin, LOW);
      delayMicroseconds(10);
      digitalWrite(ledPina, LOW);
      delayMicroseconds(10);
      digitalWrite(ledPinb, LOW);
      delayMicroseconds(10);  
      }
    else{
     //Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      //delayMicroseconds(10);  
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance= duration*0.034/2;
      safetyDistance = distance;
      if (safetyDistance <= 14 ){
        digitalWrite(ledPin, HIGH);//turn on Green Light for first lane
        delayMicroseconds(500);
        delayMicroseconds(3000);
        counter++;
        Serial.println(counter);
        Serial.println("Number of cars have passed this spot");
        }
      else if (safetyDistance <= 21 && safetyDistance>16 ){
        digitalWrite(ledPina, HIGH);//turn on Orange Light for second lane
        delayMicroseconds(500);
        delayMicroseconds(3000);
        counter++;
        Serial.println(counter);
        Serial.println("Number of cars have passed this spot");
        }
      else if (safetyDistance <= 30 && safetyDistance > 23 ){
        digitalWrite(ledPinb, HIGH);//turn on Red Light for third lane
        delayMicroseconds(500);
        delayMicroseconds(3000);
        counter++;
        Serial.println(counter);
        Serial.println("Number of cars have passed this spot");//collect and send data of live traffic     
        }
      else{
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPina, LOW);
        digitalWrite(ledPinb, LOW);
        } 
   delay(100);
  }
}

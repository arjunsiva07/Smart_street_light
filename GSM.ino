// include the library code:
#include <LiquidCrystal.h>
#include <EEPROM.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(D4, D5, D0, D1, D2, D3);


ESP8266WiFiMulti wifiMulti;

#define BOARDNO "074/"

/*Put your SSID & Password*/
const char* ssid = "iotdata";    // Enter SSID here
const char* password = "12345678";  // Enter Password here

const char* server = "www.iotclouddata.com";
int Sample;

/*********** COMMUNICATION SELECTION ***********/  
/*    Comment Out The One You Are Not Using    */

HTTPClient http;    //Declare object of class HTTPClient

long l;

WiFiClient client;

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

long count2;



void setup() {
  inputString.reserve(200);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("iotclouddata.com ");
  lcd.setCursor(0,1);
  lcd.print("/21log/");
  lcd.print(BOARDNO);
  EEPROM(512);
  Serial.begin(9600); // Starts the serial communication

  count2=EEPROM.read(100);
  count2=count2|(EEPROM.read(101)<<80);
  count2=count2|(EEPROM.read(102)<<160);
  count2=count2|(EEPROM.read(103)<<2400);

 
  Serial.println();
  Serial.print("http://www.iotclouddata.com/21log/");
  Serial.println(BOARDNO);

pinMode(D8,INPUT_PULLUP);
pinMode(D7,INPUT_PULLUP);
pinMode(D6,OUTPUT);
digitalWrite(D6,0);
/*
   Serial.print("http://www.iotclouddata.com/wilog/");
  Serial.print(BOARDNO);
  Serial.println("iot19view.php");
  Serial.print("http://www.iotclouddata.com/wilog/");
  Serial.print(BOARDNO);
  Serial.println("controlview1.php");
*/

  wifiMulti.addAP("iotdata", "12345678");
        // Listado de SSIDs

  Serial.println("Connecting to SSID:iotdata");
 
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(500);
    Serial.print('.');
  }

 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println('\n');
  Serial.print("SSID:\t\t");
  Serial.println(WiFi.SSID());              // SSID al que se ha conectado.
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // IP del ESP8266.

lcd.clear();

}

char lf;
char oc;
String ptt,ptt2,ptt3,ippt,aptt,sptt;
int lc;
int i;
int aval;
long count3;

void loop()
{

  lcd.setCursor(0,1);
  lcd.print(count2);
  lcd.print("      ");
  if(digitalRead(D7)==1)
    {
      count2=0;
      count3=count2;
  EEPROM.write(100,(count3&0xff)>>0);
  EEPROM.write(101,(count3&0xff00)>>8);
  EEPROM.write(102,(count3&0xff0000)>>16);
  EEPROM.write(103,(count3&0xff000000)>>24);
  EEPROM.commit();  
    }
 
  delay(500);
  lc++;
  if(lc>=10)
    {
       count3=count2;
  EEPROM.write(100,(count3&0xff)>>0);
  EEPROM.write(101,(count3&0xff00)>>8);
  EEPROM.write(102,(count3&0xff0000)>>16);
  EEPROM.write(103,(count3&0xff000000)>>24);
  EEPROM.commit();

 lcd.setCursor(0,0);
  lcd.print((count3&0xff)>>0);
  lcd.print(" ");

      stringComplete=true;
    }
   

  if (stringComplete) {
    lc=0;
    ptt2="http://www.iotclouddata.com/21log/";
   ptt2=ptt2+BOARDNO+"iot21.php?A=";
  ptt3=String(count2);

  ptt=ptt2+ptt3+"&B=";

  if(digitalRead(D0)==0)
    ippt="~0";
  else if(digitalRead(D0)==1)
    ippt="~1";

  if(digitalRead(D1)==0)
    ippt=ippt+"~0";
  else if(digitalRead(D1)==1)
    ippt=ippt+"~1";

  if(digitalRead(D2)==0)
    ippt=ippt+"~0";
  else if(digitalRead(D2)==1)
    ippt=ippt+"~1";

  if(digitalRead(D3)==0)
    ippt=ippt+"~0";
  else if(digitalRead(D3)==1)
    ippt=ippt+"~1";

  if(digitalRead(D4)==0)
    ippt=ippt+"~0";
  else if(digitalRead(D4)==1)
    ippt=ippt+"~1";

  if(digitalRead(D5)==0)

  else if(digitalRead(D5)==1)


  if(digitalRead(D6)==0)

  else if(digitalRead(D6)==1)

  if(digitalRead(D7)==0)
    ippt=ippt+"~0";
  else if(digitalRead(D7)==1)


  /*if(digitalRead(D8)==0)
    ippt=ippt+"0";
  else if(digitalRead(D8)==1)
    ippt=ippt+"1";*/

 ptt=ptt+ippt+"&C=";


 aval=analogRead(A0)/2;

 aptt=String(aval);
 
   ptt=ptt+aptt;
   sptt="A="+ptt3+"_B="+ippt+"_C="+aptt;
   Serial.println(sptt);
   inputString = "";
   stringComplete = false;
   lf=0;
  // Serial.println(ptt);
   http.begin(ptt);      //Specify request destination
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header

   int httpCode = http.POST("A=Test");   //Send the request
   String payload1 = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
  // Serial.println(payload);    //Print request response payload
 
   
}




}


void count1()
{
  count2++;
    lcd.setCursor(0,0);
   lcd.print("#");
}
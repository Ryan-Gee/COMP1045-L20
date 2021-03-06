//Ryan Gee - 200396244
//April 17, 2020
//Arduino sensor monitoring with ThingSpeak sending
//Monitors the value of the potentiometer on the Maker321 shield and sends the values to my ThingSpeak account
//V1.0

//Include the thingspeak library
#include "ThingSpeak.h"

//Grab the channel number and api key
unsigned long myChannelNumber = 1040222;
const char myWriteAPIKey = "FA49ETLU899HDIVF";
//Get the ThingSpeak's website ip address
#define IP "184.106.153.149"
//The post string with my api key
String Api_key = "GET /update?key=FA49ETLU899HDIVF";
float output;  
float val;
int error;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
}

void loop()
{
  //Read the sensor and call the update function
  output=analogRead(0);
  val = output;
  updatedata();
  delay(1000);
}

void updatedata(){
  //Construct the initial TCP command
  String command = "AT+CIPSTART=\"TCP\",\"";
  command += IP;
  command += "\",80";
  //Send the command
  Serial.println(command);
  Serial1.println(command);
  delay(2000);
  //Throw an error if there is one
  if(Serial1.find("Error")){
    return;
  }
  //Otherwise continue by constructing the GET call
  command = Api_key ;
  //append the value itself
  command += "&field1=";   
  command += val;
  command += "\r\n";
  //Send the command
  Serial.print("AT+CIPSEND=");
  Serial1.print("AT+CIPSEND=");
  //Monitor things on the serial monitor
  Serial.println(command.length());
  Serial1.println(command.length());
  if(Serial1.find(">")){
    Serial.print(command);
    Serial1.print(command);
  }
  //if there is an error, state so and close the connection
  else{
   Serial.println("AT+CIPCLOSE");
   Serial1.println("AT+CIPCLOSE");
    error=1;
  }
}

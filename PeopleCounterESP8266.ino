#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "index.h"  //Web page index file

const char* ssid = "iPhone"; //WiFi identification
const char* password = "87654321"; //WiFi connection password
char incomingData;   // for incoming serial data
const char*  Alarm = "Capacity Reached"; //Alarm Status Variable
const char*  NoAlarm = "Space Available"; //Alarm Status Variable
int People;

ESP8266WebServer server(80); //web server port declaration

const int led = 13;
void handleRoot() {
  digitalWrite(led, 1);
  String s = MAIN_page; 
  People = incomingData; 
  //Convert incomingData int to String then Replace @@PeopleCount@@ in HTML with People integer value
  s.replace("@@PeopleCount@@",String(People)); replacing string in html with interger value of people count  

  
//alarm state status logic
if(incomingData > 5){
s.replace("@@AlarmStatus@@",String(Alarm));
 
}
else {


  s.replace("@@AlarmStatus@@",String(NoAlarm));
}


  server.send(200, "text/html", s); //Send webpage to browser
  digitalWrite(led, 0);  
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(9600); //baud rate
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin(); //start server
  Serial.println("Esp8266 web server started");
}



void serialComm(){  //handles read uart serial communication logic
  
         // send data only when you receive data:
         if (Serial.available() > 0) {
                 // read the incoming byte:
                 incomingData = Serial.read();

                 // say what you got:
                 Serial.print("Incoming Data: ");
                 Serial.println(incomingData,DEC);
         }

}


void loop(void){
server.handleClient();
serialComm(); // runs serial comm function
}   



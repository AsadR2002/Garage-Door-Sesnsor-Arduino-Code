#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "";
const char* password = "";
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

const int trigPin = D0;  //D4
const int echoPin = D1;  //D3

// defines variables
long duration;
int distance;
 
String page = "";
String data; 
void setup(void){

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
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
  server.on("/", [](){
    page = "<Title>Asad's Garage</Title> <h1 style ='color: red;' >Asad's Garage Door Server</h1><h3>Data:</h3> <h4>Garage Door Status: "+String(data)+ " </h4> <button onClick='window.location.reload();'>Update Door Status</button>";
    server.send(200, "text/html", page);
  });
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance < 100)
  {
    data = "Door is Closed";
  }

  else
  {
    data = "Door is Open";
  }
  delay(2000);

  
  
  server.handleClient();
}

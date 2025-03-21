#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

 
// Uncomment one of the lines below for whatever DHT 
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
 
/*Put your SSID & Password*/
const char* ssid = "ssid";  // Enter SSID here
const char* password = "password";  //Enter Password here
 
ESP8266WebServer server(80);
 
// DHT Sensor
const int DHTPin = 2; 
                
// Initialize DHT sensor.
               
 
float Temperature;
float Humidity;
  
void setup() {
  Serial.begin(9600);
  delay(100);
   
  pinMode(DHTPin, INPUT);
 
  
 
  Serial.println("Connecting to ");
  Serial.println(ssid);
 
  //connect to your local wi-fi network
  WiFi.begin(ssid, password);
 
  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
 
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
 
  server.begin();
  Serial.println("HTTP server started");
 
}
void loop() {
   
  server.handleClient();
   
}
 
void handle_OnConnect() {
 const int DHTPin = 2;
 Temperature = 91; // Gets the values of the temperature
  Humidity = digitalRead(DHTPin);;// Gets the values of the humidity 
  server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
  Serial.println(Temperature,Humidity);
}
 
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
 
String SendHTML(float Temperaturestat,float Humiditystat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta http-equiv=\"refresh\" content=\"2\">\n";
  ptr +="<title>21BEC091 MEEN PATEL</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP8266 NodeMCU</h1>\n";
   
  ptr +="<p>Roll no.: ";
  ptr +=(int)Temperaturestat;
  ptr +="</p>";
  ptr +="<p>Status: ";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";
   
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

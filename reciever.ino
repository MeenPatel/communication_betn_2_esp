#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "ssid";
const char* password = "password";

//Your Domain name with URL path or IP address with path
String serverName = "http://server_url;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(9600); 
const int DHTPin = 2;
pinMode(DHTPin, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}
String extractValue(String html, const String& key) {
  int startIndex = html.indexOf(key);
  if (startIndex != -1) {
    startIndex += key.length(); // Move past the key
    int endIndex = html.indexOf("</p>", startIndex);
    if (endIndex != -1) {
      String value = html.substring(startIndex, endIndex);
      value.trim(); // Trim the value in place
      return value; // Return the trimmed value
    }
  }
  return ""; // Return empty string if not found
}
void loop() {
  // Send an HTTP POST request depending on timerDelay
  
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
  
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
        
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        //Serial.println(payload);
        delay(1000);
        String rollNo = extractValue(payload, "Roll no.: ");
        String status = extractValue(payload, "Status: ");
        int roll,sts;
        roll=rollNo.toInt();
        sts=status.toInt();
        Serial.println(roll);
        Serial.println(sts);
        const int DHTPin = 2;
        if(sts==1){digitalWrite(DHTPin,HIGH);}
        else{digitalWrite(DHTPin,LOW);}
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  
}

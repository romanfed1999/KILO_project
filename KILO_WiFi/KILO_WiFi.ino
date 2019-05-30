#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

void setup() {
 
  Serial.begin(115200);                            //Serial connection only for testing
  WiFi.begin("PROTECTED", "PROTECTED");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    StaticJsonDocument<300> JSONencoder;   //Declaring static JSON buffer
 
    JSONencoder["name"] = "ESP";
    JSONencoder["price"] = 10;
    JSONencoder["isAvaiable"] = true;
    char JSONmessageBuffer[300];
    //JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    serializeJsonPretty(JSONencoder, JSONmessageBuffer);
    Serial.println(JSONmessageBuffer);
    
    HTTPClient http;    //Declare object of class HTTPClient
    String thumbprint="PROTECTED";
    http.begin("PROTECTED", thumbprint);      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
 
  } else {
    Serial.println("Error in WiFi connection");
  }
 
  delay(30000);  //Send a request every 30 seconds
 
}

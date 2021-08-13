#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

#define FIREBASE_HOST "iotify-in.firebaseio.com"
#define FIREBASE_AUTH "n6feAXzxnp1ndrMoRalmjZWZZOUuutZvUXlCXLYh"

const char* ssid = "my-fi";
const char* password = "mumap0702";

IRsend irsend(kIrLed);
FirebaseData firebaseData;

void setup(){
  irsend.begin();  
//  Serial.begin(115200);
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  WiFi.begin(ssid, password);
  delay(500);
  Serial.println();
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting...");
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() 
{
  if (WiFi.status() == WL_CONNECTED) 
  {
    Firebase.getString(firebaseData,"Harshit/" + WiFi.macAddress() + "/Command");
    Serial.print("Command: ");
    Serial.println(firebaseData.stringData());
    if(firebaseData.stringData() == "0xE0E0 0xE01F"){
      irsend.sendSAMSUNG(0xE0E0E01F, 32, 0);
      Serial.println("Command Executed ");
    }
    else if(firebaseData.stringData() == "0xE0E0 0xD02F"){
      irsend.sendSAMSUNG(0xE0E0D02F, 32, 0);
      Serial.println("Command Executed ");
    }
    Firebase.setString(firebaseData,"Harshit/" + WiFi.macAddress() + "/Command", " ");
    
  }
  delay(1000);
}

/*
  Rui Santos
  Complete project details at our blog.
    - ESP32: https://RandomNerdTutorials.com/esp32-firebase-realtime-database/
    - ESP8266: https://RandomNerdTutorials.com/esp8266-nodemcu-firebase-realtime-database/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  Based in the RTDB Basic Example by Firebase-ESP-Client library by mobizt
  https://github.com/mobizt/Firebase-ESP-Client/blob/main/examples/RTDB/Basic/Basic.ino
*/

// Insert your network credentials
#define WIFI_SSID "ICST"
#define WIFI_PASSWORD "arduino123"

#include "C:\Project iot\SmartLendPegBoard\hw\db.hpp"


db _DB;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void setup(){
  _DB.connectToWifi("ICST", "arduino123");
}

void loop(){
    if (Firebase.ready()&& (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    if(WiFi.status() == WL_CONNECTED && Firebase.ready()){
      String documentPath = "House/Room_1";

      FirebaseJson content;

      content.set("fields/temperature/doubleValue", String(3).c_str());
      content.set("fields/humidity/doubleValue", String(2).c_str());

      if(Firebase.Firestore.patchDocument(&_DB.fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw(), "temperature,humidity")){
        Serial.printf("ok\n%s\n\n", _DB.fbdo.payload().c_str());
        return;
      }else{
        Serial.println(_DB.fbdo.errorReason());
      }

      if(Firebase.Firestore.createDocument(&_DB.fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw())){
        Serial.printf("ok\n%s\n\n", _DB.fbdo.payload().c_str());
        return;
      }else{
        Serial.println(_DB.fbdo.errorReason());
      }
    }
  }
}

#include "Firebase_Arduino_WiFiNINA.h"
#include "TESTsecret.h"
#include "TESTweight.h"

FirebaseData firebaseData;


char FIREBASE_HOST[] =  SECRET_FIREBASE_API;
char FIREBASE_AUTH[] =  SECRET_FIREBASE_AUTH;
char WIFI_SSID[] = SECRET_SSID;
char WIFI_PASSWORD[] = SECRET_WIFI_PASS;


void firebaseSetup(){
    Serial.print("Connecting to Wi-Fi");
        int status = WL_IDLE_STATUS;
    while (status != WL_CONNECTED) {
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        Serial.print(".");
        delay(300);
}
    Serial.println();
    Serial.print("Connected IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
 
    //Firebase autentimine
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
    Firebase.reconnectWiFi(true);
}

void updateWeight(float value) {
  float unit = 0;
  unit = Firebase.getInt(firebaseData, "_CONFIG/WEIGHT");
  Serial.println(value);
  Serial.println(value);
  if (unit != value) {
    Firebase.setInt(firebaseData, "_CONFIG/WEIGHT", value);
    Serial.println("Firebase Data");
  }
}

void testInt(){
    int val = 0;

      if (Firebase.getInt(firebaseData, "/_CONFIG/testInt")) {
    if (firebaseData.dataType() == "int") {
      val = firebaseData.intData();
      Serial.println(val);
    }
    delay(2000);
    
  }
}
int  *testString(){
      String t = "ON";
      String val = "";
      if (Firebase.getString(firebaseData, "/_CONFIG/testString")) {
        if (firebaseData.dataType() == "string") {
            val = firebaseData.stringData();
            long number = strtoll( &val[1], NULL, 16);

// Split them up into r, g, b values
long r = number >> 16;
long g = number >> 8 & 0xFF;
long b = number & 0xFF;
              /*
              if (val == "ON"){
                Firebase.setString(firebaseData, "/_CONFIG/testString", "OFF");
                Serial.println("Taring!");
}
              }
              */
            Serial.println(val);
    }
    delay(2000);
      }
}

void  tareScale(){
      String val = "";
      if (Firebase.getString(firebaseData, "/_CONFIG/testString")) {
        if (firebaseData.dataType() == "string") {
            val = firebaseData.stringData();
              if (val == "ON"){
                Firebase.setString(firebaseData, "/_CONFIG/testString", "OFF");
                Serial.println("Taring!");
}
              }
            Serial.println(val);
    }
    delay(2000);
      }


void testFloat(String data){
     float val = 0;
           if (Firebase.getFloat(firebaseData, "/_CONFIG/" + data)) {
    if (firebaseData.dataType() == "float") {
      val = firebaseData.floatData();
      Serial.println(val);
    }
    delay(2000);
      }
      
    }
    

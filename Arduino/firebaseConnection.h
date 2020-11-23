#include <ArduinoJson.h>
#include "Firebase_Arduino_WiFiNINA.h"
#include "secret.h"
#include "weight.h"

FirebaseData firebaseData;

char FIREBASE_HOST[] =  SECRET_FIREBASE_API;
char FIREBASE_AUTH[] =  SECRET_FIREBASE_AUTH;
char WIFI_SSID[] = SECRET_SSID;
char WIFI_PASSWORD[] = SECRET_WIFI_PASS;
String loc =  "/users/user/";

void firebaseSetup() {
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

String getUser(){
    String val;
    if (Firebase.getString(firebaseData, "/users/user/name")) {
    if (firebaseData.dataType() == "string") {
      val = firebaseData.stringData();
      return val;
        }
    }
}

void updateMaxWeight(float value) {
  float unit = 0;
  Firebase.setInt(firebaseData, "/users/user/maxweight", value);
  }
int getMaxWeight(){
    int n;
    if (Firebase.getInt(firebaseData, "/users/user/maxweight")) {
    if (firebaseData.dataType() == "int") {
      n = firebaseData.intData();
      return n;
        }
    }
}

int fetchInt(String loc) {
  int val = 0;
  if (Firebase.getInt(firebaseData, loc)) {
    if (firebaseData.dataType() == "int") {
      val = firebaseData.intData();
      return val;
    }
    delay(2000);
  }
}


void updateDateServer(String timer) {
  String loc = "/users/user/drinktotal/";
  String n = "NOTFOUND";
  QueryFilter query;
  query.clearQuery();
  query.limitToLast(1);
  if (Firebase.getJSON(firebaseData, loc, query)){

   String hasCity = (firebaseData.jsonData());
   if(hasCity.indexOf(timer) > 0)
   {
   Serial.println("Record Found");
   n = "RECORDFOUND";
   }
   if(n == "NOTFOUND"){
    Firebase.setString(firebaseData, loc + timer, "0" );
    Firebase.setInt(firebaseData, loc + timer, 0 );
    Firebase.setInt(firebaseData, "/users/user/drinkToday/", 0);
   }
  }
  }

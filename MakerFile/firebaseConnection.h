#include "Firebase_Arduino_WiFiNINA.h"
#include "secret.h"


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

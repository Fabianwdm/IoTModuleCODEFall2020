#include <NTPClient.h>
#include <WiFiUdp.h>


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String formattedDate;
String dayStamp;
String timeStamp;

//Acquires todays date on BOOT.
String TodaysDate(){
  timeClient.begin();
  timeClient.setTimeOffset(3600);
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  // Formats date : "2018-05-28"
  formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  timeClient.end();
  return(dayStamp);
}

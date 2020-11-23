  /*
    LEDval = Firebase.getInt(firebaseData, "_CONFIG/LED_STATUS");
    LEDval = firebaseData.intData();
  
  if(LEDval==1){
    digitalWrite(led1, HIGH);
    ColorMe(100,100,100);
  } else {
    digitalWrite(led1, LOW);
    ColorMe(0,0,0); }

  buttonNew = digitalRead(btn);
  
  if (buttonOld == 0 && buttonNew == 1) {
    if (btnState == 0) {
      btnState = 1;
      Firebase.setInt(firebaseData, "_CONFIG/LED_STATUS", 1);
    } else {
      btnState = 0;
      Firebase.setInt(firebaseData, "_CONFIG/LED_STATUS", 0);
    }
  }
  buttonOld = buttonNew;
  delay(100);
    
  int val = 0;

  if (Firebase.getInt(firebaseData, "_CONFIG/RED")) {
    //Success, then read the payload value
    //Make sure payload value returned from server is integer
    //This prevent you to get garbage data
    if (firebaseData.dataType() == "int") {
      val = firebaseData.intData();
      Serial.println(val); }
  } else {
    //Failed, then print out the error detail
    Serial.println(firebaseData.errorReason());
  }
   delay(1000);
   */
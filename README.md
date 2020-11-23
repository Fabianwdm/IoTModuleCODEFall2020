# IoTModuleCODEFall2020

The purpose of the coaster is to remind the user regularly to drink water by the use of visual light queues. Time and colour preferences can be customized via the web application. 
This project consists of an IoT coaster utilizing an Arduino MKR WiFi 1010 connected to a Grove shield. This in turn is connected to a firebase back-end and front-end. 

**Table of contents**

  - Hardware Requirements
  - Software Requirements
  
***
# Getting Started

**Hardware Requirements (Alternative parts may also apply):**
  - [IOTERRIFIC BUNDLE](https://store.arduino.cc/ioterrific-bundle?fbclid=IwAR3G3JZHI-c6BE_1SgtgXigrpdd4MEiYuUHgQKTsQENQeaK0O0bggGSnpeQ) ( Includes: Adruino MKR WiFi 1010, MKR MEM Shield, MKR Connector Carrier)
  - [Grove - RGB LED Ring (24-WS2813 Mini)](https://www.seeedstudio.com/Grove-RGB-LED-Ring-24-WS2813-Mini-p-4202.html?fbclid=IwAR2OOEO14tSomyQLIjXJU87P1vXfC45io5JNkmHZaqHRMI7zc15hnYPQ4zM)
  - [Grove - Button( P )](https://www.seeedstudio.com/Grove-Button-P.html?fbclid=IwAR3-3Fa21KhUW9APLRXKSOsewg5UNex6-yvkGVzSH6lJga66L1Zj7p9oX6E)
  - [Grove - ADC for Load Cell (HX711)](https://www.seeedstudio.com/Grove-ADC-for-Load-Cell-HX711-p-4361.html?fbclid=IwAR0FQ_E9Q3cQT43ACMMcyP8FBR5F_lrGnOjVAX-Jq4CSGQoFotQ4YVL8Yho)
  - [TeOhk HX711 AD Electronic Scale Module Kit Digital Weight Sensor Converter Breakout Module](https://www.amazon.de/gp/product/B07SQQ4VW5/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1&fbclid=IwAR2aaRFHEXSlEzH3PQKFm9GJmS28iWMqFsXLDmTVpSEW7Dloo7_CC9naiwg)

**Software Requirements:**
1. Create a local repository and clone this repository.
```sh
$ git clone https://github.com/Fabianwdm/IoTModuleCODEFall2020.git
```
2. Create a Virtual Environment in the repository folder running Python = 3.7 or higher and activate VENV.
```sh
$ python3 -m pip3 install --user virtualenv
$ python3 -m venv env
$ source env/bin/activate
```

3. Install the requirements.txt file located in the folder with the following command. Notice that requirements.txt might depreciate over time.
```sh
$ pip3 install -r requirements.txt 
```
4. Set up a Firebase Project and insert the following fields in a .json file. Replace NAME with user's name.

{
  "user" : {
    "drinkToday" : 1,
    "drinktotal" : {
      "2020-11-22" : 0,
      "2020-11-23" : 1
    },
    "hexempty" : "#00c7fc",
    "hexfull" : "#00c7fc",
    "hexreminder" : "#00c7fc",
    "maxweight" : 653,
    "name" : "Professor X",
    "remindertime" : 10
  }
}
5. Acquire the Firebase Access Keys located in Project Overview/Settings/General. Scroll down and copy paste the keys that apply to the Arduino "firebaseconnection.h" file and in the WebApp/server.py file.

6. Run the following commands and go to  http://127.0.0.1:5000/ .

```sh
$ ~/IoTModuleCODEFall2020/Website/
$ Python3 server.py
```
7. Fill in the user information on the web application and save changes.
8. Plug in the Arduino.

DONE, any further updates will be done via the web application.

***
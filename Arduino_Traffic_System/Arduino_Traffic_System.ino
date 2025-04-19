//Required WiFiNINA Library for Arduino from https://github.com/arduino-libraries/WiFiNINA

#include "Firebase_Arduino_WiFiNINA.h"
#include "secrets.h"

#define RED_LED 6
#define GREEN_LED 7
#define BLUE_LED 8

String getPathLED_RED = "/LED_RED";
String getPathLED_GREEN = "/LED_GREEN";
String getPathLED_BLUE = "/LED_BLUE";

//Define Firebase data object
FirebaseData fbdo;

void setup()
{
  Serial.begin(115200);
  delay(100);
  Serial.println();

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  Serial.print("Connecting to Wi-Fi");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //Provide the autntication data
  Firebase.begin(DATABASE_URL, DATABASE_SECRET, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
 
}

void loop()
{
  if(Firebase.getString(fbdo, getPathLED_RED))
  {
    Serial.println("RED_LED : " + fbdo.stringData());
    if (fbdo.stringData() == "on")
    {
      digitalWrite(RED_LED, HIGH);
    }

    else if(fbdo.stringData() == "off")
    {
      digitalWrite(RED_LED, LOW);
    }
  }

  if(Firebase.getString(fbdo, getPathLED_GREEN))
  {
    Serial.println("GREEN_LED : " + fbdo.stringData());
    if (fbdo.stringData() == "on")
    {
      digitalWrite(GREEN_LED, HIGH);
    }
    
    else if(fbdo.stringData() == "off")
    {
      digitalWrite(GREEN_LED, LOW);
    }
  }

  if(Firebase.getString(fbdo, getPathLED_BLUE))
  {
    Serial.println("BLUE_LED : " + fbdo.stringData());
    if (fbdo.stringData() == "on")
    {
      digitalWrite(BLUE_LED, HIGH);
    }

    
    else if(fbdo.stringData() == "off")
    {
      digitalWrite(BLUE_LED, LOW);
    }
  }

}

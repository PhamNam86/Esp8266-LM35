#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
const int LM35 = A0;
//----------- Enter you Wi-Fi Details---------//
char ssid[] = "HVN"; //SSID
char pass[] = "hvn12345"; // Password
//-------------------------------------------//

WiFiClient  client;

unsigned long myChannelNumber = 1705533; // Channel ID here
const int FieldNumber = 1;
const char * myWriteAPIKey = "Q2TOTE3FEWHBWTZW"; // Your Write API Key here

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}
void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  int ADC;
  float temp;
  ADC = analogRead(LM35);  /* Read Temperature */
  //temp = (ADC * 3); /* Convert adc value to equivalent voltage */
  //temp = (temp / 10); /* LM35 gives output of 10mv/°C */
  temp = (5.0 * ADC * 1000.0)/(1024*10);
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(" *C");
  delay(1000);
  ThingSpeak.writeField(myChannelNumber, FieldNumber, temp, myWriteAPIKey);
  delay(1000);
}

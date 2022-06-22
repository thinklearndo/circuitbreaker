#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP UDP;

int current_stations = 0;

bool station_connected = true;
int last_connected_time = 0;

int MAX_STATIONS = 8;
int CONNECTION_LOST_DELAY_MS = 1000;
unsigned long lost_connection_time_ms = 0;
unsigned long received_packet_time_ms = 0;


 
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  //Start the serial communication channel
  Serial.begin(115200);
  Serial.println();
   
  //Setting the AP Mode with SSID, Password, and Max Connection Limit
  bool result = false;
  result = WiFi.softAP("circuitfind", "circuitpw", 1, false, MAX_STATIONS);

  if (result == true)
  {
    Serial.print("Access Point is Creadted! ip address = ");
    Serial.println(WiFi.softAPIP());
  }
  else
  {
    Serial.println("Unable to Create Access Point");
  }

  UDP.begin(8777);

  Serial.println("setup done!");
}
 
void loop()
{
  //Continuously check how many stations are connected to Soft AP and notify whenever a new station is connected or disconnected


 Serial.println("looping!");

  int packetSize = UDP.parsePacket();
  if (packetSize) {
   received_packet_time_ms = millis();
   station_connected = true;
   digitalWrite(LED_BUILTIN, LOW);
   delay(100);
  }

  if (station_connected == false) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }

  if (station_connected == true && millis() - received_packet_time_ms > CONNECTION_LOST_DELAY_MS) {
    // turn off led
    digitalWrite(LED_BUILTIN, HIGH);
    station_connected = false;
    lost_connection_time_ms = millis();
    delay(10000);
  }
   
}

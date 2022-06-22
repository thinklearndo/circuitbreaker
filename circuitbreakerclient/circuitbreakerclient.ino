#include <ESP8266WiFi.h> 
#include <WiFiUdp.h>

WiFiUDP UDP;

IPAddress broadcastIp(255,255,255,255);

unsigned long led_blink_time_ms = 0;

bool led_on = true;
 
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  //Start the serial communication channel
  Serial.begin(115200);
  Serial.println();

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin("circuitfind", "circuitpw");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}
 
void loop()
{
UDP.beginPacket(broadcastIp, 8777);
 UDP.write("Hello");
 UDP.endPacket();
 delay(100);

 if (millis() - led_blink_time_ms > 500) {
  led_blink_time_ms = millis();
  if (led_on == true) {
    led_on = false;
    digitalWrite(LED_BUILTIN, LOW);
  }
  else {
    led_on = true;
    digitalWrite(LED_BUILTIN, HIGH);
  }
  
 }
   
}

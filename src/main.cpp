#define USE_ETHERNET          true

#include <WiFi.h>
#include <WebServer.h>

#include <SPI.h>
#include <EthernetWebServer.h>

const char* ssid     = "your_ssid";
const char* password = "your_password";

// Enter a MAC address and IP address for your controller below.

byte mac[] =
{
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Select the IP address according to your local network
IPAddress ip(192, 168, 2, 100);

EthernetWebServer ethernetServer(80);
WebServer wifiServer(80);

const int led = 13;

void handleEthernetRoot() 
{
  ethernetServer.send(200, "text/plain", "Hello from ESP32 Ethernet!");
}

void handleWiFiRoot() 
{
  wifiServer.send(200, "text/plain", "Hello from ESP32 WiFi!");
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nStarting WiFi_Ethernet_Complex_ESP32 on " + String(ARDUINO_BOARD));

  //////////////////////////////////////////////

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // start the ethernet connection and the server:
  //Ethernet.begin(mac, ip);
  Ethernet.begin(mac);

  ethernetServer.on("/", handleEthernetRoot);

  ethernetServer.begin();

  Serial.print(F("HTTP EthernetWebServer is @ IP : "));
  Serial.println(Ethernet.localIP());

  //////////////////////////////////

  wifiServer.on("/", handleWiFiRoot);
  
  wifiServer.begin();     

  Serial.print(F("HTTP WiFiWebServer is @ IP : "));
  Serial.println(WiFi.localIP());
}

void loop() 
{
  // listen for incoming clients
  ethernetServer.handleClient();
  
  wifiServer.handleClient();
}
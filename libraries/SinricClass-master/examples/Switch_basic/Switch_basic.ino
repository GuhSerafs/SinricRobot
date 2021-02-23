#include <ESP8266WiFi.h>

#include <Sinric.h>
#include <SinricSwitch.h>

// To Do: Put in your credentials

const char* ssid = "WIFI-SSID";
const char* pass = "WIFI-PASSWORD";

const char* api_key = "1aaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee";
const char* switchId = "500000000000000000000000";

// callback for switch...
void onPowerState(const String& deviceId, bool state) { 
  Serial.printf("Switch turned %s \r\n", state?"on":"off");
}


// WiFi setup
void setupWifi() {
  Serial.begin(115200); 
  delay(1000);
  Serial.printf("\r\nConnecting WiFi (%s)", ssid);

  WiFi.persistent(false);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("connected!\r\n");

  IPAddress localIP = WiFi.localIP();
  Serial.printf("IP address: %d.%d.%d.%d\r\n", localIP[0], localIP[1], localIP[2], localIP[3]);
}

// Sinric setup
void setupSinric() {
  Serial.print("Connecting Sinric");
  Sinric.begin(api_key);
  while (!Sinric.isConnected()) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("connected!");

  // add new Switch 
  SinricSwitch& mySwitch = Sinric.add<SinricSwitch>(switchId);
  // set the callback
  mySwitch.onPowerState(onPowerState);
}

void setup() {
  delay(1000);
  Serial.begin(115200); Serial.println();
  setupWifi();
  setupSinric();
}

void loop() {
  Sinric.handle();
}


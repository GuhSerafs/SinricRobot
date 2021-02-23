# SinricClass

An "easy to use" class for connecting your esp-module to io.sinric.com and make your projects alexa compatible.
- Big thank's to [kakopappa](https://github.com/kakopappa/sinric) for developing sinric and hosting of [sinric.com](https://sinric.com)!

## usage
#### include Sinric-Library (Sinric.h) and Sinric-Device-Libraries (eg. SinricSwitch.h, SinricLight.h ...) an define credentials

```
...
#include <Sinric.h>
#include <SinrichSwitch.h>
...
const char* api_key = "your-api-key"
const char* deviceId = "your-device-id"
...
```
#### define callback routine(s)
```
void onPowerState(const string& deviceId, bool state) {
  Serial.printf("device %s turned %s\r\n, deviceId.c_str(), state?"on":"off");
}
```
#### In setup()
```
  ...
  Sinric.begin(api_key);
  // add a switch
  SinricSwitch& mySwitch = Sinric.add<SinricSwitch>(deviceId);
  // set callback function
  mySwitch.onPowerState(onPowerState);
  ...
```
  
#### In loop()
```
  ...
  Sinric.handle();
  ...
```
### Implemented devices and their callbacks
- Switch (```SinricSwitch``` in SinricSwitch.h)
  - Callbacks:
  ```
  onPowerState(const String& deviceId, bool state)
  ```

- Light (```SinricLight``` in SinricLight.h)
  - Callbacks:
  ```
  onPowerState(const String& deviceId, bool state)
  onSetBrightness(const String& deviceId, int brightness)
  onAdjustBrightness(const String& deviceId, int brightness)
  onSetColor(const String& deviceId, double hue, double sat, double value)
  onDecColorTemperature(const String& deviceId)
  onIncColorTemperature(const String& deviceId)
  onSetColorTemperature(const String& deviceId, int colorTemperature)
  ```

- Thermostat (```SinricThermostat``` in SinricThermostat.h)
  - Callbacks:
  ```
  onPowerState(const String& deviceIde, bool state)
  onSetTargetTemperature(const String& deviceId, double temperature, const String& scale)
  onAdjustTargetTemperature(const String& deviceId, double temperature, const String& scale)
  onSetThermostatMode(const String& deviceId, const String& mode)
  ```

## Simple add new or not yet implemented devices
- Make a new class derrivered from ```SinricDevice``` (defined in SinricDevice.h)
- Override constructor for propper callback init
- Define prototype functions for needed callbacks
- Provide callback setter function
- Override handle() to handle incomming commands and call the right callbacks

- Use the new device like the pre-defined 
```
myNewSinricDevice& newDevice = Sinric.add<myNewSinricDevice>(deviceId);
newDevice.CallbackSetFunction(callback-function);
```

## Dependencies / Needed libraries
- WebSocketsClient -> https://github.com/Links2004/arduinoWebSockets/releases
- ArduinoJson -> https://arduinojson.org/


<!--stackedit_data:
eyJoaXN0b3J5IjpbOTE3OTIyOTQxXX0=
-->
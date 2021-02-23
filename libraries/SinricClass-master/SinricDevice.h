#ifndef sinricdevice_h_
#define sinricdevice_h_

#include <ArduinoJson.h>

class SinricDevice {
  public:
    SinricDevice(const char* newDeviceId);
    SinricDevice(const String& newDeviceId);
    virtual ~SinricDevice();
    virtual void handle(const String& action, JsonObject& json) {};
    const char* getDeviceId();
  protected:
    char* deviceId;
};

SinricDevice::SinricDevice(const char* newDeviceId) {
  deviceId = strdup(newDeviceId);
}

SinricDevice::SinricDevice(const String& newDeviceId) {
  SinricDevice(newDeviceId.c_str());
}


SinricDevice::~SinricDevice() {
  if (deviceId) free(deviceId);
}


const char* SinricDevice::getDeviceId() {
  return deviceId;
};


#endif

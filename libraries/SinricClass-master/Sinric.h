#ifndef sinric_h
#define sinric_h

#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <vector>

#include "SinricDevice.h"

class SinricClass {
  public:
    SinricClass();
    ~SinricClass();
    void begin(const char* api_key, unsigned long heartBeatInterval = 300);
    void begin(const String& api_key, unsigned long heartBeatInterval = 300);
    void handle();
    void stop();
    bool isConnected();

    template <typename DeviceType>
    DeviceType& add(const char* deviceId);
    template <typename DeviceType>
    DeviceType& add(const String& deviceId);

  private:
    bool _is_connected = false;
    unsigned long _lastHeartBeat;
    unsigned long _heartBeatInterval;

    WebSocketsClient client;
    std::vector<SinricDevice*> devices;

    void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
};

SinricClass::SinricClass() :
  _is_connected(false),
  _lastHeartBeat(0) {
};

SinricClass::~SinricClass() {
  stop();

  for (auto& device : devices) {
    delete device;
    device = nullptr;
  }
  devices.clear();
}

void SinricClass::begin(const char* api_key, unsigned long heartBeatInterval) {
  if (_is_connected) {
    stop();
  }
  _heartBeatInterval = heartBeatInterval;

  client.begin("iot.sinric.com", 80, "/");
  client.onEvent([&](WStype_t type, uint8_t * payload, size_t length) { webSocketEvent(type, payload, length); });
  client.setAuthorization("apikey", api_key);
  client.setReconnectInterval(5000);

  _lastHeartBeat = millis();
}

void SinricClass::begin(const String& api_key, unsigned long heartBeatInterval) {
  begin(api_key.c_str(), heartBeatInterval);
}

void SinricClass::handle() {
  client.loop();

  if (_is_connected) {
    unsigned long actualMillis = millis();
    if (actualMillis - _lastHeartBeat > (_heartBeatInterval * 1000)) {
      _lastHeartBeat = actualMillis;
      client.sendTXT("H");
    }
  }
}

void SinricClass::stop() {
  if (_is_connected) {
    client.disconnect();
    _is_connected = false;
  }
}

bool SinricClass::isConnected() {
  handle();
  return _is_connected;
};

void SinricClass::webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      _is_connected = false;
      break;
    case WStype_CONNECTED:
      _is_connected = true;
      break;
    case WStype_TEXT: {
      DynamicJsonBuffer jsonBuffer;
      JsonObject& json = jsonBuffer.parseObject((char*)payload);

      const char* deviceId = json["deviceId"];
      String action = json["action"];

      for (auto& device : devices) {
        if (strcmp(deviceId, device->getDeviceId()) == 0) {
          device->handle(action, json);
        }
      }
      break;
    }
    default: break;
  }
}

template <typename DeviceType>
DeviceType& SinricClass::add(const char* deviceId) {
  DeviceType* newDevice = new DeviceType(deviceId);
  devices.push_back(newDevice);
  return *newDevice;
}

template <typename DeviceType>
DeviceType& SinricClass::add(const String& deviceId) {
  return add<DeviceType>(deviceId.c_str());
}

#ifndef SINRIC_NOINSTANCE
SinricClass Sinric;
#endif

#endif

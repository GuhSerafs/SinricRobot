#ifndef sinriclight_h_
#define sinriclight_h_

#include <ArduinoJson.h>
#include "SinricDevice.h"

class SinricLight : public SinricDevice {
  public:

	SinricLight(const char* deviceId);

	typedef std::function<void(const String&, bool)>                   PowerStateCallback;
	typedef std::function<void(const String&, int)>                    SetBrightnessCallback;
	typedef std::function<void(const String&, int)>                    AdjustBrightnessCallback;
	typedef std::function<void(const String&, double, double, double)> SetColorCallback;
	typedef std::function<void(const String&)>                         DecColorTemperatureCallback;
	typedef std::function<void(const String&)>                         IncColorTemperatureCallback;
	typedef std::function<void(const String&, int)>                    SetColorTemperatureCallback;
	
	void onPowerState(PowerStateCallback callback)                   { powerState = callback; }
    void onSetBrightness(SetBrightnessCallback callback)             { setBrightness = callback; }
    void onAdjustBrightness(AdjustBrightnessCallback callback)       { adjustBrightness = callback; }
    void onSetColor(SetColorCallback callback)                       { setColor = callback; }
    void onDecColorTemperature(DecColorTemperatureCallback callback) { decColorTemperature = callback; }
    void onIncColorTemperature(IncColorTemperatureCallback callback) { incColorTemperature = callback; }
    void onSetColorTemperature(SetColorTemperatureCallback callback) { setColorTemperature = callback; }

    void handle(const String& action, JsonObject& json) override;
  private:
    PowerStateCallback          powerState;
    SetBrightnessCallback       setBrightness;
    AdjustBrightnessCallback    adjustBrightness;
    SetColorCallback            setColor;
    DecColorTemperatureCallback decColorTemperature;
    IncColorTemperatureCallback incColorTemperature;
    SetColorTemperatureCallback setColorTemperature;
};

SinricLight::SinricLight(const char* deviceId) : 
  SinricDevice(deviceId), 
  powerState(nullptr),
  setBrightness(nullptr),
  adjustBrightness(nullptr),
  setColor(nullptr),
  decColorTemperature(nullptr),
  incColorTemperature(nullptr),
  setColorTemperature(nullptr) {
};


void SinricLight::handle(const String& action, JsonObject& json) {
  // setPowerState
  if ((action == "setPowerState") && (powerState)) {
    bool state = (strcmp("ON", json["value"]) == 0);
    powerState(deviceId, state);

    // setColor
  } else if ((action == "SetColor") && (setColor)) {
    double hue = json["value"]["hue"];
    double sat = json["value"]["saturation"];
    double bri = json["value"]["brightness"];
    setColor(deviceId, hue, sat, bri);
    
    // setBrightness
  } else if ((action == "SetBrightness") && (setBrightness)) {
    int brightness = json["value"];
    setBrightness(deviceId, brightness);
    
    // AdjustBrightness
  } else if ((action == "AdjustBrightness") && (adjustBrightness)) {
    int brightness_adj = json["value"];
    adjustBrightness(deviceId, brightness_adj);
    
    // DecreaseColorTemperature
  } else if ((action == "DecreaseColorTemperature") && (decColorTemperature)) {
    decColorTemperature(deviceId);
    
    // IncreaseColorTemperature
  } else if ((action == "IncreaseColorTemperature") && (incColorTemperature)) {
    incColorTemperature(deviceId);
    
    // SetColorTemperature
  } else if ((action == "SetColorTemperature") && (setColorTemperature)) {
    int colorTemp = json["value"];
    setColorTemperature(deviceId, colorTemp);
  }
}

#endif

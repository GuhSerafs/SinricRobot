#ifndef sinricthermostat_h_
#define sinricthermostat_h_

#include <ArduinoJson.h>
#include "SinricDevice.h"


class SinricThermostat : public SinricDevice {
  public:
	typedef std::function<void(const String&, bool)>                  PowerStateCallback;
	typedef std::function<void(const String&, double, const String&)> SetTargetTemperatureCallback;
	typedef std::function<void(const String&, double, const String&)> AdjustTargetTemperatureCallback;
	typedef std::function<void(const String&, const String&)>         SetThermostatModeCallback;

	SinricThermostat(const char* deviceId);
                                          
    void onPowerState(PowerStateCallback callback)                           { powerState = callback; }
    void onSetTargetTemperature(SetTargetTemperatureCallback callback)       { setTargetTemperature = callback; }
    void onAdjustTargetTemperature(AdjustTargetTemperatureCallback callback) { adjustTargetTemperature = callback; }
    void onSetThermostatMode(SetThermostatModeCallback callback)             { setThermostatMode = callback; }
    
    void handle(const String& action, JsonObject& json) override;
  private:
    PowerStateCallback              powerState;
    SetTargetTemperatureCallback    setTargetTemperature;
    AdjustTargetTemperatureCallback adjustTargetTemperature;
    SetThermostatModeCallback       setThermostatMode;
};

SinricThermostat::SinricThermostat(const char* deviceId ) : 
  SinricDevice(deviceId), 
  powerState(nullptr),
  setTargetTemperature(nullptr),
  adjustTargetTemperature(nullptr),
  setThermostatMode(nullptr) {
}


void SinricThermostat::handle(const String& action, JsonObject& json) {
  // powerState
  if ((action == "setPowerState") && (powerState)) {
    bool state = (json["value"] == "ON");
    powerState(deviceId, state);
  } else if ((action == "SetTargetTemperature") && (setTargetTemperature)) {
    double temp = json["value"]["targetSetpoint"]["value"];
    String scale = json["value"]["targetSetoint"]["scale"];
    setTargetTemperature(deviceId, temp, scale); 
  } else if ((action == "AdjustTargetTemperature") && (adjustTargetTemperature)) {
    double temp = json["value"]["targetSetpointDelta"]["value"];
    String scale = json["value"]["targetSetpointDelta"]["scale"];
    adjustTargetTemperature(deviceId, temp, scale); 
  } else if ((action == "SetThermostatMode") && (setThermostatMode)) {
    String mode = json["value"]["themostatMode"]["value"];
    setThermostatMode(deviceId, mode);
  }
}

#endif

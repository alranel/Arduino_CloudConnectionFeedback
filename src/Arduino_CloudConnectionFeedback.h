#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#ifdef ARDUINO_UNOR4_WIFI
#include "Arduino_LED_Matrix.h"
#endif

#ifdef ARDUINO_UNOR4_WIFI
void waitForArduinoCloudConnection(ArduinoLEDMatrix &_matrix) {
#else
void waitForArduinoCloudConnection() {
#endif

  // Display an animation to tell the user we're connecting to network
  Serial.println("CONNECTION STATUS: connecting to WiFi");

#ifdef ARDUINO_UNOR4_WIFI
  _matrix.loadSequence(LEDMATRIX_ANIMATION_WIFI_SEARCH);
  _matrix.play(true);
#endif
  
  auto started = millis();
  while (ArduinoCloud.getConnection()->check() != NetworkConnectionState::CONNECTED) {
    ArduinoCloud.update();
    if ((millis() - started) > 2000) {
      // Display an animation to tell the user that network connection failed
      Serial.println("CONNECTION STATUS: WiFi connection failed (check coverage, network credentials and WiFi band)");

#ifdef ARDUINO_UNOR4_WIFI
      _matrix.play(false);
      _matrix.loadFrame(LEDMATRIX_EMOJI_SAD);
      delay(2000);
      _matrix.loadSequence(LEDMATRIX_ANIMATION_WIFI_SEARCH);
      _matrix.play(true);
#endif

      started = millis();
    }
  }

  // Display an animation to tell the user we're connectig to the cloud
  Serial.println("CONNECTION STATUS: connecting to Arduino Cloud");

#ifdef ARDUINO_UNOR4_WIFI
  _matrix.loadSequence(LEDMATRIX_ANIMATION_CLOUD);
  _matrix.play(true);
#endif

  started = millis();
  while (ArduinoCloud.connected() == 0) {
    ArduinoCloud.update();
    if ((millis() - started) > 5000) {
      // Display an animation to tell the user that cloud connection failed (but keep trying)
      Serial.println("STATUS: connection to Arduino Cloud failed (check your Internet connection or repeat device provisioning in Arduino Cloud)");

#ifdef ARDUINO_UNOR4_WIFI
      _matrix.play(false);
      _matrix.loadFrame(LEDMATRIX_EMOJI_SAD);
      delay(2000);
      _matrix.loadSequence(LEDMATRIX_ANIMATION_CLOUD);
      _matrix.play(true);
#endif

      started = millis();
    }
  }

  const uint32_t fullOff[] = {
    0x00000000,
    0x00000000,
    0x00000000
  };
  _matrix.loadFrame(fullOff);
}

#include "arduino_secrets.h"
#include "thingProperties.h"
#include "Arduino_CloudConnectionFeedback.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  // Connect to Arduino IoT Cloud
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  // This line will block until we're connected to Arduino Cloud
  // using the LED matrix to provide feedback
  waitForArduinoCloudConnection();
  
  Serial.println("Program started!");
}

void loop() {
  ArduinoCloud.update();

}

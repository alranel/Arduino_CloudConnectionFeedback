#include "arduino_secrets.h"
#include "thingProperties.h"
#include "Arduino_CloudConnectionFeedback.h"

#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;

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

  // Use the LED matrix to do something else
  matrix.begin();
  matrix.loadSequence(LEDMATRIX_ANIMATION_TETRIS_INTRO);
  matrix.play(false);
}

void loop() {
  ArduinoCloud.update();

}

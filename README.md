<img src="https://content.arduino.cc/website/Arduino_logo_teal.svg" height="100" align="right" />

# Arduino_CloudConnectionFeedback

![License](https://img.shields.io/github/license/alranel/Arduino_CloudConnectionFeedback)

This library implements a simple connection helper for projects based on [Arduino Cloud](https://cloud.arduino.cc/). It adds the following behavior to your project:

* program execution is blocked until WiFi **and** Arduino Cloud are successfully connected;
* clear feedback about connection failures is printed to serial monitor;
* if using an UNO R4 WiFi, the LED matrix will be used to provide visual feedback about connection status and failures.

## How to use it

Adding this helper to your existing project is very easy. You just need to add two lines:

```
#include "thingProperties.h"
#include "Arduino_CloudConnectionFeedback.h" // <-- add this line

void setup() {
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  waitForArduinoCloudConnection(); // <-- add this line
  
  Serial.println("Program started!");
}

void loop() {
  ArduinoCloud.update();

}
```


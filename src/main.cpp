#include "Arduino.h"
#include "WiFi.h"
#include <OSCMessage.h>

WiFiUDP Udp; // A UDP instance to let us send and receive packets over UDP
int LED_BUILTIN = 2;

// Options
int update_rate = 16;

// Network settings
char ssid[] = "wifiname"; // your network SSID (name)
char pass[] = "wifipass";  // your network password
unsigned int localPort = 8888; // local port to listen for OSC packets

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  /* setup wifi */
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Udp.begin(localPort);
}

void ledtoggle(OSCMessage &msg) {
  switch (msg.getInt(0)) {
  case 0:
    digitalWrite(LED_BUILTIN, LOW);
    break;
  case 1:
    digitalWrite(LED_BUILTIN, HIGH);
    break;
  }
}

void receiveMessage() {
  OSCMessage inmsg;
  int size = Udp.parsePacket();

  if (size > 0) {
    while (size--) {
      inmsg.fill(Udp.read());
    }
    if (!inmsg.hasError()) {
      inmsg.dispatch("/led", ledtoggle);
    } 
    //else { auto error = inmsg.getError(); }
  }
}

void loop() {
  receiveMessage();
  delay(update_rate);
}

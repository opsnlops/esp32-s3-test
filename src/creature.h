#pragma once

#define CREATURE_NAME "esp32-test"
#define CREATURE_POWER "mains"
#define CREATURE_TOPIC "creatures/esp32-test"


// Toss some things into the global namespace so that the libs can read it
const char* gCreatureName = CREATURE_NAME;

// Is the WiFi connected?
boolean gWifiConnected = false;

#include <Arduino.h>
#include <Wire.h>

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
}

#include "creature.h"

#include "logging/logging.h"
#include "network/connection.h"
#include "creatures/creatures.h"
#include "mqtt/mqtt.h"
#include "time/time.h"
#include "mdns/creature-mdns.h"
#include "mdns/magicbroker.h"
#include "home/data-feed.h"

using namespace creatures;

// Keep a link to our logger
static Logger l;
static MQTT mqtt = MQTT(String(CREATURE_NAME));

void setup()
{

  // Fire up the logging framework first
  l.init();

  pinMode(LED_BUILTIN, OUTPUT);

  NetworkConnection network = NetworkConnection();
  network.connectToWiFi();

  // Register ourselves in mDNS
  CreatureMDNS creatureMDNS = CreatureMDNS(CREATURE_NAME, CREATURE_POWER);
  creatureMDNS.registerService(666);
  creatureMDNS.addStandardTags();

  // Set the time
  Time time = Time();
  time.init();
  time.obtainTime();

  // Get the location of the magic broker
  MagicBroker magicBroker;
  magicBroker.find();

  // Connect to MQTT
  l.info("Starting MQTT");
  mqtt.connect(magicBroker.ipAddress, magicBroker.port);
  mqtt.subscribe(String("cmd"), 0);

  // Enable OTA
  // setup_ota(String(CREATURE_NAME));
  // start_ota();

  // Tell MQTT we're alive
  mqtt.publish(String("status"), String("I'm alive!!"), 0, false);
  mqtt.startHeartbeat();
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}
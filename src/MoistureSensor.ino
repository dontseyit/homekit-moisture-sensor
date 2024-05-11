#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"
//include the Arduino library for your real sensor here, e.g. <DHT.h>

#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__);
int MSensor = A0;

void setup()
{
  Serial.begin(115200);
  wifi_connect(); // in wifi_info.h
  my_homekit_setup();
  pinMode(MSensor, INPUT);
}

void loop()
{
  my_homekit_loop();
  delay(10);
}

//==============================
// Homekit setup and loop
//==============================

// access your homekit characteristics defined in my_accessory.c
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_current_humidity;

static uint32_t next_heap_millis = 0;
static uint32_t next_report_millis = 0;

void my_homekit_setup()
{
  arduino_homekit_setup(&config);
}

void my_homekit_loop()
{
  arduino_homekit_loop();
  const uint32_t t = millis();
  if (t > next_report_millis)
  {
    // report sensor values every 30 seconds
    next_report_millis = t + 30 * 1000;
    my_homekit_report();
  }
  if (t > next_heap_millis)
  {
    // show heap info every 10 seconds
    next_heap_millis = t + 10 * 1000;
    LOG_D("Free heap: %d, HomeKit clients: %d",
        ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
  }
}

void my_homekit_report()
{
  int sensor_read = analogRead(MSensor);
  LOG_D("Sensor read: %d", sensor_read);  
  float humidity_value = sensor_read;
  humidity_value = humidity_value / 1024;
  humidity_value = humidity_value * 100;
  humidity_value = 100 - humidity_value;
  cha_current_humidity.value.float_value = humidity_value;
  LOG_D("Current humidity: %.1f", humidity_value);
  homekit_characteristic_notify(&cha_current_humidity, cha_current_humidity.value);
}
